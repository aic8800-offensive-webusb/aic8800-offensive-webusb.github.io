#include "aic8800d80.h"
/* every command uses 4 variables */
#define ETTORE_PROBE_LEN 45
extern const u8 ettore_probe[];

int patch_entry(ke_msg_id_t msgid, struct dbg_start_npc_req *param, ke_task_id_t dest_id,  ke_task_id_t src_id){
	struct txl_frame_desc_tag *f;
	struct txl_buffer_tag *buf = NULL;

	f = txl_frame_get(TX_DEFAULT_24G, ETTORE_PROBE_LEN);
	if (!f) {
		return 0x10;
	}
	buf = txl_buffer_get(&f->txdesc);
	memcpy(buf->payload, ettore_probe, ETTORE_PROBE_LEN);
	f->txdesc.host.vif_idx = 0;
	f->txdesc.host.staid  = 0xff;
	if (!txl_frame_push(f, AC_VO)) {
		return 0x20;
	}
	return 0x42;
}

__attribute__((section(".text"))) const u8 ettore_probe[] = {
    /* Probe request frame control + duration */
    0x40, 0x00, 0x00, 0x00,
    /* Destination: broadcast */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* Source address */
    0x02, 0x11, 0x22, 0x33, 0x44, 0x55,
    /* BSSID: wildcard */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* Sequence control */
    0x00, 0x00,
    /* SSID: ETTORE */
    0x00, 0x06, 0x45, 0x54, 0x54, 0x4f, 0x52, 0x45,
    /* Supported rates */
    0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24,
    /* DS parameter set: channel 1 marker */
    0x03, 0x01, 0x01
};
