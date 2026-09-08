#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libtcc.h"

static char tcc_error_log[4096];

static void append_error(const char *text){
	int used = strlen(tcc_error_log);
	int room = sizeof(tcc_error_log) - used - 1;
	if (room == 0){
		return;
	}
	strncat(tcc_error_log, text, room);
	used = strlen(tcc_error_log);
	if (used + 1 < sizeof(tcc_error_log)){
		strcat(tcc_error_log, "\n");
	}
}

static void tcc_error_func(void *opaque, const char *msg){
	append_error(msg);
}

const char *compiler_log(void){
	return tcc_error_log;
}

uint8_t *compile_program(const char *options_json, const char *code){
	long length = 0;
	/* '.o' compiled filehandle */
	FILE *file = NULL;
	uint8_t *output = NULL;

	tcc_error_log[0] = '\0';
	remove("/patch.o");

	TCCState *state = tcc_new();
	if (!state) {
		append_error("tcc_new failed");
		return NULL;
	}

	tcc_set_error_func(state, NULL, tcc_error_func);
	tcc_set_lib_path(state, "/");
	tcc_add_include_path(state, "/include");
	tcc_add_include_path(state, "/");
	tcc_set_options(state, "-nostdinc -nostdlib -ffreestanding -Os");

	if (tcc_set_output_type(state, TCC_OUTPUT_OBJ) < 0) {
 		append_error("tcc_set_output_type(TCC_OUTPUT_OBJ) failed");
		tcc_delete(state);
		return NULL;
	}

	/* the most important function here, use 'tcc_compile_string' for compiling every string of code */
	if (tcc_compile_string(state, code ? code : "") < 0) {
		tcc_delete(state);
		return NULL;
	}

	if (tcc_output_file(state, "/patch.o") < 0) {
		append_error("tcc_output_file failed");
		tcc_delete(state);
		return NULL;
	}
	tcc_delete(state);

	file = fopen("/patch.o", "rb");
	if (!file) {
		append_error("cannot reopen /patch.o");
		return NULL;
	}
	if (fseek(file, 0, SEEK_END) != 0) {
		fclose(file);
		append_error("fseek failed");
		return NULL;
	}
	length = ftell(file);
	if (length <= 0) {
		fclose(file);
		append_error("empty object file");
		return NULL;
	}
	rewind(file);

	output = (uint8_t *)malloc(length + 4);
	if (output == NULL) {
		fclose(file);
		append_error("malloc failed");
		return NULL;
	}
	output[0] = (uint8_t)(length);
	output[1] = (uint8_t)(length >> 8);
	output[2] = (uint8_t)(length >> 16);
	output[3] = (uint8_t)(length >> 24);
	if (fread(output + 4, 1, length, file) != length) {
		fclose(file);
		free(output);
		append_error("fread failed");
		return NULL;
	}
	fclose(file);
	return output;
}
