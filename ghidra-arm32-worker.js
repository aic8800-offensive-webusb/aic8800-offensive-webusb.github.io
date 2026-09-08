"use strict";

let pyreLoaderImportError = null;
try {
	importScripts("assets/ghidra-arm32/pyre_decompiler-classic.js");
}catch (error) {
	pyreLoaderImportError = error;
}

const DEFAULT_MODULE_URL = "assets/ghidra-arm32/pyre_decompiler.js";
const DEFAULT_WASM_BASE_URL = "assets/ghidra-arm32/";
const DEFAULT_SPEC_BASE_URL = "assets/ghidra-arm32/specs/";
const DEFAULT_MANIFEST_URL = "assets/ghidra-arm32/specs/manifest.json";
const DEFAULT_ARCH = "ARM";
const DEFAULT_LANGUAGE_ID = "ARM:LE:32:v7:default";

let wasmModule = null;
let decompilerApi = null;
let cachedManifest = null;
const mountedArchs = new Set();

function hex32(value) {
	return (value >>> 0).toString(16).padStart(8, "0");
}

/* decodeBase64Bytes: decode the ghidra sla and specfile embedded in this page */
function decodeBase64Bytes(base64) {
	const clean = String(base64 || "").replace(/\s+/g, "");
	const binary = atob(clean);
	const bytes = new Uint8Array(binary.length);
	for (let index = 0; index < binary.length; index += 1) {
		bytes[index] = binary.charCodeAt(index);
	}
	return bytes;
}

function bindApi(mod) {
	return {
		init: mod.cwrap("pyre_init", "number", ["string"]),
		addSpecDir: mod.cwrap("pyre_add_spec_dir", "number", ["string"]),
		create: mod.cwrap("pyre_create", "number", ["string"]),
		addRegion: mod.cwrap("pyre_add_region", "number", ["number", "bigint", "number", "number"]),
		addSymbol: mod.cwrap("pyre_add_symbol", "number", ["number", "bigint", "string"]),
		decompile: mod.cwrap("pyre_decompile", "number", ["number", "bigint", "string"]),
		freeString: mod.cwrap("pyre_free_string", null, ["number"]),
		destroy: mod.cwrap("pyre_destroy", null, ["number"]),
	};
}

async function instantiateDecompiler(options) {
	if (wasmModule && decompilerApi) {
		return;
	}
	const moduleUrl = options.moduleUrl || DEFAULT_MODULE_URL;
	let factory = typeof PyreDecompiler === "function" ? PyreDecompiler : null;
	if (!factory && pyreLoaderImportError) {
		const detail = pyreLoaderImportError && pyreLoaderImportError.message ? pyreLoaderImportError.message : String(pyreLoaderImportError);
		throw new Error("Ghidra decompiler loader import failed: " + detail);
	}
	if (!factory) {
		let imported;
		try {
			imported = await import(moduleUrl);
		}catch (error) {
			throw new Error("Ghidra decompiler loader not found at " + moduleUrl);
		}
		factory = imported.default || imported.PyreDecompiler;
	}
	if (typeof factory !== "function") {
		throw new Error("Ghidra decompiler loader does not export an Emscripten factory");
	}

	const wasmBaseUrl = options.wasmBaseUrl || DEFAULT_WASM_BASE_URL;
	const factoryOptions = {
		locateFile(path) {
			return wasmBaseUrl + path;
		},
	};
	if (options.wasmBase64) {
		const wasmBytes = decodeBase64Bytes(options.wasmBase64);
		factoryOptions.instantiateWasm = (imports, receiveInstance) => {
			const module = new WebAssembly.Module(wasmBytes);
			const instance = new WebAssembly.Instance(module, imports);
			receiveInstance(instance);
			return instance.exports;
		};
	}
	wasmModule = await factory(factoryOptions);
	decompilerApi = bindApi(wasmModule);
	try{
		wasmModule.FS.mkdir("/spec");
	}catch (error) {
		/* do nothing */
	}
}

function mountLazyFile(fs, relPath, url) {
	const parts = relPath.split("/");
	let current = "/spec";
	for (let index = 0; index < parts.length - 1; index += 1) {
		current += "/" + parts[index];
		try {
			fs.mkdir(current);
		}catch (error){
			/* do nothing */
		}
	}
	fs.createLazyFile(current, parts[parts.length - 1], url, true, false);
}

function prepareSpecBytes(relPath, bytes, options) {
	if (relPath === "ARM/data/languages/ARMt.pspec" && (!options || options.thumb !== false)) {
		const decoder = new TextDecoder();
		const encoder = new TextEncoder();
		const text = decoder.decode(bytes).replace("<set name=\"TMode\" val=\"0\"", "<set name=\"TMode\" val=\"1\"");
		return encoder.encode(text);
	}
	return bytes;
}

function mountDataFile(fs, relPath, bytes) {
	const parts = relPath.split("/");
	let current = "/spec";
	for (let index = 0; index < parts.length - 1; index += 1) {
		current += "/" + parts[index];
		try {
			fs.mkdir(current);
		}catch (error){

		}
	}
	const createDataFile = fs.createDataFile || (wasmModule && wasmModule.FS_createDataFile);
	if (typeof createDataFile !== "function") {
		throw new Error("Ghidra FS_createDataFile is unavailable");
	}
	createDataFile(current, parts[parts.length - 1], bytes, true, false, true);
}

function getEmbeddedSpecFiles(options) {
	return options && options.specFiles && typeof options.specFiles === "object" ? options.specFiles : null;
}

async function mountSpecs(options) {
	const arch = options.arch || DEFAULT_ARCH;
	if (mountedArchs.has(arch)) {
		return;
	}
	const embeddedSpecs = getEmbeddedSpecFiles(options);
	let manifest = null;
	if (embeddedSpecs) {
		manifest = {
			files: Object.keys(embeddedSpecs).map((path) => ({ path, size: 0 })),
		};
	}else if (!cachedManifest){
		const manifestUrl = options.manifestUrl || DEFAULT_MANIFEST_URL;
		let response;
		try {
			response = await fetch(manifestUrl);
		}catch (error){
			throw new Error("Ghidra ARM SLEIGH manifest cannot be fetched at " + manifestUrl + "; stage ARM specs and serve the page over http:// instead of file://");
		}
		if (!response.ok) {
			throw new Error("Ghidra ARM SLEIGH manifest not found at " + manifestUrl);
		}
		cachedManifest = await response.json();
	}
	if (!manifest) {
		manifest = cachedManifest;
	}

	const specBaseUrl = options.specBaseUrl || DEFAULT_SPEC_BASE_URL;
	const archPrefix = arch + "/";
	const langDirs = new Set();
	for (const entry of manifest.files || []) {
		if (!entry.path || !entry.path.startsWith(archPrefix)) {
			continue;
		}
		if (embeddedSpecs && Object.prototype.hasOwnProperty.call(embeddedSpecs, entry.path)) {
			mountDataFile(wasmModule.FS, entry.path, prepareSpecBytes(entry.path, decodeBase64Bytes(embeddedSpecs[entry.path]), options));
		}else{
			mountLazyFile(wasmModule.FS, entry.path, specBaseUrl + entry.path);
		}
		const parts = entry.path.split("/");
		if (parts[parts.length - 2] === "languages") {
			langDirs.add("/spec/" + parts.slice(0, -1).join("/"));
		}
	}
	if (langDirs.size === 0) {
		throw new Error("Ghidra ARM SLEIGH specs are not staged");
	}
	for (const dir of langDirs) {
		if (decompilerApi.addSpecDir(dir) !== 0) {
			throw new Error("Ghidra add_spec_dir failed for " + dir);
		}
	}
	mountedArchs.add(arch);
}

async function initDecompiler(options) {
	await instantiateDecompiler(options);
	await mountSpecs(options);
}

function uniqueLanguageIds(request) {
	const out = [];
	const add = (value) => {
		const id = String(value || "").trim();
		if (id && !out.includes(id)) {
			out.push(id);
		}
	};
	if (Array.isArray(request.languageIds)) {
		request.languageIds.forEach(add);
	}
	add(request.languageId);
	add(DEFAULT_LANGUAGE_ID);
	return out;
}

function normalizeRegionBytes(region) {
	const source = region && region.bytes;
	if (source instanceof Uint8Array) {
		return source;
	}
	if (source instanceof ArrayBuffer) {
		return new Uint8Array(source);
	}
	if (ArrayBuffer.isView(source)) {
		return new Uint8Array(source.buffer, source.byteOffset, source.byteLength);
	}
	if (source && typeof source.byteLength === "number") {
		return new Uint8Array(source);
	}
	return new Uint8Array(source || []);
}

function describeRegionSource(region) {
	const source = region && region.bytes;
	if (!source) {
		return "missing";
	}
	const type = Object.prototype.toString.call(source);
	const byteLength = typeof source.byteLength === "number" ? source.byteLength : "n/a";
	const length = typeof source.length === "number" ? source.length : "n/a";
	return type + " byteLength=" + byteLength + " length=" + length;
}

function collectRegions(request, addressNumber) {
	const out = [];
	const addRegion = (region, fallbackAddress) => {
	const bytes = normalizeRegionBytes(region);
	if (!bytes.length) {
		return;
	}
	out.push({
		address: region && region.address !== undefined ? (region.address >>> 0) : fallbackAddress,
		bytes,
	});
	};

	if (Array.isArray(request.regions)) {
		for (const region of request.regions) {
			addRegion(region, addressNumber);
		}
	}else{
		const fallbackAddress = request.regionAddress === undefined ? addressNumber : (request.regionAddress >>> 0);
		addRegion({ address: fallbackAddress, bytes: request.bytes }, fallbackAddress);
	}
	if (!out.length) {
		const details = [];
		if (Array.isArray(request.regions)) {
			for (let index = 0; index < request.regions.length; index += 1) {
				details.push("region" + index + "=" + describeRegionSource(request.regions[index]));
			}
 		}
 		details.push("bytes=" + describeRegionSource({ bytes: request.bytes }));
 		throw new Error("empty firmware memory block (" + details.join(", ") + ")");
	}
	return out;
}

function decompileWithLanguage(languageId, address, regions, name) {
	const handle = decompilerApi.create(languageId);
	if (!handle) {
		throw new Error("Ghidra decompiler create failed for " + languageId);
	}
	const ptrs = [];
	try {
		for (const region of regions) {
			const ptr = wasmModule._malloc(region.bytes.length);
			if (!ptr) {
				throw new Error("Ghidra region allocation failed");
			}
			ptrs.push(ptr);
			wasmModule.HEAPU8.set(region.bytes, ptr);
			if (decompilerApi.addRegion(handle, BigInt(region.address >>> 0), ptr, region.bytes.length) !== 0) {
				throw new Error("Ghidra add_region failed at 0x" + hex32(region.address));
			}
		}
		decompilerApi.addSymbol(handle, address, name);
		const cstr = decompilerApi.decompile(handle, address, name);
		if (!cstr) {
			throw new Error("Ghidra decompile returned null");
		}
		const code = wasmModule.UTF8ToString(cstr);
		decompilerApi.freeString(cstr);
		return { code, languageId };
	}finally{
		for (const ptr of ptrs) {
			wasmModule._free(ptr);
		}
		decompilerApi.destroy(handle);
	}
}

function decompileRegion(request) {
	const addressNumber = request.address >>> 0;
	const address = BigInt(addressNumber);
	const name = request.name || ("FUN_" + hex32(addressNumber));
	const regions = collectRegions(request, addressNumber);
	const errors = [];

	for (const languageId of uniqueLanguageIds(request)) {
		try {
			return decompileWithLanguage(languageId, address, regions, name);
		}catch (error){
			errors.push(languageId + ": " + (error && error.message ? error.message : String(error)));
		}
	}
	throw new Error(errors.length ? errors.join("; ") : "Ghidra decompilation failed");
}

self.onmessage = async (event) => {
	const id = event.data && event.data.id;
	try {
		if (!event.data || event.data.type !== "decompile") {
			throw new Error("unknown worker command");
		}
		await initDecompiler(event.data);
		const result = decompileRegion(event.data);
		self.postMessage({ id, ok: true, result });
	}catch (error){
		self.postMessage({id, ok: false, error: error && error.message ? error.message : String(error), });
	}
};
