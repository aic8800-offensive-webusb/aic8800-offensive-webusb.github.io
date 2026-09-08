/* made by Edoardo Mantovani, 2026, webusb driver for the low cost Wi-Fi + Bluetooth dongle aic8800 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

/* content of 'errno-base.h' */
#define	EPERM		 1	/* Operation not permitted */
#define	ENOENT		 2	/* No such file or directory */
#define	ESRCH		 3	/* No such process */
#define	EINTR		 4	/* Interrupted system call */
#define	EIO		 5	/* I/O error */
#define	ENXIO		 6	/* No such device or address */
#define	E2BIG		 7	/* Argument list too long */
#define	ENOEXEC		 8	/* Exec format error */
#define	EBADF		 9	/* Bad file number */
#define	ECHILD		10	/* No child processes */
#define	EAGAIN		11	/* Try again */
#define	ENOMEM		12	/* Out of memory */
#define	EACCES		13	/* Permission denied */
#define	EFAULT		14	/* Bad address */
#define	ENOTBLK		15	/* Block device required */
#define	EBUSY		16	/* Device or resource busy */
#define	EEXIST		17	/* File exists */
#define	EXDEV		18	/* Cross-device link */
#define	ENODEV		19	/* No such device */
#define	ENOTDIR		20	/* Not a directory */
#define	EISDIR		21	/* Is a directory */
#define	EINVAL		22	/* Invalid argument */
#define	ENFILE		23	/* File table overflow */
#define	EMFILE		24	/* Too many open files */
#define	ENOTTY		25	/* Not a typewriter */
#define	ETXTBSY		26	/* Text file busy */
#define	EFBIG		27	/* File too large */
#define	ENOSPC		28	/* No space left on device */
#define	ESPIPE		29	/* Illegal seek */
#define	EROFS		30	/* Read-only file system */
#define	EMLINK		31	/* Too many links */
#define	EPIPE		32	/* Broken pipe */
#define	EDOM		33	/* Math argument out of domain of func */
#define	ERANGE		34	/* Math result not representable */

/* C baseed defines/macro for the WebUSB driver */
#define RX_HWHRD_LEN 	60
#define RX_ALIGNMENT 	4
#define ETH_ALEN 	6
#define TXDESC_API_SIZE 28
#define MAC_ADDR_LEN ETH_ALEN
#define MAC_SSID_LEN 	32
#define TX_AC_BE 	1
#define USB_TYPE_DATA_TX 0x01
#define USB_TYPE_CFG 	0x10
#define USB_TYPE_CFG_CMD_RSP 0x11
#define USB_TYPE_CFG_PRINT 0x13
#define USB_TYPE_CFG_DATA_CFM 0x12
#define ETH_P_IP_HOST 0x0008
#define IFACE_INVALID 	0xff
#define PHY_CHNL_BW_20 	0
#define PHY_CHNL_BW_40 	1
#define PHY_CHNL_BW_80 	2
#define PHY_CHNL_BW_160 3
#define PHY_CHNL_BW_80P80 4
#define ETH_P_PAE 	0x888e
#define ETH_P_IP 	0x0800
#define ETH_P_ARP 	0x0806
#define ETH_P_PAE_HOST 	0x8e88
#define ETH_P_WAPI_HOST 0xb488
#define RWNX_RX_HD_DECR_WEP 	1
#define RWNX_RX_HD_DECR_TKIP 	2
#define RWNX_RX_HD_DECR_CCMP128 3
#define RWNX_RX_HD_DECR_WAPI 	7
#define AIC8800_RX_HWVECT_STATUS_OFFSET 36
#define AIC8800_RX_FLAGS_OFFSET 48
#define DHCP_DISCOVER 	1
#define DHCP_OFFER 	2
#define DHCP_REQUEST 	3
#define DHCP_ACK 	5
#define AIC_DHCP_META_SIZE 	16
#define AIC_DHCP_SERVER_IP	0xc0a84d01
#define AIC_DHCP_CLIENT_IP 	0xc0a84d0a
#define AIC_DHCP_SUBNET_MASK 	0xffffff00
#define AIC_DHCP_LEASE_SECONDS	3600
#define NL80211_BAND_2GHZ 	0
#define NL80211_BAND_5GHZ 	1
#define MAC_CHAN_DEF_SIZE 	6
#define MAC_CHAN_OP_SIZE 	10
#define SCAN_CHANNEL_MAX 	42
#define SCAN_SSID_MAX 		3
#define SCAN_REQ_SIZE		376
#define MAC_DOMAINCHANNEL_24G_MAX 14
#define MAC_DOMAINCHANNEL_5G_MAX  28
#define MAC_CIPHER_CCMP 2
#define WPA2_CCMP_KEY_LEN 16
#define MM_KEY_ADD_REQ_SIZE 44
#define MM_START_REQ_SIZE 72
#define RF_CALIB_REQ_SIZE 24
#define AIC_MAX_BLOCK_WRITE 1024
#define MAC_SEC_KEY_LEN 32
#define PHY_CFG_BUF_SIZE 16
#define PCAP_LINKTYPE_IEEE802_11 105
#define PCAP_SNAPLEN 65535
#define MAC_RATESET_LEN 12
#define MESH_MESHID_MAX_LEN 32
#define MESH_START_REQ_SIZE 76
#define MONITOR_CONFIG_REQ_SIZE 14
#define MONITOR_CFM_META_SIZE 12
#define APM_SET_BCN_IE_REQ_SIZE 516
#define APM_START_REQ_SIZE 52
#define APM_START_CFM_META_SIZE 4
#define ME_STA_ADD_CFM_META_SIZE 4
#define AIC8800_AP_BEACON_META_SIZE 16
#define AIC8800_MONITOR_RX_FILTER 0x7fffffde
#define SM_CONNECT_REQ_SIZE 320
#define CONTROL_PORT_HOST   (1 << 0)
#define CONTROL_PORT_NO_ENC (1 << 1)
#define WPA_WPA2_IN_USE     (1 << 3)
#define WLAN_AUTH_OPEN 			0
#define STA_DATA_META_SIZE 		28
#define SCAN_RESULT_META_SIZE 		48
#define RX_AGGR_META_SIZE 		20
#define LMAC_RESPONSE_META_SIZE 	16
#define CONNECT_IND_META_SIZE 		12
#define MEM_RW_META_SIZE 		8
#define AIC_MAX_DECOMP_SIZE 		0x400
#define AIC_FW_IMAGE_FMAC_U01 		1
#define AIC_FW_IMAGE_FMAC_D80_U02 	2
#define AIC_FW_PATCH_VERSION_SPLIT	0x06090100
#define AIC_PATCH_MAGIC_NATIVE 		0x48435450
#define AIC_PATCH_MAGIC2_NATIVE 	0x50544348
#define AIC_PATCH_START_DEFAULT 	0x001d7000
#define AIC_PATCH_OFF_MAGIC_NATIVE 	0
#define AIC_PATCH_OFF_PAIR_START_NATIVE 4
#define AIC_PATCH_OFF_MAGIC2_NATIVE 8
#define AIC_PATCH_OFF_PAIR_COUNT_NATIVE 12
/* Owfuzz configuration */
#define OWFUZZ_CFG_META_SIZE 64
#define OWFUZZ_CFG_FLAG_CAPTURE 1
#define OWFUZZ_CFG_FLAG_MONITOR 2
#define OWFUZZ_CFG_FLAG_MUTATE  4
#define OWFUZZ_CFG_FLAG_REWRITE 8
#define OWFUZZ_MUT_NOT_PRESENT  0
#define OWFUZZ_MUT_REPEATED	1
#define OWFUZZ_MUT_ALL_BITS_ZERO 2
#define OWFUZZ_MUT_MIN_SUB_1 3
#define OWFUZZ_MUT_MIN 4
#define OWFUZZ_MUT_MIN_ADD_1 5
#define OWFUZZ_MUT_RANDOM_VALUE 6
#define OWFUZZ_MUT_MAX_SUB_1 7
#define OWFUZZ_MUT_MAX 8
#define OWFUZZ_MUT_MAX_ADD_1 9
#define OWFUZZ_MUT_ALL_BITS_ONE 10
#define OWFUZZ_VALUE_ZERO 0
#define OWFUZZ_VALUE_RANDOM 1
#define OWFUZZ_VALUE_ONE  2
#define OWFUZZ_VALUE_SAME 3
#define AIC_OWFUZZ_TICK_IDLE 0
#define AIC_OWFUZZ_TICK_COMPLETE 1
#define AIC_OWFUZZ_TICK_BUSY 2
#define AIC_OWFUZZ_TICK_SEND 3
#define AIC_OWFUZZ_NEXT_NONE 0
#define AIC_OWFUZZ_NEXT_GENERATED 1
#define AIC_OWFUZZ_NEXT_CAPTURED  2
/* aic usb mode macro */
#define AIC_USB_MODE_UNKNOWN 0
#define AIC_USB_MODE_STORAGE 1
#define AIC_USB_MODE_ROM 2
#define AIC_USB_MODE_RAM 3
/* AIC8800 rx event macro */
#define AIC_RX_EVENT_NONE 0
#define AIC_RX_EVENT_CFG_CMD_RSP 1
#define AIC_RX_EVENT_CFG_PRINT 2
#define AIC_RX_EVENT_CFG_OTHER 3
#define AIC_RX_EVENT_MONITOR_DATA 4
#define AIC_RX_EVENT_STA_DATA 5
/* user shell codes */
#define AIC_SHELL_ACT_UNKNOWN 0
#define AIC_SHELL_ACT_CLEAR 1
#define AIC_SHELL_ACT_SCAN 2
#define AIC_SHELL_ACT_STATUS 3
#define AIC_SHELL_ACT_SAVE 4
#define AIC_SHELL_ACT_READ_MEM 5
#define AIC_SHELL_ACT_WRITE_MEM 6
#define AIC_SHELL_ACT_NETWORKS 7
#define AIC_SHELL_ACT_MESHP2P 8
#define AIC_SHELL_ACT_MESH 9
#define AIC_SHELL_ACT_P2P 10
#define AIC_SHELL_ACT_MONITOR 11
#define AIC_SHELL_ACT_FUZZ_STOP 12
#define AIC_SHELL_ACT_FUZZ_STATUS 13
#define AIC_SHELL_ACT_FUZZ_CLEAR 14
#define AIC_SHELL_ACT_FUZZ_LAUNCH 15
#define AIC_SHELL_ACT_FUZZ_INIT 16
#define AIC_SHELL_ACT_LAUNCH_STOP 17
#define AIC_SHELL_ACT_LAUNCH_STATUS 18
#define AIC_SHELL_ACT_LAUNCH_PAYLOAD 19
#define AIC_SHELL_ACT_LAUNCH_PROFILE 20
#define AIC_SHELL_ACT_PATCH_DECOMPILE 21
#define AIC_SHELL_ACT_PATCH_OPEN 22
#define AIC_SHELL_ACT_SEND_BOX 23
#define AIC_SHELL_ACT_SEND_MONITOR 24
#define AIC_SHELL_ACT_SEND_ETH 25
#define AIC_SHELL_ACT_CONNECT 26
#define AIC_SHELL_ACT_SET_MAC 27
#define AIC_SHELL_ACT_HELP 28
#define AIC_SHELL_ACT_DEAUTH 29
#define AIC_SHELL_ACT_START_AP 30
#define AIC_SHELL_ACT_STOP_AP 31
#define AIC_SHELL_ACT_STOP_MONITOR 32
#define AIC_SHELL_ACT_OBSERVER 33
#define AIC_SHELL_ACT_STOP_OBSERVER 34
#define AIC_SHELL_ACT_INJECT 35
#define AIC_SHELL_ACT_EDIT_CAPTIVE 36

#define AIC_WPA_M1_META_SIZE 32
#define AIC_WPA_M1_ANONCE_OFF 0
#define AIC_WPA_M1_SNONCE_OFF 32
#define AIC_WPA_M1_PMK_OFF 64
#define AIC_WPA_M1_PTK_OFF 96
#define AIC_WPA_M1_MSG2_OFF 160
#define AIC_WPA_M1_OUT_SIZE 281
#define AIC_WPA_AP_M3_META_SIZE 32
#define AIC_WPA_AP_M3_PTK_OFF 0
#define AIC_WPA_AP_M3_MSG3_OFF 64
#define AIC_WPA_AP_M3_OUT_SIZE 512

#define AIC_FW_STEP_READ_CHIP 1
#define AIC_FW_STEP_UPLOAD_FW 2
#define AIC_FW_STEP_PATCH_CONFIG 3
#define AIC_FW_STEP_START_APP 4
#define AIC_FW_STEP_REENUMERATE 5
#define AIC_FW_STEP_INIT_STACK 6
#define AIC_FW_STEP_DONE 7

#define AIC_LMAC_ROUTE_NONE 0
#define AIC_LMAC_ROUTE_SCAN_RESULT 1
#define AIC_LMAC_ROUTE_CONNECT_IND 2

#define AIC_TX_STATUS_OK 0
#define AIC_TX_STATUS_SHORT 1
#define AIC_TX_STATUS_NOT_ASSOC 2
#define AIC_TX_STATUS_NEED_MONITOR 3
#define AIC_TX_STATUS_DESC_FAIL 4
#define TXU_CNTRL_MGMT_NATIVE (1 << 3)
#define TXU_CNTRL_MGMT_ROBUST_NATIVE (1 << 7)
#define TX_STATUS_DESC_NEED_CFM 0x80000000u
#define STA_QOS_CAPA_NATIVE (1 << 0)

#define AIC_CONNECT_STATUS_OK 0
#define AIC_CONNECT_STATUS_MISSING_TARGET 1
#define AIC_CONNECT_STATUS_BAD_BSSID 2

/* kernel like types */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;

struct mac_addr {
	u16 array[MAC_ADDR_LEN / 2];
};

struct mac_ssid {
	u8 length;
	u8 array[MAC_SSID_LEN];
};

struct mac_chan_op {
	u8 band;
	u8 type;
	u16 prim20_freq;
	u16 center1_freq;
	u16 center2_freq;
	s8 tx_power;
	u8 flags;
};

struct mac_chan_def {
	u16 freq;
	u8 band;
	u8 flags;
	s8 tx_power;
};

struct mac_rateset {
	u8 length;
	u8 array[MAC_RATESET_LEN];
};

struct hostdesc {
	u16 packet_len;
	u16 flags_ext;
	u32 status_desc_addr;
	struct mac_addr eth_dest_addr;
	struct mac_addr eth_src_addr;
	u16 ethertype;
	u8 ac;
	u8 tid;
	u8 vif_idx;
	u8 staid;
	u16 flags;
};

struct txdesc_api {
	struct hostdesc host;
};

struct mac_sec_key {
	u8 length;
	u32 array[MAC_SEC_KEY_LEN / 4];
};

struct mm_key_add_req {
	u8 key_idx;
	u8 sta_idx;
	struct mac_sec_key key;
	u8 cipher_suite;
	u8 inst_nbr;
	u8 spp;
	bool pairwise;
};

struct phy_cfg_tag {
	u32 parameters[PHY_CFG_BUF_SIZE];
};

struct mm_start_req {
	struct phy_cfg_tag phy_cfg;
	u32 uapsd_timeout;
	u16 lp_clk_accuracy;
};

struct mm_add_if_req {
	u8 type;
	struct mac_addr addr;
	bool p2p;
};

struct me_config_monitor_req {
	struct mac_chan_op chan;
	bool chan_set;
	bool uf;
	bool auto_reply;
};

struct me_config_monitor_cfm {
	u8 chan_index;
	struct mac_chan_op chan;
};

struct mm_set_filter_req {
	u32 filter;
};

struct apm_set_bcn_ie_req {
	u8 vif_idx;
	u16 bcn_ie_len;
	u8 bcn_ie[512];
};

struct apm_start_req {
	struct mac_rateset basic_rates;
	struct mac_chan_def chan;
	u32 center_freq1;
	u32 center_freq2;
	u8 ch_width;
	u32 bcn_addr;
	u16 bcn_len;
	u16 tim_oft;
	u16 bcn_int;
	u32 flags;
	u16 ctrl_port_ethertype;
	u8 tim_len;
	u8 vif_idx;
};

struct apm_start_cfm {
	u8 status;
	u8 vif_idx;
	u8 ch_idx;
	u8 bcmc_idx;
};

struct apm_stop_req {
	u8 vif_idx;
};

struct me_chan_config_req {
	struct mac_chan_def chan2G4[MAC_DOMAINCHANNEL_24G_MAX];
	struct mac_chan_def chan5G[MAC_DOMAINCHANNEL_5G_MAX];
	u8 chan2G4_cnt;
	u8 chan5G_cnt;
};

struct me_set_control_port_req {
	u8 sta_idx;
	bool control_port_open;
};

struct mac_htcapability {
	u16 ht_capa_info;
	u8 a_mpdu_param;
	u8 mcs_rate[16];
	u16 ht_extended_capa;
	u32 tx_beamforming_capa;
	u8 asel_capa;
};

struct mac_vhtcapability {
	u32 vht_capa_info;
	u16 rx_mcs_map;
	u16 rx_highest;
	u16 tx_mcs_map;
	u16 tx_highest;
};

struct mac_he_mcs_nss_supp {
	u16 rx_mcs_80;
	u16 tx_mcs_80;
	u16 rx_mcs_160;
	u16 tx_mcs_160;
	u16 rx_mcs_80p80;
	u16 tx_mcs_80p80;
};

struct mac_hecapability {
	u8 mac_cap_info[6];
	u8 phy_cap_info[11];
	struct mac_he_mcs_nss_supp mcs_supp;
	u8 ppe_thres[25];
};

struct me_sta_add_req {
	struct mac_addr mac_addr;
	struct mac_rateset rate_set;
	struct mac_htcapability ht_cap;
	struct mac_vhtcapability vht_cap;
	struct mac_hecapability he_cap;
	u32 flags;
	u16 aid;
	u8 uapsd_queues;
	u8 max_sp_len;
	u8 opmode;
	u8 vif_idx;
	bool tdls_sta;
	bool tdls_sta_initiator;
	bool tdls_chsw_allowed;
};

struct me_sta_add_cfm {
	u8 sta_idx;
	u8 status;
	u8 pm_state;
	u8 aligned;
};

struct me_sta_del_req {
	u8 sta_idx;
	bool tdls_sta;
};

struct scanu_start_req {
	struct mac_chan_def chan[SCAN_CHANNEL_MAX];
	struct mac_ssid ssid[SCAN_SSID_MAX];
	struct mac_addr bssid;
	u32 add_ies;
	u16 add_ie_len;
	u8 vif_idx;
	u8 chan_cnt;
	u8 ssid_cnt;
	bool no_cck;
	u32 duration;
};

struct mesh_start_req {
	struct mac_rateset basic_rates;
	struct mac_chan_def chan;
	u32 center_freq1;
	u32 center_freq2;
	u8 ch_width;
	u8 dtim_period;
	u16 bcn_int;
	u8 vif_index;
	u8 mesh_id_len;
	u8 mesh_id[MESH_MESHID_MAX_LEN];
	u32 ie_addr;
	u8 ie_len;
	bool user_mpm;
	bool is_auth;
	u8 auth_id;
};

struct dbg_mem_block_write_req {
	u32 memaddr;
	u32 memsize;
	u32 memdata[AIC_MAX_BLOCK_WRITE / sizeof(u32)];
};

struct sm_connect_req {
	struct mac_ssid ssid;
	struct mac_addr bssid;
	struct mac_chan_def chan;
	u32 flags;
	u16 ctrl_port_ethertype;
	u16 ie_len;
	u16 listen_interval;
	bool dont_wait_bcmc;
	u8 auth_type;
	u8 uapsd_queues;
	u8 vif_idx;
	u32 ie_buf[64];
};

struct mm_set_stack_start_req {
	u8 is_stack_start;
	u8 efuse_valid;
	u8 set_vendor_info;
	u8 fwtrace_redir;
};

struct mm_set_rf_calib_req {
	u32 cal_cfg_24g;
	u32 cal_cfg_5g;
	u32 param_alpha;
	u32 bt_calib_en;
	u32 bt_calib_param;
	u8 xtal_cap;
	u8 xtal_cap_fine;
};

struct aic8800_usb_lmac_msg {
	u16 usb_len;
	u8 usb_type;
	u8 usb_reserved;
	u32 usb_padding;
	u16 id;
	u16 dest_id;
	u16 src_id;
	u16 param_len;
};

static const uint16_t channels_2ghz[] = {
	2412, 2417, 2422, 2427, 2432, 2437, 2442,
	2447, 2452, 2457, 2462, 2467, 2472, 2484,
};

static const uint16_t channels_5ghz[] = {
	5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320,
	5500, 5520, 5540, 5560, 5580, 5600, 5620, 5640,
	5660, 5680, 5700, 5720, 5745, 5765, 5785, 5805, 5825,
};

static const int aic8800_d80_patch_table_native[][2] = {
	{0x00b4, 0xf3010001},
	{0x0170, 0x0001000au},
};

/* contains the pair of "frame-name":"frame-type" */
struct owfuzz_name_type {
	const char *name;
	uint8_t type;
};

/* taken from the aic8800 source code:
 * txpwr power values hardcoded here and not in the .txt files under the firmware directory */
static const int8_t txpwr_11b_11ag_2g4[] = {18, 18, 18, 18, 18, 18, 18, 18, 16, 16, 15, 15};
static const int8_t txpwr_11n_11ac_2g4[] = {18, 18, 18, 18, 16, 16, 15, 15, 14, 14};
static const int8_t txpwr_11ax_2g4[] = {18, 18, 18, 18, 16, 16, 15, 15, 14, 14, 13, 13};
static const int8_t txpwr_11a_5g[] = {-128, -128, -128, -128, 18, 18, 18, 18, 16, 16, 15, 15};
static const int8_t txpwr_11n_11ac_5g[] = {18, 18, 18, 18, 16, 16, 15, 15, 14, 14};
static const int8_t txpwr_11ax_5g[] = {18, 18, 18, 18, 16, 16, 14, 14, 13, 13, 12, 12};
static const uint8_t mesh_rates[] = {0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24, 0x30, 0x48, 0x60, 0x6c};
static const uint8_t ap_wpa2_psk_rsn_ie[] = {
	0x30, 0x14, 0x01, 0x00, 0x00, 0x0f, 0xac, 0x04,
	0x01, 0x00, 0x00, 0x0f, 0xac, 0x04, 0x01, 0x00,
	0x00, 0x0f, 0xac, 0x02, 0x00, 0x00,
};
static const uint8_t ap_wmm_param_ie[] = {
	0xdd, 0x18, 0x00, 0x50, 0xf2, 0x02, 0x01, 0x01,
	0x00, 0x00, 0x03, 0xa4, 0x00, 0x00, 0x27, 0xa4,
	0x00, 0x00, 0x42, 0x43, 0x5e, 0x00, 0x62, 0x32,
	0x2f, 0x00,
};

static const uint8_t owfuzz_broadcast_mac[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static const uint8_t owfuzz_supported_rates[] = {0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24};
static const uint8_t owfuzz_extended_rates[] = {0x30, 0x48, 0x60, 0x6c};
static const uint8_t owfuzz_rsn_payload[] = {
    0x01, 0x00, 0x00, 0x0f, 0xac, 0x04, 0x01, 0x00,
    0x00, 0x0f, 0xac, 0x04, 0x01, 0x00, 0x00, 0x0f,
    0xac, 0x02, 0x00, 0x00,
};
/* Wi-Fi frame names and id */
static const struct owfuzz_name_type owfuzz_frame_names[] = {
	{"associationrequest", 0x00},
	{"associationreq", 0x00},
	{"assocrequest", 0x00},
	{"assocreq", 0x00},
	{"associationresponse", 0x10},
	{"associationresp", 0x10},
	{"assocresponse", 0x10},
	{"assocresp", 0x10},
	{"assocres", 0x10},
	{"reassociationrequest", 0x20},
	{"reassociationreq", 0x20},
	{"reassocrequest", 0x20},
	{"reassocreq", 0x20},
	{"reassociationresponse", 0x30},
	{"reassociationresp", 0x30},
	{"reassocresponse", 0x30},
	{"reassocresp", 0x30},
	{"reassocres", 0x30},
	{"proberq", 0x40},
	{"proberequest", 0x40},
	{"probereq", 0x40},
	{"proberesponse", 0x50},
	{"proberesp", 0x50},
	{"proberes", 0x50},
	{"timingadvertisement", 0x60},
	{"timingad", 0x60},
	{"timing", 0x60},
	{"beacon", 0x80},
	{"atim", 0x90},
	{"disassociation", 0xa0},
	{"disassoc", 0xa0},
	{"authentication", 0xb0},
	{"auth", 0xb0},
	{"deauthentication", 0xc0},
	{"deauth", 0xc0},
	{"action", 0xd0},
	{"actionnoack", 0xe0},
	{"beamformingreportpoll", 0x44},
	{"beamforming", 0x44},
	{"vhtndpannouncement", 0x54},
	{"vht", 0x54},
	{"controlframeextension", 0x64},
	{"ctrlfrmext", 0x64},
	{"controlwrapper", 0x74},
	{"ctrlwrap", 0x74},
	{"blockackrequest", 0x84},
	{"blockackreq", 0x84},
	{"blockack", 0x94},
	{"pspoll", 0xa4},
	{"rts", 0xb4},
	{"cts", 0xc4},
	{"ack", 0xd4},
	{"cfend", 0xe4},
	{"cfendcfack", 0xf4},
	{"cfendack", 0xf4},
	{"data", 0x08},
	{"datacfack", 0x18},
	{"datacfpoll", 0x28},
	{"datacfackpoll", 0x38},
	{"null", 0x48},
	{"nulldata", 0x48},
	{"cfack", 0x58},
	{"cfpoll", 0x68},
	{"cfackpoll", 0x78},
	{"qosdata", 0x88},
	{"qosdatacfack", 0x98},
	{"qosdatacfpoll", 0xa8},
	{"qosdatacfackpoll", 0xb8},
	{"qosnull", 0xc8},
	{"qoscfack", 0xd8},
	{"qoscfpoll", 0xe8},
	{"qoscfackpoll", 0xf8},
};

static const uint8_t owfuzz_profile_management[] = {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0};
static const uint8_t owfuzz_profile_sta[] = {0x00,0x20,0x40,0xb0,0xd0,0xe0,0x08,0x88,0x48,0xc8,0xb4,0x84,0xa4};
static const uint8_t owfuzz_profile_ap[] = {0x10,0x30,0x50,0x60,0x80,0x90,0xb0,0xd0,0xe0,0x08,0x88,0x48,0xc8,0xc4,0x94};
static const uint8_t owfuzz_profile_p2p[] = {0x80,0x40,0x50,0xb0,0x10,0xd0};
static const uint8_t owfuzz_profile_control[] = {0x44,0x54,0x64,0x74,0x84,0x94,0xa4,0xb4,0xc4,0xd4,0xe4,0xf4};
static const uint8_t owfuzz_profile_data[] = {0x08,0x18,0x28,0x38,0x48,0x58,0x68,0x78,0x88,0x98,0xa8,0xb8,0xc8,0xd8,0xe8,0xf8};
static const uint8_t owfuzz_profile_all[] = {
    0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0,
    0x44,0x54,0x64,0x74,0x84,0x94,0xa4,0xb4,0xc4,0xd4,0xe4,0xf4,
    0x08,0x18,0x28,0x38,0x48,0x58,0x68,0x78,0x88,0x98,0xa8,0xb8,0xc8,0xd8,0xe8,0xf8
};

#define OWFUZZ_ARRAY_COUNT(a) (int)((sizeof(a) / sizeof((a)[0])))

typedef struct {
	const uint8_t *ies;
	int ie_count;
	const uint8_t *ext_ies;
	int ext_ie_count;
} owfuzz_ie_target_set;

typedef struct {
	uint8_t id;
	uint8_t min_len;
	uint8_t max_len;
} owfuzz_ie_range_entry;

static const uint8_t owfuzz_ie_beacon[] = {
	0,1,3,4,6,5,7,32,37,40,41,35,42,50,48,11,12,46,51,63,64,67,68,66,71,70,54,58,60,59,
	45,61,72,74,127,86,89,69,107,108,111,112,114,113,119,120,174,123,118,181,186,187,158,191,
	192,195,196,193,198,199,201,202,255,255,237,240,239,241,255,255,255,255,244,221
};
static const uint8_t owfuzz_ie_probe_response[] = {
	0,1,3,4,6,5,7,32,37,40,41,35,42,50,48,11,12,46,51,63,64,67,68,66,71,70,54,58,60,59,
	45,61,72,74,127,86,89,69,107,108,111,112,114,113,119,120,174,123,118,181,186,187,158,191,
	192,195,196,193,198,199,201,202,255,255,237,240,239,241,255,255,255,255,244,221
};
static const uint8_t owfuzz_ie_probereq[] = {
	0,1,10,50,3,59,45,72,127,84,97,107,114,158,148,170,191,
	255,255,255,239,215,226,229,217,230,235,255,255,255,255,255,255,221
};
static const uint8_t owfuzz_ie_assocreq[] = {
	0,1,50,33,36,48,46,70,54,59,45,72,127,89,94,107,158,148,170,191,199,
	255,255,255,255,255,216,210,217,230,224,90,233,235,225,236,255,255,255,55,244,255,255,221
};
static const uint8_t owfuzz_ie_reassocreq[] = {
	0,1,50,33,36,48,46,70,54,59,45,72,127,89,94,107,158,148,170,191,199,
	255,255,255,255,255,216,210,217,230,224,90,233,235,225,236,255,255,255,55,244,255,255,221
};
static const uint8_t owfuzz_ie_assocres[] = {
	1,50,12,53,65,70,54,55,58,56,45,61,72,74,127,90,95,110,181,158,148,151,170,52,191,192,199,
	255,255,255,255,255,255,255,212,216,223,217,232,211,231,224,233,234,235,236,255,255,255,255,244,255,221
};
static const uint8_t owfuzz_ie_reassocres[] = {
	1,50,12,53,65,70,54,55,58,56,45,61,72,74,127,90,95,110,181,158,148,151,170,52,191,192,199,
	255,255,255,255,255,255,255,212,216,223,217,232,211,231,224,233,234,235,236,255,255,255,255,244,255,221
};
static const uint8_t owfuzz_ie_auth[] = {16,48,54,55,56,75,57,158,52,255,255,255,255,255,255,255,221};
static const uint8_t owfuzz_ie_action[] = {221,76,139};
static const uint8_t owfuzz_ie_timing[] = {7,32,69,127,221};
static const uint8_t owfuzz_ie_default[] = {221};

static const uint8_t owfuzz_ext_beacon[] = {11,14,52,53,15,16};
static const uint8_t owfuzz_ext_probe_response[] = {11,14,52,53,15,16};
static const uint8_t owfuzz_ext_probereq[] = {11,10,2,44,17,21,27,53,90};
static const uint8_t owfuzz_ext_assocreq[] = {4,12,3,5,6,17,27,34,90,88};
static const uint8_t owfuzz_ext_reassocreq[] = {4,12,3,5,6,17,27,34,90,88};
static const uint8_t owfuzz_ext_assocres[] = {14,4,12,3,5,6,7,17,27,28,34,88};
static const uint8_t owfuzz_ext_reassocres[] = {14,4,12,3,5,6,7,17,27,28,34,88};
static const uint8_t owfuzz_ext_auth[] = {13,4,8,1,33,92,93};

static const owfuzz_ie_range_entry owfuzz_ie_ranges2020[] = {
	{0,0,32},{1,1,8},{3,1,1},{4,6,6},{5,4,254},{6,2,2},{7,6,254},{10,0,254},
	{11,5,5},{12,18,18},{13,55,55},{14,0,255},{15,14,14},{16,1,253},{32,1,1},
	{33,2,2},{34,0,0},{35,2,2},{36,2,2},{37,3,3},{38,3,255},{39,3,255},
	{40,6,6},{41,9,253},{42,1,1},{43,4,4},{44,1,1},{45,26,26},{46,1,1},
	{48,34,254},{50,1,255},{51,1,255},{52,13,255},{53,1,1},{54,3,3},{55,82,255},
	{56,5,5},{57,4,4},{58,20,20},{59,2,253},{60,4,4},{61,22,22},{62,1,1},
	{63,1,1},{64,1,1},{65,1,1},{66,1,255},{67,2,26},{68,4,4},{69,1,16},
	{70,5,5},{71,1,255},{72,1,1},{73,1,255},{74,14,14},{75,1,255},{76,16,16},
	{78,3,255},{79,3,255},{80,4,255},{81,3,255},{82,0,255},{83,2,2},{84,0,255},
	{85,1,3},{86,1,255},{87,1,255},{88,16,255},{89,1,3},{90,3,3},{91,4,255},
	{92,4,254},{93,4,4},{94,1,1},{95,1,10},{96,21,21},{97,1,255},{98,1,255},
	{99,1,255},{100,1,255},{101,18,18},{102,18,18},{104,4,4},{105,3,3},
	{106,3,3},{107,3,11},{108,0,255},{109,1,1},{110,16,58},{111,0,255},
	{112,8,8},{113,7,7},{114,0,32},{115,1,255},{116,14,14},{117,3,23},
	{118,6,6},{119,2,2},{120,1,253},{121,6,6},{122,2,7},{123,2,255},
	{124,1,7},{125,15,15},{126,21,21},{127,1,10},{130,37,252},{131,31,37},
	{132,15,249},{137,30,255},{138,7,7},{139,76,255},{140,16,16},{141,1,255},
	{142,12,255},{143,8,8},{144,15,255},{145,2,254},{146,15,255},{147,6,6},
	{148,22,22},{151,10,10},{152,7,7},{153,5,5},{154,0,255},{157,2,2},
	{158,22,255},{159,1,1},{160,1,255},{161,13,13},{162,8,8},{163,4,255},
	{164,11,11},{165,0,255},{166,2,255},{167,2,2},{168,8,8},{169,1,1},
	{170,7,255},{171,1,255},{172,5,5},{174,6,6},{175,17,17},{177,10,10},
	{181,2,255},{182,11,15},{183,1,1},{184,1,1},{185,2,255},{186,21,255},
	{187,1,1},{188,1,255},{189,6,6},{190,3,3},{191,12,12},{192,5,5},
	{193,6,6},{194,3,3},{195,2,5},{196,0,255},{197,2,2},{198,1,7},
	{199,1,1},{200,1,33},{201,0,255},{202,6,6},{204,16,16},{205,1,255},
	{206,9,9},{207,1,1},{208,3,12},{209,4,8},{210,1,16},{211,5,5},
	{212,3,255},{213,8,8},{214,2,2},{215,1,1},{216,7,28},{217,15,15},
	{220,2,4},{221,1,254},{222,2,3},{223,1,1},{224,1,7},{225,7,14},
	{226,1,9},{228,8,248},{229,2,7},{230,4,4},{231,1,254},{232,6,6},
	{233,1,18},{234,2,2},{235,2,2},{236,1,2},{237,2,254},{239,1,1},
	{240,2,254},{241,2,4},{242,1,254},{244,1,254},{255,1,254}
};

static const owfuzz_ie_range_entry owfuzz_ext_ie_ranges2020[] = {
	{1,1,1},{2,2,2},{3,1,254},{4,8,8},{5,12,254},{6,1,21},{7,8,254},
	{8,1,254},{9,4,4},{10,1,254},{11,3,12},{12,2,254},{13,16,16},
	{14,4,254},{15,1,254},{16,6,254},{17,12,12},{18,20,20},{19,19,254},
	{20,5,254},{21,11,11},{22,13,22},{23,11,11},{24,2,2},{25,11,254},
	{26,2,2},{27,21,21},{28,3,3},{29,2,2},{30,8,8},{31,5,5},{33,1,254},
	{34,3,3},{40,1,254},{44,1,254},{52,3,3},{53,1,5},{54,3,6},
	{56,1,254},{88,7,254},{89,1,254},{90,4,4},{91,8,8},{92,1,254},{93,1,254}
};
static const char *const owfuzz_value_steps[] = {
	"zero",
	"random",
	"one",
	"same"
};
static const char *const owfuzz_mutation_steps[] = {
	"not-present",
	"repeated",
	"all-bits-zero",
	"min-sub-1",
	"min",
	"min-add-1",
	"random-value",
	"max-sub-1",
	"max",
	"max-add-1",
	"all-bits-one"
};

/* crypto structs */
typedef struct {
	uint32_t state[5];
	uint64_t total_len;
	uint8_t buffer[64];
	int buffer_len;
} sha1_ctx;

static const uint8_t aes_sbox[256] = {
	0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
	0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
	0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
	0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
	0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
	0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
	0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
	0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
	0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
	0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
	0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
	0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
	0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
	0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
	0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
	0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

static const uint8_t aes_inv_sbox[256] = {
	0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
	0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
	0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
	0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
	0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
	0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
	0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
	0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
	0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
	0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
	0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
	0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
	0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
	0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
	0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
	0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};

/* it is necessary to put the prototype here */
static int clean_match(const uint8_t *text, int len, const char *name);

static void put_u16_le(uint8_t *dst, int offset, int value){
	dst[offset] = (uint8_t)(value & 0xff);
	dst[offset + 1] = (uint8_t)((value >> 8) & 0xff);
}

static void put_u32_le(uint8_t *dst, int offset, int value){
	dst[offset] = (uint8_t)(value & 0xff);
	dst[offset + 1] = (uint8_t)((value >> 8) & 0xff);
	dst[offset + 2] = (uint8_t)((value >> 16) & 0xff);
	dst[offset + 3] = (uint8_t)((value >> 24) & 0xff);
}

static uint16_t get_u16_le(const uint8_t *src, int offset){
	return (uint16_t)(src[offset] | ((uint16_t)src[offset + 1] << 8));
}

static int get_u32_le(const uint8_t *src, int offset){
	return src[offset] | (src[offset + 1] << 8) | (src[offset + 2] << 16) | (src[offset + 3] << 24);
}

static uint16_t get_u16_be(const uint8_t *src, int offset){
	return ((src[offset] << 8) | src[offset + 1]);
}

static void write_mac_addr(struct mac_addr *addr, const uint8_t *bytes){
	memcpy(addr->array, bytes, ETH_ALEN);
}

static void write_chan_def(struct mac_chan_def *chan, int freq, int band, int flags, int tx_power){
	chan->freq = (u16)freq;
	chan->band = (u8)band;
	chan->flags = (u8)flags;
	chan->tx_power = (s8)tx_power;
}

static void write_chan_op(struct mac_chan_op *chan, int freq, int band, int type, int tx_power){
	chan->band = (u8)band;
	chan->type = (u8)type;
	chan->prim20_freq = (u16)freq;
	chan->center1_freq = (u16)freq;
	chan->center2_freq = 0;
	chan->tx_power = (s8)tx_power;
	chan->flags = 0;
}

static int frequency_band(int freq){
	int ret = 0;

	if(freq >= 5000){
		ret = NL80211_BAND_5GHZ;
	}else{
		ret = NL80211_BAND_2GHZ;
	}
	return ret;
}

static int frequency_supported(int freq){
	for (int i = 0; i < (sizeof(channels_2ghz) / sizeof(channels_2ghz[0])); i++) {
		if (channels_2ghz[i] == freq) {
			return 1;
		}
	}
	for (int i = 0; i < (sizeof(channels_5ghz) / sizeof(channels_5ghz[0])); i++) {
		if (channels_5ghz[i] == freq) {
			return 1;
		}
	}
	return 0;
}

static int monitor_width_to_fw(int width){
	int ret = 0;

	if (width == 20) {
		ret = PHY_CHNL_BW_20;
		return ret;
	}
	if (width == 40) {
		ret = PHY_CHNL_BW_40;
		return ret;
	}
	if (width == 80) {
		ret = PHY_CHNL_BW_80;
		return ret;
	}
	if (width == 160) {
		ret = PHY_CHNL_BW_160;
		return ret;
	}
	ret = -EINVAL;
	return ret;
}

static int ascii_space(uint8_t c){
	return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

static int trim_ascii(const uint8_t *text, int len, int *start, int *end){
	int s = 0;
	int e = 0;

	e = len;
	while (s < e && ascii_space(text[s])) {
		s++;
	}
	while (e > s && ascii_space(text[e - 1])) {
		e--;
	}
	*start = s;
	*end = e;
	return e > s;
}

static int hex_value(uint8_t c){
	int ret = 0;

	if (c >= '0' && c <= '9') {
		return (c - '0');
	}
	if (c >= 'a' && c <= 'f') {
		return (10 + c - 'a');
	}
	if (c >= 'A' && c <= 'F') {
		return (10 + c - 'A');
	}
	ret = -EINVAL;
	return ret;
}

static int parse_u32_ascii(const uint8_t *text, int len, int *value){
	int ret = 0;
	int end = 0;
	int out = 0;
	int pos = 0;
	int start = 0;
	int digit = 0;
	int base = 10;

	if (text == NULL || !value) {
		return ret;
	}
	if (!trim_ascii(text, len, &start, &end)) {
		return ret;
	}
	pos = start;
	if (pos + 2 <= end && text[pos] == '0' && (text[pos + 1] == 'x' || text[pos + 1] == 'X')) {
		base = 16;
		pos += 2;
	}
	if (pos >= end) {
		return ret;
	}
	for (; pos < end; pos++) {
		digit = base == 16 ? hex_value(text[pos]) : (text[pos] >= '0' && text[pos] <= '9' ? (int)(text[pos] - '0') : -1);
		if (digit < 0 || digit >= base) {
			return ret;
		}
		if (out > (0xffffffffu - digit) / base) {
			return ret;
		}
		out = out * base + digit;
	}
	*value = out;
	ret = 1;
	return ret;
}

static int parse_mac_text(const uint8_t *text, int len, uint8_t *out){
	int ret = 0;
	int end = 0;
	int hi  = 0;
	int low = 0;
	int pos = 0;
	int start = 0;

	if (text == NULL || out == NULL) {
		return ret;
	}
	if (!trim_ascii(text, len, &start, &end) || end - start != 17) {
		return ret;
	}
	for (int i = 0; i < ETH_ALEN; i++) {
		pos = start + i * 3;
		hi = hex_value(text[pos]);
		low = hex_value(text[pos + 1]);
		if (hi < 0 || low < 0) {
			return ret;
		}
		out[i] = ((hi << 4) | low);
		if (i != ETH_ALEN - 1 && text[pos + 2] != ':') {
			return ret;
		}
	}
	ret = 1;
	return ret;
}

int aic8800_native_version(void){
	int ret = 0;

	ret = true;
	return ret;
}

int aic8800_build_tx_power_level_v3(uint8_t *out, int out_len){
	int ret = 0;
	int offset = 0;

	/* 105 is the sum of the various sizef(txpwr_11XXX...) */
	if (out == NULL || out_len < 105) {
		return ret;
	}
	memset(out, 0, 105);
	out[offset++] = 1;
	memcpy(out + offset, txpwr_11b_11ag_2g4, sizeof(txpwr_11b_11ag_2g4));
	offset = sizeof(txpwr_11b_11ag_2g4);
	memcpy(out + offset, txpwr_11n_11ac_2g4, sizeof(txpwr_11n_11ac_2g4));
	offset = sizeof(txpwr_11n_11ac_2g4);
	memcpy(out + offset, txpwr_11ax_2g4, sizeof(txpwr_11ax_2g4));
	offset = sizeof(txpwr_11ax_2g4);
	memcpy(out + offset, txpwr_11a_5g, sizeof(txpwr_11a_5g));
	offset = sizeof(txpwr_11a_5g);
	memcpy(out + offset, txpwr_11n_11ac_5g, sizeof(txpwr_11n_11ac_5g));
	offset = sizeof(txpwr_11n_11ac_5g);
	memcpy(out + offset, txpwr_11ax_5g, sizeof(txpwr_11ax_5g));
	return 105;
}

int aic8800_build_me_chan_config(uint8_t *out, int out_len, int include_5g){
	int ret = 0;
	int channels_5g_count = 0;
	struct me_chan_config_req *req = NULL;

	req = (struct me_chan_config_req *)out;
	if (out == NULL || out_len < sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	for (int i = 0; i < (sizeof(channels_2ghz) / sizeof(channels_2ghz[0])); i++) {
		write_chan_def(&req->chan2G4[i], channels_2ghz[i], NL80211_BAND_2GHZ, 0, 30);
	}
	channels_5g_count = include_5g ? (sizeof(channels_5ghz) / sizeof(channels_5ghz[0])) : 0;
	for (int i = 0; i < channels_5g_count; i++) {
		write_chan_def(&req->chan5G[i], channels_5ghz[i], NL80211_BAND_5GHZ, 0, 30);
	}
	req->chan2G4_cnt = (sizeof(channels_2ghz) / sizeof(channels_2ghz[0]));
	req->chan5G_cnt = channels_5g_count;
	ret = sizeof(*req);
	return ret;
}

int aic8800_build_scan_request(uint8_t *out, int out_len, int vif_idx, int include_5g){
	int ret = 0;
	int count = 0;
	struct scanu_start_req *req = (struct scanu_start_req *)out;

	if (out == NULL || out_len < (int)sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	for (int i = 0; i < (sizeof(channels_2ghz) / sizeof(channels_2ghz[0])) && count < SCAN_CHANNEL_MAX; i++, count++) {
		write_chan_def(&req->chan[count], channels_2ghz[i], NL80211_BAND_2GHZ, 0, 30);
	}
	if (include_5g) {
		for (int i = 0; i < (sizeof(channels_5ghz) / sizeof(channels_5ghz[0])) && count < SCAN_CHANNEL_MAX; i++, count++) {
			write_chan_def(&req->chan[count], channels_5ghz[i], NL80211_BAND_5GHZ, 0, 30);
		}
	}
	memset(&req->bssid, 0xff, ETH_ALEN);
	req->add_ies = 0;
	req->add_ie_len = 0;
	req->vif_idx = (u8)vif_idx;
	req->chan_cnt = (u8)count;
	req->ssid_cnt = 1;
	req->no_cck = false;
	req->duration = 0;
	ret = sizeof(*req);
	return ret;
}

int aic8800_write_chan_op(uint8_t *out, int out_len, int offset, int freq, int band, int type, int tx_power){
	int ret = 0;
	struct mac_chan_op *chan = NULL;

	if (out == NULL || offset > out_len || out_len - offset < (int)sizeof(*chan)) {
		return ret;
	}
	chan = (struct mac_chan_op *)(out + offset);
	memset(chan, 0, sizeof(*chan));
	write_chan_op(chan, freq, band, type, tx_power);
	ret = sizeof(*chan);
	return ret;
}

int aic8800_build_add_interface_request(uint8_t *out, int out_len, int type, uint8_t *mac, int mac_len, int p2p){
	int ret = 0;
	struct mm_add_if_req *req = NULL;

	req = (struct mm_add_if_req *)out;
	if (out == NULL || out_len < (int)sizeof(*req) || mac == NULL || mac_len < ETH_ALEN) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->type = (u8)type;
	write_mac_addr(&req->addr, mac);
	req->p2p = p2p ? true : false;
	ret = sizeof(*req);
	return ret;
}

/* aic8800_build_tx_descriptor: create a tx frame */
int aic8800_build_tx_descriptor(uint8_t *out, int out_len, int packet_len, const uint8_t *dest, int dest_len, const uint8_t *src, int src_len,
                                 int ethertype, int ac, int tid, int vif_idx, int staid, int flags, u32 status_desc_addr){
	int ret = 0;
	struct txdesc_api *desc = NULL;

	desc = (struct txdesc_api *)out;
	if (out == NULL || out_len < sizeof(*desc)) {
		return ret;
	}
	memset(desc, 0, sizeof(*desc));
	desc->host.packet_len = (u16)packet_len;
	desc->host.flags_ext = 0;
	desc->host.status_desc_addr = (u32)status_desc_addr;
	if (dest && dest_len >= ETH_ALEN) {
		write_mac_addr(&desc->host.eth_dest_addr, dest);
	}
	if (src && src_len >= ETH_ALEN) {
		write_mac_addr(&desc->host.eth_src_addr, src);
	}
	desc->host.ethertype = (u16)ethertype;
	desc->host.ac = (u8)ac;
	desc->host.tid = (u8)tid;
	desc->host.vif_idx = (u8)vif_idx;
	desc->host.staid = (u8)staid;
	desc->host.flags = (u16)flags;
	ret = sizeof(*desc);
	return ret;
}

int aic8800_build_key_add_request(uint8_t *out, int out_len, int vif_idx, int sta_idx, int pairwise, const uint8_t *key, int key_len, int key_idx){
	int ret = 0;
	int copy_len = 0;
	struct mm_key_add_req *req = NULL;

	req = (struct mm_key_add_req *)out;
	if (out == NULL || out_len < (int)sizeof(*req) || (key == NULL && key_len)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->key_idx = (u8)key_idx;
	req->sta_idx = (u8)sta_idx;
	req->key.length = (u8)key_len;
	copy_len = key_len < MAC_SEC_KEY_LEN ? key_len : MAC_SEC_KEY_LEN;
	if (copy_len) {
		memcpy(req->key.array, key, copy_len);
	}
	req->cipher_suite = MAC_CIPHER_CCMP;
	req->inst_nbr = (u8)vif_idx;
	req->spp = 0;
	req->pairwise = pairwise ? true : false;
	ret = sizeof(*req);
	return ret;
}

int aic8800_build_control_port_request(uint8_t *out, int out_len, int sta_idx, int opened){
	int ret = 0;
	struct me_set_control_port_req *req = NULL;

	req = (struct me_set_control_port_req *)out;
	if (out == NULL || out_len < sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->sta_idx = (u8)sta_idx;
	req->control_port_open = opened ? true : false;
	ret = sizeof(*req);
	return ret;
}

/* aic8800_build_rf_calib_request: build rf calibration request */
int aic8800_build_rf_calib_request(uint8_t *out, int out_len, int band_5g){
	int ret = 0;
	struct mm_set_rf_calib_req *req = NULL;

	req = (struct mm_set_rf_calib_req *)out;
	if (out == NULL || out_len < (int)sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->cal_cfg_24g = 0x00000f8f;
	req->cal_cfg_5g = band_5g ? 0x00000f0f : 0;
	req->param_alpha = 0x0c34c008;
	req->bt_calib_en = 0;
	req->bt_calib_param = 0x00264203;
	ret = sizeof(*req);
	return ret;
}

/* aic8800_build_start_request: build the command for starting the RAM mode Wi-Fi fw */
int aic8800_build_start_request(uint8_t *out, int out_len){
	int ret = 0;
	struct mm_start_req *req = NULL;

	req = (struct mm_start_req *)out;
	if (out == NULL || out_len < sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->uapsd_timeout = 300;
	req->lp_clk_accuracy = 20;
	ret = sizeof(*req);
	return ret;
}

int aic8800_build_dbg_start_npc_request(uint8_t *out, int out_len, int bootaddr, int bootidx){
	if (out == NULL || out_len < 8) {
		return 0;
	}
	memset(out, 0, 8);
	put_u32_le(out, 0, (u32)bootaddr);
	put_u16_le(out, 4, (u16)bootidx);
	return 8;
}

/* aic8800_build_mem_block_write_request: build the memory write command */
int aic8800_build_mem_block_write_request(uint8_t *out, int out_len, int address, uint8_t *bytes, int bytes_len){
	int ret = 0;
	int off = 0;
	int total_len = 0;
	struct dbg_mem_block_write_req *req = NULL;

	req = (struct dbg_mem_block_write_req *)out;
	if (out == NULL || (bytes == NULL && bytes_len) || bytes_len > AIC_MAX_BLOCK_WRITE) {
		return ret;
	}
	total_len = offsetof(struct dbg_mem_block_write_req, memdata) + bytes_len;
	if (out_len < total_len || total_len < bytes_len) {
		return ret;
	}
	memset(req, 0, total_len);
	req->memaddr = (u32)address;
	req->memsize = (u32)bytes_len;
	if (bytes_len) {
		memcpy(req->memdata, bytes, bytes_len);
	}

	ret = total_len;
	return ret;
}

/* aic8800_decode_mem_rw_cfm: when the firmware returns a response for the mem read command, decode it, in general it contains the tuple 'address : value ' */
int aic8800_decode_mem_rw_cfm(uint8_t *params, int params_len, uint8_t *meta, int meta_len){
	int ret = 0;

	if (params == NULL || meta == NULL || meta_len < MEM_RW_META_SIZE || params_len < MEM_RW_META_SIZE) {
		return ret;
	}
	put_u32_le(meta, 0, get_u32_le(params, 0));
	put_u32_le(meta, 4, get_u32_le(params, 4));
	ret = 1;
	return ret;
}

int aic8800_decode_connect_ind(uint8_t *params, int params_len, uint8_t *meta, int meta_len){
	int ret = 0;

	if (params == NULL || meta == NULL || meta_len < CONNECT_IND_META_SIZE || params_len < 10) {
		return ret;
	}
	memset(meta, 0, CONNECT_IND_META_SIZE);
	put_u16_le(meta, 0, get_u16_le(params, 0));
	memcpy(meta + 2, params + 2, ETH_ALEN);
	meta[8] = params[9];
	meta[9] = params_len > 10 ? params[10] : IFACE_INVALID;
	ret = 1;
	return ret;
}

int aic8800_pack_u32(uint8_t *out, int out_len, int first, int second, int count){
	int ret = 0;

	if (out == NULL || count > 2 || out_len < count * 4) {
		return ret;
	}
	if (count >= 1) {
		put_u32_le(out, 0, first);
	}
	if (count >= 2) {
		put_u32_le(out, 4, second);
	}
	ret = count * 4;
	return ret;
}

/* aic8800_build_lmac_message: low level function for creating the lmac message which will be sent to the aic8800 firmware */
int aic8800_build_lmac_message(uint8_t *out, int out_len, int id, int dest_id, int src_id, uint8_t *params, int params_len){
	int ret = 0;
	int total_len = 0;
	struct aic8800_usb_lmac_msg *msg = NULL;

	msg = (struct aic8800_usb_lmac_msg *)out;
	if (out == NULL || (params == NULL && params_len)) {
		return ret;
	}
	total_len = sizeof(*msg) + params_len;
	if (out_len < total_len || params_len > 0xffff - 8) {
		return ret;
	}
	memset(msg, 0, total_len);
	msg->usb_len = (u16)(params_len + 12);
	msg->usb_type = USB_TYPE_CFG_CMD_RSP;
	msg->usb_reserved = 0;
	msg->usb_padding = 0;
	msg->id = (u16)id;
	msg->dest_id = (u16)dest_id;
	msg->src_id = (u16)src_id;
	msg->param_len = (u16)params_len;
	if (params_len) {
		memcpy(msg + 1, params, params_len);
	}
	ret = total_len;
	return ret;
}

/* aic8800_build_usb_tx_data: build the usb urb which will be sent to the aic8800 Wi-Fi controller */
int aic8800_build_usb_tx_data(uint8_t *out, int out_len, uint8_t *desc, int desc_len, uint8_t *payload, int payload_len){
	int ret = 0;
	int usb_len = 0;
	int transfer_len = 0;

	if (out == NULL || desc == NULL || desc_len != TXDESC_API_SIZE || (payload == NULL && payload_len)) {
		return ret;
	}
	usb_len = 4 + TXDESC_API_SIZE + payload_len;
	if (usb_len > 0x0fff) {
		return ret;
	}
	/* Match aicwf_usb_bus_txdata() exactly: the firmware USB stream is not
	 * word-padded.  Only avoid a max-packet-sized transfer with one byte. */
	transfer_len = usb_len;
	if ((transfer_len % 512) == 0) {
		transfer_len++;
	}
	if (out_len < transfer_len) {
		return ret;
	}
	memset(out, 0, transfer_len);
	put_u16_le(out, 0, usb_len);
	out[1] &= 0x0f;
	out[2] = USB_TYPE_DATA_TX;
	out[3] = 0;
	memcpy(out + 4, desc, TXDESC_API_SIZE);
	if (payload_len) {
		memcpy(out + 4 + TXDESC_API_SIZE, payload, payload_len);
	}
	ret = transfer_len;
	return ret;
}

/* aic8800_parse_rx_aggregate: parse an incoming RX frame from the aic8800 firmware, in this case the expected frame contains many subframes aggregated in a single urb */
int aic8800_parse_rx_aggregate(uint8_t *bytes, int bytes_len, uint8_t *meta, int meta_len){
	int ret = 0;
	int cfg = 0;
	int type = 0;
	int offset = 0;
	int pkt_len = 0;
	int invalid = 0;
	int records = 0;
	int aggr_len = 0;
	int capacity = 0;
	int remaining = 0;
	int adjust_len = 0;
	uint8_t *rec = NULL;

	if (bytes == NULL || meta == NULL || meta_len < RX_AGGR_META_SIZE) {
		return ret;
	}
	remaining = bytes_len;
	capacity = meta_len / RX_AGGR_META_SIZE;
	while (remaining >= 4 && records < capacity) {
		pkt_len = get_u16_le(bytes, offset);
		type = bytes[offset + 2];
		cfg = (type & USB_TYPE_CFG) == USB_TYPE_CFG;
		aggr_len = cfg ? pkt_len + 4 : pkt_len + RX_HWHRD_LEN;
		adjust_len = cfg ? ((pkt_len + RX_ALIGNMENT - 1) & ~(RX_ALIGNMENT - 1)) + 4 : aggr_len;
		invalid = (aggr_len == 0 || aggr_len > remaining || adjust_len > remaining) ? 1 : 0;
		rec = meta + records * RX_AGGR_META_SIZE;
		put_u32_le(rec, 0, offset);
		put_u32_le(rec, 4, aggr_len);
		put_u32_le(rec, 8, adjust_len);
		put_u32_le(rec, 12, remaining);
		put_u16_le(rec, 16, pkt_len);
		rec[18] = (uint8_t)type;
		rec[19] = (uint8_t)((cfg ? 1 : 0) | (invalid ? 2 : 0));
		records++;
		if (invalid) {
			break;
		}
		offset += adjust_len;
		remaining -= adjust_len;
	}
	return records;
}

/* aic8800_parse_lmac_response: function called for parsing an incoming command data frame from the aic8800 usb dongle */
int aic8800_parse_lmac_response(uint8_t *block, int block_len, uint8_t *meta, int meta_len){
	int ret = 0;
	int param_len = 0;
	int param_end = 0;
	int param_start = 0;

	if (block == NULL || meta == NULL || meta_len < LMAC_RESPONSE_META_SIZE || block_len < 16) {
		return ret;
	}
	param_len = get_u16_le(block, 10);
	param_start = 16;
	param_end = param_start + param_len;
	if (param_end > block_len || param_end < param_start) {
		param_end = block_len;
	}
	memset(meta, 0, LMAC_RESPONSE_META_SIZE);
	put_u16_le(meta, 0, get_u16_le(block, 4));
	put_u16_le(meta, 2, param_len);
	put_u32_le(meta, 4, get_u32_le(block, 12));
	put_u32_le(meta, 8, param_start);
	put_u32_le(meta, 12, param_end);
	ret = 1;
	return ret;
}

static int aic8800_rx_sec_hdr_len_block(const uint8_t *block, int block_len){
	int decr_status = 0;
	int ret = 0;

	if (block == NULL || block_len < RX_HWHRD_LEN) {
		return ret;
	}
	decr_status = (block[AIC8800_RX_HWVECT_STATUS_OFFSET] >> 2) & 0x07;
	switch (decr_status) {
		case RWNX_RX_HD_DECR_CCMP128:
		case RWNX_RX_HD_DECR_TKIP:
			ret = 8;
			return ret;
		case RWNX_RX_HD_DECR_WEP:
			ret = 4;
			return ret;
		case RWNX_RX_HD_DECR_WAPI:
			ret = 18;
			return ret;
		default:
			return ret;
	}
}

static int aic8800_rx_flags_is_amsdu_block(const uint8_t *block, int block_len){
	if (block == NULL || block_len <= AIC8800_RX_FLAGS_OFFSET) {
		return 0;
	}
	return (block[AIC8800_RX_FLAGS_OFFSET] & 0x01) != 0;
}

/* aic8800_decode_sta_data_frame: parse an incoming frame, very useful for building a fast packet analyzer in the future */
int aic8800_decode_sta_data_frame(const uint8_t *block, int block_len, uint8_t *meta, int meta_len){
	int ret = 0;
	int ds = 0;
	int type = 0;
	int subtype = 0;
	int hdr_len = 0;
	int sec_len = 0;
	int frame_off = 0;
	int frame_len = 0;
	int msdu_len = 0;
	int msdu_off = 0;
	uint16_t fc = 0;
	const uint8_t *frame = NULL;
	const uint8_t *llc = NULL;
	const uint8_t *amsdu = NULL;

	if (block == NULL || meta == NULL || meta_len < STA_DATA_META_SIZE) {
		return ret;
	}
	memset(meta, 0, STA_DATA_META_SIZE);
	frame_off = block_len >= RX_HWHRD_LEN ? RX_HWHRD_LEN : 0;
	frame = block + frame_off;
	frame_len = block_len - frame_off;

	if (frame_len >= 14 && ((frame[12] == 0x88 && frame[13] == 0x8e) || (frame[12] == 0x08 && frame[13] == 0x00) || (frame[12] == 0x08 && frame[13] == 0x06))) {
		memcpy(meta, frame, ETH_ALEN);
		memcpy(meta + ETH_ALEN, frame + ETH_ALEN, ETH_ALEN);
		put_u16_le(meta, 12, get_u16_be(frame, 12));
		put_u32_le(meta, 16, frame_off + 14);
		put_u32_le(meta, 20, frame_len - 14);
		put_u32_le(meta, 24, frame_off);
		ret = 1;
		return ret;
	}
	if (frame_len < 24) {
		return ret;
	}
	fc = get_u16_le(frame, 0);
	type = (fc >> 2) & 0x03;
	subtype = (fc >> 4) & 0x0fu;
	if (type != 2) {
		return ret;
	}
	hdr_len = 24;
	if (subtype & 0x08) {
		hdr_len += 2;
	}
	if (frame[1] & 0x80) {
		hdr_len += 4;
	}
	ds = frame[1] & 0x03;
	if (ds == 0x03) {
		hdr_len += ETH_ALEN;
	}
	sec_len = aic8800_rx_sec_hdr_len_block(block, block_len);
	if (frame_len < hdr_len + sec_len + 8) {
		return ret;
	}
	if (ds == 0x00) {
		memcpy(meta, frame + 4, ETH_ALEN);
		memcpy(meta + ETH_ALEN, frame + 10, ETH_ALEN);
	}else if (ds == 0x01) {
		memcpy(meta, frame + 16, ETH_ALEN);
		memcpy(meta + ETH_ALEN, frame + 10, ETH_ALEN);
	}else if (ds == 0x02) {
		memcpy(meta, frame + 4, ETH_ALEN);
		memcpy(meta + ETH_ALEN, frame + 16, ETH_ALEN);
	}else {
		memcpy(meta, frame + 16, ETH_ALEN);
		memcpy(meta + ETH_ALEN, frame + 24, ETH_ALEN);
	}
	if (aic8800_rx_flags_is_amsdu_block(block, block_len) || ((subtype & 0x08) && frame_len > 25 && (frame[24] & 0x80))) {
		amsdu = frame + hdr_len + sec_len;
		msdu_len = frame_len - hdr_len - sec_len;
		if (msdu_len < 22) {
			return ret;
		}
		msdu_off = get_u16_be(amsdu, 12);
		if (msdu_off < 8 || msdu_off + 14 > msdu_len) {
			return ret;
		}
		llc = amsdu + 14;
		if (llc[0] != 0xaa || llc[1] != 0xaa || llc[2] != 0x03) {
			return ret;
		}
		memcpy(meta, amsdu, ETH_ALEN);
		memcpy(meta + ETH_ALEN, amsdu + ETH_ALEN, ETH_ALEN);
		put_u16_le(meta, 12, get_u16_be(llc, 6));
		put_u32_le(meta, 16, frame_off + hdr_len + sec_len + 14 + 8);
		put_u32_le(meta, 20, msdu_off - 8);
		put_u32_le(meta, 24, frame_off);
		ret = 1;
		return ret;
	}
	llc = frame + hdr_len + sec_len;
	if (llc[0] != 0xaa || llc[1] != 0xaa || llc[2] != 0x03) {
		return ret;
	}
	put_u16_le(meta, 12, get_u16_be(llc, 6));
	put_u32_le(meta, 16, frame_off + hdr_len + sec_len + 8);
	put_u32_le(meta, 20, frame_len - hdr_len - sec_len - 8);
	put_u32_le(meta, 24, frame_off);
	ret = 1;
	return ret;
}

/* aic8800_decode_scan_result: parse the Wi-Fi scan results from the aic8800 mcu */
int aic8800_decode_scan_result(const uint8_t *params, int params_len, uint8_t *meta, int meta_len){
	int ret = 0;
	int len = 0;
	int off = 0;
	int freq = 0;
	int copy_len = 0;
	int frame_len = 0;
	int frame_req = 0;
	int available = 0;
	int payload_off = 0;
	uint8_t id = 0;
	uint8_t band = 0;
	uint8_t rssi = 0;
	uint8_t *frame = NULL;

	if (params == NULL || meta == NULL || meta_len < SCAN_RESULT_META_SIZE || params_len < 48) {
		return ret;
	}
	memset(meta, 0, SCAN_RESULT_META_SIZE);
	frame_len = get_u16_le(params, 0);
	freq = get_u16_le(params, 4);
	band = params[6];
	rssi = params[9];
	payload_off = 12;
	available = params_len - payload_off;
	if (frame_len < available) {
		available = frame_len;
	}
	if (available < 36) {
		return ret;
	}
	frame = params + payload_off;
	memcpy(meta, frame + 16, ETH_ALEN);
	off = 36;
	while (off + 2 <= available) {
		id = frame[off];
		len = frame[off + 1];
		off += 2;
		if (off + len > available) {
			break;
		}
		if (id == 0) {
			copy_len = len < 32 ? len : 32;
			if (copy_len) {
				memcpy(meta + 8, frame + off, copy_len);
			}
			meta[40] = (uint8_t)copy_len;
			break;
		}
		off += len;
	}
	put_u16_le(meta, 42, freq);
	meta[44] = band;
	meta[45] = rssi;
	ret = 1;
	return ret;
}

int aic8800_mem_read_word_bytes(uint8_t *out, int out_len, int value, int take){
	int ret = 0;

	if (out == NULL || take == 0) {
		return ret;
	}
	if (take > 4) {
		take = 4;
	}
	if (take > out_len) {
		return ret;
	}
	for (int i = 0; i < take; i++) {
		out[i] = (uint8_t)((value >> (i * 8)) & 0xffu);
	}
	ret = take;
	return ret;
}

int aic8800_parse_u32(const uint8_t *text, int text_len, uint8_t *out, int out_len){
	int ret = 0;
	int value = 0;

	if (out == NULL || out_len < 4 || !parse_u32_ascii(text, text_len, &value)) {
		return ret;
	}
	put_u32_le(out, 0, value);
	ret = sizeof(u32);
	return ret;
}

int aic8800_parse_hex_bytes(const uint8_t *text, int text_len, uint8_t *out, int out_len){
	int ret = 0;
	int nibbles = 0;
	int out_pos = 0;
	uint8_t c = 0;
	uint8_t high = 0;
	int32_t value = 0;

	if (text == NULL || out == NULL) {
		return ret;
	}
	for (int i = 0; i < text_len; i++) {
		c = text[i];
		if (c == '0' && i + 1 < text_len && (text[i + 1] == 'x' || text[i + 1] == 'X')) {
			i++;
			continue;
		}
		if (ascii_space(c) || c == ':' || c == '_' || c == '-') {
			continue;
		}
		value = hex_value(c);
		if (value < 0) {
			return ret;
		}
		if ((nibbles & 1) == 0) {
			high = (uint8_t)value;
		}else{
			if (out_pos >= out_len) {
				return ret;
			}
			out[out_pos++] = (uint8_t)((high << 4) | (uint8_t)value);
		}
		nibbles++;
	}
	if (!nibbles || (nibbles & 1)) {
		return ret;
	}
	ret = out_pos;
	return ret;
}

/* aic8800_parse_mac_address: put the wrapper for the function 'parse_mac_text' here as C code, unsure if it will speedup the performance */
int aic8800_parse_mac_address(const uint8_t *text, int text_len, uint8_t *out, int out_len){
	int ret = 0;

	if (out == NULL || out_len < ETH_ALEN || !parse_mac_text(text, text_len, out)) {
		return ret;
	}
	ret = ETH_ALEN;
	return ret;
}

/* aic8800_is_hex_digit: very simple wrapper for verify if a given u8 value is an hex number */
int aic8800_is_hex_digit(int value){
	return hex_value((uint8_t)value) >= 0 ? 1 : 0;
}

/* aic8800_bytes_equal: simple wrapper for comparing 2 bytes sequence */
int aic8800_bytes_equal(const uint8_t *a, int a_len, const uint8_t *b, int b_len){
	uint8_t diff = 0;

	if (a == NULL || b == NULL || a_len != b_len) {
		return 0;
	}
	for (int i = 0; i < a_len; i++) {
		diff |= (uint8_t)(a[i] ^ b[i]);
	}
	return diff == 0 ? 1 : 0;
}

/* -- functions for checking the mac corretness -- */
int aic8800_is_broadcast_mac(const uint8_t *mac, int mac_len){
	int ret = 0;
	uint8_t diff = 0;

	if (mac == NULL|| mac_len != ETH_ALEN) {
		return ret;
	}
	for (int i = 0; i < ETH_ALEN; i++) {
		diff |= (uint8_t)(mac[i] ^ 0xffu);
	}
	return diff == 0 ? 1 : 0;
}

int aic8800_is_zero_mac(const uint8_t *mac, int mac_len){
	int ret = 0;
	uint8_t any = 0;

	if (!mac || mac_len != ETH_ALEN) {
		ret = 1;
		return ret;
	}
	for (int i = 0; i < ETH_ALEN; i++) {
		any |= mac[i];
	}
	return any == 0 ? 1 : 0;
}

int aic8800_is_usable_unicast_mac(const uint8_t *mac, int mac_len){
	int ret = 0;

	if (!mac || mac_len != ETH_ALEN || (mac[0] & 1)) {
		return ret;
	}
	ret = !aic8800_is_zero_mac(mac, mac_len) && !aic8800_is_broadcast_mac(mac, mac_len);
	return ret;
}

int aic8800_derive_interface_mac(uint8_t *out, int out_len, const uint8_t *base, int base_len, int slot){
	int ret = 0;

	if (out == NULL || out_len < ETH_ALEN || !base || base_len < ETH_ALEN) {
		return ret;
	}
	memcpy(out, base, ETH_ALEN);
	out[5] ^= (uint8_t)slot;
	ret = ETH_ALEN;
	return ret;
}

/* aic8800_build_deauth_frame: build the deauthentication frame for our attacks */
int aic8800_build_deauth_frame(uint8_t *out, int out_len, const uint8_t *bssid, int bssid_len, const uint8_t *target, int target_len, int reason){
	int ret = 0;

	if (out == NULL || out_len < 26 || bssid == NULL || target == NULL || bssid_len < ETH_ALEN || target_len < ETH_ALEN) {
		return ret;
	}
	if (!aic8800_is_usable_unicast_mac(bssid, ETH_ALEN) || aic8800_is_zero_mac(target, ETH_ALEN)) {
		return ret;
	}
	if ((target[0] & 1) && !aic8800_is_broadcast_mac(target, ETH_ALEN)) {
		return ret;
	}
	if (reason <= 0 || reason > 0xffffu) {
		/*
		 *	Code 1: Unspecified reason / client is no longer authorized
		 *	Code 2: Previous authentication no longer valid
		 *	Code 3: Station is leaving or has left the network (roaming or shutting down)
		 *	Code 4: Disassociated due to inactivity or timeout
		 *	Code 5: Access point is busy or overloaded with too many clients
		 *	Code 7: Class 3 frame received from a non-associated station
		 *	Code 15: 4-way handshake timeout (often a Wi-Fi password mismatch)
		 *	Code 23: 802.1X authentication failure
		 */
		reason = 7;
	}
	memset(out, 0, 26);
	out[0] = 0xc0;
	out[1] = 0x00;
	put_u16_le(out, 2, 0);
	memcpy(out + 4, target, ETH_ALEN);
	memcpy(out + 10, bssid, ETH_ALEN);
	memcpy(out + 16, bssid, ETH_ALEN);
	put_u16_le(out, 22, 0);
	put_u16_le(out, 24, reason);
	ret = 26;
	return ret;
}

static int mgmt_addr_matches_ap(const uint8_t *frame, const uint8_t *ap_mac){
	int ret = 0;

	ret = aic8800_bytes_equal(frame + 4, ETH_ALEN, ap_mac, ETH_ALEN) && aic8800_bytes_equal(frame + 16, ETH_ALEN, ap_mac, ETH_ALEN);
	return ret;
}

static int mgmt_ssid_matches(const uint8_t *ies, int ies_len, const uint8_t *ssid, int ssid_len){
	int ret = 0;
	int off = 0;
	int id = 0;
	int len = 0;

	if (ssid == NULL || ssid_len <= 0) {
		ret = -EINVAL;
		return ret;
	}
	while (off + 2 <= ies_len) {
		id = ies[off];
		len = ies[off + 1];
		off += 2;
		if (off + len > ies_len) {
			break;
		}
		if (id == 0) {
			return len == ssid_len && aic8800_bytes_equal(ies + off, len, ssid, ssid_len);
		}
		off += len;
	}
	return ret;
}

static int mgmt_ies_have_wmm(const uint8_t *ies, int ies_len){
	int ret = 0;
	int off = 0;
	int id = 0;
	int len = 0;

	while (off + 2 <= ies_len) {
		id = ies[off];
		len = ies[off + 1];
		off += 2;
		if (off + len > ies_len) {
			break;
		}
		if (id == 221 && len >= 6 && ies[off] == 0x00 && ies[off + 1] == 0x50 && ies[off + 2] == 0xf2 && ies[off + 3] == 0x02) {
			return 1;
		}
		off += len;
	}
	return 0;
}

/* aic8800_decode_ap_mgmt_frame: parse a management frame from the aic8800 dongle */
int aic8800_decode_ap_mgmt_frame(uint8_t *meta, int meta_len, const uint8_t *block, int block_len, const uint8_t *ap_mac, int ap_mac_len, const uint8_t *ssid, int ssid_len){
	int ret = 0;
	int frame_off = 0;
	int frame_len = 0;
	int subtype = 0;
	int body_off = 0;
	int ies_off = 0;
	int ies_len = 0;
	uint16_t fc = 0;
	const uint8_t *frame = NULL;

	if (meta == NULL || meta_len < 60 || block == NULL || ap_mac == NULL || ap_mac_len < ETH_ALEN || (!ssid && ssid_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	frame_off = block_len >= RX_HWHRD_LEN ? RX_HWHRD_LEN : 0;
	frame = block + frame_off;
	frame_len = block_len - frame_off;
	if (frame_len < 24) {
		return ret;
	}
	fc = get_u16_le(frame, 0);
	if (((fc >> 2) & 0x03) != 0) {
		return ret;
	}
	subtype = (fc >> 4) & 0x0f;
	if (!mgmt_addr_matches_ap(frame, ap_mac)) {
		return ret;
	}
	meta[1] = (uint8_t)subtype;
	put_u32_le(meta, 4, frame_off);
	put_u32_le(meta, 8, frame_len);
	put_u16_le(meta, 12, get_u16_le(frame, 22));
	memcpy(meta + 36, frame + 4, ETH_ALEN);
	memcpy(meta + 42, frame + 10, ETH_ALEN);
	memcpy(meta + 48, frame + 16, ETH_ALEN);

	if (subtype == 11) {
		if (frame_len < 30) {
			return ret;
		}
		put_u16_le(meta, 18, get_u16_le(frame, 24));
		put_u16_le(meta, 20, get_u16_le(frame, 26));
		put_u16_le(meta, 22, get_u16_le(frame, 28));
		if (get_u16_le(frame, 24) != 0 || get_u16_le(frame, 26) != 1) {
			return ret;
		}
		meta[0] = 1;
		ret = meta[0];
		return ret;
	}

	if (subtype == 0 || subtype == 2) {
		body_off = 24;
		ies_off = subtype == 0 ? 28 : 34;
		if (frame_len < ies_off) {
			return ret;
		}
		ies_len = frame_len - ies_off;
		if (!mgmt_ssid_matches(frame + ies_off, ies_len, ssid, ssid_len)) {
			return ret;
		}
		meta[0] = subtype == 0 ? 2 : 3;
		meta[2] = mgmt_ies_have_wmm(frame + ies_off, ies_len) ? 1 : 0;
		put_u16_le(meta, 14, get_u16_le(frame, body_off));
		put_u16_le(meta, 16, get_u16_le(frame, body_off + 2));
		put_u32_le(meta, 24, frame_off + ies_off);
		put_u32_le(meta, 28, ies_len);
		put_u16_le(meta, 32, ssid_len);
		return 1;
	}
	return ret;
}

/* aic8800_build_ap_auth_response: build the authentication response from the AP mode */
int aic8800_build_ap_auth_response(uint8_t *out, int out_len, const uint8_t *ap_mac, int ap_mac_len, const uint8_t *sta_mac, int sta_mac_len, int seq){
	int ret = 0;

	if (out == NULL || out_len < 30 || ap_mac == NULL || sta_mac == NULL || ap_mac_len < ETH_ALEN || sta_mac_len < ETH_ALEN) {
		return ret;
	}
	memset(out, 0, 30);
	out[0] = 0xb0;
	out[1] = 0x00;
	memcpy(out + 4, sta_mac, ETH_ALEN);
	memcpy(out + 10, ap_mac, ETH_ALEN);
	memcpy(out + 16, ap_mac, ETH_ALEN);
	put_u16_le(out, 22, (seq & 0x0fff) << 4);
	put_u16_le(out, 24, 0);
	put_u16_le(out, 26, 2);
	put_u16_le(out, 28, 0);
	ret = 30;
	return 30;
}

int aic8800_build_ap_assoc_response(uint8_t *out, int out_len, const uint8_t *ap_mac, int ap_mac_len, const uint8_t *sta_mac, int sta_mac_len, int aid, int seq, int use_wpa2, int qos, int status){
	int ret = 0;
	int off = 0;
	static const uint8_t ext_rates_2g[] = {0x30, 0x48, 0x60, 0x6c};
	static const uint8_t rates_2g[] = {0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24};

	if (out == NULL || out_len < 64 || ap_mac == NULL || !sta_mac || ap_mac_len < ETH_ALEN || sta_mac_len < ETH_ALEN) {
		return ret;
	}
	if (aid <= 0 || aid > 2007) {
		aid = 1;
	}
	memset(out, 0, out_len);
	out[0] = 0x10;
	out[1] = 0x00;
	memcpy(out + 4, sta_mac, ETH_ALEN);
	memcpy(out + 10, ap_mac, ETH_ALEN);
	memcpy(out + 16, ap_mac, ETH_ALEN);
	put_u16_le(out, 22, (seq & 0x0fff) << 4);
	put_u16_le(out, 24, use_wpa2 ? 0x0011 : 0x0001);
	put_u16_le(out, 26, status & 0xffff);
	put_u16_le(out, 28, status == 0 ? (0xc000 | (aid & 0x3fff)) : 0);
	off = 30;
	if (off + 2 + (int)sizeof(rates_2g) > out_len) {
		return ret;
	}
	out[off++] = 1;
	out[off++] = sizeof(rates_2g);
	memcpy(out + off, rates_2g, sizeof(rates_2g));
	off += sizeof(rates_2g);
	if (off + 2 + (int)sizeof(ext_rates_2g) > out_len) {
		return ret;
	}
	out[off++] = 50;
	out[off++] = sizeof(ext_rates_2g);
	memcpy(out + off, ext_rates_2g, sizeof(ext_rates_2g));
	off += sizeof(ext_rates_2g);
	if (status == 0 && use_wpa2) {
		if (off + sizeof(ap_wpa2_psk_rsn_ie) > out_len) {
			return ret;
		}
		memcpy(out + off, ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie));
		off += sizeof(ap_wpa2_psk_rsn_ie);
	}
	if (status == 0 && qos) {
		if (off + sizeof(ap_wmm_param_ie) > out_len) {
			return ret;
		}
		memcpy(out + off, ap_wmm_param_ie, sizeof(ap_wmm_param_ie));
		off += sizeof(ap_wmm_param_ie);
	}
	return off;
}

int aic8800_is_robust_mgmt_frame(const uint8_t *frame, int frame_len){
	int ret = 0;
	int type = 0;
	int subtype = 0;
	uint16_t fc = 0;

	if (frame == NULL || frame_len < 2) {
		return ret;
	}
	fc = get_u16_le(frame, 0);
	type = (fc >> 2) & 0x03;
	subtype = (fc >> 4) & 0x0fu;
	if (type != 0) {
		return ret;
	}
	if (subtype == 10 || subtype == 12) {
		ret = 1;
		return ret;
	}
	if (subtype == 13) {
		ret = frame_len <= 24 || frame[24] != 4;
		return ret;
	}
	return ret;
}

/* aic8800_channel_to_frequency: taken from the kernel functions, covert a channel to its frequency */
int aic8800_channel_to_frequency(int channel){
	if (channel >= 1 && channel <= 13) {
		return 2407 + channel * 5;
	}
	if (channel == 14) {
		return 2484;
	}
	return channel;
}

/* aic8800_frequency_to_channel: do the opposite of the function above, giving a frequency, return its channel */
int aic8800_frequency_to_channel(int freq){
	int ret = 0;

	if (freq == 2484) {
		ret = 14;
		return ret;
	}
	if (freq >= 2412 && freq <= 2472 && ((freq - 2407) % 5) == 0) {
		ret = (freq - 2407) / 5;
		return ret;
	}
	return ret;
}

/* aic8800_build_mesh_start_request: build the firmware command for starting the mesh network */
int aic8800_build_mesh_start_request(uint8_t *out, int out_len, int vif_idx, int freq, int dtim, int beacon, int user_mpm, int auth, int auth_id, const uint8_t *mesh_id, int mesh_id_len){
	int ret = 0;
	int id_len = 0;
	struct mesh_start_req *req = NULL;

	req = (struct mesh_start_req *)out;
	if (out == NULL || out_len < sizeof(*req) || (!mesh_id && mesh_id_len)) {
		return ret;
	}
	if (!freq) {
		freq = 2412;
	}
	memset(req, 0, sizeof(*req));
	req->basic_rates.length = MAC_RATESET_LEN;
	memcpy(req->basic_rates.array, mesh_rates, MAC_RATESET_LEN);
	write_chan_def(&req->chan, freq, frequency_band(freq), 0, 30);
	req->center_freq1 = (u32)freq;
	req->center_freq2 = 0;
	req->ch_width = PHY_CHNL_BW_20;
	req->dtim_period = (u8)dtim;
	req->bcn_int = (u16)beacon;
	req->vif_index = (u8)vif_idx;
	id_len = mesh_id_len < MESH_MESHID_MAX_LEN ? mesh_id_len : MESH_MESHID_MAX_LEN;
	req->mesh_id_len = (u8)id_len;
	if (id_len) {
		memcpy(req->mesh_id, mesh_id, id_len);
	}
	req->ie_addr = 0;
	req->ie_len = 0;
	req->user_mpm = user_mpm ? true : false;
	req->is_auth = auth ? true : false;
	req->auth_id = (u8)auth_id;
	ret = sizeof(*req);
	return ret;
}

/* aic8800_build_monitor_config_request: create the monitor mode configuration command for the aic8800 firmware */
int aic8800_build_monitor_config_request(uint8_t *out, int out_len, int freq, int freq_valid, int width, int center1, int center2, int uf, int auto_reply){
	int ret = 0;
	int fw_width = 0;
	struct me_config_monitor_req *req = (struct me_config_monitor_req *)out;

	if (out == NULL || out_len < (int)sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	if (freq_valid) {
		fw_width = monitor_width_to_fw(width);
		if (fw_width < 0 || !frequency_supported(freq)) {
			return ret;
		}
		req->chan.band = (u8)frequency_band(freq);
		req->chan.type = (u8)fw_width;
		req->chan.prim20_freq = (u16)freq;
		req->chan.center1_freq = (u16)(center1 ? center1 : freq);
		req->chan.center2_freq = (u16)center2;
		req->chan.tx_power = 30;
		req->chan.flags = 0;
		req->chan_set = true;
	}
	req->uf = uf ? true : false;
	req->auto_reply = auto_reply ? true : false;
	ret = sizeof(*req);
	return ret;
}

int aic8800_build_set_filter_request(uint8_t *out, int out_len, int rx_filter){
	int ret = 0;
	struct mm_set_filter_req *req = (struct mm_set_filter_req *)out;

	if (out == NULL || out_len < (int)sizeof(*req)) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->filter = (u32)rx_filter;
	ret = sizeof(*req);
	return ret;
}

int aic8800_decode_monitor_cfm(uint8_t *meta, int meta_len, const uint8_t *params, int params_len){
	int ret = 0;
	const struct me_config_monitor_cfm *cfm = (const struct me_config_monitor_cfm *)params;

	if (meta == NULL || meta_len < MONITOR_CFM_META_SIZE || !params || params_len < (int)sizeof(*cfm)) {
		return ret;
	}
	memset(meta, 0, MONITOR_CFM_META_SIZE);
	meta[0] = cfm->chan_index;
	meta[1] = cfm->chan.band;
	meta[2] = cfm->chan.type;
	meta[3] = (uint8_t)cfm->chan.tx_power;
	put_u16_le(meta, 4, cfm->chan.prim20_freq);
	put_u16_le(meta, 6, cfm->chan.center1_freq);
	put_u16_le(meta, 8, cfm->chan.center2_freq);
	meta[10] = cfm->chan.flags;
	ret = 1;
	return ret;
}

int aic8800_build_ap_beacon_request(uint8_t *out, int out_len, uint8_t *meta, int meta_len, int vif_idx, const uint8_t *mac, int mac_len, const uint8_t *ssid, int ssid_len, int freq, int dtim, int beacon, int use_wpa2){
	int ret = 0;
	int pos = 0;
	int channel = 0;
	int tim_offset = 0;
	uint8_t frame[512] = {};
	static const uint8_t rates_2g[] = {0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24};
	static const uint8_t ext_rates_2g[] = {0x30, 0x48, 0x60, 0x6c};
	static const uint8_t rates_5g[] = {0x8c, 0x12, 0x98, 0x24, 0xb0, 0x48, 0x60, 0x6c};
	struct apm_set_bcn_ie_req *req = NULL;

	req = (struct apm_set_bcn_ie_req *)out;
	if (out == NULL || out_len < (int)sizeof(*req) || !meta || meta_len < AIC8800_AP_BEACON_META_SIZE || !mac || mac_len < ETH_ALEN || !ssid || ssid_len <= 0 || ssid_len > MAC_SSID_LEN || !frequency_supported(freq)) {
		return ret;
	}
	if (!beacon) {
		beacon = 100;
	}
	if (!dtim) {
		dtim = 2;
	}
	memset(req, 0, sizeof(*req));
	memset(meta, 0, AIC8800_AP_BEACON_META_SIZE);

	frame[0] = 0x80;
	frame[1] = 0x00;
	memset(frame + 4, 0xff, ETH_ALEN);
	memcpy(frame + 10, mac, ETH_ALEN);
	memcpy(frame + 16, mac, ETH_ALEN);
	put_u16_le(frame, 22, 0);
	put_u16_le(frame, 32, beacon);
	put_u16_le(frame, 34, use_wpa2 ? 0x0011 : 0x0001);
	pos = 36;

	frame[pos++] = 0;
	frame[pos++] = (uint8_t)ssid_len;
	memcpy(frame + pos, ssid, ssid_len);
	pos += ssid_len;

	frame[pos++] = 1;
	if (frequency_band(freq) == NL80211_BAND_2GHZ) {
		frame[pos++] = sizeof(rates_2g);
		memcpy(frame + pos, rates_2g, sizeof(rates_2g));
		pos += sizeof(rates_2g);
		channel = freq == 2484 ? 14 : ((freq >= 2412 && freq <= 2472) ? (freq - 2407) / 5 : 0);
		if (channel > 0) {
			frame[pos++] = 3;
			frame[pos++] = 1;
			frame[pos++] = (uint8_t)channel;
		}
	}else{
		frame[pos++] = sizeof(rates_5g);
		memcpy(frame + pos, rates_5g, sizeof(rates_5g));
		pos += sizeof(rates_5g);
	}

	tim_offset = pos;
	frame[pos++] = 5;
	frame[pos++] = 4;
	frame[pos++] = 0;
	frame[pos++] = (uint8_t)dtim;
	frame[pos++] = 0;
	frame[pos++] = 0;

	if (frequency_band(freq) == NL80211_BAND_2GHZ) {
		frame[pos++] = 50;
		frame[pos++] = sizeof(ext_rates_2g);
		memcpy(frame + pos, ext_rates_2g, sizeof(ext_rates_2g));
		pos += sizeof(ext_rates_2g);
	}

	if (use_wpa2) {
		if (pos + (int)sizeof(ap_wpa2_psk_rsn_ie) > (int)sizeof(frame)) {
			return ret;
		}
		memcpy(frame + pos, ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie));
		pos += sizeof(ap_wpa2_psk_rsn_ie);
	}

	if (pos > (int)sizeof(req->bcn_ie)) {
		return ret;
	}
	req->vif_idx = (u8)vif_idx;
	req->bcn_ie_len = (u16)pos;
	memcpy(req->bcn_ie, frame, pos);
	put_u16_le(meta, 0, pos);
	put_u16_le(meta, 2, tim_offset);
	meta[4] = 6;
	meta[5] = (uint8_t)frequency_band(freq);
	put_u16_le(meta, 6, beacon);
	put_u16_le(meta, 8, freq);
	meta[10] = (uint8_t)dtim;
	ret = sizeof(*req);
	return ret;
}


int aic8800_build_inject_beacon_frame(uint8_t *out, int out_len, uint8_t *meta, int meta_len, const uint8_t *mac, int mac_len, const uint8_t *ssid, int ssid_len, int freq, int dtim, int beacon, int use_wpa2){
	int ret = 0;
	int pos = 0;
	int channel = 0;
	int tim_offset = 0;
	static const uint8_t rates_2g[] = {0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24};
	static const uint8_t ext_rates_2g[] = {0x30, 0x48, 0x60, 0x6c};
	static const uint8_t rates_5g[] = {0x8c, 0x12, 0x98, 0x24, 0xb0, 0x48, 0x60, 0x6c};

	if (out == NULL || out_len < 36 || !mac || mac_len < ETH_ALEN || !ssid || ssid_len <= 0 || ssid_len > MAC_SSID_LEN || !frequency_supported(freq)) {
		return ret;
	}
	if (!beacon) {
		beacon = 100;
	}
	if (!dtim) {
		dtim = 2;
	}
	memset(out, 0, out_len);
	if (meta != NULL && meta_len > 0) {
		memset(meta, 0, meta_len);
	}

	out[0] = 0x80;
	out[1] = 0x00;
	memset(out + 4, 0xff, ETH_ALEN);
	memcpy(out + 10, mac, ETH_ALEN);
	memcpy(out + 16, mac, ETH_ALEN);
	put_u16_le(out, 22, 0);
	put_u16_le(out, 32, beacon);
	put_u16_le(out, 34, use_wpa2 ? 0x0011 : 0x0001);
	pos = 36;

	if (pos + 2 + ssid_len > out_len) {
		return 0;
	}
	out[pos++] = 0;
	out[pos++] = (uint8_t)ssid_len;
	memcpy(out + pos, ssid, ssid_len);
	pos += ssid_len;

	if (frequency_band(freq) == NL80211_BAND_2GHZ) {
		if (pos + 2 + (int)sizeof(rates_2g) > out_len) {
			return 0;
		}
		out[pos++] = 1;
		out[pos++] = sizeof(rates_2g);
		memcpy(out + pos, rates_2g, sizeof(rates_2g));
		pos += sizeof(rates_2g);
		channel = freq == 2484 ? 14 : ((freq >= 2412 && freq <= 2472) ? (freq - 2407) / 5 : 0);
		if (channel > 0) {
			if (pos + 3 > out_len) {
				return 0;
			}
			out[pos++] = 3;
			out[pos++] = 1;
			out[pos++] = (uint8_t)channel;
		}
	}else{
		if (pos + 2 + (int)sizeof(rates_5g) > out_len) {
			return 0;
		}
		out[pos++] = 1;
		out[pos++] = sizeof(rates_5g);
		memcpy(out + pos, rates_5g, sizeof(rates_5g));
		pos += sizeof(rates_5g);
	}

	tim_offset = pos;
	if (pos + 6 > out_len) {
		return 0;
	}
	out[pos++] = 5;
	out[pos++] = 4;
	out[pos++] = 0;
	out[pos++] = (uint8_t)dtim;
	out[pos++] = 0;
	out[pos++] = 0;

	if (frequency_band(freq) == NL80211_BAND_2GHZ) {
		if (pos + 2 + (int)sizeof(ext_rates_2g) > out_len) {
			return 0;
		}
		out[pos++] = 50;
		out[pos++] = sizeof(ext_rates_2g);
		memcpy(out + pos, ext_rates_2g, sizeof(ext_rates_2g));
		pos += sizeof(ext_rates_2g);
	}

	if (use_wpa2) {
		if (pos + (int)sizeof(ap_wpa2_psk_rsn_ie) > out_len) {
			return 0;
		}
		memcpy(out + pos, ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie));
		pos += sizeof(ap_wpa2_psk_rsn_ie);
	}

	if (meta != NULL && meta_len >= AIC8800_AP_BEACON_META_SIZE) {
		put_u16_le(meta, 0, pos);
		put_u16_le(meta, 2, tim_offset);
		meta[4] = 6;
		meta[5] = (uint8_t)frequency_band(freq);
		put_u16_le(meta, 6, beacon);
		put_u16_le(meta, 8, freq);
		meta[10] = (uint8_t)dtim;
		meta[11] = (uint8_t)channel;
	}
	ret = pos;
	return ret;
}

int aic8800_build_ap_start_request(uint8_t *out, int out_len, int vif_idx, int freq, int beacon_len, int tim_offset, int tim_len, int beacon, int use_wpa2){
	int ret = 0;
	struct apm_start_req *req = NULL;

	req = (struct apm_start_req *)out;
	if (out == NULL || out_len < sizeof(*req) || !frequency_supported(freq) || beacon_len <= 0 || beacon_len > 512) {
		return ret;
	}
	if (!beacon) {
		beacon = 100;
	}
	memset(req, 0, sizeof(*req));
	if (frequency_band(freq) == NL80211_BAND_2GHZ) {
		req->basic_rates.length = 4;
		req->basic_rates.array[0] = 0x82;
		req->basic_rates.array[1] = 0x84;
		req->basic_rates.array[2] = 0x8b;
		req->basic_rates.array[3] = 0x96;
	}else{
		req->basic_rates.length = 3;
		req->basic_rates.array[0] = 0x8c;
		req->basic_rates.array[1] = 0x98;
		req->basic_rates.array[2] = 0xb0;
	}
	write_chan_def(&req->chan, freq, frequency_band(freq), 0, 30);
	req->center_freq1 = (u32)freq;
	req->center_freq2 = 0;
	req->ch_width = PHY_CHNL_BW_20;
	req->bcn_addr = 0;
	req->bcn_len = (u16)beacon_len;
	req->tim_oft = (u16)tim_offset;
	req->bcn_int = (u16)beacon;
	req->flags = use_wpa2 ? (CONTROL_PORT_HOST | CONTROL_PORT_NO_ENC | WPA_WPA2_IN_USE) : 0;
	//req->ctrl_port_ethertype = use_wpa2 ? (u16)(((ETH_P_PAE & 0xffu) << 8) | ((ETH_P_PAE >> 8) & 0xffu)) : 0;
	req->ctrl_port_ethertype = (u16)(((ETH_P_PAE & 0xffu) << 8) | ((ETH_P_PAE >> 8) & 0xffu));
	req->tim_len = (u8)tim_len;
	req->vif_idx = (u8)vif_idx;
	ret = sizeof(*req);
	return ret;
}

int aic8800_decode_ap_start_cfm(uint8_t *meta, int meta_len, const uint8_t *params, int params_len){
	int ret = 0;
	const struct apm_start_cfm *cfm = NULL;

	cfm = (const struct apm_start_cfm *)params;
	if (meta == NULL || meta_len < APM_START_CFM_META_SIZE || params == NULL || params_len < sizeof(*cfm)) {
		return ret;
	}
	meta[0] = cfm->status;
	meta[1] = cfm->vif_idx;
	meta[2] = cfm->ch_idx;
	meta[3] = cfm->bcmc_idx;
	ret = 1;
	return ret;
}

int aic8800_build_ap_stop_request(uint8_t *out, int out_len, int vif_idx){
	int ret = 0;
	struct apm_stop_req *req = (struct apm_stop_req *)out;

	if (!out || out_len < sizeof(*req)) {
		return ret;
	}
	req->vif_idx = (u8)vif_idx;
	ret = sizeof(*req);
	return ret;
}

int aic8800_build_me_sta_add_request(uint8_t *out, int out_len, int vif_idx, const uint8_t *mac, int mac_len, int aid, int qos){
	int ret = 0;
	struct me_sta_add_req *req = (struct me_sta_add_req *)out;

	if (!out || out_len < sizeof(*req) || !mac || mac_len < ETH_ALEN || !aic8800_is_usable_unicast_mac(mac, ETH_ALEN) || vif_idx < 0 || vif_idx > 0xff) {
		return ret;
	}
	if (aid <= 0 || aid > 2007) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	memcpy(req->mac_addr.array, mac, ETH_ALEN);
	req->rate_set.length = MAC_RATESET_LEN;
	memcpy(req->rate_set.array, mesh_rates, MAC_RATESET_LEN);
	req->flags = qos ? STA_QOS_CAPA_NATIVE : 0;
	req->aid = (u16)aid;
	req->uapsd_queues = 0;
	req->max_sp_len = 0;
	req->opmode = 0;
	req->vif_idx = (u8)vif_idx;
	ret = sizeof(*req);
	return ret;
}

int aic8800_decode_me_sta_add_cfm(uint8_t *meta, int meta_len, const uint8_t *params, int params_len){
	int ret = 0;
	const struct me_sta_add_cfm *cfm = (const struct me_sta_add_cfm *)params;

	if (!meta || meta_len < ME_STA_ADD_CFM_META_SIZE || !params || params_len < 3) {
		return ret;
	}
	memset(meta, 0, ME_STA_ADD_CFM_META_SIZE);
	meta[0] = cfm->status;
	meta[1] = cfm->sta_idx;
	meta[2] = cfm->pm_state;
	meta[3] = params_len >= 4 ? cfm->aligned : 0;
	ret = 1;
	return ret;
}

int aic8800_build_me_sta_del_request(uint8_t *out, int out_len, int sta_idx){
	int ret = 0;
	struct me_sta_del_req *req = (struct me_sta_del_req *)out;

	if (!out || out_len < sizeof(*req) || sta_idx < 0 || sta_idx > 0xff) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	req->sta_idx = (u8)sta_idx;
	req->tdls_sta = false;
	ret = sizeof(*req);
	return ret;
}

/* aic8800_build_connect_request: build the connect request for starting the connection with an AP */
int aic8800_build_connect_request(uint8_t *out, int out_len, int vif_idx, const uint8_t *ssid, int ssid_len, const uint8_t *bssid_text, int bssid_text_len, int freq, int freq_valid, int use_wpa2){
	int ret = 0;
	int copy_len = 0;
	int connect_flags = 0;
	struct sm_connect_req *req = (struct sm_connect_req *)out;

	if (!out || out_len < sizeof(*req) || (!ssid && ssid_len) || ssid_len <= 0 || ssid_len > MAC_SSID_LEN ||
	    (freq_valid && !frequency_supported(freq))) {
		return ret;
	}
	memset(req, 0, sizeof(*req));
	copy_len = ssid_len;
	req->ssid.length = (u8)copy_len;
	if (copy_len) {
		memcpy(req->ssid.array, ssid, copy_len);
	}

	if (bssid_text && bssid_text_len) {
		if (!parse_mac_text(bssid_text, bssid_text_len, (uint8_t *)req->bssid.array)) {
			return ret;
		}
	}else{
		memset(&req->bssid, 0xff, ETH_ALEN);
	}
	if (freq_valid) {
		write_chan_def(&req->chan, freq, frequency_band(freq), 0, 30);
	}else{
		req->chan.freq = 0xffffu;
	}

	if (use_wpa2) {
		connect_flags = CONTROL_PORT_HOST | CONTROL_PORT_NO_ENC | WPA_WPA2_IN_USE;
		req->ctrl_port_ethertype = (u16)(((ETH_P_PAE & 0xffu) << 8) | ((ETH_P_PAE >> 8) & 0xffu));
		req->ie_len = sizeof(ap_wpa2_psk_rsn_ie);
		memcpy(req->ie_buf, ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie));
	}else{
		req->ctrl_port_ethertype = 0;
		req->ie_len = 0;
	}
	req->flags = (u32)connect_flags;
	req->listen_interval = 0;
	req->auth_type = WLAN_AUTH_OPEN;
	req->uapsd_queues = 1;
	req->vif_idx = (u8)vif_idx;
	ret = sizeof(*req);
	return ret;
}

int aic8800_build_owfuzz_le16(uint8_t *out, int out_len, int value){
	int ret = 0;

	if (!out || out_len < 2) {
		return ret;
	}
	put_u16_le(out, 0, value);
	ret = sizeof(u16);
	return ret;
}

int aic8800_build_owfuzz_frame_header(uint8_t *out, int out_len, int type, int flags,
                                       int duration, const uint8_t *addr1, int addr1_len,
                                       const uint8_t *addr2, int addr2_len, const uint8_t *addr3,
                                       int addr3_len, int seq){
	int ret = 0;

	if (!out || out_len < 24 || !addr1 || !addr2 || !addr3 ||
		addr1_len < ETH_ALEN || addr2_len < ETH_ALEN || addr3_len < ETH_ALEN) {
		return ret;
	}
	memset(out, 0, 24);
	out[0] = (uint8_t)type;
	out[1] = (uint8_t)flags;
	put_u16_le(out, 2, duration);
	memcpy(out + 4, addr1, ETH_ALEN);
	memcpy(out + 10, addr2, ETH_ALEN);
	memcpy(out + 16, addr3, ETH_ALEN);
	put_u16_le(out, 22, ((seq & 0x0fffu) << 4) & 0xffffu);
	ret = 24;
	return ret;
}

static int owfuzz_min_u32(int a, int b){
	return a < b ? a : b;
}

static int owfuzz_mac_is_broadcast(const uint8_t *mac){
	int ret = 0;

	for (int i = 0; i < ETH_ALEN; i++) {
		if (mac[i] != 0xffu) {
			return ret;
		}
	}
	ret = 1;
	return ret;
}

static uint32_t owfuzz_rand_next(int *state){
	uint32_t value = 0;

	value = (uint32_t)*state;
	value = value * 1664525u + 1013904223u;
	*state = value;
	return value;
}

/* owfuzz_rand_int: generate a random seed for the fuzzer */
static int owfuzz_rand_int(int *state, int min, int max){
	uint32_t range = 0;
	uint64_t scaled = 0;

	if (max <= min) {
		owfuzz_rand_next(state);
		return min;
	}
	range = (uint32_t)(max - min + 1);
	scaled = (uint64_t)owfuzz_rand_next(state) * (uint64_t)range;
	return min + (scaled >> 32);
}

static int owfuzz_append(uint8_t *out, int cap, int *off, const uint8_t *src, int len){
	int ret = 0;
	int copy_len = 0;

	if (!src || !len || *off >= cap) {
		return ret;
	}
	copy_len = owfuzz_min_u32(len, cap - *off);
	memcpy(out + *off, src, copy_len);
	*off += copy_len;
	return ret;
}

static void owfuzz_append_byte(uint8_t *out, int cap, int *off, int value){
	uint8_t byte = 0;

	byte = (uint8_t)value;
	owfuzz_append(out, cap, off, &byte, 1);
}

static void owfuzz_append_le16(uint8_t *out, int cap, int *off, int value){
	uint8_t tmp[2] = {};

	put_u16_le(tmp, 0, value);
	owfuzz_append(out, cap, off, tmp, sizeof(tmp));
}

static void owfuzz_append_le64_words(uint8_t *out, int cap, int *off, int low, int high){
	uint8_t tmp[8] = {};

	put_u32_le(tmp, 0, low);
	put_u32_le(tmp, 4, high);
	owfuzz_append(out, cap, off, tmp, sizeof(tmp));
}

/* owfuzz_append_ie: append the generated information element to the frame which will be sent over the air */
static void owfuzz_append_ie(uint8_t *out, int cap, int *off, int id, const uint8_t *payload, int payload_len, int len_override){
	owfuzz_append_byte(out, cap, off, id);
	owfuzz_append_byte(out, cap, off, len_override & 0xffu);
	owfuzz_append(out, cap, off, payload, payload_len);
}

static void owfuzz_fill_payload(uint8_t *dst, int len, int value_kind, int *rng_state){
	uint8_t same = 0;

	same = (uint8_t)owfuzz_rand_int(rng_state, 0, 255);
	for (int i = 0; i < len; i++) {
		if (value_kind == OWFUZZ_VALUE_ZERO) {
			dst[i] = 0;
		}else if (value_kind == OWFUZZ_VALUE_ONE) {
			dst[i] = 0xffu;
		}else if (value_kind == OWFUZZ_VALUE_SAME) {
			dst[i] = same;
		}else{
			dst[i] = (uint8_t)owfuzz_rand_int(rng_state, 0, 255);
		}
	}
}

static void owfuzz_append_random_tail(uint8_t *out, int cap, int *off, int *rng_state, int value_kind){
	int payload_len = 0;
	uint8_t payload[255] = {};

	payload_len = owfuzz_rand_int(rng_state, 0, 255);
	owfuzz_fill_payload(payload, payload_len, value_kind, rng_state);
	owfuzz_append(out, cap, off, payload, payload_len);
}

static int owfuzz_mutation_length(int *rng_state, int step, int min_len, int max_len){
	int ret = 0;

	if (step == OWFUZZ_MUT_NOT_PRESENT || step == OWFUZZ_MUT_ALL_BITS_ZERO) {
		return ret;
	}
	if (step == OWFUZZ_MUT_REPEATED || step == OWFUZZ_MUT_RANDOM_VALUE) {
		ret = owfuzz_rand_int(rng_state, min_len, max_len);
		return ret;
	}
	if (step == OWFUZZ_MUT_MIN_SUB_1) {
		ret = min_len > 0 ? min_len - 1 : 0;
		return ret;
	}
	if (step == OWFUZZ_MUT_MIN) {
		ret = min_len;
		return ret;
	}
	if (step == OWFUZZ_MUT_MIN_ADD_1) {
		ret = min_len < 255 ? min_len + 1 : 255;
		return ret;
	}
	if (step == OWFUZZ_MUT_MAX_SUB_1) {
		ret = max_len > 0 ? max_len - 1 : 0;
		return ret;
	}
	if (step == OWFUZZ_MUT_MAX) {
		ret = max_len;
		return ret;
	}
	if (step == OWFUZZ_MUT_MAX_ADD_1) {
		ret = max_len < 255 ? max_len + 1 : 255;
		return ret;
	}
	if (step == OWFUZZ_MUT_ALL_BITS_ONE) {
		ret = 255;
		return ret;
	}
	return ret;
}

static int owfuzz_append_mutation_ie(uint8_t *out, int cap, int *off, int *rng_state, int id, int step, int value_kind, int ext_id, int min_len, int max_len){
	int ret = 0;
	int len = 0;
	int item_len = 0;
	int payload_len = 0;
	uint8_t item[260] = {};

	len = owfuzz_mutation_length(rng_state, step, min_len, max_len);
	if (step == OWFUZZ_MUT_NOT_PRESENT) {
		ret = len;
		return ret;
	}

	item[item_len++] = (uint8_t)id;
	item[item_len++] = (uint8_t)(len & 0xffu);
	if (id == 255) {
		item[item_len++] = (uint8_t)ext_id;
	}
	payload_len = owfuzz_min_u32(len, 255);
	payload_len = owfuzz_min_u32(payload_len, sizeof(item) - item_len);
	owfuzz_fill_payload(item + item_len, payload_len, value_kind, rng_state);
	item_len += payload_len;
	owfuzz_append(out, cap, off, item, item_len);
	if (step == OWFUZZ_MUT_REPEATED) {
		owfuzz_append(out, cap, off, item, item_len);
	}
	return len;
}

static void owfuzz_append_header(uint8_t *out, int cap, int *off, int type, int flags, int duration, const uint8_t *addr1, const uint8_t *addr2, const uint8_t *addr3, int seq){
	uint8_t header[24] = {};

	memset(header, 0, sizeof(header));
	header[0] = (uint8_t)type;
	header[1] = (uint8_t)flags;
	put_u16_le(header, 2, duration);
	memcpy(header + 4, addr1, ETH_ALEN);
	memcpy(header + 10, addr2, ETH_ALEN);
	memcpy(header + 16, addr3, ETH_ALEN);
	put_u16_le(header, 22, ((seq & 0x0fffu) << 4) & 0xffffu);
	owfuzz_append(out, cap, off, header, sizeof(header));
}

static int owfuzz_is_type(int type, int a){
	return (type & 0xfcu) == a;
}

static void owfuzz_mgmt_addresses(int type, int mode_ap, const uint8_t *source,
                                   const uint8_t *target, const uint8_t *bssid,
                                   const uint8_t **addr1, const uint8_t **addr2, const uint8_t **addr3){

	if (owfuzz_is_type(type, 0x80)) {
		*addr1 = owfuzz_broadcast_mac;
		*addr2 = bssid;
		*addr3 = bssid;
		return;
	}
	if (mode_ap && (owfuzz_is_type(type, 0x50) || owfuzz_is_type(type, 0x10) || owfuzz_is_type(type, 0x30) || owfuzz_is_type(type, 0xa0) || owfuzz_is_type(type, 0xc0))) {
		*addr1 = target;
		*addr2 = bssid;
		*addr3 = bssid;
		return;
	}
	if (owfuzz_is_type(type, 0x40) && owfuzz_mac_is_broadcast(target)) {
		*addr1 = owfuzz_broadcast_mac;
		*addr2 = source;
		*addr3 = owfuzz_broadcast_mac;
		return;
	}
	*addr1 = target;
	*addr2 = source;
	*addr3 = bssid;
}

static void owfuzz_append_base_ies(uint8_t *out, int cap, int *off, int type, int auth_wpa, int channel, const uint8_t *ssid, int ssid_len){
	int ht_type = 0;
	int ssid_type = 0;
	int rates_type = 0;
	uint8_t ds[1] = {};
	uint8_t tim[4] = {0, 1, 0, 0};
	uint8_t ht[26] = {};

	ssid_type = owfuzz_is_type(type, 0x80) || owfuzz_is_type(type, 0x40) || owfuzz_is_type(type, 0x50) || owfuzz_is_type(type, 0x00) || owfuzz_is_type(type, 0x20);
	if (ssid_type) {
		owfuzz_append_ie(out, cap, off, 0, ssid, owfuzz_min_u32(ssid_len, 32), owfuzz_min_u32(ssid_len, 32));
	}
	rates_type = ssid_type || owfuzz_is_type(type, 0x10) || owfuzz_is_type(type, 0x30);
	if (rates_type) {
		owfuzz_append_ie(out, cap, off, 1, owfuzz_supported_rates, sizeof(owfuzz_supported_rates), sizeof(owfuzz_supported_rates));
	}
	if (owfuzz_is_type(type, 0x80) || owfuzz_is_type(type, 0x50)) {
		ds[0] = (uint8_t)(channel & 0xffu);
		owfuzz_append_ie(out, cap, off, 3, ds, sizeof(ds), sizeof(ds));
		owfuzz_append_ie(out, cap, off, 5, tim, sizeof(tim), sizeof(tim));
	}

	ht_type = owfuzz_is_type(type, 0x40) || owfuzz_is_type(type, 0x00) || owfuzz_is_type(type, 0x20) || owfuzz_is_type(type, 0x80) || owfuzz_is_type(type, 0x50);
	if (ht_type) {
		memset(ht, 0, sizeof(ht));
		ht[0] = 0x6e;
		ht[1] = 0x01;
		ht[2] = 0x1b;
		ht[3] = 0xff;
		ht[4] = 0xff;
		owfuzz_append_ie(out, cap, off, 45, ht, sizeof(ht), sizeof(ht));
		owfuzz_append_ie(out, cap, off, 50, owfuzz_extended_rates, sizeof(owfuzz_extended_rates), sizeof(owfuzz_extended_rates));
	}
	if (auth_wpa) {
		owfuzz_append_ie(out, cap, off, 48, owfuzz_rsn_payload, sizeof(owfuzz_rsn_payload), sizeof(owfuzz_rsn_payload));
	}
}

static void owfuzz_build_mgmt_frame(uint8_t *out, int cap, int *off, int type,
                                    int mode_ap, int auth_wpa, int channel,
                                    int seq, int ts_low, int ts_high,
                                    int *rng_state, int mutate, int mut_ie_id,
                                    int mut_step, int mut_value, int mut_ext_id,
                                    int mut_min, int mut_max, const uint8_t *source,
                                    const uint8_t *target, const uint8_t *bssid, const uint8_t *ssid,
                                    int ssid_len, int *mutation_len){
	uint8_t action[4] = {};
	const uint8_t *addr1 = NULL;
	const uint8_t *addr2 = NULL;
	const uint8_t *addr3 = NULL;

	owfuzz_mgmt_addresses(type, mode_ap, source, target, bssid, &addr1, &addr2, &addr3);
	owfuzz_append_header(out, cap, off, type, 0, (owfuzz_is_type(type, 0x80) || owfuzz_is_type(type, 0x40)) ? 0 : 0x013au, addr1, addr2, addr3, seq);

	if (owfuzz_is_type(type, 0x80) || owfuzz_is_type(type, 0x50)) {
		owfuzz_append_le64_words(out, cap, off, ts_low, ts_high);
		owfuzz_append_le16(out, cap, off, 100);
		owfuzz_append_le16(out, cap, off, 0x0431);
	}else if (owfuzz_is_type(type, 0x60)){
		owfuzz_append_le64_words(out, cap, off, ts_low, ts_high);
		owfuzz_append_le16(out, cap, off, 0);
	}else if (owfuzz_is_type(type, 0x00) || owfuzz_is_type(type, 0x20)) {
		owfuzz_append_le16(out, cap, off, 0x0431);
		owfuzz_append_le16(out, cap, off, 10);
		if (owfuzz_is_type(type, 0x20)) {
			owfuzz_append(out, cap, off, bssid, ETH_ALEN);
		}
	}else if (owfuzz_is_type(type, 0x10) || owfuzz_is_type(type, 0x30)) {
		owfuzz_append_le16(out, cap, off, 0x0431);
		owfuzz_append_le16(out, cap, off, 0);
		owfuzz_append_le16(out, cap, off, 1);
	}else if (owfuzz_is_type(type, 0xb0)) {
		owfuzz_append_le16(out, cap, off, 0);
		owfuzz_append_le16(out, cap, off, 1);
		owfuzz_append_le16(out, cap, off, 0);
	}else if (owfuzz_is_type(type, 0xc0) || owfuzz_is_type(type, 0xa0)) {
		owfuzz_append_le16(out, cap, off, 1);
	}else if (owfuzz_is_type(type, 0xd0) || owfuzz_is_type(type, 0xe0)) {
		action[0] = 0x04;
		action[1] = 0x09;
		action[2] = (uint8_t)owfuzz_rand_int(rng_state, 0, 255);
		action[3] = (uint8_t)owfuzz_rand_int(rng_state, 0, 255);
		owfuzz_append(out, cap, off, action, sizeof(action));
	}
	if (owfuzz_is_type(type, 0x90) || owfuzz_is_type(type, 0xa0) || owfuzz_is_type(type, 0xc0)) {
		owfuzz_append_random_tail(out, cap, off, rng_state, OWFUZZ_VALUE_SAME);
	}else if (owfuzz_is_type(type, 0xd0) || owfuzz_is_type(type, 0xe0)) {
		owfuzz_append_random_tail(out, cap, off, rng_state, OWFUZZ_VALUE_RANDOM);
	}
	owfuzz_append_base_ies(out, cap, off, type, auth_wpa, channel, ssid, ssid_len);
	if (mutate) {
		*mutation_len = owfuzz_append_mutation_ie(out, cap, off, rng_state, mut_ie_id, mut_step, mut_value, mut_ext_id, mut_min, mut_max);
	}
}

static void owfuzz_build_control_frame(uint8_t *out, int cap, int *off, int type, int *rng_state, const uint8_t *source, const uint8_t *target){
	int two_addr = 0;
	int base_len = 0;
	uint8_t frame[20] = {};

	two_addr =  !(owfuzz_is_type(type, 0xd4) || owfuzz_is_type(type, 0xc4));
	base_len = two_addr ? 16 : 10;
	memset(frame, 0, sizeof(frame));
	frame[0] = (uint8_t)type;
	frame[1] = 0;
	frame[2] = 0x3a;
	frame[3] = 0x01;
	memcpy(frame + 4, target, ETH_ALEN);
	if (two_addr) {
		memcpy(frame + 10, source, ETH_ALEN);
	}
	if (owfuzz_is_type(type, 0x84) || owfuzz_is_type(type, 0x94)) {
		for (int i = 0; i < 4; i++) {
			frame[base_len + i] = (uint8_t)owfuzz_rand_int(rng_state, 0, 255);
		}
		base_len += 4;
	}
	owfuzz_append(out, cap, off, frame, base_len);
}

static void owfuzz_build_data_frame(uint8_t *out, int cap, int *off, int type, int mode_ap, int seq, int *rng_state, const uint8_t *source, const uint8_t *target, const uint8_t *bssid){
	int flags = 0;
	int from_ap = 0;
	int payload_len = 0;
	uint8_t qos[2] = {};
	uint8_t payload[64] = {};
	const uint8_t *addr1 = NULL;
	const uint8_t *addr2 = NULL;
	const uint8_t *addr3 = NULL;
	uint8_t llc[] = {0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x88, 0xb5};

	if(mode_ap == true){
		from_ap = true;
	}else{
		from_ap = false;
	}
	if(from_ap == true){
		flags = 2;
	}else{
		flags = 1;
	}
	if(from_ap == true){
		addr1 = target;
		addr2 = bssid;
		addr3 = source;
	}else{
		addr1 = bssid;
		addr2 = source;
		addr3 = target;
	}
	owfuzz_append_header(out, cap, off, type, flags, 0x013au, addr1, addr2, addr3, seq);
	if (type & 0x80) {
		owfuzz_append(out, cap, off, qos, sizeof(qos));
	}
    if (!owfuzz_is_type(type, 0x48) && !owfuzz_is_type(type, 0xc8)) {
		owfuzz_append(out, cap, off, llc, sizeof(llc));
		payload_len = owfuzz_rand_int(rng_state, 8, 64);
		owfuzz_fill_payload(payload, payload_len, OWFUZZ_VALUE_RANDOM, rng_state);
		owfuzz_append(out, cap, off, payload, payload_len);
	}
}

int aic8800_build_owfuzz_generated_frame(uint8_t *out, int out_len, uint8_t *meta, int meta_len,
                                          int frame_type, int mode_ap, int auth_wpa,
                                          int channel, int max_len, int seq,
                                          int ts_low, int ts_high, int rng_state,
                                          int mutate, int mut_ie_id, int mut_step,
                                          int mut_value, int mut_ext_id, int mut_min,
                                          int mut_max, const uint8_t *source, int source_len,
                                          const uint8_t *target, int target_len, const uint8_t *bssid,
                                          int bssid_len, const uint8_t *ssid, int ssid_len){
	int ret = 0;
	int cap = 0;
	int off = 0;
	int kind = 0;
	int mutation_len = 0;

	if (!out || !meta || meta_len < 8 || !source || !target || !bssid ||
		source_len < ETH_ALEN || target_len < ETH_ALEN || bssid_len < ETH_ALEN || (!ssid && ssid_len)) {
		return ret;
	}
	cap = owfuzz_min_u32(out_len, max_len ? max_len : out_len);
	if (cap == 0) {
		return ret;
	}
	memset(out, 0, cap);
	memset(meta, 0, meta_len);
	kind = frame_type & 0x0cu;
	if (kind == 0x04) {
		owfuzz_build_control_frame(out, cap, &off, frame_type, &rng_state, source, target);
	}else if (kind == 0x08) {
		owfuzz_build_data_frame(out, cap, &off, frame_type, mode_ap, seq, &rng_state, source, target, bssid);
	}else{
		owfuzz_build_mgmt_frame(out, cap, &off, frame_type, mode_ap, auth_wpa, channel, seq, ts_low, ts_high,
                                &rng_state, mutate, mut_ie_id, mut_step, mut_value, mut_ext_id, mut_min,
                                mut_max, source, target, bssid, ssid, ssid_len, &mutation_len);
	}
	put_u32_le(meta, 0, rng_state);
	put_u16_le(meta, 4, mutation_len);
	put_u16_le(meta, 6, off);
	ret = off;
	return ret;
}


int aic8800_build_owfuzz_captured_frame(uint8_t *out, int out_len, uint8_t *meta, int meta_len,
                                         const uint8_t *frame, int frame_len, int mode_ap,
                                         int rewrite_captured, int mutate, int max_len,
                                         int seq, int rng_state, int mut_ie_id,
                                         int mut_step, int mut_value, int mut_ext_id,
                                         int mut_min, int mut_max, const uint8_t *source,
                                         int source_len, const uint8_t *target, int target_len,
                                         const uint8_t *bssid, int bssid_len){
	int ret = 0;
	int cap = 0;
	int off = 0;
	int kind = 0;
	int offset = 0;
	int min_offset = 0;
	int mutation_len = 0;
	const uint8_t *addr1 = NULL;
	const uint8_t *addr2 = NULL;
	const uint8_t *addr3 = NULL;

	if (!out || !meta || meta_len < 8 || !frame || !source || !target || !bssid ||
		source_len < ETH_ALEN || target_len < ETH_ALEN || bssid_len < ETH_ALEN) {
		return ret;
	}
	kind = frame_len ? (frame[0] & 0x0cu) : 0;
	cap = out_len;
	if (kind == 0x00 && max_len && cap > max_len) {
		cap = max_len;
	}
	if (cap == 0) {
		return ret;
	}
	memset(out, 0, cap);
	memset(meta, 0, meta_len);

	off = owfuzz_min_u32(frame_len, cap);
	memcpy(out, frame, off);

	if (rewrite_captured && off >= 24 && kind != 0x04) {
		if (kind == 0) {
			owfuzz_mgmt_addresses(out[0] & 0xfcu, mode_ap, source, target, bssid, &addr1, &addr2, &addr3);
			memcpy(out + 4, addr1, ETH_ALEN);
			memcpy(out + 10, addr2, ETH_ALEN);
			memcpy(out + 16, addr3, ETH_ALEN);
		}
	}

	if (off >= 24) {
		put_u16_le(out, 22, ((seq & 0x0fffu) << 4) & 0xffffu);
	}

	mutation_len = 0;
	if (mutate && kind == 0) {
		mutation_len = owfuzz_append_mutation_ie(out, cap, &off, &rng_state, mut_ie_id, mut_step, mut_value, mut_ext_id, mut_min, mut_max);
	}else if (mutate && off > 10) {
		min_offset = off - 1 < 10 ? off - 1 : 10;
		offset = owfuzz_rand_int(&rng_state, min_offset, off - 1);
		out[offset] = (uint8_t)owfuzz_rand_int(&rng_state, 0, 255);
	}
	put_u32_le(meta, 0, rng_state);
	put_u16_le(meta, 4, mutation_len);
	put_u16_le(meta, 6, off);
	ret = off;
	return ret;
}

static int write_ascii_string(uint8_t *out, int out_len, const char *text){
	int ret = 0;
	int len = 0;

	if (!out || !text) {
		return ret;
	}
	while (text[len]) {
		len++;
	}
	if (out_len < len) {
		return ret;
	}
	for (int i = 0; i < len; i++) {
		out[i] = (uint8_t)text[i];
	}
	return len;
}

static uint8_t hex_digit_u4(int value){
	value &= 0x0fu;
	return (uint8_t)(value < 10 ? ('0' + value) : ('a' + value - 10));
}

static int append_ascii_byte(uint8_t *out, int out_len, int *off, int value){
	int ret = 0;

	if (*off >= out_len) {
		return ret;
	}
	out[(*off)++] = (uint8_t)value;
	ret = 1;
	return ret;
}

static int append_ascii_cstr(uint8_t *out, int out_len, int *off, const char *text){
	int ret = 0;

	if (text == NULL) {
		return ret;
	}
	for (int i = 0; text[i]; i++) {
		append_ascii_byte(out, out_len, off, (uint8_t)text[i]);
	}
	ret = 1;
	return ret;
}

static int append_dec_u32(uint8_t *out, int out_len, int *off, int value){
	int ret = 0;
	int len = 0;
	uint8_t tmp[10] = {};

	do {
		tmp[len++] = (uint8_t)(48 + (value % 10));
		value /= 10;
	}while (value && len < sizeof(tmp));
		while (len) {
			append_ascii_byte(out, out_len, off, tmp[--len]);
		}
	ret = 1;
	return ret;
}

static int append_hex_u32(uint8_t *out, int out_len, int *off, int value, int width){
	int ret = 0;
	int shift = 0;

	if (width == 0 || width > 8 || out_len - *off < width) {
		return ret;
	}
	for (int i = 0; i < width; i++) {
		shift = (width - 1 - i) * 4;
		out[(*off)++] = hex_digit_u4(value >> shift);
	}
	ret = 1;
	return ret;
}

static int append_hex_byte(uint8_t *out, int out_len, int *off, int value){
	int ret = 0;

	ret = append_ascii_byte(out, out_len, off, hex_digit_u4(value >> 4)) && append_ascii_byte(out, out_len, off, hex_digit_u4(value));
	return ret;
}

int aic8800_format_hex_u32(uint8_t *out, int out_len, int value, int width){
	int ret = 0;
	int shift = 0;

	if (!out || width == 0 || width > 8 || out_len < width) {
		return ret;
	}
	for (int i = 0; i < width; i++) {
		shift = (width - 1 - i) * 4;
		out[i] = hex_digit_u4(value >> shift);
	}
	ret = width;
	return ret;
}

int aic8800_format_mac(uint8_t *out, int out_len, const uint8_t *mac, int mac_len){
	int ret = 0;
	int off = 0;

	if (!out || !mac || mac_len < ETH_ALEN || out_len < 17) {
		return ret;
	}
	for (int i = 0; i < ETH_ALEN; i++) {
		append_hex_byte(out, out_len, &off, mac[i]);
		if (i + 1 < ETH_ALEN) {
			append_ascii_byte(out, out_len, &off, ':');
		}
	}
	ret = off;
	return ret;
}

int aic8800_format_hex_preview(uint8_t *out, int out_len, const uint8_t *bytes, int bytes_len){
	int ret = 0;
	int off = 0;
	int needed = 0;

	if (!out || (!bytes && bytes_len)) {
		return ret;
	}
	if (bytes_len == 0) {
		return ret;
	}
	needed = bytes_len * 3 - 1;
	if (out_len < needed) {
		return ret;
	}
	for (int i = 0; i < bytes_len; i++) {
		append_hex_byte(out, out_len, &off, bytes[i]);
		if (i + 1 < bytes_len) {
			append_ascii_byte(out, out_len, &off, ' ');
		}
	}
	ret = off;
	return ret;
}

int aic8800_format_hexdump(uint8_t *out, int out_len, const uint8_t *bytes, int bytes_len){
	int ret = 0;
	int off = 0;
	int rows = 0;
	int needed = 0;
	int hex_start = 0;
	int chunk_len = 0;
	uint8_t c = 0;

	if (!out || (!bytes && bytes_len)) {
		return ret;
	}
	if (bytes_len == 0) {
		ret = write_ascii_string(out, out_len, "0000  <empty>");
		return ret;
	}
	rows = (bytes_len + 15) / 16;
	needed = rows * 73 + rows - 1;
	if (out_len < needed) {
		return ret;
	}
	for (int row = 0; row < bytes_len; row += 16) {
		if (row) {
			append_ascii_byte(out, out_len, &off, '\n');
		}
		if (out_len - off < 4) {
			return ret;
		}
		aic8800_format_hex_u32(out + off, out_len - off, row & 0xffff, 4);
		off += 4;
		append_ascii_byte(out, out_len, &off, ' ');
		append_ascii_byte(out, out_len, &off, ' ');
		chunk_len = bytes_len - row;
		if (chunk_len > 16) {
			chunk_len = 16;
		}
		hex_start = off;
		for (int i = 0; i < chunk_len; i++) {
			append_hex_byte(out, out_len, &off, bytes[row + i]);
			if (i + 1 < chunk_len) {
				append_ascii_byte(out, out_len, &off, ' ');
			}
		}
		while (off - hex_start < 47) {
			append_ascii_byte(out, out_len, &off, ' ');
		}
		append_ascii_byte(out, out_len, &off, ' ');
		append_ascii_byte(out, out_len, &off, ' ');
		append_ascii_byte(out, out_len, &off, '|');
		for (int i = 0; i < chunk_len; i++) {
			c = bytes[row + i];
			append_ascii_byte(out, out_len, &off, (c >= 0x20 && c <= 0x7eu) ? c : '.');
		}
		append_ascii_byte(out, out_len, &off, '|');
		if (off > out_len) {
			return ret;
		}
	}
	ret = off;
	return ret;
}

int aic8800_format_ascii_preview(uint8_t *out, int out_len, const uint8_t *bytes, int bytes_len, int width){
	int ret = 0;
	uint8_t c = 0;

	if (!out || (!bytes && bytes_len) || out_len < width) {
		return ret;
	}
	for (int i = 0; i < width; i++) {
		if (i >= bytes_len) {
			out[i] = 32;
		}else{
			c = bytes[i];
			out[i] = (c >= 0x20 && c <= 0x7eu) ? c : 46;
		}
	}
	ret = width;
	return ret;
}

/* aic8800_usb_is_known_vendor: always select the aic8800 usb vendor 0xa69c */
int aic8800_usb_is_known_vendor(int vendor_id){
	return vendor_id == 0xa69c;
}

/* aic8800_usb_is_storage_product: known SCSI/storage bootstrap product IDs */
int aic8800_usb_is_storage_product(int product_id){
	return product_id == 0x1111 || product_id == 0x5721 ||
		product_id == 0x5723 || product_id == 0x5725;
}

/* aic8800_usb_is_rom_product: for now the only ROM mode known is the one of the aic8800d80 */
int aic8800_usb_is_rom_product(int product_id){
	return product_id == 0x8d80;
}

int aic8800_usb_device_mode_code(int vendor_id, int product_id){
	int ret = 0;

	if (!aic8800_usb_is_known_vendor(vendor_id)) {
		ret = AIC_USB_MODE_UNKNOWN;
		return ret;
	}
	if (aic8800_usb_is_storage_product(product_id)) {
		ret = AIC_USB_MODE_STORAGE;
		return ret;
	}
	if (aic8800_usb_is_rom_product(product_id)) {
		ret = AIC_USB_MODE_ROM;
		return ret;
	}
	ret = AIC_USB_MODE_RAM;
	return ret;
}

int aic8800_usb_device_mode_string(uint8_t *out, int out_len, int vendor_id, int product_id){
	int ret = 0;

	switch (aic8800_usb_device_mode_code(vendor_id, product_id)) {
		case AIC_USB_MODE_STORAGE:
			ret = write_ascii_string(out, out_len, "SCSI/storage");
			break;
		case AIC_USB_MODE_ROM:
			ret = write_ascii_string(out, out_len, "rom");
			break;
		case AIC_USB_MODE_RAM:
			ret = write_ascii_string(out, out_len, "ram");
			break;
		default:
			ret = write_ascii_string(out, out_len, "unknown");
			break;
	}
	return ret;
}

int aic8800_usb_mode_matches(int vendor_id, int product_id, const uint8_t *preferred, int preferred_len){
	int ret = 0;
	int code = 0;

	if (!preferred || preferred_len == 0 || clean_match(preferred, preferred_len, "any")) {
		ret = 1;
		return ret;
	}
	code = aic8800_usb_device_mode_code(vendor_id, product_id);
	if (code == AIC_USB_MODE_STORAGE) {
		ret = clean_match(preferred, preferred_len, "storage") || clean_match(preferred, preferred_len, "scsistorage");
		return ret;
	}
	if (code == AIC_USB_MODE_ROM) {
		ret = clean_match(preferred, preferred_len, "rom");
		return ret;
	}
	if (code == AIC_USB_MODE_RAM) {
		ret = clean_match(preferred, preferred_len, "ram");
		return ret;
	}
	ret = clean_match(preferred, preferred_len, "unknown");
	return ret;
}

/* aic8800_usb_device_mode_score: return the current status of the userspace driver, from 20% (storage mode) to 100% RAM mode with owfuzz running */
int aic8800_usb_device_mode_score(int vendor_id, int product_id, const uint8_t *preferred, int preferred_len){
	int ret = 0;
	int code = 0;

	code = aic8800_usb_device_mode_code(vendor_id, product_id);
	if (preferred && preferred_len && !clean_match(preferred, preferred_len, "any") && aic8800_usb_mode_matches(vendor_id, product_id, preferred, preferred_len)) {
		ret = 100;
		return ret;
	}
	if (code == AIC_USB_MODE_RAM) {
		ret = 60;
		return ret;
	}
	if (code == AIC_USB_MODE_ROM) {
		ret = 40;
		return ret;
	}
	if (code == AIC_USB_MODE_STORAGE) {
		ret = 20;
		return ret;
	}
	return ret;
}

int aic8800_usb_is_vendor_alternate(int iface_class, int iface_subclass, int iface_protocol){
	return iface_class == 0xffu && iface_subclass == 0xffu && iface_protocol == 0xffu;
}

int aic8800_usb_interface_score(int iface_class, int iface_subclass, int iface_protocol, int in_count, int out_count, int prefer_storage){
	int ret = 0;
	int storage_iface = 0;
	int vendor_iface = 0;

	if (out_count == 0) {
		return ret;
	}
	if (iface_class == 0x08 ||
		(prefer_storage && iface_class == 0xffu &&
		 iface_subclass == 0x06u && iface_protocol == 0x50u)) {
		storage_iface = true;
	}
	vendor_iface = aic8800_usb_is_vendor_alternate(iface_class, iface_subclass, iface_protocol);
	if (storage_iface && !prefer_storage) {
		return ret;
	}
	if (!vendor_iface && !storage_iface) {
		return ret;
	}
	ret = (vendor_iface ? 80 : storage_iface ? 10 : 0) + in_count * 4 + out_count;
	return ret;
}

int aic8800_usb_product_name(uint8_t *out, int out_len, int product_id){
	int ret = 0;

	switch (product_id) {
		case 0x5721:
			ret = write_ascii_string(out, out_len, "AIC storage");
			break;
		case 0x5723:
			ret = write_ascii_string(out, out_len, "AIC D80 storage bootstrap");
			break;
		case 0x5725:
			ret = write_ascii_string(out, out_len, "AIC storage/ROM");
			break;
		case 0x8800:
			ret = write_ascii_string(out, out_len, "AIC8800");
			break;
		case 0x8801:
			ret = write_ascii_string(out, out_len, "AIC8801");
			break;
		case 0x88dc:
			ret = write_ascii_string(out, out_len, "AIC8800DC");
			break;
		case 0x88dd:
			ret = write_ascii_string(out, out_len, "AIC8800DW");
			break;
		case 0x88df:
			ret = write_ascii_string(out, out_len, "AIC8800FC CUS1");
			break;
		case 0x88e0:
			ret = write_ascii_string(out, out_len, "AIC8800FC CUS2");
			break;
		case 0x88e1:
			ret = write_ascii_string(out, out_len, "AIC8800FC CUS3");
			break;
		case 0x88e2:
			ret = write_ascii_string(out, out_len, "AIC8800FC CUS4");
			break;
		case 0x88e3:
			ret = write_ascii_string(out, out_len, "AIC8800FC CUS5");
			break;
		case 0x88e5:
			ret = write_ascii_string(out, out_len, "AIC8800FC CUS6");
			break;
		case 0x8d40:
			ret = write_ascii_string(out, out_len, "AIC8800D40");
			break;
		case 0x8d41:
			ret = write_ascii_string(out, out_len, "AIC8800D41");
			break;
		case 0x8d80:
			ret = write_ascii_string(out, out_len, "AIC8800D80 ROM");
			break;
		case 0x8d81:
			ret = write_ascii_string(out, out_len, "AIC8800D81");
			break;
		case 0x8d83:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS1");
			break;
		case 0x8d85:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS2");
			break;
		case 0x8d86:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS3");
			break;
		case 0x8d88:
			ret = write_ascii_string(out, out_len, "AIC8800D80 UGREEN");
			break;
		case 0x8d89:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS4");
			break;
		case 0x8d8a:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS5");
			break;
		case 0x8d8b:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS7");
			break;
		case 0x8d8c:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS6");
			break;
		case 0x8d8d:
			ret = write_ascii_string(out, out_len, "AIC8800M80 CUS8");
			break;
		case 0x8d90:
			ret = write_ascii_string(out, out_len, "AIC8800D80X2");
			break;
		case 0x8d91:
			ret = write_ascii_string(out, out_len, "AIC8800D81X2");
			break;
		case 0x8d99:
			ret = write_ascii_string(out, out_len, "AIC8800D89X2");
			break;
		case 0x0013:
			ret = write_ascii_string(out, out_len, "Tenda AIC8800");
			break;
		case 0x0014:
			ret = write_ascii_string(out, out_len, "Tenda U2");
			break;
		case 0x001f:
			ret = write_ascii_string(out, out_len, "Tenda U11");
			break;
		case 0x0020:
			ret = write_ascii_string(out, out_len, "Tenda AIC 8800D80");
			break;
		case 0x0110:
			ret = write_ascii_string(out, out_len, "Tenda TX1U Nano");
			break;
		case 0x014b:
			ret = write_ascii_string(out, out_len, "Mercury");
			break;
		default:
			ret = 0;
			break;
	}
	return ret;
}

/* aic8800_default_mac: get the default mac address of aic8800, in general it is retrieved from the efuse */
int aic8800_default_mac(uint8_t *out, int out_len){
	int ret = 0;
	static const uint8_t mac[ETH_ALEN] = {0x88, 0x00, 0x33, 0x77, 0x10, 0x99};

	if (!out || out_len < ETH_ALEN) {
		return ret;
	}
	memcpy(out, mac, ETH_ALEN);
	ret = ETH_ALEN;
	return ret;
}

/* aic8800_build_scsi_switch_command: get the SCSI switch command for entering in ROM mode */
int aic8800_build_scsi_switch_command(uint8_t *out, int out_len){
	int ret = 0;
	/* our special SCSI command */
	static const uint8_t cmd[32] = {
	        0x55,0x53,0x42,0x43,0x12,0x34,0x56,0x78,
	        0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x1bu,
	        0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
	        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	};
	if (!out || out_len < sizeof(cmd)) {
		return ret;
	}
	memcpy(out, cmd, sizeof(cmd));
	return sizeof(cmd);
}

int aic8800_start_app_boot_type(void){
	int ret = 0;

	ret = true;
	return ret;
}

int aic8800_max_block_write(void){
	int ret = 0;

	/* remember that 'AIC_MAX_BLOCK_WRITE' must be a multiple of '4' */
	ret = AIC_MAX_BLOCK_WRITE;
	return ret;
}

int aic8800_default_patch_source(void){
	int ret = 0;

	return ret;
}

int aic8800_patch_decompile_default_length(void){
	int ret = 0;

	ret = AIC_MAX_DECOMP_SIZE;
	return ret;
}

int aic8800_patch_decompile_max_length(void){
	int ret = 0;

	ret = AIC_MAX_DECOMP_SIZE;
	return ret;
}

/* aic8800_patch_script_count: returns the number of available patches, needs to be updated for every new patch */
int aic8800_patch_script_count(void){
	int ret = 0;

	ret = 5;
	return ret;
}

/* aic8800_patch_script_name: this function permits to visualize the names of the patches available in the WebUSB driver */
int aic8800_patch_script_name(uint8_t *out, int out_len, int index){
	int ret = 0;

	if (index == 0) {
		ret = write_ascii_string(out, out_len, "beacon frames");
	}
	if (index == 1) {
		ret = write_ascii_string(out, out_len, "empty test");
	}
	if (index == 2) {
		ret = write_ascii_string(out, out_len, "iq dump");
	}
	if (index == 3) {
		ret = write_ascii_string(out, out_len, "deauth frames");
	}
	if (index == 4) {
		ret = write_ascii_string(out, out_len, "low level tx");
	}
	return ret;
}

/* aic8800_patch_script_source: given the patch index as input, returns the respective patch text, still need to find a solution for storing the patch in a text file instead of hardcoding them here */
int aic8800_patch_script_source(uint8_t *out, int out_len, int index){
	int ret = 0;

	if (index == 0) {
		ret = write_ascii_string(out, out_len,
				"#include \"aic8800d80.h\"\n"
				"#define ETTORE_BEACON_LEN 69\n"
				"#define AIC_TXL_FRAME_BUFFER_OFT 0x48\n"
				"#define AIC_TXL_BUFFER_PAYLOAD_OFT 0x6c\n"
				"extern const u8 ettore_beacon[];\n\n"
				"int patch_entry(ke_msg_id_t msgid, struct dbg_start_npc_req *param, ke_task_id_t dest_id,  ke_task_id_t src_id){\n"
				"    int ret = 0;\n"
				"    struct txl_buffer_tag *buf = NULL;\n"
				"    struct txl_frame_desc_tag *f = NULL;\n\n"
				"    f = txl_frame_get(TX_DEFAULT_24G, ETTORE_BEACON_LEN);\n"
				"    if (f == NULL) {\n"
				"        return ret;\n"
				"    }\n"
				"    buf = *(struct txl_buffer_tag **)((u8 *)f + AIC_TXL_FRAME_BUFFER_OFT);\n"
				"    if (buf == NULL) {\n"
				"        return ret;\n"
				"    }\n"
				"    memcpy((u8 *)buf + AIC_TXL_BUFFER_PAYLOAD_OFT, ettore_beacon, ETTORE_BEACON_LEN);\n"
				"    f->txdesc.host.vif_idx = 0;\n"
				"    f->txdesc.host.staid  = 0xff;\n"
				"    txl_frame_push(f, AC_VO);\n"
				"    return 0;\n"
				"}\n\n"
				"__attribute__((section(\".text\"))) const u8 ettore_beacon[] = {\n"
				"    /* Beacon frame control + duration */\n"
				"    0x80, 0x00, 0x00, 0x00,\n"
				"    /* Destination: broadcast */\n"
				"    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,\n"
				"    /* Source address */\n"
				"    0x02, 0x11, 0x22, 0x33, 0x44, 0x55,\n"
				"    /* BSSID */\n"
				"    0x02, 0x11, 0x22, 0x33, 0x44, 0x55,\n"
				"    /* Sequence control */\n"
				"    0x00, 0x00,\n"
				"    /* Timestamp, beacon interval 100 TU, ESS + short slot */\n"
				"    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\n"
				"    0x64, 0x00, 0x01, 0x04,\n"
				"    /* SSID: ETTORE */\n"
				"    0x00, 0x06, 0x45, 0x54, 0x54, 0x4f, 0x52, 0x45,\n"
				"    /* Supported rates */\n"
				"    0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24,\n"
				"    /* DS parameter set: channel 1 marker */\n"
				"    0x03, 0x06, 0x01,\n"
				"    /* TIM: empty bitmap */\n"
				"    0x05, 0x04, 0x00, 0x01, 0x00, 0x00,\n"
				"    /* Extended supported rates */\n"
				"    0x32, 0x04, 0x30, 0x48, 0x60, 0x6c\n"
				"};\n\n");
	}
	if (index == 1) {
		ret = write_ascii_string(out, out_len,
				"#include \"aic8800d80.h\"\n\n"
				"int patch_entry(ke_msg_id_t msgid, struct dbg_start_npc_req *param, ke_task_id_t dest_id, ke_task_id_t src_id){\n"
				"    return 0;\n"
				"}\n\n");
	}
	if (index == 2) {
		ret = write_ascii_string(out, out_len,
				"#include \"aic8800d80.h\"\n\n"
				"\/* DUMP_ADC\n"
				" * DUMP_RX_DATA\n"
				" * DUMP_RC_ADC\n"
				" * DUMP_DCCANCEL\n"
				" * DUMP_PRE_DGC\n"
				" * DUMP_NOTCH\n"
				" * DUMP_RC_IN\n"
				" * DUMP_RC_OUT\n"
				" */\n\n"
				"static inline void aic8800_fw_delay(int n) {\n"
				"    volatile int i = 0;\n"
				"    volatile int j = 0;\n"
				"    for (i = 0; i < n; i++)"
				"        for (j = 0; j < 0x20; j++);\n"
				"}\n\n"
				"int patch_entry(ke_msg_id_t msgid, struct dbg_start_npc_req *param, ke_task_id_t dest_id, ke_task_id_t src_id){\n"
				"    int ret = 0;\n"
				"    ret = rx_low_level_dump(DUMP_ADC);\n"
				"    aic8800_fw_delay(500);\n"
				"    rx_low_level_get_data();\n"
				"    return ret;\n"
				"}\n"
				);
	}
	/* deauthentication test, taken from bk72xx Wi-Fi sdk */
	if (index == 3) {
		ret = write_ascii_string(out, out_len,
				"#include \"aic8800d80.h\"\n"
				"#define DEAUTH_REASON 7\n"
				"#define SET_MAC_BCAST(_addr) do { (_addr).array[0] = 0xFFFF; (_addr).array[1] = 0xFFFF; (_addr).array[2] = 0xFFFF; } while (0)\n\n"
				"int patch_entry(ke_msg_id_t msgid, struct dbg_start_npc_req *param, ke_task_id_t dest_id, ke_task_id_t src_id){\n"
				"    int ret = 0;\n"
				"    int txtype = 0;\n"
				"    u32 ssid_addr = 0;\n"
				"    struct preq_frame *buf = NULL;\n"
				"    struct txl_frame_desc_tag *frame = NULL;\n\n"
				"    txtype = TX_DEFAULT_24G;\n"
				"    for (int i = 0; i < 5; i++){\n"
				"    // Chose the right rate according to the band\n"
				"    // Allocate a frame descriptor from the TX path\n"
				"    frame = txl_frame_get(txtype, 26);\n"
				"    if (frame == NULL){\n"
				"        break;\n"
				"    }\n"
				"    // Get the buffer pointer\n"
				"    #if NX_AMSDU_TX\n"
				"    buf = (struct preq_frame *)frame->txdesc.lmac.buffer[0]->payload;\n"
				"    #else\n"
				"    buf = (struct preq_frame *)frame->txdesc.lmac.buffer->payload;\n"
				"    #endif\n"
				"    // Prepare the MAC Header\n"
				"    buf->h.fctl = MAC_FCTRL_DEAUTHENT;\n"
				"    buf->h.durid = 0;\n"
				"    SET_MAC_BCAST(buf->h.addr1);  // broadcast\n"
				"    SET_MAC_BCAST(buf->h.addr2);\n"
				"    SET_MAC_BCAST(buf->h.addr3);\n"
				"    buf->h.seq = 0;\n"
				"    ssid_addr = (u32)buf->payload;\n"
				"    co_write8p(ssid_addr++, DEAUTH_REASON);   // reason\n"
				"    co_write8p(ssid_addr++, 0);\n"
				"    frame->cfm.cfm_func = NULL;\n"
				"    frame->cfm.env = NULL;\n"
				"    #if (NX_CHNL_CTXT || NX_P2P)\n"
				"        // Set VIF and STA indexes\n"
				"        frame->txdesc.host.vif_idx = 0;\n"
				"        frame->txdesc.host.staid   = 0xFF;\n"
				"    #endif // (NX_CHNL_CTXT || NX_P2P)\n"
				"    // Push the frame for TX\n"
				"    txl_frame_push(frame, AC_VO);\n"
				"    }\n"
				"    return ret;\n"
				"}\n"
				);
	}
	/* lower level way for transmitting a frame */
	if(index == 4){
		ret = write_ascii_string(out, out_len,
			"#include \"aic8800d80.h\"\n"
			"#ifndef KE_MSG_CONSUMED\n"
			"#define KE_MSG_CONSUMED 0\n"
			"#endif\n"
			"#define R(a)    (*(volatile u32 *)(a))\n"
			"#define W(a,v)  (*(volatile u32 *)(a) = (v))\n"
			"#define U(p)    ((u32)(p))\n"
			"#define DMA_STATUS1     0x40328188\n"
			"#define AC3_HEAD        0x403281a8\n"
			"#define DMA_CONTROL     0x40328180\n"
			"#define AC3_STATE_MASK  0x00030000\n"
			"#define AC3_BUSY        0x00020000\n"
			"#define AC3_NEW_HEAD    0x00001000\n"
			"#define DONE            0x80000000\n"
			"#define WAIT            0xffff\n"
			"#define FRAME_LEN       69\n\n"
			"int patch_entry(ke_msg_id_t msgid, struct dbg_start_npc_req *param, ke_task_id_t dest_id, ke_task_id_t src_id) {\n"
			"    volatile u32 thd[17];\n"
			"    volatile u32 pol[13];\n"
			"    volatile u32 frm[18];\n"
			"    for (i = 17; i; i--) {\n"
			"        thd[i - 1] = 0;\n"
			"        if (i <= 13){\n"
			"            pol[i - 1] = 0;\n"
			"        }\n"
			"    }\n"
			"    frm[0]  = 0x00000080;\n"
			"    frm[1]  = 0xffffffff;\n"
			"    frm[2]  = 0x1102ffff;\n"
			"    frm[3]  = 0x55443322;\n"
			"    frm[4]  = 0x33221102;\n"
			"    frm[5]  = 0x00005544;\n"
			"    frm[6]  = 0x00000000;\n"
			"    frm[7]  = 0x00000000;\n"
			"    frm[8]  = 0x04010064;\n"
			"    frm[9]  = 0x54450600;\n"
			"    frm[10] = 0x45524f54;\n"
			"    frm[11] = 0x84820801;\n"
			"    frm[12] = 0x120c968b;\n"
			"    frm[13] = 0x01032418;\n"
			"    frm[14] = 0x00040501;\n"
			"    frm[15] = 0x32000001;\n"
			"    frm[16] = 0x60483004;\n"
			"    frm[17] = 0x0000006c;\n"
			"    pol[0] = 0xBADCAB1E;\n"
			"    pol[2] = 1;\n"
			"    pol[4] = 0xffff0704;\n"
			"    pol[5] = 0x400;\n"
			"    pol[9] = 0x0404;\n"
			"    thd[0] = 0xCAFEBABE;\n"
			"    thd[4] = U(frm);\n"
			"    thd[5] = U(((u8 *)frm) + FRAME_LEN - 1);\n"
			"    thd[6] = FRAME_LEN + 4;\n"
			"    thd[9] = U(pol);\n"
			"    for (i = WAIT; i && ((R(DMA_STATUS1) & AC3_STATE_MASK) == AC3_BUSY); i--){\n"
			"        ;\n"
			"    }\n"
			"    if (i) {\n"
			"        W(AC3_HEAD, U(thd));\n"
			"        W(DMA_CONTROL, AC3_NEW_HEAD);\n"
			"        for (i = WAIT; i && !(thd[15] & DONE); i--){\n"
			"            ;\n"
			"        }\n"
			"    }\n"
			"    return KE_MSG_CONSUMED;\n"
			"}\n"
		);
	}
	return ret;
}

int aic8800_format_endpoint(uint8_t *out, int out_len, int endpoint_number, int is_in, int present){
	int ret = 0;
	int off = 0;
	int address = 0;

	if (out == NULL) {
		return ret;
	}
	if (present == false) {
		ret = write_ascii_string(out, out_len, "-");
		return ret;
	}

	address = is_in ? (endpoint_number | 0x80) : endpoint_number;
	append_ascii_cstr(out, out_len, &off, "0x");
	append_hex_u32(out, out_len, &off, address, 2);
	append_ascii_cstr(out, out_len, &off, is_in ? " (in)" : " (out)");
	ret = off;
	return ret;
}

int aic8800_rx_frame_offset(int block_len){
	int ret = 0;

	if(block_len >= RX_HWHRD_LEN){
		ret = RX_HWHRD_LEN;
	}
	return ret;
}

/* aic8800_rx_classify_record: used in the early RX loop in js code for filtering the frames type */
int aic8800_rx_classify_record(uint8_t *meta, int meta_len, int record_type, int record_cfg, int monitor_mode){
	int ret = 0;
	int event = 0;
	int clean_type = 0;

	if (meta == NULL || meta_len < 8) {
		return ret;
	}
	memset(meta, 0, meta_len);
	clean_type = record_type & 0x7fu;
	event = AIC_RX_EVENT_NONE;
	if (record_cfg) {
 		if (clean_type == USB_TYPE_CFG_CMD_RSP) {
			event = AIC_RX_EVENT_CFG_CMD_RSP;
		}else if (clean_type == USB_TYPE_CFG_PRINT) {
			event = AIC_RX_EVENT_CFG_PRINT;
		}else{
			event = AIC_RX_EVENT_CFG_OTHER;
		}
	}else{
		event = monitor_mode ? AIC_RX_EVENT_MONITOR_DATA : AIC_RX_EVENT_STA_DATA;
	}
	put_u32_le(meta, 0, event);
	meta[4] = (uint8_t)clean_type;
	meta[5] = record_cfg ? 1 : 0;
	meta[6] = monitor_mode ? 1 : 0;
	ret = 1;
	return ret;
}

int aic8800_owfuzz_tick_decision(uint8_t *meta, int meta_len, int running, int count, int sent, int tx_busy, int interval_ms){
	int ret = 0;
	int delay = 0;
	int action = 0;

	if (meta == NULL || meta_len < 8) {
		return ret;
	}
	memset(meta, 0, meta_len);
	action = AIC_OWFUZZ_TICK_IDLE;
	delay = 0;
	if (!running) {
		action = AIC_OWFUZZ_TICK_IDLE;
	}else if (count > 0 && sent >= count) {
		action = AIC_OWFUZZ_TICK_COMPLETE;
	}else if (tx_busy) {
		action = AIC_OWFUZZ_TICK_BUSY;
		delay = interval_ms;
	}else{
		action = AIC_OWFUZZ_TICK_SEND;
	}
	put_u32_le(meta, 0, action);
	put_u32_le(meta, 4, delay);
	ret = 1;
	return ret;
}

int aic8800_owfuzz_should_log_tx(int sent_after, int log_every){
	int ret = 0;

	if(sent_after == 1 || (log_every > 0 && (sent_after % log_every) == 0)){
		ret = 1;
	}
	return ret;
}

int aic8800_owfuzz_capture_log_needed(int captured_after){
	int ret = 0;

	if(captured_after <= 6 || ((captured_after % 8) == 0)){
		ret = 1;
	}
	return ret;
}

int aic8800_owfuzz_template_key(uint8_t *out, int out_len, const uint8_t *frame, int frame_len){
	int ret = 0;
	int off = 0;

	if (out == NULL || !frame || frame_len < 10) {
		return ret;
	}
	append_hex_u32(out, out_len, &off, frame[0] & 0xfc, 2);
	append_ascii_byte(out, out_len, &off, (uint8_t)':');
	append_dec_u32(out, out_len, &off, frame_len);
	ret = off;
	return ret;
}

int aic8800_owfuzz_template_meta(uint8_t *meta, int meta_len, const uint8_t *frame, int frame_len, int capture_enabled, int captured_count, int capture_max){
	int ret = 0;
	int captured_after = 0;

	if (meta == NULL || meta_len < 16) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (capture_enabled == 0 || frame == NULL || frame_len < 10 || captured_count >= capture_max) {
		ret = 1;
		return ret;
	}
	captured_after = captured_count + 1;
	meta[0] = 1;
	meta[1] = (uint8_t)(frame[0] & 0xfcu);
	meta[2] = (uint8_t)aic8800_owfuzz_capture_log_needed(captured_after);
	put_u32_le(meta, 4, frame_len);
	put_u32_le(meta, 8, captured_after);
	ret = 1;
	return ret;
}

static int append_mac_text(uint8_t *out, int out_len, int *off, const uint8_t *mac, int mac_len){
	int ret = 0;

	if (!mac || mac_len < ETH_ALEN) {
		ret = append_ascii_cstr(out, out_len, off, "??:??:??:??:??:??");
		return ret;
	}
	for (int i = 0; i < ETH_ALEN; i++) {
		append_hex_byte(out, out_len, off, mac[i]);
		if (i + 1 < ETH_ALEN && !append_ascii_byte(out, out_len, off, (uint8_t)':')) {
			return ret;
		}
	}
	ret = 1;
	return ret;
}

int aic8800_owfuzz_status(uint8_t *out, int out_len, int running, const uint8_t *profile, int profile_len, int sent, int captured, const uint8_t *target, int target_len, const uint8_t *bssid, int bssid_len, int interval_ms){
	int ret = 0;
	int off = 0;

	if (out == NULL) {
		return ret;
	}
	append_ascii_cstr(out, out_len, &off, "fuzz: ");
	append_ascii_cstr(out, out_len, &off, running ? "running" : "idle");
	append_ascii_cstr(out, out_len, &off, " profile=");
	if (profile && profile_len) {
 		for (int i = 0; i < profile_len; i++) {
			append_ascii_byte(out, out_len, &off, profile[i]);
		}
	}

	append_ascii_cstr(out, out_len, &off, " sent=");
	append_dec_u32(out, out_len, &off, sent);
	append_ascii_cstr(out, out_len, &off, " captured=");
	append_dec_u32(out, out_len, &off, captured);
	append_ascii_cstr(out, out_len, &off, " target=");
	append_mac_text(out, out_len, &off, target, target_len);
	append_ascii_cstr(out, out_len, &off, " bssid=");
	append_mac_text(out, out_len, &off, bssid, bssid_len);
	ret = off;
	return ret;
}

int aic8800_format_memory_preview(uint8_t *out, int out_len, const uint8_t *bytes, int bytes_len, int address, int entry_offset, int include_entry){
	int ret = 0;
	int off = 0;
	int chunk_len = 0;
	int hex_start = 0;
	uint8_t c = 0;

	if (out == NULL || (!bytes && bytes_len)) {
		return ret;
	}
	append_ascii_cstr(out, out_len, &off, "base  0x");
	append_hex_u32(out, out_len, &off, address, 8);
	append_ascii_byte(out, out_len, &off, 10);
	if (include_entry) {
		append_ascii_cstr(out, out_len, &off, "entry 0x");
		append_hex_u32(out, out_len, &off, address + entry_offset, 8);
		append_ascii_byte(out, out_len, &off, 10);
	}
	append_ascii_cstr(out, out_len, &off, "size  ");
	append_dec_u32(out, out_len, &off, bytes_len);
	append_ascii_cstr(out, out_len, &off, " bytes");
	append_ascii_byte(out, out_len, &off, 10);
	append_ascii_byte(out, out_len, &off, 10);
	for (int row = 0; row < bytes_len; row += 16) {
		if (row && !append_ascii_byte(out, out_len, &off, 10)) {
			return ret;
		}
		append_hex_u32(out, out_len, &off, address + row, 8);
		append_ascii_cstr(out, out_len, &off, "  ");
		chunk_len = bytes_len - row;
		if (chunk_len > 16) {
			chunk_len = 16;
		}
		hex_start = off;
		for (int i = 0; i < chunk_len; i++) {
			append_hex_byte(out, out_len, &off, bytes[row + i]);
			if (i + 1 < chunk_len && !append_ascii_byte(out, out_len, &off, 32)) {
				return ret;
			}
		}
		while (off - hex_start < 47) {
			if (!append_ascii_byte(out, out_len, &off, 32)) {
				return ret;
			}
		}
		if (!append_ascii_cstr(out, out_len, &off, "  |")) {
			return ret;
		}
		for (int i = 0; i < chunk_len; i++) {
			c = bytes[row + i];
			if (!append_ascii_byte(out, out_len, &off, (c >= 0x20 && c <= 0x7eu) ? c : 46)) {
				return ret;
			}
		}
		if (!append_ascii_byte(out, out_len, &off, 124)) {
			return ret;
		}
	}
	ret = off;
	return ret;
}

static uint8_t aic8800_ascii_lower(uint8_t c){
	if(c >= 65 && c <= 90){
		return (uint8_t)(c + 32);
	}else{
		return c;
	}
}

static bool skip_name_byte(uint8_t c){
	if(c == 32 || c == 9 || c == 10 || c == 13 || c == 12 || c == 11 || c == 95 || c == 45){
		return true;
	}else{
		return false;
	}
}

static int clean_match(const uint8_t *text, int len, const char *name){
	int ret = 0;
	int ti = 0;
	int ni = 0;
	uint8_t c = 0;

	if (!text || !name) {
		return ret;
	}
	while (ti < len) {
		c = text[ti++];
		if (skip_name_byte(c)) {
			continue;
		}
		c = aic8800_ascii_lower(c);
		if ((u8)name[ni] == 0 || c != (u8)name[ni]) {
			return ret;
		}
		ni++;
	}
	ret = (name[ni] == 0) ? 1 : 0;
	return ret;
}

/* owfuzz_lookup_frame_type: given the frame name, return the frame ID if available */
static int owfuzz_lookup_frame_type(const uint8_t *text, int len, int *type){
	int ret = 0;

	for (int i = 0; i < sizeof(owfuzz_frame_names) / sizeof(owfuzz_frame_names[0]); i++) {
		if (clean_match(text, len, owfuzz_frame_names[i].name)) {
			*type = owfuzz_frame_names[i].type;
			ret = 1;
			return ret;
		}
	}
	return ret;
}

int aic8800_owfuzz_canonical_frame_type(const uint8_t *text, int len){
	int ret = 0;
	int type = 0;

	ret = owfuzz_lookup_frame_type(text, len, &type) ? type : 0xffffffffu;
	return ret;
}

int aic8800_owfuzz_is_captured_profile(const uint8_t *text, int len){
	int ret = 0;

	ret = clean_match(text, len, "captured") || clean_match(text, len, "capture") || clean_match(text, len, "poc");
	return ret;
}

static int owfuzz_profile_select(const uint8_t *text, int len, const uint8_t **types, int *count){
	int ret = 0;

	if (clean_match(text, len, "management")){
		*types = owfuzz_profile_management;
		*count = sizeof(owfuzz_profile_management);
		ret = 1;
		return ret;
	}
	if (clean_match(text, len, "sta")){
		*types = owfuzz_profile_sta;
		*count = sizeof(owfuzz_profile_sta);
		ret = 1;
		return ret;
	}
	if (clean_match(text, len, "ap")){
		*types = owfuzz_profile_ap;
		*count = sizeof(owfuzz_profile_ap);
		ret = 1;
		return ret;
	}
	if (clean_match(text, len, "p2p")){
		*types = owfuzz_profile_p2p;
		*count = sizeof(owfuzz_profile_p2p);
		ret = 1;
		return ret;
	}
	if (clean_match(text, len, "control")){
		*types = owfuzz_profile_control;
		*count = sizeof(owfuzz_profile_control);
		ret = 1;
		return ret;
	}
	if (clean_match(text, len, "data")){
		*types = owfuzz_profile_data;
		*count = sizeof(owfuzz_profile_data);
		ret = 1;
		return ret;
	}
	if (clean_match(text, len, "all")){
		*types = owfuzz_profile_all;
		*count = sizeof(owfuzz_profile_all);
		ret = 1;
		return ret;
	}
	return ret;
}

int aic8800_owfuzz_profile_types(const uint8_t *text, int len, uint8_t *out, int out_len){
	int ret = 0;
	int type = 0;
	int count = 0;
	const uint8_t *types = NULL;

	if (out == NULL) {
		return ret;
	}
	if (owfuzz_profile_select(text, len, &types, &count)) {
		if (out_len < count) {
			return ret;
		}
		memcpy(out, types, count);
		ret = count;
		return ret;
	}
	if (owfuzz_lookup_frame_type(text, len, &type)) {
		if (out_len < 1) {
			return ret;
		}
		out[0] = (uint8_t)type;
		ret = 1;
		return ret;
	}
	return ret;
}

int aic8800_owfuzz_looks_hex_payload(const uint8_t *text, int len){
	int ret = 0;
	int digits = 0;
	uint8_t c = 0;

	if (text == NULL) {
		return ret;
	}
	for (int i = 0; i < len; i++) {
		c = text[i];
		if (c == 48 && i + 1 < len && (text[i + 1] == 120 || text[i + 1] == 88)) {
			i++;
			continue;
		}
		if (ascii_space(c) || c == 58 || c == 95 || c == 45) {
			continue;
		}
		if (hex_value(c) < 0) {
			return ret;
		}
		digits++;
	}
	if(digits >= 2 && (digits & 1) == 0){
		ret = 1;
	}
	return ret;
}

int aic8800_owfuzz_parse_bool(const uint8_t *text, int len, int fallback){
	int ret = 0;

	if (!text || len == 0) {
		if(fallback){
			ret = 1;
		}
		return ret;
	}
	ret = clean_match(text, len, "1") || clean_match(text, len, "true") || clean_match(text, len, "yes") || clean_match(text, len, "on");
	return ret;
}

int aic8800_owfuzz_parse_number(const uint8_t *text, int len, uint8_t *meta, int meta_len, int min_value, int max_value){
	int ret = 0;
	int value = 0;

	if (meta == NULL || meta_len < 4) {
		return ret;
	}
	if (!parse_u32_ascii(text, len, &value) || value < min_value || value > max_value) {
		return ret;
	}
	put_u32_le(meta, 0, value);
	ret = 1;
	return ret;
}

static void owfuzz_targets_for_type(int frame_type, int captured, owfuzz_ie_target_set *set){
	if (set == NULL) {
		return;
	}
	memset(set, 0, sizeof(*set));
	switch (frame_type & 0xfc) {
		case 0x80:
			set->ies = owfuzz_ie_beacon;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_beacon);
			set->ext_ies = owfuzz_ext_beacon;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_beacon);
			return;
		case 0x50:
			set->ies = owfuzz_ie_probe_response;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_probe_response);
			set->ext_ies = owfuzz_ext_probe_response;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_probe_response);
			return;
		case 0x40:
			set->ies = owfuzz_ie_probereq;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_probereq);
			set->ext_ies = owfuzz_ext_probereq;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_probereq);
			return;
		case 0x00:
			set->ies = owfuzz_ie_assocreq;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_assocreq);
			set->ext_ies = owfuzz_ext_assocreq;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_assocreq);
			return;
		case 0x20:
			set->ies = owfuzz_ie_reassocreq;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_reassocreq);
			set->ext_ies = owfuzz_ext_reassocreq;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_reassocreq);
			return;
		case 0x10:
			set->ies = owfuzz_ie_assocres;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_assocres);
			set->ext_ies = owfuzz_ext_assocres;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_assocres);
			return;
		case 0x30:
			set->ies = owfuzz_ie_reassocres;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_reassocres);
			set->ext_ies = owfuzz_ext_reassocres;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_reassocres);
			return;
		case 0xb0:
			set->ies = owfuzz_ie_auth;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_auth);
			set->ext_ies = owfuzz_ext_auth;
			set->ext_ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ext_auth);
			return;
		case 0xd0:
		case 0xe0:
			set->ies = owfuzz_ie_action;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_action);
			return;
		case 0x60:
			set->ies = owfuzz_ie_timing;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_timing);
			return;
		case 0x90:
		case 0xa0:
		case 0xc0:
			return;
		default:
			set->ies = owfuzz_ie_default;
			set->ie_count = OWFUZZ_ARRAY_COUNT(owfuzz_ie_default);
			return;
	}
}

static void owfuzz_range_lookup(const owfuzz_ie_range_entry *entries, int count, int id, int *min_value, int *max_value){

	*min_value = 0;
	*max_value = 255;
	for (int i = 0; i < count; i++) {
		if (entries[i].id == (uint8_t)id) {
			*min_value = entries[i].min_len;
			*max_value = entries[i].max_len;
			return;
		}
	}
}

static void owfuzz_ie_range_native(int id, int *min_value, int *max_value){
	owfuzz_range_lookup(owfuzz_ie_ranges2020, OWFUZZ_ARRAY_COUNT(owfuzz_ie_ranges2020), id, min_value, max_value);
}

static void owfuzz_ext_ie_range_native(int ext_id, int *min_value, int *max_value){
	owfuzz_range_lookup(owfuzz_ext_ie_ranges2020, OWFUZZ_ARRAY_COUNT(owfuzz_ext_ie_ranges2020), ext_id, min_value, max_value);
}

int aic8800_owfuzz_mutation_plan(uint8_t *meta, int meta_len, int frame_type, int mutate, int ie_index, int ext_index, int step_index, int value_index, int captured){
	int ret = 0;
	int next_ie = 0;
	int next_ext = 0;
	int min_value = 0;
	int max_value = 0;
	int next_step = 0;
	int next_value = 0;
	int selected_ie = 0;
	int selected_ext = 0;
	int target_count = 0;
	int ext_count = 0;
	owfuzz_ie_target_set target_set = {};

	if (meta == NULL || meta_len < 16) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (mutate == false || (frame_type & 0x0cu) != 0x00) {
		ret = 1;
		return ret;
	}
	owfuzz_targets_for_type(frame_type, captured, &target_set);
	target_count = target_set.ie_count;
	ext_count = target_set.ext_ie_count;
	if (target_set.ies == NULL || target_count == 0) {
		ret = 1;
		return ret;
	}

	ie_index %= target_count;
	if (ie_index < 0) {
		ie_index = 0;
	}
	step_index %= OWFUZZ_ARRAY_COUNT(owfuzz_mutation_steps);
	value_index %= OWFUZZ_ARRAY_COUNT(owfuzz_value_steps);
	selected_ie = target_set.ies[ie_index];
	if (selected_ie == 255 && target_set.ext_ies != NULL && ext_count > 0) {
		ext_index %= ext_count;
		if (ext_index < 0) {
			ext_index = 0;
		}
		selected_ext = target_set.ext_ies[ext_index];
		owfuzz_ext_ie_range_native(selected_ext, &min_value, &max_value);
	}else{
		ext_index = 0;
		owfuzz_ie_range_native(selected_ie, &min_value, &max_value);
	}

	next_value = value_index + 1;
	next_step = step_index;
	next_ie = ie_index;
	next_ext = ext_index;
	if (next_value >= OWFUZZ_ARRAY_COUNT(owfuzz_value_steps)) {
		next_value = 0;
		next_step++;
	}
	if (next_step >= OWFUZZ_ARRAY_COUNT(owfuzz_mutation_steps)) {
		next_step = 0;
		if (selected_ie == 255 && target_set.ext_ies != NULL && ext_count > 0 && next_ext + 1 < ext_count) {
			next_ext++;
		}else{
			next_ie++;
			next_ext = 0;
			if (next_ie >= target_count) {
				next_ie = 0;
			}
		}
	}
	meta[0] = 1;
	meta[1] = (uint8_t)selected_ie;
	meta[2] = (uint8_t)step_index;
	meta[3] = (uint8_t)value_index;
	meta[4] = (uint8_t)selected_ext;
	meta[5] = (uint8_t)min_value;
	meta[6] = (uint8_t)max_value;
	meta[7] = (uint8_t)target_count;
	put_u16_le(meta, 8, next_ie);
	put_u16_le(meta, 10, next_ext);
	put_u16_le(meta, 12, next_step);
	put_u16_le(meta, 14, next_value);
	ret = 1;
	return ret;
}

int aic8800_owfuzz_mutation_label(uint8_t *out, int out_len, int ie_id, int step_index, int value_index, int mutation_len){
	int ret = 0;
	int off = 0;

	if (out == NULL) {
		return ret;
	}
	step_index %= (sizeof(owfuzz_mutation_steps) / sizeof(owfuzz_mutation_steps[0]));
	value_index %= (sizeof(owfuzz_value_steps) / sizeof(owfuzz_value_steps[0]));
	if (!append_ascii_cstr(out, out_len, &off, "ie=") || !append_dec_u32(out, out_len, &off, ie_id) || !append_ascii_cstr(out, out_len, &off, " step=") || !append_ascii_cstr(out, out_len, &off, owfuzz_mutation_steps[step_index]) ||
		!append_ascii_cstr(out, out_len, &off, " value=") || !append_ascii_cstr(out, out_len, &off, owfuzz_value_steps[value_index]) || !append_ascii_cstr(out, out_len, &off, " len=") || !append_dec_u32(out, out_len, &off, mutation_len)) {
		return ret;
	}
	ret = off;
	return ret;
}

int aic8800_owfuzz_next_seq(uint8_t *meta, int meta_len, int current){
	int ret = 0;

	if (meta == NULL || meta_len < 4) {
		return ret;
	}
	put_u16_le(meta, 0, current & 0x0fffu);
	put_u16_le(meta, 2, (current + 1) & 0x0fffu);
	ret = 1;
	return ret;
}

int aic8800_owfuzz_profile_frame_count(const uint8_t *profile, int profile_len, int captured_count){
	int ret = 0;
	int type = 0;
	int count = 0;
	uint8_t *types = NULL;

	ret = aic8800_owfuzz_is_captured_profile(profile, profile_len);
	if(ret){
		ret = captured_count;
		return ret;
	}
	ret = owfuzz_profile_select(profile, profile_len, &types, &count);
	if(ret){
		ret = count;
		return ret;
	}
	ret = owfuzz_lookup_frame_type(profile, profile_len, &type);
	if(ret){
		ret = 1;
	}
	return ret;
}

int aic8800_owfuzz_select_next_frame(uint8_t *meta, int meta_len, const uint8_t *profile, int profile_len, int captured_count, int sent){
	int ret = 0;
	int count = 0;
	int frame_type = 0;
	uint8_t *types = NULL;

	if (meta == NULL || meta_len < 16) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (aic8800_owfuzz_is_captured_profile(profile, profile_len)) {
		if (captured_count == 0) {
			ret = ret;
		}
		put_u32_le(meta, 0, AIC_OWFUZZ_NEXT_CAPTURED);
		put_u32_le(meta, 4, 0);
		put_u32_le(meta, 8, sent % captured_count);
		put_u32_le(meta, 12, captured_count);
		ret = 1;
		return ret;
	}

	ret = owfuzz_profile_select(profile, profile_len, &types, &count);
	if(ret){
		if (count == 0) {
			ret = 1;
			return ret;
		}
		frame_type = types[sent % count];
	}else if (owfuzz_lookup_frame_type(profile, profile_len, &frame_type)) {
		count = 1;
	}else{
		ret = 1;
		return ret;
	}

	put_u32_le(meta, 0, AIC_OWFUZZ_NEXT_GENERATED);
	put_u32_le(meta, 4, frame_type & 0xfcu);
	put_u32_le(meta, 8, 0xffffffffu);
	put_u32_le(meta, 12, count);
	ret = 1;
	return ret;
}

int aic8800_owfuzz_frame_build_plan(uint8_t *meta, int meta_len, int action, int frame_type,
                                     int seq_current, int mutate, int ie_index,
                                     int ext_index, int step_index, int value_index,
                                     const uint8_t *template_frame, int template_len){
	int ret = 0;
	int seq = 0;
	int type = 0;
	int kind = 0;
	int next_seq = 0;
	int captured = 0;
	int needs_seq = 0;
	int should_mutate = 0;
	uint8_t mut_meta[16] ={};

	if (meta == NULL || meta_len < 68) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (action != AIC_OWFUZZ_NEXT_GENERATED && action != AIC_OWFUZZ_NEXT_CAPTURED) {
		ret = 1;
		return ret;
	}

	captured = action == AIC_OWFUZZ_NEXT_CAPTURED;
	type = captured && template_frame && template_len ? (template_frame[0] & 0xfcu) : (frame_type & 0xfcu);
	kind = captured && template_frame && template_len ? (template_frame[0] & 0x0cu) : (type & 0x0cu);
	needs_seq = captured ? ((template_frame && template_len >= 24) ? 1 : 0) : (kind == 0x04 ? 0 : 1);
	seq = needs_seq ? (seq_current & 0x0fffu) : 0;
	next_seq = needs_seq ? ((seq_current + 1) & 0x0fffu) : (seq_current & 0x0fffu);
	should_mutate = mutate && kind == 0x00;

	put_u32_le(meta, 0, action);
	put_u32_le(meta, 4, type);
	put_u32_le(meta, 8, seq);
	put_u32_le(meta, 12, next_seq);

	memset(mut_meta, 0, sizeof(mut_meta));
	ret = aic8800_owfuzz_mutation_plan(mut_meta, sizeof(mut_meta), type, should_mutate, ie_index, ext_index, step_index, value_index, captured);
	if(ret == 0){
		return ret;
	}
	put_u32_le(meta, 16, mut_meta[0] ? 1 : 0);
	put_u32_le(meta, 20, mut_meta[1]);
	put_u32_le(meta, 24, mut_meta[2]);
	put_u32_le(meta, 28, mut_meta[3]);
	put_u32_le(meta, 32, mut_meta[4]);
	put_u32_le(meta, 36, mut_meta[5]);
	put_u32_le(meta, 40, mut_meta[6]);
	put_u32_le(meta, 44, mut_meta[7]);
	put_u32_le(meta, 48, get_u16_le(mut_meta, 8));
	put_u32_le(meta, 52, get_u16_le(mut_meta, 10));
	put_u32_le(meta, 56, get_u16_le(mut_meta, 12));
	put_u32_le(meta, 60, get_u16_le(mut_meta, 14));
	put_u32_le(meta, 64, should_mutate ? 1 : 0);
	ret = 1;
	return ret;
}

static int shell_key_char(uint8_t c){
	c = aic8800_ascii_lower(c);
	return (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 95 || c == 45;
}

static int shell_append_slice(uint8_t *out, int out_len, int *off, const uint8_t *text, int start, int end, int lower){
	int ret = 0;

	if (out == NULL || off == NULL || text == NULL || end < start) {
		return ret;
	}
	if (*off + (end - start) + 1 > out_len) {
		return ret;
	}
	for (int i = start; i < end; i++) {
		out[(*off)++] = lower ? aic8800_ascii_lower(text[i]) : text[i];
	}
	out[(*off)++] = 0;
	ret = 1;
	return ret;
}

int aic8800_parse_shell_command(const uint8_t *text, int text_len, uint8_t *meta, int meta_len, uint8_t *out, int out_len){
	int ret = 0;
	int p = 0;
	int off = 0;
	int end = 0;
	int start = 0;
	int key_end = 0;
	int kv_count = 0;
	int name_end = 0;
	int arg_start = 0;
	int key_start = 0;
	int value_end = 0;
	int part_count = 0;
	int part_start = 0;
	int value_start = 0;

	if (text == NULL || meta == NULL || meta_len < 4 || !out) {
		return ret;
	}
	ret = !trim_ascii(text, text_len, &start, &end);
	if(ret){
		ret = 0;
		return ret;
	}
	name_end = start;
	while (name_end < end && !ascii_space(text[name_end])) {
		name_end++;
	}
	arg_start = name_end;
	while (arg_start < end && ascii_space(text[arg_start])) {
		arg_start++;
	}
	memset(meta, 0, meta_len);
	if (!shell_append_slice(out, out_len, &off, text, start, name_end, 1) || !shell_append_slice(out, out_len, &off, text, arg_start, end, 0)) {
		return ret;
	}
	p = start;
	while (p < end) {
		while (p < end && ascii_space(text[p])) {
			p++;
		}
		if (p >= end) {
			break;
		}
		part_start = p;
		while (p < end && !ascii_space(text[p])) {
			p++;
		}
		ret = shell_append_slice(out, out_len, &off, text, part_start, p, part_count == 0);
		if(ret == 0){
			return ret;
		}
		part_count++;
	}
	p = arg_start;
	while (p < end) {
		while (p < end && !shell_key_char(text[p])) {
			p++;
		}
		if (p >= end) {
			break;
		}
		key_start = p;
		while (p < end && shell_key_char(text[p])) {
			p++;
		}
        	key_end = p;
        	if (p >= end || text[p] != 61) {
			continue;
		}
		p++;
		value_start = p;
		value_end = p;
		if (p < end && text[p] == 34) {
			value_start = ++p;
			while (p < end && text[p] != 34) {
				p++;
			}
			value_end = p;
			if (p < end && text[p] == 34) {
				p++;
			}
		}else{
			while (p < end && !ascii_space(text[p])) {
				p++;
			}
			value_end = p;
		}
		if (!shell_append_slice(out, out_len, &off, text, key_start, key_end, 1) || !shell_append_slice(out, out_len, &off, text, value_start, value_end, 0)) {
			return ret;
		}
		kv_count++;
	}

	put_u16_le(meta, 0, part_count);
	put_u16_le(meta, 2, kv_count);
	ret = off;
	return ret;
}

/* aic8800_shell_command_action: convert a shell command into it's ID code */
int aic8800_shell_command_action(const uint8_t *name, int name_len, const uint8_t *subcmd, int subcmd_len, const uint8_t *arg_text, int arg_text_len, int has_payload_arg){
	int ret = 0;

	if (clean_match(name, name_len, "clear")){
		ret = AIC_SHELL_ACT_CLEAR;
		return ret;
	}
	if (clean_match(name, name_len, "scan")){
		ret = AIC_SHELL_ACT_SCAN;
		return ret;
	}
	if (clean_match(name, name_len, "status")){
		ret = AIC_SHELL_ACT_STATUS;
		return ret;
	}
	if (clean_match(name, name_len, "save")){
		ret = AIC_SHELL_ACT_SAVE;
		return ret;
	}
	if (clean_match(name, name_len, "readmem") || clean_match(name, name_len, "read_mem") || clean_match(name, name_len, "read-mem")){
		ret = AIC_SHELL_ACT_READ_MEM;
		return ret;
	}
	if (clean_match(name, name_len, "writemem") || clean_match(name, name_len, "write_mem") || clean_match(name, name_len, "write-mem")){
		ret = AIC_SHELL_ACT_WRITE_MEM;
		return ret;
	}
	if (clean_match(name, name_len, "networks")){
		ret = AIC_SHELL_ACT_NETWORKS;
		return ret;
	}
	if (clean_match(name, name_len, "meshp2p") || clean_match(name, name_len, "mesh_p2p") || clean_match(name, name_len, "mesh-p2p")){
		ret = AIC_SHELL_ACT_MESHP2P;
		return ret;
	}
	if (clean_match(name, name_len, "mesh")){
		ret = AIC_SHELL_ACT_MESH;
		return ret;
	}
	if (clean_match(name, name_len, "p2p")){
		ret = AIC_SHELL_ACT_P2P;
		return ret;
	}
	if (clean_match(name, name_len, "monitor") || clean_match(name, name_len, "startmonitor") || clean_match(name, name_len, "start_monitor") || clean_match(name, name_len, "start-monitor")){
		ret = AIC_SHELL_ACT_MONITOR;
		return ret;
	}
	if (clean_match(name, name_len, "observer") || clean_match(name, name_len, "startobserver") || clean_match(name, name_len, "start_observer") || clean_match(name, name_len, "start-observer")){
		if (clean_match(subcmd, subcmd_len, "stop")){
			ret = AIC_SHELL_ACT_STOP_OBSERVER;
		}else{
			ret = AIC_SHELL_ACT_OBSERVER;
		}
		return ret;
	}
	if (clean_match(name, name_len, "stopobserver") || clean_match(name, name_len, "stop_observer") || clean_match(name, name_len, "stop-observer") || (clean_match(name, name_len, "stop") && clean_match(subcmd, subcmd_len, "observer"))){
		ret = AIC_SHELL_ACT_STOP_OBSERVER;
		return ret;
	}
	if (clean_match(name, name_len, "stopmonitor") || clean_match(name, name_len, "stop_monitor") || clean_match(name, name_len, "stop-monitor") || (clean_match(name, name_len, "stop") && clean_match(subcmd, subcmd_len, "monitor"))){
		ret = AIC_SHELL_ACT_STOP_MONITOR;
		return ret;
	}
	if (clean_match(name, name_len, "startap") || clean_match(name, name_len, "start_ap") || clean_match(name, name_len, "start-ap") || (clean_match(name, name_len, "start") && clean_match(subcmd, subcmd_len, "ap"))){
		ret = AIC_SHELL_ACT_START_AP;
		return ret;
	}
	if (clean_match(name, name_len, "stopap") || clean_match(name, name_len, "stop_ap") || clean_match(name, name_len, "stop-ap") || (clean_match(name, name_len, "stop") && clean_match(subcmd, subcmd_len, "ap"))){
		ret = AIC_SHELL_ACT_STOP_AP;
		return ret;
	}
	if (clean_match(name, name_len, "fuzz")) {
		if (clean_match(subcmd, subcmd_len, "stop")){
			ret = AIC_SHELL_ACT_FUZZ_STOP;
			return ret;
		}
		if (clean_match(subcmd, subcmd_len, "status")){
			ret = AIC_SHELL_ACT_FUZZ_STATUS;
			return ret;
		}
		if (clean_match(subcmd, subcmd_len, "clear") || clean_match(subcmd, subcmd_len, "reset")){
			ret = AIC_SHELL_ACT_FUZZ_CLEAR;
			return ret;
		}
		if (clean_match(subcmd, subcmd_len, "launch") || clean_match(subcmd, subcmd_len, "start")){
			ret = AIC_SHELL_ACT_FUZZ_LAUNCH;
			return ret;
		}
		return AIC_SHELL_ACT_FUZZ_INIT;
	}
	if (clean_match(name, name_len, "launch")) {
		if (clean_match(subcmd, subcmd_len, "stop")){
			ret = AIC_SHELL_ACT_LAUNCH_STOP;
			return ret;
		}
		if (clean_match(subcmd, subcmd_len, "status")){
			ret = AIC_SHELL_ACT_LAUNCH_STATUS;
			return ret;
		}
		if (has_payload_arg || aic8800_owfuzz_looks_hex_payload(subcmd, subcmd_len)){
			ret = AIC_SHELL_ACT_LAUNCH_PAYLOAD;
			return ret;
		}
		return AIC_SHELL_ACT_LAUNCH_PROFILE;
	}
	if (clean_match(name, name_len, "patch")) {
		if(clean_match(subcmd, subcmd_len, "decompile") || clean_match(subcmd, subcmd_len, "decomp")){
			ret = AIC_SHELL_ACT_PATCH_DECOMPILE;
		}else{
			ret = AIC_SHELL_ACT_PATCH_OPEN;
		}
		return ret;
	}
	if (clean_match(name, name_len, "send")){
		if(arg_text_len){
			ret = AIC_SHELL_ACT_SEND_MONITOR;
			return ret;
		}else{
			ret = AIC_SHELL_ACT_SEND_BOX;
			return ret;
		}
	}
	if (clean_match(name, name_len, "sendeth") || clean_match(name, name_len, "send_eth") || clean_match(name, name_len, "send-eth") || clean_match(name, name_len, "tx")){
		ret = AIC_SHELL_ACT_SEND_ETH;
		return ret;
	}
	if (clean_match(name, name_len, "connect")){
		ret = AIC_SHELL_ACT_CONNECT;
		return ret;
	}
	if (clean_match(name, name_len, "mac") || clean_match(name, name_len, "setmac") || clean_match(name, name_len, "set_mac") || clean_match(name, name_len, "set-mac")){
		ret = AIC_SHELL_ACT_SET_MAC;
		return ret;
	}
	if (clean_match(name, name_len, "deauth") || clean_match(name, name_len, "deauthentication")){
		ret = AIC_SHELL_ACT_DEAUTH;
		return ret;
	}
	if (clean_match(name, name_len, "inject") || clean_match(name, name_len, "injector")){
		ret = AIC_SHELL_ACT_INJECT;
		return ret;
	}
	if (clean_match(name, name_len, "editcaptive") || clean_match(name, name_len, "edit_captive") || clean_match(name, name_len, "edit-captive")){
		ret = AIC_SHELL_ACT_EDIT_CAPTIVE;
		return ret;
	}
	if (clean_match(name, name_len, "help")){
		ret = AIC_SHELL_ACT_HELP;
		return ret;
	}
	ret = AIC_SHELL_ACT_UNKNOWN;
	return ret;
}

int aic8800_shell_help_text(uint8_t *out, int out_len){
	int ret = 0;

	ret = write_ascii_string(out, out_len,
		"commands:\n"
		"* scan -> start scan\n"
		"* status -> get dongle status\n"
		"* meshp2p id=<mesh> freq=<mhz> [pass=<pw>] [dtim=<n>] [beacon=<ms>] -> start mesh and P2P networking\n"
		"* mesh id=<mesh> freq=<mhz> [pass=<pw>] [dtim=<n>] [beacon=<ms>] -> start mesh networking\n"
		"* p2p -> start a P2P interface\n"
		"* start_monitor freq=<mhz> [filter=<data|beacon|mgmt>] [width=<20|40|80|160>] [center1=<mhz>] [center2=<mhz>] -> start monitor mode\n"
		"* observer filter=<data|mgmt|beacon> [band=<2g|5g|all>] [channels=<mhz,...>] [interval=<sec|ms>] -> hop monitor channels\n"
		"* stop_observer -> stop channel hopping and keep monitor mode active\n"
		"* stop_monitor -> remove the monitor interface\n"
		"* start_ap ssid=<name> freq=<mhz> [pass=<pw>] [dtim=<n>] [beacon=<ms>] [portal=<on|off>] [portal_title=<text>] [portal_message=<text>] [portal_url=<url>] -> start an open or WPA2-PSK AP\n"
		"* edit_captive -> open the captive portal HTML editor\n"
		"* stop_ap -> stop and remove the AP interface\n"
		"* ap_dump state=<on|off|toggle> -> show or hide AP-mode raw RX hexdumps\n"
		"* send data=<hex> -> send one raw frame through monitor TX\n"
		"* inject type=beacon ssid=<name> [freq=<mhz>] [src=<mac>] [interval=<ms>] [count=<n>] -> repeatedly inject beacon frames\n"
		"* send_eth data=<hex> -> send regular networking data when authenticated\n"
		"* deauth bssid=<mac> target=<mac> [reason=<code>] -> send one deauthentication frame\n"
		"* read_mem addr=<addr> -> read memory from the Wi-Fi RAM\n"
		"* write_mem addr=<addr> value=<value> -> write memory to the Wi-Fi RAM\n"
		"* patch addr=<addr> -> compile and apply an ARM32 C patch\n"
		"* patch decompile addr=<addr> len=<bytes> -> decompile RAM bytes with Ghidra\n"
		"* connect ssid=<name>|bssid=<mac> [pass=<pw>] [freq=<mhz>] -> connect to a Wi-Fi network\n"
		"* save type=pcap [file=<name>] -> save captured traffic as a PCAP file\n"
		"* mac addr=<mac> -> change the MAC address\n"
		"* fuzz profile=<name> [freq=<mhz>] [interval=<ms>] [count=<n>] -> initialize fuzzing\n"
		"* fuzz launch profile=<name> [interval=<ms>] [count=<n>] -> launch the fuzzer\n"
		"* launch data=<hex>|profile=<name> -> transmit a frame or launch a fuzz profile\n");
	return ret;
}

int aic8800_shell_status_line(uint8_t *out, int out_len, const uint8_t *mode, int mode_len,
                               int fw_version, int sta_vif, int mesh_vif, int p2p_vif,
                               int monitor_vif, int ap_vif, const uint8_t *mac, int mac_len, int networks,
                               int pcap_frames, int pcap_bytes){
	int ret = 0;
	int off = 0;

	if (out == NULL) {
		return ret;
	}
	append_ascii_cstr(out, out_len, &off, " fw=");
	append_dec_u32(out, out_len, &off, fw_version);
	append_ascii_cstr(out, out_len, &off, " monitor=");
	append_dec_u32(out, out_len, &off, monitor_vif);
	append_ascii_cstr(out, out_len, &off, " mac=");
	append_mac_text(out, out_len, &off, mac, mac_len);
	ret = off;
	return ret;
}

int aic8800_frame_type_to_string(uint8_t *out, int out_len, const uint8_t *frame, int frame_len){
	int ret = 0;
	int type = 0;
	int subtype = 0;
	int frame_control = 0;

	static const char *const management[] = {
		"association-req",
		"association-resp",
		"reassociation-req",
		"reassociation-resp",
		"probe-req",
		"probe-resp",
		"timing-ad",
		"reserved-mgmt",
		"beacon",
		"atim",
		"disassociation",
		"authentication",
		"deauthentication",
		"action",
		"action-no-ack",
		"reserved-mgmt"
	};
	static const char *const control[] = {
		"reserved-ctrl",
		"reserved-ctrl",
		"trigger",
		"tack",
		"beamforming-report-poll",
		"vht-he-ndp-announcement",
		"control-frame-extension",
		"control-wrapper",
		"block-ack-req",
		"block-ack",
		"ps-poll",
		"rts",
		"cts",
		"ack",
		"cf-end",
		"cf-end-cf-ack"
	};
	static const char *const data[] = {
		"data",
		"data-cf-ack",
		"data-cf-poll",
		"data-cf-ack-poll",
		"null",
		"cf-ack",
		"cf-poll",
		"cf-ack-poll",
		"qos-data",
		"qos-data-cf-ack",
		"qos-data-cf-poll",
		"qos-data-cf-ack-poll",
		"qos-null",
		"reserved-data",
		"qos-cf-poll",
		"qos-cf-ack-poll"
	};
	if (frame == NULL || frame_len < 2) {
		ret = write_ascii_string(out, out_len, "short");
		return ret;
	}
	frame_control = (int)frame[0] | ((int)frame[1] << 8);
	type = (frame_control >> 2) & 0x03;
	subtype = (frame_control >> 4) & 0x0fu;
	if (type == 0) {
		ret = write_ascii_string(out, out_len, management[subtype]);
		return ret;
	}
	if (type == 1) {
		ret = write_ascii_string(out, out_len, control[subtype]);
		return ret;
	}
	if (type == 2) {
		ret = write_ascii_string(out, out_len, data[subtype]);
		return ret;
	}
	ret = write_ascii_string(out, out_len, "extension");
	return ret;
}

static uint32_t rotl32(uint32_t value, int bits){
	return (value << bits) | (value >> (32 - bits));
}

static uint32_t get_u32_be(const uint8_t *src, int offset){
	return ((uint32_t)src[offset] << 24) | ((uint32_t)src[offset + 1] << 16) |
	       ((uint32_t)src[offset + 2] << 8) | (uint32_t)src[offset + 3];
}

static void put_u16_be(uint8_t *dst, int offset, int value){
	dst[offset] = (uint8_t)((value >> 8) & 0xffu);
	dst[offset + 1] = (uint8_t)(value & 0xffu);
}

static void put_u32_be(uint8_t *dst, int offset, uint32_t value){
	dst[offset] = (uint8_t)((value >> 24) & 0xffu);
	dst[offset + 1] = (uint8_t)((value >> 16) & 0xffu);
	dst[offset + 2] = (uint8_t)((value >> 8) & 0xffu);
	dst[offset + 3] = (uint8_t)(value & 0xffu);
}

static int aic8800_dhcp_get_message_type(const uint8_t *dhcp, int len){
	int ret = 0;
	int pos = 0;
	uint8_t code = 0;
	uint8_t olen = 0;

	if (dhcp == NULL || len < 240) {
		return ret;
	}
	if (dhcp[236] != 0x63 || dhcp[237] != 0x82 || dhcp[238] != 0x53 || dhcp[239] != 0x63) {
		return ret;
	}
	pos = 240;
	while (pos < len) {
		code = dhcp[pos++];
		if (code == 0) {
			continue;
		}
		if (code == 255) {
			break;
		}
		if (pos >= len) {
			break;
		}
		olen = dhcp[pos++];
		if (pos + olen > len) {
			break;
		}
		if (code == 53 && olen == 1) {
			ret = dhcp[pos];
			return ret;
		}
		pos += olen;
	}
	return ret;
}

static uint16_t aic8800_checksum16(const uint8_t *data, int len){
	uint32_t sum = 0;

	while (len > 1) {
		sum += ((uint16_t)data[0] << 8) | data[1];
		data += 2;
		len -= 2;
	}
	if (len != 0) {
		sum += (uint16_t)data[0] << 8;
	}
	while (sum >> 16) {
		sum = (sum & 0xffffu) + (sum >> 16);
	}
	return (uint16_t)~sum;
}

static int aic8800_build_dhcp_payload(uint8_t *out, int out_size, const uint8_t *request, int request_len, int msg_type){
	int pos = 0;

	if (out == NULL || request == NULL || request_len < 240 || out_size < 300) {
		return 0;
	}
	memset(out, 0, out_size);
	out[0] = 2;
	out[1] = 1;
	out[2] = ETH_ALEN;
	out[3] = 0;
	memcpy(out + 4, request + 4, 4);
	memcpy(out + 10, request + 10, 2);
	put_u32_be(out, 16, AIC_DHCP_CLIENT_IP);
	memcpy(out + 28, request + 28, 16);
	out[236] = 0x63;
	out[237] = 0x82;
	out[238] = 0x53;
	out[239] = 0x63;

	pos = 240;
	out[pos++] = 53;
	out[pos++] = 1;
	out[pos++] = (uint8_t)msg_type;

	out[pos++] = 54;
	out[pos++] = 4;
	put_u32_be(out, pos, AIC_DHCP_SERVER_IP);
	pos += 4;

	out[pos++] = 51;
	out[pos++] = 4;
	put_u32_be(out, pos, AIC_DHCP_LEASE_SECONDS);
	pos += 4;

	out[pos++] = 1;
	out[pos++] = 4;
	put_u32_be(out, pos, AIC_DHCP_SUBNET_MASK);
	pos += 4;

	out[pos++] = 3;
	out[pos++] = 4;
	put_u32_be(out, pos, AIC_DHCP_SERVER_IP);
	pos += 4;

	out[pos++] = 6;
	out[pos++] = 4;
	put_u32_be(out, pos, AIC_DHCP_SERVER_IP);
	pos += 4;

	out[pos++] = 255;
	while (pos < 300) {
		out[pos++] = 0;
	}
	return pos;
}

int aic8800_decode_dhcp_request(uint8_t *meta, int meta_len, const uint8_t *ip, int ip_len){
	int ihl = 0;
	int total_len = 0;
	int udp_len = 0;
	int dhcp_off = 0;
	int dhcp_len = 0;
	int msg_type = 0;
	uint16_t sport = 0;
	uint16_t dport = 0;
	const uint8_t *udp = NULL;
	const uint8_t *dhcp = NULL;

	if (meta == NULL || meta_len < AIC_DHCP_META_SIZE) {
		return 0;
	}
	memset(meta, 0, meta_len);
	if (ip == NULL || ip_len < 20) {
		return 1;
	}
	if ((ip[0] >> 4) != 4) {
		return 1;
	}
	ihl = (ip[0] & 0x0f) * 4;
	if (ihl < 20 || ip_len < ihl + 8) {
		return 1;
	}
	if (ip[9] != 17) {
		return 1;
	}
	total_len = get_u16_be(ip, 2);
	if (total_len < ihl + 8 || total_len > ip_len) {
		return 1;
	}
	udp = ip + ihl;
	sport = get_u16_be(udp, 0);
	dport = get_u16_be(udp, 2);
	if (sport != 68 || dport != 67) {
		return 1;
	}
	udp_len = get_u16_be(udp, 4);
	if (udp_len < 8 || udp_len > total_len - ihl) {
		return 1;
	}
	dhcp_off = ihl + 8;
	dhcp_len = udp_len - 8;
	dhcp = ip + dhcp_off;
	if (dhcp_len < 240 || dhcp[0] != 1) {
		return 1;
	}
	msg_type = aic8800_dhcp_get_message_type(dhcp, dhcp_len);
	if (msg_type == 0) {
		return 1;
	}
	put_u32_le(meta, 0, 1);
	put_u32_le(meta, 4, msg_type);
	put_u32_le(meta, 8, dhcp_off);
	put_u32_le(meta, 12, dhcp_len);
	return 1;
}

int aic8800_build_dhcp_reply_frame(uint8_t *out, int out_len,
                                    const uint8_t *ap_mac, int ap_mac_len,
                                    const uint8_t *request, int request_len,
                                    int msg_type){
	int dhcp_len = 0;
	int udp_len = 0;
	int ip_len = 0;
	int frame_len = 0;
	int reply_type = msg_type;
	int request_type = 0;
	uint8_t dhcp[576] = {};
	uint8_t *ip = NULL;
	uint8_t *udp = NULL;

	if (out == NULL || ap_mac == NULL || ap_mac_len < ETH_ALEN || request == NULL || request_len < 240) {
		return 0;
	}
	if (reply_type == DHCP_DISCOVER) {
		reply_type = DHCP_OFFER;
	}else if (reply_type == DHCP_REQUEST) {
		reply_type = DHCP_ACK;
	}else if (reply_type != DHCP_OFFER && reply_type != DHCP_ACK) {
		request_type = aic8800_dhcp_get_message_type(request, request_len);
		if (request_type == DHCP_DISCOVER) {
			reply_type = DHCP_OFFER;
		}else if (request_type == DHCP_REQUEST) {
			reply_type = DHCP_ACK;
		}else{
			return 0;
		}
	}
	dhcp_len = aic8800_build_dhcp_payload(dhcp, sizeof(dhcp), request, request_len, reply_type);
	if (dhcp_len == 0) {
		return 0;
	}
	udp_len = 8 + dhcp_len;
	ip_len = 20 + udp_len;
	frame_len = 14 + ip_len;
	if (frame_len > out_len) {
		return 0;
	}
	memset(out, 0, frame_len);
	memset(out, 0xff, ETH_ALEN);
	memcpy(out + ETH_ALEN, ap_mac, ETH_ALEN);
	out[12] = 0x08;
	out[13] = 0x00;

	ip = out + 14;
	udp = ip + 20;
	ip[0] = 0x45;
	ip[1] = 0;
	put_u16_be(ip, 2, ip_len);
	put_u16_be(ip, 4, 0);
	put_u16_be(ip, 6, 0);
	ip[8] = 64;
	ip[9] = 17;
	put_u32_be(ip, 12, AIC_DHCP_SERVER_IP);
	put_u32_be(ip, 16, 0xffffffffu);
	put_u16_be(ip, 10, aic8800_checksum16(ip, 20));

	put_u16_be(udp, 0, 67);
	put_u16_be(udp, 2, 68);
	put_u16_be(udp, 4, udp_len);
	put_u16_be(udp, 6, 0);
	memcpy(udp + 8, dhcp, dhcp_len);
	return frame_len;
}

int aic8800_decode_arp_request(uint8_t *meta, int meta_len, const uint8_t *arp, int arp_len){
	if (meta == NULL || meta_len < 8) {
		return 0;
	}
	memset(meta, 0, meta_len);
	if (arp == NULL || arp_len < 28) {
		return 1;
	}
	if (get_u16_be(arp, 0) != 1 || get_u16_be(arp, 2) != ETH_P_IP || arp[4] != ETH_ALEN || arp[5] != 4) {
		return 1;
	}
	if (get_u16_be(arp, 6) != 1) {
		return 1;
	}
	if ((uint32_t)get_u32_be(arp, 24) != AIC_DHCP_SERVER_IP) {
		return 1;
	}
	put_u32_le(meta, 0, 1);
	put_u32_le(meta, 4, get_u32_be(arp, 14));
	return 1;
}

int aic8800_build_arp_reply_frame(uint8_t *out, int out_len,
                                   const uint8_t *ap_mac, int ap_mac_len,
                                   const uint8_t *request, int request_len){
	uint8_t *arp = NULL;

	if (out == NULL || out_len < 42 || ap_mac == NULL || ap_mac_len < ETH_ALEN || request == NULL || request_len < 28) {
		return 0;
	}
	if (get_u16_be(request, 0) != 1 || get_u16_be(request, 2) != ETH_P_IP || request[4] != ETH_ALEN || request[5] != 4 || get_u16_be(request, 6) != 1) {
		return 0;
	}
	memset(out, 0, 42);
	memcpy(out, request + 8, ETH_ALEN);
	memcpy(out + ETH_ALEN, ap_mac, ETH_ALEN);
	out[12] = 0x08;
	out[13] = 0x06;
	arp = out + 14;
	put_u16_be(arp, 0, 1);
	put_u16_be(arp, 2, ETH_P_IP);
	arp[4] = ETH_ALEN;
	arp[5] = 4;
	put_u16_be(arp, 6, 2);
	memcpy(arp + 8, ap_mac, ETH_ALEN);
	put_u32_be(arp, 14, AIC_DHCP_SERVER_IP);
	memcpy(arp + 18, request + 8, ETH_ALEN);
	memcpy(arp + 24, request + 14, 4);
	return 42;
}


static uint32_t aic8800_checksum_add(uint32_t sum, const uint8_t *data, int len){
	while (len > 1) {
		sum += ((uint16_t)data[0] << 8) | data[1];
		data += 2;
		len -= 2;
	}
	if (len != 0) {
		sum += (uint16_t)data[0] << 8;
	}
	return sum;
}

static uint16_t aic8800_tcp_checksum(const uint8_t *ip, const uint8_t *tcp, int tcp_len){
	uint32_t sum = 0;

	sum = aic8800_checksum_add(sum, ip + 12, 8);
	sum += 6;
	sum += (uint16_t)tcp_len;
	sum = aic8800_checksum_add(sum, tcp, tcp_len);
	while (sum >> 16) {
		sum = (sum & 0xffffu) + (sum >> 16);
	}
	sum = (~sum) & 0xffffu;
	return (uint16_t)(sum == 0 ? 0xffffu : sum);
}

static int aic8800_dns_question_end(const uint8_t *dns, int dns_len){
	int pos = 12;
	int label_len = 0;

	if (dns == NULL || dns_len < 17 || get_u16_be(dns, 4) == 0) {
		return 0;
	}
	while (pos < dns_len) {
		label_len = dns[pos++];
		if (label_len == 0) {
			break;
		}
		if ((label_len & 0xc0) != 0 || label_len > 63 || pos + label_len > dns_len) {
			return 0;
		}
		pos += label_len;
	}
	if (pos + 4 > dns_len) {
		return 0;
	}
	return pos + 4;
}

int aic8800_decode_portal_ipv4(uint8_t *meta, int meta_len, const uint8_t *ip, int ip_len){
	int ihl = 0;
	int total_len = 0;
	int header_len = 0;
	int payload_off = 0;
	int payload_len = 0;
	int protocol = 0;
	const uint8_t *transport = NULL;

	if (meta == NULL || meta_len < 40) {
		return 0;
	}
	memset(meta, 0, meta_len);
	if (ip == NULL || ip_len < 20 || (ip[0] >> 4) != 4) {
		return 1;
	}
	ihl = (ip[0] & 0x0f) * 4;
	total_len = get_u16_be(ip, 2);
	if (ihl < 20 || total_len < ihl || total_len > ip_len || (get_u16_be(ip, 6) & 0x1fffu) != 0) {
		return 1;
	}
	protocol = ip[9];
	transport = ip + ihl;
	if (protocol == 17) {
		int udp_len = 0;
		if (total_len < ihl + 8 || get_u16_be(transport, 2) != 53) {
			return 1;
		}
		udp_len = get_u16_be(transport, 4);
		if (udp_len < 20 || udp_len > total_len - ihl || aic8800_dns_question_end(transport + 8, udp_len - 8) == 0) {
			return 1;
		}
		header_len = 8;
		payload_off = ihl + header_len;
		payload_len = udp_len - header_len;
	}else if (protocol == 6) {
		if (total_len < ihl + 20 || get_u16_be(transport, 2) != 80) {
			return 1;
		}
		header_len = ((transport[12] >> 4) & 0x0f) * 4;
		if (header_len < 20 || header_len > total_len - ihl) {
			return 1;
		}
		payload_off = ihl + header_len;
		payload_len = total_len - payload_off;
	}else{
		return 1;
	}
	put_u32_le(meta, 0, 1);
	put_u32_le(meta, 4, protocol);
	put_u32_le(meta, 8, get_u16_be(transport, 0));
	put_u32_le(meta, 12, get_u16_be(transport, 2));
	if (protocol == 6) {
		put_u32_le(meta, 16, get_u32_be(transport, 4));
		put_u32_le(meta, 20, get_u32_be(transport, 8));
		put_u32_le(meta, 24, transport[13]);
	}
	put_u32_le(meta, 28, payload_off);
	put_u32_le(meta, 32, payload_len);
	put_u32_le(meta, 36, get_u32_be(ip, 12));
	return 1;
}

int aic8800_build_portal_dns_reply_frame(uint8_t *out, int out_len,
                                         const uint8_t *ap_mac, int ap_mac_len,
                                         const uint8_t *client_mac, int client_mac_len,
                                         const uint8_t *request_ip, int request_ip_len){
	int ihl = 0;
	int request_total = 0;
	int request_udp_len = 0;
	int question_end = 0;
	int answer = 0;
	int dns_len = 0;
	int udp_len = 0;
	int ip_len = 0;
	int frame_len = 0;
	const uint8_t *request_udp = NULL;
	const uint8_t *request_dns = NULL;
	uint8_t *ip = NULL;
	uint8_t *udp = NULL;
	uint8_t *dns = NULL;
	int pos = 0;

	if (out == NULL || ap_mac == NULL || ap_mac_len < ETH_ALEN || client_mac == NULL || client_mac_len < ETH_ALEN ||
	    request_ip == NULL || request_ip_len < 28 || (request_ip[0] >> 4) != 4) {
		return 0;
	}
	ihl = (request_ip[0] & 0x0f) * 4;
	request_total = get_u16_be(request_ip, 2);
	if (ihl < 20 || request_total < ihl + 20 || request_total > request_ip_len || request_ip[9] != 17) {
		return 0;
	}
	request_udp = request_ip + ihl;
	request_udp_len = get_u16_be(request_udp, 4);
	if (get_u16_be(request_udp, 2) != 53 || request_udp_len < 20 || request_udp_len > request_total - ihl) {
		return 0;
	}
	request_dns = request_udp + 8;
	question_end = aic8800_dns_question_end(request_dns, request_udp_len - 8);
	if (question_end == 0) {
		return 0;
	}
	answer = get_u16_be(request_dns, question_end - 4) == 1 || get_u16_be(request_dns, question_end - 4) == 255;
	dns_len = question_end + (answer ? 16 : 0);
	udp_len = 8 + dns_len;
	ip_len = 20 + udp_len;
	frame_len = 14 + ip_len;
	if (frame_len > out_len) {
		return 0;
	}
	memset(out, 0, frame_len);
	memcpy(out, client_mac, ETH_ALEN);
	memcpy(out + ETH_ALEN, ap_mac, ETH_ALEN);
	put_u16_be(out, 12, ETH_P_IP);
	ip = out + 14;
	udp = ip + 20;
	dns = udp + 8;
	ip[0] = 0x45;
	put_u16_be(ip, 2, ip_len);
	put_u16_be(ip, 6, 0x4000);
	ip[8] = 64;
	ip[9] = 17;
	put_u32_be(ip, 12, get_u32_be(request_ip, 16));
	put_u32_be(ip, 16, get_u32_be(request_ip, 12));
	put_u16_be(ip, 10, aic8800_checksum16(ip, 20));
	put_u16_be(udp, 0, 53);
	put_u16_be(udp, 2, get_u16_be(request_udp, 0));
	put_u16_be(udp, 4, udp_len);
	memcpy(dns, request_dns, question_end);
	put_u16_be(dns, 2, 0x8180);
	put_u16_be(dns, 4, 1);
	put_u16_be(dns, 6, answer ? 1 : 0);
	put_u16_be(dns, 8, 0);
	put_u16_be(dns, 10, 0);
	if (answer) {
		pos = question_end;
		put_u16_be(dns, pos, 0xc00c);
		put_u16_be(dns, pos + 2, 1);
		put_u16_be(dns, pos + 4, 1);
		put_u32_be(dns, pos + 6, 30);
		put_u16_be(dns, pos + 10, 4);
		put_u32_be(dns, pos + 12, AIC_DHCP_SERVER_IP);
	}
	return frame_len;
}

int aic8800_build_portal_tcp_reply_frame(uint8_t *out, int out_len,
                                         const uint8_t *ap_mac, int ap_mac_len,
                                         const uint8_t *client_mac, int client_mac_len,
                                         const uint8_t *request_ip, int request_ip_len,
                                         uint32_t sequence, uint32_t acknowledgement, int flags,
                                         const uint8_t *payload, int payload_len){
	int ihl = 0;
	int request_total = 0;
	int tcp_len = 0;
	int ip_len = 0;
	int frame_len = 0;
	const uint8_t *request_tcp = NULL;
	uint8_t *ip = NULL;
	uint8_t *tcp = NULL;

	if (out == NULL || ap_mac == NULL || ap_mac_len < ETH_ALEN || client_mac == NULL || client_mac_len < ETH_ALEN ||
	    request_ip == NULL || request_ip_len < 40 || payload_len < 0 || (payload_len > 0 && payload == NULL)) {
		return 0;
	}
	ihl = (request_ip[0] & 0x0f) * 4;
	request_total = get_u16_be(request_ip, 2);
	if ((request_ip[0] >> 4) != 4 || ihl < 20 || request_total < ihl + 20 || request_total > request_ip_len || request_ip[9] != 6) {
		return 0;
	}
	request_tcp = request_ip + ihl;
	if (get_u16_be(request_tcp, 2) != 80) {
		return 0;
	}
	tcp_len = 20 + payload_len;
	ip_len = 20 + tcp_len;
	frame_len = 14 + ip_len;
	if (frame_len > out_len) {
		return 0;
	}
	memset(out, 0, frame_len);
	memcpy(out, client_mac, ETH_ALEN);
	memcpy(out + ETH_ALEN, ap_mac, ETH_ALEN);
	put_u16_be(out, 12, ETH_P_IP);
	ip = out + 14;
	tcp = ip + 20;
	ip[0] = 0x45;
	put_u16_be(ip, 2, ip_len);
	put_u16_be(ip, 6, 0x4000);
	ip[8] = 64;
	ip[9] = 6;
	put_u32_be(ip, 12, get_u32_be(request_ip, 16));
	put_u32_be(ip, 16, get_u32_be(request_ip, 12));
	put_u16_be(ip, 10, aic8800_checksum16(ip, 20));
	put_u16_be(tcp, 0, 80);
	put_u16_be(tcp, 2, get_u16_be(request_tcp, 0));
	put_u32_be(tcp, 4, sequence);
	put_u32_be(tcp, 8, acknowledgement);
	tcp[12] = 0x50;
	tcp[13] = (uint8_t)(flags & 0xff);
	put_u16_be(tcp, 14, 64240);
	if (payload_len > 0) {
		memcpy(tcp + 20, payload, payload_len);
	}
	put_u16_be(tcp, 16, aic8800_tcp_checksum(ip, tcp, tcp_len));
	return frame_len;
}

static void sha1_transform(sha1_ctx *ctx, const uint8_t block[64]){
	uint32_t a = 0;
	uint32_t b = 0;
	uint32_t d = 0;
	uint32_t e = 0;
	uint32_t f = 0;
	uint32_t k = 0;
	uint32_t cc = 0;
	uint32_t temp = 0;
	uint32_t w[80] = {};

	for (int i = 0; i < 16; i++) {
		w[i] = get_u32_be(block, i * 4);
	}
	for (int i = 16; i < 80; i++) {
		w[i] = rotl32(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
	}

	a = ctx->state[0];
	b = ctx->state[1];
	cc = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];

	for (int i = 0; i < 80; i++) {
		if (i < 20) {
			f = (b & cc) | ((~b) & d);
			k = 0x5a827999;
		}else if (i < 40) {
			f = b ^ cc ^ d;
			k = 0x6ed9eba1;
		}else if (i < 60) {
			f = (b & cc) | (b & d) | (cc & d);
			k = 0x8f1bbcdc;
		}else{
			f = b ^ cc ^ d;
			k = 0xca62c1d6;
		}
		temp = rotl32(a, 5) + f + e + k + w[i];
		e = d;
		d = cc;
		cc = rotl32(b, 30);
		b = a;
		a = temp;
	}
	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += cc;
	ctx->state[3] += d;
	ctx->state[4] += e;
}

static void sha1_init(sha1_ctx *ctx){
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
	ctx->state[4] = 0xc3d2e1f0;
	ctx->total_len = 0;
	ctx->buffer_len = 0;
}

static void sha1_update(sha1_ctx *ctx, const uint8_t *data, int len){
	int pos = 0;
	int take = 0;
	int need = 0;

	if (data == NULL || len == 0) {
		return;
	}
	ctx->total_len += len;
	if (ctx->buffer_len) {
		need = 64 - ctx->buffer_len;
		take = len < need ? len : need;
		memcpy(ctx->buffer + ctx->buffer_len, data, take);
		ctx->buffer_len += take;
		pos += take;
		if (ctx->buffer_len == 64) {
			sha1_transform(ctx, ctx->buffer);
			ctx->buffer_len = 0;
		}
	}
	while (pos + 64 <= len) {
		sha1_transform(ctx, data + pos);
		pos += 64;
	}
	if (pos < len) {
		ctx->buffer_len = len - pos;
		memcpy(ctx->buffer, data + pos, ctx->buffer_len);
	}
}

static void sha1_final(sha1_ctx *ctx, uint8_t out[20]){
	int pad_len = 0;
	uint64_t bit_len = 0;
	uint8_t pad[64] = {};
	uint8_t len_bytes[8] ={};

	bit_len = ctx->total_len * 8;
	memset(pad, 0, sizeof(pad));
	pad[0] = 0x80;
	pad_len = ctx->buffer_len < 56 ? (56 - ctx->buffer_len) : (120 - ctx->buffer_len);
	sha1_update(ctx, pad, pad_len);
	for (int i = 0; i < 8; i++) {
		len_bytes[7 - i] = (uint8_t)((bit_len >> (i * 8)) & 0xffu);
	}
	sha1_update(ctx, len_bytes, 8);
	for (int i = 0; i < 5; i++) {
		put_u32_be(out, i * 4, ctx->state[i]);
	}
}

static void sha1_digest(const uint8_t *data, int len, uint8_t out[20]){
	sha1_ctx ctx;
	sha1_init(&ctx);
	sha1_update(&ctx, data, len);
	sha1_final(&ctx, out);
}

static void hmac_sha1(const uint8_t *key, int key_len, const uint8_t *data, int data_len, uint8_t out[20]){
	sha1_ctx ctx = {};
	uint8_t ipad[64] = {};
	uint8_t opad[64] = {};
	uint8_t inner[20] = {};
	uint8_t key_block[64] = {};

	memset(key_block, 0, sizeof(key_block));
	if (key_len > 64){
		sha1_digest(key, key_len, key_block);
	}else if (key_len){
		memcpy(key_block, key, key_len);
	}
	for (int i = 0; i < 64; i++) {
		ipad[i] = (uint8_t)(key_block[i] ^ 0x36);
		opad[i] = (uint8_t)(key_block[i] ^ 0x5cu);
	}
	sha1_init(&ctx);
	sha1_update(&ctx, ipad, sizeof(ipad));
	sha1_update(&ctx, data, data_len);
	sha1_final(&ctx, inner);
	sha1_init(&ctx);
	sha1_update(&ctx, opad, sizeof(opad));
	sha1_update(&ctx, inner, sizeof(inner));
	sha1_final(&ctx, out);
}

static int compare_bytes_lex(const uint8_t *a, const uint8_t *b, int len){
	int ret = 0;

	for (int i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			return a[i] - b[i];
		}
	}
	return ret;
}

int aic8800_decode_wpa_key_eapol(const uint8_t *eapol, int eapol_len, uint8_t *meta, int meta_len){
	int ret = 0;
	int body_len = 0;
	int key_info = 0;
	int key_data_len = 0;
	int key_data_end = 0;
	int key_len_field = 0;

	if (eapol == NULL || meta == NULL || meta_len < 32 || eapol_len < 99 || eapol[1] != 3 || eapol[4] != 2) {
		return ret;
	}
	body_len = get_u16_be(eapol, 2) + 4;
	if (body_len > eapol_len || body_len < 99) {
		return ret;
	}
	key_info = get_u16_be(eapol, 5);
	key_len_field = get_u16_be(eapol, 7);
	key_data_len = get_u16_be(eapol, 97);
	key_data_end = 99 + key_data_len;
	if (key_data_end > body_len) {
		return ret;
	}
	memset(meta, 0, meta_len);
	put_u32_le(meta, 0, body_len);
	put_u16_le(meta, 4, key_info);
	put_u16_le(meta, 6, key_data_len);
	put_u32_le(meta, 8, 99);
	put_u32_le(meta, 12, key_data_end);
	memcpy(meta + 16, eapol + 9, 8);
	meta[24] = (uint8_t)(key_info & 0x07);
	meta[25] = (key_info & 0x0008) ? 1 : 0;
	meta[26] = (key_info & 0x0080) ? 1 : 0;
	meta[27] = (key_info & 0x0100) ? 1 : 0;
	meta[28] = (key_info & 0x1000) ? 1 : 0;
	meta[29] = (key_info & 0x0200) ? 1 : 0;
	put_u16_le(meta, 30, key_len_field);
	ret = 1;
	return ret;
}

int aic8800_verify_wpa_key_mic(const uint8_t *eapol, int eapol_len, const uint8_t *kck, int kck_len){
	int ret = 0;
	int body_len = 0;
	uint8_t mic[20] = {};
	uint8_t tmp[512] = {};

	if (eapol == NULL || eapol_len < 99 || kck == NULL || kck_len == 0) {
		return ret;
	}
	body_len = get_u16_be(eapol, 2) + 4;
	if (body_len > eapol_len || body_len < 99) {
		return ret;
	}
	if (body_len > sizeof(tmp)) {
		return ret;
	}
	memcpy(tmp, eapol, body_len);
	memset(tmp + 81, 0, 16);
	hmac_sha1(kck, kck_len, tmp, body_len, mic);
	for (int i = 0; i < 16; i++) {
		if (mic[i] != eapol[81 + i]) {
			return ret;
		}
	}
	ret = 1;
	return ret;
}

int aic8800_validate_wpa2_context(const uint8_t *ssid, int ssid_len, const uint8_t *passphrase, int passphrase_len){
	int ret = 0;
	static const uint8_t hidden[] = {91,104,105,100,100,101,110,93};

	if ((ssid == NULL && ssid_len) || (passphrase == NULL && passphrase_len)) {
		return ret;
	}
	if (ssid_len == 0 || (ssid_len == sizeof(hidden) && compare_bytes_lex(ssid, hidden, sizeof(hidden)) == 0)) {
		ret = 2;
		return ret;
	}
	if (passphrase_len < 8 || passphrase_len > 63) {
		ret = 3;
		return ret;
	}
	ret = 1;
	return ret;
}

int aic8800_wpa_eapol_action(uint8_t *meta, int meta_len,
                              const uint8_t *da, int da_len, const uint8_t *local, int local_len,
                              const uint8_t *eapol, int eapol_len,
                              int associated, int completed, int busy){
	int ret = 0;
	u8 key_meta[32] = {};

	if (meta == NULL || meta_len < 36 || (da == NULL && da_len) || (local == NULL && local_len) || (eapol == NULL && eapol_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	/* Completed stations must still answer a retransmitted message 3 with
	 * message 4.  The caller serializes busy EAPOL work and queues one frame. */
	if (associated == 0 || busy) {
		ret = 1;
		return ret;
	}
	if (da_len < ETH_ALEN || local_len < ETH_ALEN || !aic8800_bytes_equal(da, ETH_ALEN, local, ETH_ALEN)) {
		ret = 1;
		return ret;
	}
	ret = aic8800_decode_wpa_key_eapol(eapol, eapol_len, key_meta, sizeof(key_meta));
	if(ret == 0) {
		ret = 1;
		return ret;
	}
	memcpy(meta + 4, key_meta, sizeof(key_meta));
	if (key_meta[24] != 2 || key_meta[25] == 0 || key_meta[26] == 0) {
		meta[0] = 3;
		ret = 1;
		return ret;
	}
	meta[0] = key_meta[27] ? 2 : 1;
	ret = 1;
	return ret;
}

int aic8800_build_eapol_eth_frame(uint8_t *out, int out_len,
                                   const uint8_t *bssid, int bssid_len,
                                   const uint8_t *local, int local_len,
                                   const uint8_t *eapol, int eapol_len){
	int ret = 0;

	if (out == NULL || !bssid || !local || (!eapol && eapol_len) || bssid_len < ETH_ALEN || local_len < ETH_ALEN || out_len < 14 + eapol_len) {
		return ret;
	}
	memcpy(out, bssid, ETH_ALEN);
	memcpy(out + ETH_ALEN, local, ETH_ALEN);
	out[12] = 0x88;
	out[13] = 0x8e;
	if (eapol_len) {
		memcpy(out + 14, eapol, eapol_len);
	}
	ret = 14 + eapol_len;
	return ret;
}

int aic8800_sha1(uint8_t *out, int out_len, const uint8_t *data, int data_len){
	int ret = 0;

	if (out == NULL || out_len < 20 || (data == NULL && data_len)) {
		return ret;
	}
	sha1_digest(data, data_len, out);
	ret = 20;
	return ret;
}

int aic8800_hmac_sha1(uint8_t *out, int out_len, const uint8_t *key, int key_len,
                       const uint8_t *data, int data_len){
	int ret = 0;

	if (out == NULL || out_len < 20 || (key == NULL && key_len) || (data == NULL && data_len)) {
		return ret;
	}
	hmac_sha1(key, key_len, data, data_len, out);
	ret = 20;
	return ret;
}

int aic8800_wpa_derive_pmk(uint8_t *out, int out_len, const uint8_t *passphrase, int passphrase_len,
                            const uint8_t *ssid, int ssid_len)
{
    if (!out || out_len < 32 || (!passphrase && passphrase_len) || (!ssid && ssid_len)) {
        return 0;
    }

    uint8_t salt_block[256];
    if (ssid_len + 4 > sizeof(salt_block)) {
        return 0;
    }
    memcpy(salt_block, ssid, ssid_len);

    int out_pos = 0;
    for (int block_index = 1; out_pos < 32; block_index++) {
        put_u32_be(salt_block, ssid_len, block_index);
        uint8_t u[20];
        uint8_t t[20];
        hmac_sha1(passphrase, passphrase_len, salt_block, ssid_len + 4, u);
        memcpy(t, u, 20);
        for (int iter = 1; iter < 4096; iter++) {
            hmac_sha1(passphrase, passphrase_len, u, 20, u);
            for (int i = 0; i < 20; i++) {
                t[i] ^= u[i];
            }
        }
        int take = (32 - out_pos) < 20 ? (32 - out_pos) : 20;
        memcpy(out + out_pos, t, take);
        out_pos += take;
    }
    return 32;
}

int aic8800_wpa_prf512(uint8_t *out, int out_len, const uint8_t *pmk, int pmk_len,
                        const uint8_t *amac, int amac_len, const uint8_t *smac, int smac_len,
                        const uint8_t *anonce, int anonce_len, const uint8_t *snonce, int snonce_len)
{
    if (!out || out_len < 64 || !pmk || pmk_len < 32 || !amac || !smac || !anonce || !snonce ||
        amac_len < ETH_ALEN || smac_len < ETH_ALEN || anonce_len < 32 || snonce_len < 32) {
        return 0;
    }

    static const uint8_t label[] = "Pairwise key expansion";
    const uint8_t *mac1 = amac;
    const uint8_t *mac2 = smac;
    if (compare_bytes_lex(mac1, mac2, ETH_ALEN) > 0) {
        mac1 = smac;
        mac2 = amac;
    }
    const uint8_t *nonce1 = anonce;
    const uint8_t *nonce2 = snonce;
    if (compare_bytes_lex(nonce1, nonce2, 32) > 0) {
        nonce1 = snonce;
        nonce2 = anonce;
    }

    uint8_t data[sizeof(label) - 1 + 1 + ETH_ALEN * 2 + 32 * 2 + 1];
    int off = 0;
    memcpy(data + off, label, sizeof(label) - 1); off += sizeof(label) - 1;
    data[off++] = 0;
    memcpy(data + off, mac1, ETH_ALEN); off += ETH_ALEN;
    memcpy(data + off, mac2, ETH_ALEN); off += ETH_ALEN;
    memcpy(data + off, nonce1, 32); off += 32;
    memcpy(data + off, nonce2, 32); off += 32;

    int out_pos = 0;
    for (int i = 0; out_pos < 64; i++) {
        data[off] = (uint8_t)i;
        uint8_t digest[20];
        hmac_sha1(pmk, pmk_len, data, off + 1, digest);
        int take = (64 - out_pos) < 20 ? (64 - out_pos) : 20;
        memcpy(out + out_pos, digest, take);
        out_pos += take;
    }
    return 64;
}

static int aic8800_build_wpa_key_eapol_ex(uint8_t *out, int out_len, int key_info, int key_len_field,
                                    const uint8_t *replay_counter, int replay_counter_len,
                                    const uint8_t *nonce, int nonce_len,
                                    const uint8_t *key_data, int key_data_len,
                                    const uint8_t *kck, int kck_len)
{
    if (!out || !replay_counter || replay_counter_len < 8 || (!nonce && nonce_len) || (!key_data && key_data_len) ||
        !kck || kck_len == 0 || out_len < 99 + key_data_len) {
        return 0;
    }

    int total = 99 + key_data_len;
    memset(out, 0, total);
    out[0] = 2;
    out[1] = 3;
    put_u16_be(out, 2, 95 + key_data_len);
    out[4] = 2;
    put_u16_be(out, 5, key_info);
    put_u16_be(out, 7, key_len_field);
    memcpy(out + 9, replay_counter, 8);
    if (nonce && nonce_len) {
        memcpy(out + 17, nonce, nonce_len < 32 ? nonce_len : 32);
    }
    put_u16_be(out, 97, key_data_len);
    if (key_data_len) {
        memcpy(out + 99, key_data, key_data_len);
    }
    uint8_t mic[20];
    hmac_sha1(kck, kck_len, out, total, mic);
    memcpy(out + 81, mic, 16);
    return total;
}

int aic8800_build_wpa_key_eapol(uint8_t *out, int out_len, int key_info,
                                 const uint8_t *replay_counter, int replay_counter_len,
                                 const uint8_t *nonce, int nonce_len,
                                 const uint8_t *key_data, int key_data_len,
                                 const uint8_t *kck, int kck_len)
{
    return aic8800_build_wpa_key_eapol_ex(out, out_len, key_info, WPA2_CCMP_KEY_LEN,
                                          replay_counter, replay_counter_len,
                                          nonce, nonce_len, key_data, key_data_len,
                                          kck, kck_len);
}

int aic8800_build_wpa_ap_message1(uint8_t *out, int out_len,
                                   const uint8_t *replay_counter, int replay_counter_len,
                                   const uint8_t *anonce, int anonce_len)
{
    if (!out || out_len < 99 || !replay_counter || replay_counter_len < 8 || !anonce || anonce_len < 32) {
        return 0;
    }
    memset(out, 0, 99);
    out[0] = 2;
    out[1] = 3;
    put_u16_be(out, 2, 95);
    out[4] = 2;
    put_u16_be(out, 5, 0x008au);
    put_u16_be(out, 7, WPA2_CCMP_KEY_LEN);
    memcpy(out + 9, replay_counter, 8);
    memcpy(out + 17, anonce, 32);
    put_u16_be(out, 97, 0);
    return 99;
}

static uint8_t aes_gmul(uint8_t a, uint8_t b){
	u8 p = 0;
	u8 hi = 0;

	for (int i = 0; i < 8; i++) {
		if (b & 1) {
			p ^= a;
	        }
		hi = a & 0x80;
		a <<= 1;
		if (hi) {
			a ^= 0x1bu;
		}
		b >>= 1;
	}
	return p;
}

static void aes_key_expansion(const uint8_t key[16], uint8_t round_key[176]){
    static const uint8_t rcon[] = {0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
    memcpy(round_key, key, 16);
    int bytes = 16;
    int rcon_idx = 1;
    uint8_t temp[4];
    while (bytes < 176) {
        memcpy(temp, round_key + bytes - 4, 4);
        if ((bytes % 16) == 0) {
            uint8_t t = temp[0];
            temp[0] = (uint8_t)(aes_sbox[temp[1]] ^ rcon[rcon_idx++]);
            temp[1] = aes_sbox[temp[2]];
            temp[2] = aes_sbox[temp[3]];
            temp[3] = aes_sbox[t];
        }
        for (int i = 0; i < 4; i++) {
            round_key[bytes] = (uint8_t)(round_key[bytes - 16] ^ temp[i]);
            bytes++;
        }
    }
}

static void aes_inv_shift_rows(uint8_t s[16]){
	uint8_t t = s[13]; s[13] = s[9]; s[9] = s[5]; s[5] = s[1]; s[1] = t;
	
	t = s[2];
	s[2] = s[10];
	s[10] = t;
	
	t = s[6];
	s[6] = s[14];
	s[14] = t;
	
	t = s[3];
	s[3] = s[7];
	s[7] = s[11];
	s[11] = s[15];
	s[15] = t;
}

static void aes_inv_sub_bytes(uint8_t s[16])
{
    for (int i = 0; i < 16; i++) {
        s[i] = aes_inv_sbox[s[i]];
    }
}

static void aes_add_round_key(uint8_t s[16], const uint8_t round_key[176], int round)
{
    for (int i = 0; i < 16; i++) {
        s[i] ^= round_key[round * 16 + i];
    }
}

static void aes_inv_mix_columns(uint8_t s[16])
{
    for (int c = 0; c < 4; c++) {
        int i = c * 4;
        uint8_t a0 = s[i];
        uint8_t a1 = s[i + 1];
        uint8_t a2 = s[i + 2];
        uint8_t a3 = s[i + 3];
        s[i] = (uint8_t)(aes_gmul(a0, 14) ^ aes_gmul(a1, 11) ^ aes_gmul(a2, 13) ^ aes_gmul(a3, 9));
        s[i + 1] = (uint8_t)(aes_gmul(a0, 9) ^ aes_gmul(a1, 14) ^ aes_gmul(a2, 11) ^ aes_gmul(a3, 13));
        s[i + 2] = (uint8_t)(aes_gmul(a0, 13) ^ aes_gmul(a1, 9) ^ aes_gmul(a2, 14) ^ aes_gmul(a3, 11));
        s[i + 3] = (uint8_t)(aes_gmul(a0, 11) ^ aes_gmul(a1, 13) ^ aes_gmul(a2, 9) ^ aes_gmul(a3, 14));
    }
}

static void aes128_decrypt_block(const uint8_t key[16], const uint8_t block[16], uint8_t out[16])
{
    uint8_t round_key[176];
    aes_key_expansion(key, round_key);
    memcpy(out, block, 16);
    aes_add_round_key(out, round_key, 10);
    for (int round = 9; round > 0; round--) {
        aes_inv_shift_rows(out);
        aes_inv_sub_bytes(out);
        aes_add_round_key(out, round_key, round);
        aes_inv_mix_columns(out);
    }
    aes_inv_shift_rows(out);
    aes_inv_sub_bytes(out);
    aes_add_round_key(out, round_key, 0);
}

static void aes_shift_rows(uint8_t s[16]){
	uint8_t t = s[1]; s[1] = s[5]; s[5] = s[9]; s[9] = s[13]; s[13] = t;

	t = s[2];
	s[2] = s[10];
	s[10] = t;

	t = s[6];
	s[6] = s[14];
	s[14] = t;

	t = s[3];
	s[3] = s[15];
	s[15] = s[11];
	s[11] = s[7];
	s[7] = t;
}

static void aes_sub_bytes(uint8_t s[16]){
	for (int i = 0; i < 16; i++) {
		s[i] = aes_sbox[s[i]];
	}
}

static void aes_mix_columns(uint8_t s[16]){
	for (int c = 0; c < 4; c++) {
		int i = c * 4;
		uint8_t a0 = s[i];
		uint8_t a1 = s[i + 1];
		uint8_t a2 = s[i + 2];
		uint8_t a3 = s[i + 3];
		s[i] = (uint8_t)(aes_gmul(a0, 2) ^ aes_gmul(a1, 3) ^ a2 ^ a3);
		s[i + 1] = (uint8_t)(a0 ^ aes_gmul(a1, 2) ^ aes_gmul(a2, 3) ^ a3);
		s[i + 2] = (uint8_t)(a0 ^ a1 ^ aes_gmul(a2, 2) ^ aes_gmul(a3, 3));
		s[i + 3] = (uint8_t)(aes_gmul(a0, 3) ^ a1 ^ a2 ^ aes_gmul(a3, 2));
	}
}

static void aes128_encrypt_block(const uint8_t key[16], const uint8_t block[16], uint8_t out[16]){
	uint8_t round_key[176] = {};

	aes_key_expansion(key, round_key);
	memcpy(out, block, 16);
	aes_add_round_key(out, round_key, 0);
	for (int round = 1; round < 10; round++) {
		aes_sub_bytes(out);
		aes_shift_rows(out);
		aes_mix_columns(out);
		aes_add_round_key(out, round_key, round);
	}
	aes_sub_bytes(out);
	aes_shift_rows(out);
	aes_add_round_key(out, round_key, 10);
}

int aic8800_aes_key_wrap(uint8_t *out, int out_len, const uint8_t *kek, int kek_len, const uint8_t *plain, int plain_len){
	int ret = 0;
	int n = 0;
	int t = 0;
	uint8_t a[8] ={};
	uint8_t r[32][8] = {};
	uint8_t enc[16] ={};
	uint8_t block[16] = {};

	if (out == NULL || kek == NULL || kek_len < 16 || !plain || plain_len < 8 || (plain_len % 8) != 0) {
		return ret;
	}
	n = plain_len / 8;
	if (out_len < (n + 1) * 8 || n > 32) {
		return ret;
	}

	memset(a, 0xa6, sizeof(a));
	for (int i = 0; i < n; i++) {
		memcpy(r[i], plain + i * 8, 8);
	}
	for (int j = 0; j < 6; j++) {
		for (int i = 1; i <= n; i++) {
			memcpy(block, a, 8);
			memcpy(block + 8, r[i - 1], 8);
			aes128_encrypt_block(kek, block, enc);
			memcpy(a, enc, 8);
			t = n * j + i;
			for (int k = 7; k >= 0 && t; k--) {
				a[k] ^= (uint8_t)(t & 0xffu);
				t >>= 8;
			}
		memcpy(r[i - 1], enc + 8, 8);
		}
	}

	memcpy(out, a, 8);
	for (int i = 0; i < n; i++) {
		memcpy(out + 8 * (i + 1), r[i], 8);
	}
	ret = (n + 1) * 8;
	return ret;
}

int aic8800_aes_key_unwrap(uint8_t *out, int out_len, const uint8_t *kek, int kek_len, const uint8_t *wrapped, int wrapped_len){
	int ret = 0;
	int n = 0;
	int t = 0;
	uint8_t a[8] = {};
	uint8_t dec[16] = {};
	uint8_t r[32][8] = {};
	uint8_t block[16] = {};

	if (out == NULL || kek == NULL || kek_len < 16 || !wrapped || wrapped_len < 16 || (wrapped_len % 8) != 0) {
		return ret;
	}
	n = wrapped_len / 8 - 1;
	if (out_len < n * 8 || n > 32) {
		return ret;
	}
	memcpy(a, wrapped, 8);
	for (int i = 0; i < n; i++) {
		memcpy(r[i], wrapped + 8 * (i + 1), 8);
	}
	for (int j = 5; j >= 0; j--) {
		for (int i = (int32_t)n; i >= 1; i--) {
			memcpy(block, a, 8);
			t = ((int)n * (int)j + (int)i);
			for (int k = 7; k >= 0 && t; k--) {
				block[k] ^= (uint8_t)(t & 0xffu);
				t >>= 8;
			}
			memcpy(block + 8, r[i - 1], 8);
			aes128_decrypt_block(kek, block, dec);
			memcpy(a, dec, 8);
			memcpy(r[i - 1], dec + 8, 8);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (a[i] != 0xa6) {
			return ret;
		}
	}
	for (int i = 0; i < n; i++) {
		memcpy(out + i * 8, r[i], 8);
	}
	ret = n * 8;
	return ret;
}

int aic8800_find_gtk_kde(const uint8_t *buf, int buf_len, uint8_t *meta, int meta_len){
	int ret = 0;
	int pos = 0;
	int len = 0;
	uint8_t eid = 0;

	if (buf == NULL || meta == NULL || meta_len < 8) {
		return ret;
	}
	memset(meta, 0, meta_len);
	while (pos + 2 <= buf_len) {
		eid = buf[pos];
		len = buf[pos + 1];
		if (pos + 2 + len > buf_len) {
			return ret;
		}
		/* Message 3 starts with an RSN IE; keep scanning for the GTK KDE. */
		if (eid == 0xdd && len >= 22 && buf[pos + 2] == 0x00 && buf[pos + 3] == 0x0f &&
			buf[pos + 4] == 0xac && buf[pos + 5] == 0x01) {
			meta[0] = (uint8_t)(buf[pos + 6] & 0x03);
			put_u32_le(meta, 1, pos + 8);
			put_u16_le(meta, 5, len - 6);
			ret = 1;
			return ret;
		}
		pos += 2 + len;
	}
	return ret;
}

/* aic8800_write_pcap_global_header: generate the pcap header, invoked by the user for saving the monitor mode data */
int aic8800_write_pcap_global_header(uint8_t *out, int out_len){
	int ret = 0;

	if (out == NULL || out_len < 24) {
		return ret;
	}
	/* '0xa1b2c3d4' is the magic number for pcap */
	put_u32_le(out, 0, 0xa1b2c3d4);
	put_u16_le(out, 4, 2);
	put_u16_le(out, 6, 4);
	put_u32_le(out, 8, 0);
	put_u32_le(out, 12, 0);
	put_u32_le(out, 16, PCAP_SNAPLEN);
	put_u32_le(out, 20, PCAP_LINKTYPE_IEEE802_11);
	/* total size written */
	ret = 24;
	return ret;
}

int aic8800_write_pcap_record_header(uint8_t *out, int out_len, int ts_sec, int ts_usec, int captured_len, int original_len){
	int ret = 0;

	if (out == NULL || out_len < 16) {
		return ret;
	}
	put_u32_le(out, 0, ts_sec);
	put_u32_le(out, 4, ts_usec);
	put_u32_le(out, 8, captured_len);
	put_u32_le(out, 12, original_len);
	ret = 16;
	return ret;
}

/* aic8800_build_pcap_file: main function for building the entire pcap file, usually created for storing the frames captured in monitor mode */
int aic8800_build_pcap_file(uint8_t *out, int out_len, const uint8_t *frames, int frames_len, const uint8_t *meta, int meta_len){
	int ret = 0;
	int m = 0;
	int ts_sec = 0;
	int ts_usec = 0;
	int cap_len = 0;
	int out_off = 0;
	int data_off = 0;
	int orig_len = 0;
	int frame_count = 0;

	if (out == NULL || (frames == NULL && frames_len) || meta == NULL || (meta_len % 20) != 0) {
		return ret;
	}
	frame_count = meta_len / 20;
	/* store in 'out_off' the total size of the pcap header bytes */
	out_off = aic8800_write_pcap_global_header(out, out_len);
	if (out_off == 0) {
		return ret;
	}
	for (int i = 0; i < frame_count; i++) {
		m = i * 20;
		data_off = get_u32_le(meta, m);
		cap_len = get_u32_le(meta, m + 4);
		orig_len = get_u32_le(meta, m + 8);
		ts_sec = get_u32_le(meta, m + 12);
		ts_usec = get_u32_le(meta, m + 16);
		if (cap_len > PCAP_SNAPLEN || data_off > frames_len || cap_len > frames_len - data_off) {
			return ret;
		}
		if (out_off > out_len || 16 + cap_len > out_len - out_off) {
			return ret;
		}
		ret = aic8800_write_pcap_record_header(out + out_off, out_len - out_off, ts_sec, ts_usec, cap_len, orig_len);
		if(ret == 0){
			return ret;
		}
		out_off += 16;
		if (cap_len) {
			memcpy(out + out_off, frames + data_off, cap_len);
			out_off += cap_len;
		}
	}
	ret = out_off;
	return ret;
}

static int ascii_equal_lower_cstr(const uint8_t *text, int len, const char *name){
	int ret = 0;
	int i = 0;

	while (i < len && name[i]) {
		if (aic8800_ascii_lower(text[i]) != (uint8_t)name[i]) {
			return ret;
		}
		i++;
	}
	return i == len && name[i] == 0;
}

static int kv_find_one(const uint8_t *opts, int opts_len, const char *name, const uint8_t **value, int *value_len){
	int ret = 0;
	int pos = 0;
	int val_len = 0;
	int key_len = 0;
	int key_start = 0;
	int val_start = 0;

	while (pos < opts_len) {
		key_start = pos;
		while (pos < opts_len && opts[pos] != 0) {
			pos++;
		}
		if (pos >= opts_len) {
			break;
		}
		key_len = pos - key_start;
		pos++;
		val_start = pos;
		while (pos < opts_len && opts[pos] != 0) {
			pos++;
		}
		val_len = pos - val_start;
		if (pos < opts_len) {
			pos++;
		}
		ret = ascii_equal_lower_cstr(opts + key_start, key_len, name);
		if(ret) {
			*value = opts + val_start;
			*value_len = val_len;
			ret = 1;
			return ret;
		}
	}
	return ret;
}

/* kv_find_any: search for a string in a names group (used for retrieving a config value inside a config string array names) */
static int kv_find_any(const uint8_t *opts, int opts_len, const char *const *names, int name_count, const uint8_t **value, int *value_len){
	int ret = 0;

	for (int i = 0; i < name_count; i++) {
		if (kv_find_one(opts, opts_len, names[i], value, value_len)) {
			ret = 1;
			return ret;
		}
	}
	return ret;
}

static int prev_string_at(const uint8_t *strings, int strings_len, int wanted, const uint8_t **value, int *value_len){
	int ret = 0;
	int pos = 0;
	int index = 0;
	int start = 0;

	while (pos < strings_len) {
		start = pos;
		while (pos < strings_len && strings[pos] != 0) {
			pos++;
		}
		if (index == wanted) {
			*value = strings + start;
			*value_len = pos - start;
			ret = 1;
			return ret;
		}
		index++;
		if (pos < strings_len) {
			pos++;
		}
	}
	return ret;
}

static int write_string_field(uint8_t *out, int out_len, int *off, const uint8_t *value, int value_len, const char *fallback, int lower){
	int ret = 0;

	if (!value) {
		value = (const uint8_t *)fallback;
		value_len = 0;
		while (fallback[value_len]) {
			value_len++;
		}
	}
	if (*off + value_len + 1 > out_len) {
		return ret;
	}
	for (int i = 0; i < value_len; i++) {
		out[(*off)++] = lower ? aic8800_ascii_lower(value[i]) : value[i];
	}
	out[(*off)++] = 0;
	ret = 1;
	return ret;
}

static int parse_option_number_any(const uint8_t *opts, int opts_len, const char *const *names, int name_count, int fallback, int min_value, int max_value, int *out){
	int ret = 0;
	int parsed = 0;
	int value_len = 0;
	uint8_t *value = NULL;

	ret = kv_find_any(opts, opts_len, names, name_count, &value, &value_len);
	if(ret == 0) {
		*out = fallback;
		ret = 1;
		return ret;
	}
	ret = parse_u32_ascii(value, value_len, &parsed);
	if(ret == 0 || parsed < min_value || parsed > max_value){
		return ret;
	}
	*out = parsed;
	ret = 1;
	return ret;
}

static int parse_option_bool_any(const uint8_t *opts, int opts_len, const char *const *names, int name_count, int fallback){
	int ret = 0;
	int value_len = 0;
	const uint8_t *value = NULL;

	ret = kv_find_any(opts, opts_len, names, name_count, &value, &value_len);
	if(ret) {
		return fallback ? 1 : 0;
	}
	ret = aic8800_owfuzz_parse_bool(value, value_len, fallback);
	return ret;
}

static int parse_option_mac_any(const uint8_t *opts, int opts_len, const char *const *names, int name_count, const uint8_t *fallback, uint8_t out[ETH_ALEN]){
	int ret = 0;
	int value_len = 0;
	const uint8_t *value = 0;

	ret = kv_find_any(opts, opts_len, names, name_count, &value, &value_len);
	if(ret && value_len) {
		ret = parse_mac_text(value, value_len, out);
		return ret;
	}
	memcpy(out, fallback, ETH_ALEN);
	ret = 1;
	return ret;
}

/* aic8800_build_wpa_message2: build the wpa2 eapol msg during AP connection */
int aic8800_build_wpa_message2(uint8_t *out, int out_len,
                                const uint8_t *replay_counter, int replay_counter_len,
                                const uint8_t *snonce, int snonce_len,
                                const uint8_t *kck, int kck_len){
	int ret = 0;

	ret = aic8800_build_wpa_key_eapol_ex(out, out_len, 0x010au, 0, replay_counter, replay_counter_len, snonce, snonce_len, ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie), kck, kck_len);
	return ret;
}

/* aic8800_build_wpa_message4: build the wpa2 eapol msg during AP connection */
int aic8800_build_wpa_message4(uint8_t *out, int out_len,
                                const uint8_t *replay_counter, int replay_counter_len,
                                const uint8_t *kck, int kck_len){
	int ret = 0;

	ret = aic8800_build_wpa_key_eapol_ex(out, out_len, 0x030au, 0, replay_counter, replay_counter_len, 0, 0, 0, 0, kck, kck_len);
	return ret;
}

int aic8800_wpa_prepare_context(uint8_t *meta, int meta_len, const uint8_t *ssid, int ssid_len, const uint8_t *passphrase, int passphrase_len, const uint8_t *bssid_text, int bssid_text_len){
	int ret = 0;
	int validation = 0;

	if (meta == NULL || meta_len < 16 || (ssid == NULL && ssid_len) || (!passphrase && passphrase_len) || (!bssid_text && bssid_text_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	validation = aic8800_validate_wpa2_context(ssid, ssid_len, passphrase, passphrase_len);
	put_u32_le(meta, 0, validation);
	put_u32_le(meta, 4, ssid_len);
	if (validation != 1) {
		ret = 1;
		return ret;
	}
	if (bssid_text && bssid_text_len) {
		ret = parse_mac_text(bssid_text, bssid_text_len, meta + 8);
		if(ret == 0) {
			put_u32_le(meta, 0, 4);
			ret = 1;
			return ret;
		}
		meta[14] = 1;
	}
	ret = 1;
	return ret;
}

int aic8800_wpa_build_message1_material(uint8_t *out, int out_len, uint8_t *meta, int meta_len,
                                         const uint8_t *ssid, int ssid_len,
                                         const uint8_t *passphrase, int passphrase_len,
                                         const uint8_t *ap_mac, int ap_mac_len,
                                         const uint8_t *local_mac, int local_mac_len,
                                         const uint8_t *eapol, int eapol_len,
                                         const uint8_t *snonce, int snonce_len){
	int ret = 0;
	int msg2_len = 0;
	int eapol_len_body = 0;
	uint8_t key_meta[32] = {};

	if (out == NULL || out_len < AIC_WPA_M1_OUT_SIZE || meta == NULL || meta_len < AIC_WPA_M1_META_SIZE ||
        ssid == NULL || passphrase == NULL || ap_mac == NULL || local_mac == NULL || eapol == NULL || snonce == NULL ||
        ap_mac_len < ETH_ALEN || local_mac_len < ETH_ALEN || snonce_len < 32) {
		return ret;
	}
	ret = aic8800_decode_wpa_key_eapol(eapol, eapol_len, key_meta, sizeof(key_meta));
	if(ret == 0) {
		return ret;
	}
	eapol_len_body = get_u32_le(key_meta, 0);
	if (eapol_len_body < 49 || eapol_len_body > eapol_len) {
		return ret;
	}
	memset(out, 0, AIC_WPA_M1_OUT_SIZE);
	memset(meta, 0, meta_len);
	memcpy(out + AIC_WPA_M1_ANONCE_OFF, eapol + 17, 32);
	memcpy(out + AIC_WPA_M1_SNONCE_OFF, snonce, 32);
	ret = aic8800_wpa_derive_pmk(out + AIC_WPA_M1_PMK_OFF, 32, passphrase, passphrase_len, ssid, ssid_len);
	if(ret == 0) {
		return ret;
	}
	if (!aic8800_wpa_prf512(out + AIC_WPA_M1_PTK_OFF, 64, out + AIC_WPA_M1_PMK_OFF, 32,
                        ap_mac, ap_mac_len, local_mac, local_mac_len,
                        out + AIC_WPA_M1_ANONCE_OFF, 32, out + AIC_WPA_M1_SNONCE_OFF, 32)) {
		return ret;
	}
	msg2_len = aic8800_build_wpa_key_eapol_ex(out + AIC_WPA_M1_MSG2_OFF, out_len - AIC_WPA_M1_MSG2_OFF,
                                                   0x010a, 0, key_meta + 16, 8,
                                                   out + AIC_WPA_M1_SNONCE_OFF, 32,
                                                   ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie),
                                                   out + AIC_WPA_M1_PTK_OFF, 16);
	if (msg2_len == 0) {
		return ret;
	}
	put_u32_le(meta, 0, AIC_WPA_M1_ANONCE_OFF);
	put_u32_le(meta, 4, AIC_WPA_M1_SNONCE_OFF);
	put_u32_le(meta, 8, AIC_WPA_M1_PMK_OFF);
	put_u32_le(meta, 12, AIC_WPA_M1_PTK_OFF);
	put_u32_le(meta, 16, AIC_WPA_M1_MSG2_OFF);
	put_u32_le(meta, 20, msg2_len);
	memcpy(meta + 24, key_meta + 16, 8);
	ret = AIC_WPA_M1_MSG2_OFF + msg2_len;
	return ret;
}

int aic8800_wpa_build_message3_material(uint8_t *out, int out_len, uint8_t *meta, int meta_len,
                                         const uint8_t *eapol, int eapol_len,
                                         const uint8_t *ptk, int ptk_len){
	int ret = 0;
	int out_off = 0;
	int body_len = 0;
	int plain_len = 0;
	int unwrapped = 0;
	int key_data_len = 0;
	int key_data_off = 0;
	int key_data_end = 0;
	uint8_t key_meta[32] = {};
	uint8_t unwrap_buf[256] = {};
	const uint8_t *plain = NULL;

	if (out == NULL || meta == NULL || meta_len < 24 || !eapol || !ptk || ptk_len < 48 || out_len < 128) {
		return ret;
	}
	memset(out, 0, out_len);
	memset(meta, 0, meta_len);
	ret = aic8800_decode_wpa_key_eapol(eapol, eapol_len, key_meta, sizeof(key_meta));
	if(ret == 0) {
		put_u32_le(meta, 0, 1);
		ret = 1;
		return ret;
	}
	body_len = get_u32_le(key_meta, 0);
	if (body_len > eapol_len || !aic8800_verify_wpa_key_mic(eapol, body_len, ptk, 16)) {
		put_u32_le(meta, 0, 2);
		ret = 1;
		return ret;
	}
	if (key_meta[24] != 2 || key_meta[25] == 0 || key_meta[26] == 0 || key_meta[27] == 0 ||
	    key_meta[29] == 0 || (get_u16_le(key_meta, 4) & 0x0040u) == 0) {
		put_u32_le(meta, 0, 3);
		return ret;
	}
	out_off = 0;
	key_data_len = get_u16_le(key_meta, 6);
	if (key_meta[28] && key_data_len == 0) {
		put_u32_le(meta, 0, 4);
		return ret;
	}
	if (key_data_len > 0) {
		key_data_off = get_u32_le(key_meta, 8);
		key_data_end = get_u32_le(key_meta, 12);
        if (key_data_end <= eapol_len && key_data_end >= key_data_off) {
		plain = eapol + key_data_off;
		plain_len = key_data_end - key_data_off;
			if (key_meta[28]) {
				if (plain_len < 16 || plain_len > sizeof(unwrap_buf) + 8 || (plain_len & 7)) {
					put_u32_le(meta, 0, 4);
					return 1;
				}
		unwrapped = aic8800_aes_key_unwrap(unwrap_buf, sizeof(unwrap_buf), ptk + 16, 16, plain, plain_len);
				if (!unwrapped) {
					put_u32_le(meta, 0, 4);
					return 1;
				}
				plain = unwrap_buf;
				plain_len = unwrapped;
            }
            uint8_t gtk_meta[8];
            if (aic8800_find_gtk_kde(plain, plain_len, gtk_meta, sizeof(gtk_meta))) {
                int gtk_off = get_u32_le(gtk_meta, 1);
                int gtk_len = get_u16_le(gtk_meta, 5);
				if (gtk_off + WPA2_CCMP_KEY_LEN <= plain_len && gtk_len == WPA2_CCMP_KEY_LEN) {
					memcpy(out, plain + gtk_off, WPA2_CCMP_KEY_LEN);
                    out_off = 16;
                    meta[4] = 1;
                    meta[5] = gtk_meta[0] & 0x03;
                    put_u32_le(meta, 8, 0);
					put_u32_le(meta, 12, WPA2_CCMP_KEY_LEN);
                }
            }
			if (key_meta[28] && meta[4] == 0) {
				put_u32_le(meta, 0, 5);
				return 1;
			}
        }
    }
    int msg4_off = out_off;
    int msg4_len = aic8800_build_wpa_key_eapol_ex(out + msg4_off, out_len - msg4_off,
                                                   0x030au, 0, key_meta + 16, 8,
                                                   0, 0, 0, 0, ptk, 16);
    if (!msg4_len) {
        put_u32_le(meta, 0, 3);
        return 1;
    }
    put_u32_le(meta, 0, 0);
    put_u32_le(meta, 16, msg4_off);
    put_u32_le(meta, 20, msg4_len);
    return msg4_off + msg4_len;
}

static int wpa_append_ap_key_data(uint8_t *out, int out_len, const uint8_t *gtk, int gtk_len, int gtk_key_index)
{
    int off = 0;

    if (!out || !gtk || gtk_len < 16 || gtk_len > 32 || out_len < 80) {
        return 0;
    }
    memcpy(out + off, ap_wpa2_psk_rsn_ie, sizeof(ap_wpa2_psk_rsn_ie));
    off += sizeof(ap_wpa2_psk_rsn_ie);

    out[off++] = 0xddu;
    out[off++] = (uint8_t)(6 + gtk_len);
    out[off++] = 0x00;
    out[off++] = 0x0f;
    out[off++] = 0xac;
    out[off++] = 0x01;
    out[off++] = (uint8_t)(gtk_key_index & 0x03);
    out[off++] = 0x00;
    memcpy(out + off, gtk, gtk_len);
    off += gtk_len;

    if (off & 7) {
        out[off++] = 0xdd;
        while (off & 7) {
            out[off++] = 0x00;
        }
    }
    return off;
}

int aic8800_wpa_ap_build_message3_material(uint8_t *out, int out_len, uint8_t *meta, int meta_len,
                                            const uint8_t *ssid, int ssid_len,
                                            const uint8_t *passphrase, int passphrase_len,
                                            const uint8_t *ap_mac, int ap_mac_len,
                                            const uint8_t *sta_mac, int sta_mac_len,
                                            const uint8_t *eapol_m2, int eapol_m2_len,
                                            const uint8_t *anonce, int anonce_len,
                                            const uint8_t *gtk, int gtk_len, int gtk_key_index,
                                            const uint8_t *replay_counter, int replay_counter_len)
{
    uint8_t key_meta[32];
	uint8_t pmk[32] = {};
	uint8_t plain[128];
    uint8_t wrapped[144];
    int plain_len = 0;
    int wrapped_len = 0;
    int msg3_len = 0;
    int body_len = 0;
    const uint8_t *snonce = NULL;

    if (!out || out_len < AIC_WPA_AP_M3_OUT_SIZE || !meta || meta_len < AIC_WPA_AP_M3_META_SIZE ||
        !ssid || !passphrase || !ap_mac || !sta_mac || !eapol_m2 || !anonce || !gtk || !replay_counter ||
        ap_mac_len < ETH_ALEN || sta_mac_len < ETH_ALEN || anonce_len < 32 || gtk_len < 16 || replay_counter_len < 8) {
        return 0;
    }
    memset(out, 0, out_len);
    memset(meta, 0, meta_len);

    if (!aic8800_decode_wpa_key_eapol(eapol_m2, eapol_m2_len, key_meta, sizeof(key_meta))) {
        put_u32_le(meta, 0, 1);
        return 1;
    }
    if (key_meta[24] != 2 || key_meta[25] == 0 || key_meta[26] != 0 || key_meta[27] == 0 || key_meta[29] != 0) {
        put_u32_le(meta, 0, 2);
        return 1;
    }
    body_len = get_u32_le(key_meta, 0);
    if (body_len > eapol_m2_len || body_len < 99) {
        put_u32_le(meta, 0, 1);
        return 1;
    }
    snonce = eapol_m2 + 17;

    if (!aic8800_wpa_derive_pmk(pmk, sizeof(pmk), passphrase, passphrase_len, ssid, ssid_len)) {
        put_u32_le(meta, 0, 4);
        return 1;
    }
    if (!aic8800_wpa_prf512(out + AIC_WPA_AP_M3_PTK_OFF, 64, pmk, sizeof(pmk),
                            ap_mac, ap_mac_len, sta_mac, sta_mac_len,
                            anonce, 32, snonce, 32)) {
        put_u32_le(meta, 0, 4);
        return 1;
    }
    if (!aic8800_verify_wpa_key_mic(eapol_m2, body_len, out + AIC_WPA_AP_M3_PTK_OFF, 16)) {
        put_u32_le(meta, 0, 3);
        return 1;
    }

    plain_len = wpa_append_ap_key_data(plain, sizeof(plain), gtk, gtk_len, gtk_key_index);
    if (!plain_len) {
        put_u32_le(meta, 0, 5);
        return 1;
    }
    wrapped_len = aic8800_aes_key_wrap(wrapped, sizeof(wrapped), out + AIC_WPA_AP_M3_PTK_OFF + 16, 16, plain, plain_len);
    if (!wrapped_len) {
        put_u32_le(meta, 0, 5);
        return 1;
    }

    msg3_len = aic8800_build_wpa_key_eapol(out + AIC_WPA_AP_M3_MSG3_OFF, out_len - AIC_WPA_AP_M3_MSG3_OFF,
                                           0x13cau, replay_counter, replay_counter_len,
                                           anonce, anonce_len, wrapped, wrapped_len,
                                           out + AIC_WPA_AP_M3_PTK_OFF, 16);
    if (!msg3_len) {
        put_u32_le(meta, 0, 5);
        return 1;
    }

    put_u32_le(meta, 0, 0);
    put_u32_le(meta, 4, AIC_WPA_AP_M3_PTK_OFF);
    put_u32_le(meta, 8, 64);
    put_u32_le(meta, 12, AIC_WPA_AP_M3_MSG3_OFF);
    put_u32_le(meta, 16, msg3_len);
    put_u32_le(meta, 20, wrapped_len);
    meta[24] = (uint8_t)(gtk_key_index & 0x03);
    return AIC_WPA_AP_M3_MSG3_OFF + msg3_len;
}

int aic8800_wpa_ap_verify_message4(const uint8_t *eapol, int eapol_len,
                                    const uint8_t *ptk, int ptk_len,
                                    const uint8_t *expected_replay, int expected_replay_len)
{
    uint8_t key_meta[32];

    if (!eapol || !ptk || ptk_len < 16 || !expected_replay || expected_replay_len < 8) {
        return 1;
    }
    if (!aic8800_decode_wpa_key_eapol(eapol, eapol_len, key_meta, sizeof(key_meta))) {
        return 1;
    }
    if (key_meta[24] != 2 || key_meta[25] == 0 || key_meta[26] != 0 || key_meta[27] == 0 || key_meta[29] == 0) {
        return 2;
    }
    if (memcmp(key_meta + 16, expected_replay, 8) != 0) {
        return 3;
    }
    if (!aic8800_verify_wpa_key_mic(eapol, get_u32_le(key_meta, 0), ptk, 16)) {
        return 4;
    }
    return 0;
}

int aic8800_fw_step_label(uint8_t *out, int out_len, int step)
{
    switch (step) {
    case AIC_FW_STEP_READ_CHIP: return write_ascii_string(out, out_len, "reading chip");
    case AIC_FW_STEP_UPLOAD_FW: return write_ascii_string(out, out_len, "uploading firmware");
    case AIC_FW_STEP_PATCH_CONFIG: return write_ascii_string(out, out_len, "patch config");
    case AIC_FW_STEP_START_APP: return write_ascii_string(out, out_len, "starting app");
    case AIC_FW_STEP_REENUMERATE: return write_ascii_string(out, out_len, "start sent");
    case AIC_FW_STEP_INIT_STACK: return write_ascii_string(out, out_len, "initializing STA");
    case AIC_FW_STEP_DONE: return write_ascii_string(out, out_len, "ready");
    default: return write_ascii_string(out, out_len, "-");
    }
}

int aic8800_build_stack_start_params(uint8_t *out, int out_len, int use_vendor_info_bit)
{
    struct mm_set_stack_start_req *req = (struct mm_set_stack_start_req *)out;

    if (!out || out_len < sizeof(*req)) {
        return 0;
    }
    memset(req, 0, sizeof(*req));
    req->is_stack_start = 1;
    req->efuse_valid = 0;
    req->set_vendor_info = use_vendor_info_bit ? (1 << 5) : 0;
    req->fwtrace_redir = 0;
    return sizeof(*req);
}

int aic8800_decode_fw_version_text(uint8_t *out, int out_len, const uint8_t *params, int params_len)
{
    if (!out || !params || params_len == 0) {
        return 0;
    }
    int len = params[0];
    if (len > params_len - 1) len = params_len - 1;
    if (len > 63) len = 63;
    if (out_len < len) {
        return 0;
    }
    int written = 0;
    for (int i = 0; i < len; i++) {
        uint8_t c = params[1 + i];
        if (c == 0) break;
        out[written++] = c;
    }
    return written;
}

int aic8800_select_mac_from_cfm(uint8_t *out, int out_len, uint8_t *meta, int meta_len,
                                 const uint8_t *params, int params_len)
{
    if (!out || out_len < ETH_ALEN || !meta || meta_len < 4) {
        return 0;
    }
    memset(meta, 0, meta_len);
    if (params && params_len >= ETH_ALEN && (params[0] || params[1] || params[2] || params[3])) {
        memcpy(out, params, ETH_ALEN);
        put_u32_le(meta, 0, 1);
    } else {
        aic8800_default_mac(out, out_len);
        put_u32_le(meta, 0, 0);
    }
    return ETH_ALEN;
}

int aic8800_decode_add_if_cfm(uint8_t *meta, int meta_len, const uint8_t *params, int params_len){
	int ret = 0;

	if (meta == NULL|| meta_len < 8) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (params == NULL || params_len < 2) {
		put_u32_le(meta, 0, 0xffffffffu);
		put_u32_le(meta, 4, IFACE_INVALID);
		ret = 1;
		return ret;
	}
	put_u32_le(meta, 0, params[0]);
	put_u32_le(meta, 4, params[1]);
	ret = 1;
	return ret;
}

int aic8800_decode_status_cfm(uint8_t *meta, int meta_len, const uint8_t *params, int params_len){
	int ret = 0;

	if (meta == NULL || meta_len < 4) {
		return ret;
	}
	put_u32_le(meta, 0, (params && params_len > 0) ? params[0] : 0);
	ret = 1;
	return ret;
}

int aic8800_lmac_response_route(int id){
	int ret = 0;

	if (id == ((4 << 10) + 4)){
		ret = AIC_LMAC_ROUTE_SCAN_RESULT;
		return ret;
	}
	if (id == ((6 << 10) + 2)){
		ret = AIC_LMAC_ROUTE_CONNECT_IND;
		return ret;
	}
	ret = AIC_LMAC_ROUTE_NONE;
	return ret;
}

int aic8800_lmac_confirm_can_wait(int confirm_id, int already_pending){
	int ret = 0;

	if (confirm_id == 0xffffffffu){
		ret = 1;
		return ret;
	}
	if(already_pending){
		return ret;
	}else{
		ret = 1;
		return ret;
	}
}

int aic8800_lmac_confirm_message(uint8_t *out, int out_len, int kind, int confirm_id)
{
    int off = 0;
    const char *prefix = kind == 1 ? "confirmation 0x" : kind == 2 ? "timeout waiting for confirmation 0x" : "device disconnected while waiting for 0x";
    if (!append_ascii_cstr(out, out_len, &off, prefix) || !append_hex_u32(out, out_len, &off, confirm_id, 4)) {
        return 0;
    }
    if (kind == 1 && !append_ascii_cstr(out, out_len, &off, " already pending")) {
        return 0;
    }
    return off;
}

int aic8800_network_merge_plan(uint8_t *meta, int meta_len, const uint8_t *prev_ssid, int prev_ssid_len, const uint8_t *new_ssid, int new_ssid_len){
	int ret = 0;
	int use_prev = 0;
	int log_change = 0;
	int new_hidden = 0;
	int prev_hidden = 0;
	static const uint8_t hidden[] = { 91, 104, 105, 100, 100, 101, 110, 93 };

	if (meta == NULL || meta_len < 8 || (prev_ssid == NULL && prev_ssid_len) || (new_ssid == NULL && new_ssid_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	prev_hidden = prev_ssid_len == sizeof(hidden) && compare_bytes_lex(prev_ssid, hidden, sizeof(hidden)) == 0;
	new_hidden = new_ssid_len == sizeof(hidden) && compare_bytes_lex(new_ssid, hidden, sizeof(hidden)) == 0;
	use_prev = prev_ssid_len && !prev_hidden && new_hidden;
	log_change = !prev_ssid_len || prev_ssid_len != new_ssid_len || compare_bytes_lex(prev_ssid, new_ssid, prev_ssid_len < new_ssid_len ? prev_ssid_len : new_ssid_len) != 0;
	if (use_prev) {
		log_change = 0;
	}
	put_u32_le(meta, 0, use_prev);
	put_u32_le(meta, 4, log_change);
	ret = 1;
	return ret;
}

/* aic8800_format_network_line: given a Wi-Fi network, format it's parameters (bssid, Mhz, freq and rssi) and print them */
int aic8800_format_network_line(uint8_t *out, int out_len, const uint8_t *ssid, int ssid_len, const uint8_t *bssid, int bssid_len, int freq, int32_t rssi, int scan_prefix){
	int ret = 0;
	int off = 0;

	if (out == NULL || (ssid == NULL && ssid_len) || (bssid == NULL && bssid_len)) {
		return ret;
	}
	if (scan_prefix && !append_ascii_cstr(out, out_len, &off, "[scan] ")){
		return ret;
	}
	for (int i = 0; i < ssid_len; i++) {
		if (!append_ascii_byte(out, out_len, &off, ssid[i])){
			return ret;
		}
	}
	if (scan_prefix) {
		if (!append_ascii_cstr(out, out_len, &off, " bssid=")){
			return ret;
		}
	}else if (!append_ascii_byte(out, out_len, &off, 32)){
		return ret;
	}
	for (int i = 0; i < bssid_len; i++) {
		if (!append_ascii_byte(out, out_len, &off, bssid[i])){
			return ret;
		}
	}
	if (!scan_prefix) {
        if (!append_ascii_byte(out, out_len, &off, 32) || !append_dec_u32(out, out_len, &off, freq) ||
            !append_ascii_cstr(out, out_len, &off, "MHz ")) return 0;
        if (rssi < 0) {
            if (!append_ascii_byte(out, out_len, &off, 45)) return 0;
            rssi = -rssi;
        }
        if (!append_dec_u32(out, out_len, &off, rssi) || !append_ascii_cstr(out, out_len, &off, "dBm")) return 0;
    } else {
        if (!append_ascii_cstr(out, out_len, &off, " freq=") || !append_dec_u32(out, out_len, &off, freq) ||
            !append_ascii_cstr(out, out_len, &off, " rssi=")) return 0;
        if (rssi < 0) {
            if (!append_ascii_byte(out, out_len, &off, 45)) return 0;
            rssi = -rssi;
        }
        if (!append_dec_u32(out, out_len, &off, rssi)) return 0;
    }
    return off;
}

int aic8800_usb_select_best_interface(uint8_t *meta, int meta_len, const uint8_t *records, int records_len, int product_id, int ram_mode){
	int ret = 0;
	int score = 0;
	int count = 0;
	int vendor = 0;
	int in_count = 0;
	int out_count = 0;
	int best_score = 0;
	int best_index = 0;
	int best_vendor = 0;
	int iface_class = 0;
	int iface_subclass = 0;
	int iface_protocol = 0;
	int prefer_storage = 0;
	uint8_t *r = NULL;

	if (meta == NULL || meta_len < 16 || (records == NULL && records_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	prefer_storage = aic8800_usb_is_storage_product(product_id);
	best_score = 0;
	best_index = 0xffffffffu;
	best_vendor = 0;
	count = records_len / 32;
	for (int i = 0; i < count; i++) {
		r = records + i * 32;
		iface_class = get_u32_le(r, 8);
		iface_subclass = get_u32_le(r, 12);
		iface_protocol = get_u32_le(r, 16);
		in_count = get_u32_le(r, 20);
		out_count = get_u32_le(r, 24);
		score = aic8800_usb_interface_score(iface_class, iface_subclass, iface_protocol, in_count, out_count, prefer_storage);
		vendor = aic8800_usb_is_vendor_alternate(iface_class, iface_subclass, iface_protocol);
		if (score && (!best_score || score > best_score)) {
			best_score = score;
			best_index = i;
			best_vendor = vendor;
		}
	}
	if (ram_mode && best_score && !best_vendor) {
		put_u32_le(meta, 0, 2);
		return ret;
	}
	put_u32_le(meta, 0, best_score ? 1 : 0);
	put_u32_le(meta, 4, best_index);
	put_u32_le(meta, 8, best_score);
	put_u32_le(meta, 12, best_vendor);
	return 1;
}

/* aic8800_decode_fw_print_text: decode the firmware logs from the aic8800 dongle */
int aic8800_decode_fw_print_text(uint8_t *out, int out_len, const uint8_t *block, int block_len, int pkt_len){
	int ret = 0;
	int len = 0;
	uint8_t c = 0;

	if (out == NULL || block == NULL || block_len < 4) {
		return ret;
	}
	len = pkt_len;
	if (len > block_len - 4) {
		len = block_len - 4;
	}
	while (len > 0 && block[4 + len - 1] == 0) {
		len--;
	}
	if (len > out_len) {
		return ret;
	}
	for (int i = 0; i < len; i++) {
		c = block[4 + i];
		out[i] = (c >= 0x20 && c <= 0x7eu) || c == '\n' || c == '\r' || c == '\t' ? c : '.';
	}
	if(len){
		ret = len;
	}else{
		ret = write_ascii_string(out, out_len, "");
	}
	return ret;
}

int aic8800_format_invalid_rx_detail(uint8_t *out, int out_len, int block_len, int adjust_len, int remaining, int record_type){
	int ret = 0;
	int off = 0;

	if (out == NULL) {
		return ret;
	}
	#ifdef ENABLE_RX_DEBUGGING
	append_ascii_cstr(out, out_len, &off, "len=");
	append_dec_u32(out, out_len, &off, block_len);
	append_ascii_cstr(out, out_len, &off, " type=0x");
	append_hex_u32(out, out_len, &off, record_type & 0xff, 2);
	#endif
	ret = off;
	return ret;
}

/* aic8800_format_rx_dump_header: show some informative text (only the frame length..) on the incoming rx frame which will be hexdump-ed */
int aic8800_format_rx_dump_header(uint8_t *out, int out_len, int frame_len, int preview_len){
	int ret = 0;
	int off = 0;

	if (out == NULL || out_len <= 0){
		return ret;
	}
	#ifdef ENABLE_RX_DEBUGGING
	append_ascii_cstr(out, out_len, &off, "[rx] len=");
	append_dec_u32(out, out_len, &off, frame_len);
	#endif
	return ret;
}

/* aic8800_format_monitor_dump_header: create the monitor mode rx dumped frame descriptor, for now it will be empty/very minimal */
int aic8800_format_monitor_dump_header(uint8_t *out, int out_len, const uint8_t *frame, int frame_len, int count, int block_len, int pkt_len){
	int ret = 0;
	int off = 0;
	int type_len = 0;
	uint8_t type_text[32] = {0};

	if (out == NULL || out_len <= 0) {
		return ret;
	}
	#ifdef ENABLE_RX_DEBUGGING
	append_ascii_cstr(out, out_len, &off, "[monitor] #");
	append_dec_u32(out, out_len, &off, count);
	append_ascii_cstr(out, out_len, &off, " len=");
	append_dec_u32(out, out_len, &off, frame_len);
	append_ascii_cstr(out, out_len, &off, " block=");
	append_dec_u32(out, out_len, &off, block_len);
	append_ascii_cstr(out, out_len, &off, " pkt=");
	append_dec_u32(out, out_len, &off, pkt_len);
	type_len = aic8800_frame_type_to_string(type_text, sizeof(type_text), frame, frame_len);
	append_ascii_cstr(out, out_len, &off, " type=");
	for (int i = 0; i < type_len; i++) {
		append_ascii_byte(out, out_len, &off, type_text[i]);
	}
	#endif
	return ret;
}

int aic8800_prepare_ethernet_tx(uint8_t *desc, int desc_len, uint8_t *meta, int meta_len, const uint8_t *frame, int frame_len, int sta_vif, int sta_ap){
	int ret = 0;
	int ethertype = 0;
	int packet_len = 0;
	u32 status_desc_addr = 0;

	if (!meta || meta_len < 32 || !desc || desc_len < TXDESC_API_SIZE || (!frame && frame_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	memset(desc, 0, desc_len);
	if (frame_len < 14) {
		put_u32_le(meta, 0, AIC_TX_STATUS_SHORT);
		return 1;
	}
	if (sta_ap == IFACE_INVALID) {
		put_u32_le(meta, 0, AIC_TX_STATUS_NOT_ASSOC);
		return 1;
	}
	ethertype = frame[12] | (frame[13] << 8);
	packet_len = frame_len - 14;
	if (ethertype == ETH_P_PAE_HOST || ethertype == ETH_P_WAPI_HOST) {
		status_desc_addr = TX_STATUS_DESC_NEED_CFM;
	}
	ret = aic8800_build_tx_descriptor(desc, desc_len, packet_len, frame, ETH_ALEN, frame + ETH_ALEN, ETH_ALEN, ethertype, TX_AC_BE, 0, sta_vif, sta_ap, 0, status_desc_addr);
	if(ret == 0){
		put_u32_le(meta, 0, AIC_TX_STATUS_DESC_FAIL);
		return 1;
	}
	put_u32_le(meta, 0, AIC_TX_STATUS_OK);
	put_u32_le(meta, 4, 14);
	put_u32_le(meta, 8, packet_len);
	put_u32_le(meta, 12, frame_len);
	put_u32_le(meta, 16, sta_vif);
	put_u32_le(meta, 20, sta_ap);
	put_u32_le(meta, 24, ethertype);
	put_u32_le(meta, 28, status_desc_addr);
	return 1;
}

/* aic8800_prepare_monitor_tx: send a frame from monitor mode, this is essentially what we call 'frame injection' */
int aic8800_prepare_monitor_tx(uint8_t *desc, int desc_len, uint8_t *meta, int meta_len, const uint8_t *frame, int frame_len, int monitor_vif, int monitor_active){
	int ret = 0;
	int flags = 0;

	if (meta == NULL || meta_len < 32 || desc == NULL || desc_len < TXDESC_API_SIZE || (frame == NULL && frame_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	memset(desc, 0, desc_len);
	if (frame_len == 0) {
		put_u32_le(meta, 0, AIC_TX_STATUS_SHORT);
		ret = 1;
		return ret;
	}
	if (monitor_vif == IFACE_INVALID || monitor_active == false) {
		put_u32_le(meta, 0, AIC_TX_STATUS_NEED_MONITOR);
		ret = 1;
		return ret;
	}
	flags = TXU_CNTRL_MGMT_NATIVE;
	ret = aic8800_is_robust_mgmt_frame(frame, frame_len);
	if (ret) {
		flags |= TXU_CNTRL_MGMT_ROBUST_NATIVE;
	}
	ret = aic8800_build_tx_descriptor(desc, desc_len, frame_len, 0, 0, 0, 0, 0, TX_AC_BE, 0xff, monitor_vif, 0xff, flags, 0x40000000);
	if (ret == 0){
		put_u32_le(meta, 0, AIC_TX_STATUS_DESC_FAIL);
		return 1;
	}
	put_u32_le(meta, 0, AIC_TX_STATUS_OK);
	put_u32_le(meta, 4, 0);
	put_u32_le(meta, 8, frame_len);
	put_u32_le(meta, 12, frame_len);
	put_u32_le(meta, 16, monitor_vif);
	put_u32_le(meta, 20, flags);
	return 1;
}

/* aic8800_format_tx_eth_log: print some informations on the transmitted frame */
int aic8800_prepare_mgmt_tx(uint8_t *desc, int desc_len, uint8_t *meta, int meta_len, const uint8_t *frame, int frame_len, int vif_idx, int sta_idx){
	int ret = 0;
	int flags = 0;

	if (meta == NULL || meta_len < 32 || desc == NULL || desc_len < TXDESC_API_SIZE || (frame == NULL && frame_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	memset(desc, 0, desc_len);
	if (frame_len == 0) {
		put_u32_le(meta, 0, AIC_TX_STATUS_SHORT);
		return 1;
	}
	if (vif_idx == IFACE_INVALID) {
		put_u32_le(meta, 0, AIC_TX_STATUS_NEED_MONITOR);
		return 1;
	}
	if (sta_idx < 0 || sta_idx > 0xff) {
		sta_idx = 0xff;
	}
	flags = TXU_CNTRL_MGMT_NATIVE;
	if (aic8800_is_robust_mgmt_frame(frame, frame_len)) {
		flags |= TXU_CNTRL_MGMT_ROBUST_NATIVE;
	}
	ret = aic8800_build_tx_descriptor(desc, desc_len, frame_len, 0, 0, 0, 0, 0, TX_AC_BE, 0xff, vif_idx, sta_idx, flags, 0x40000000);
	if (ret == 0){
		put_u32_le(meta, 0, AIC_TX_STATUS_DESC_FAIL);
		return 1;
	}
	put_u32_le(meta, 0, AIC_TX_STATUS_OK);
	put_u32_le(meta, 4, 0);
	put_u32_le(meta, 8, frame_len);
	put_u32_le(meta, 12, frame_len);
	put_u32_le(meta, 16, vif_idx);
	put_u32_le(meta, 20, flags);
	put_u32_le(meta, 24, sta_idx);
	return 1;
}

int aic8800_format_tx_eth_log(uint8_t *out, int out_len, int frame_len, int vif, int sta){
	int off = 0;

	if (out == NULL || out_len <= 0) {
		return 0;
	}
	if (!append_ascii_cstr(out, out_len, &off, "[*] tx ethernet len=") ||
	    !append_dec_u32(out, out_len, &off, frame_len) ||
	    !append_ascii_cstr(out, out_len, &off, " vif=") ||
	    !append_dec_u32(out, out_len, &off, vif) ||
	    !append_ascii_cstr(out, out_len, &off, " sta=") ||
	    !append_dec_u32(out, out_len, &off, sta)) {
		return 0;
	}
	return off;
}

/* aic8800_format_tx_monitor_log: print some informations on the injected frame */
int aic8800_format_tx_monitor_log(uint8_t *out, int out_len, const uint8_t *frame, int frame_len, int vif){
	int off = 0;
	int type_len = 0;
	uint8_t type_text[32] = {0};

	#if 0
	if (out == NULL || out_len <= 0 || (frame == NULL && frame_len)) {
		return 0;
	}
	append_ascii_cstr(out, out_len, &off, "[*] tx monitor len=");
	//append_dec_u32(out, out_len, &off, frame_len);
	//append_ascii_cstr(out, out_len, &off, " vif=");
	//append_dec_u32(out, out_len, &off, vif);
	//append_ascii_cstr(out, out_len, &off, " type=");
	type_len = aic8800_frame_type_to_string(type_text, sizeof(type_text), frame, frame_len);
	if (type_len <= 0) {
		append_ascii_cstr(out, out_len, &off, "unknown");
	} else {
		for (int i = 0; i < type_len; i++) {
			append_ascii_byte(out, out_len, &off, type_text[i]);
		}
	}
	#endif
	return off;
}

int aic8800_scan_guard(int sta_ready, int scan_busy){
	int ret = 0;

	if (sta_ready == false) {
		ret = true;
		return ret;
	}
	if (scan_busy == true) {
		ret = 2;
		return ret;
	}
	return ret;
}

int aic8800_auto_scan_should_run(int connected, int sta_ready, int scan_busy, int action_busy){
	int ret = 0;

	ret = connected && sta_ready && !scan_busy && !action_busy;
	return ret;
}

int aic8800_pcap_retention_should_evict(int frame_count, int byte_count, int max_frames, int max_bytes){
	return frame_count > max_frames || byte_count > max_bytes;
}

int aic8800_pcap_download_name(uint8_t *out, int out_len, const uint8_t *requested, int requested_len, const uint8_t *stamp, int stamp_len){
	int ret = 0;
	int off = 0;
	int has_pcap = 0;
	uint8_t c = 0;

	if (out == NULL || (requested == NULL && requested_len) || (stamp == NULL && stamp_len)) {
		return ret;
	}
	if (requested_len) {
		for (int i = 0; i < requested_len; i++) {
			append_ascii_byte(out, out_len, &off, requested[i]);
		}
	}else{
		append_ascii_cstr(out, out_len, &off, "aic8800-");
		for (int i = 0; i < stamp_len; i++) {
			c = stamp[i];
			if (c == ':' || c == '.'){
				c = '-';
			}
			append_ascii_byte(out, out_len, &off, c);
		}
	}
	has_pcap = off >= 5 && (aic8800_ascii_lower(out[off - 5]) == '.' && aic8800_ascii_lower(out[off - 4]) == 'p' && aic8800_ascii_lower(out[off - 3]) == 'c' && aic8800_ascii_lower(out[off - 2]) == 'a' && aic8800_ascii_lower(out[off - 1]) == 'p');
	if (has_pcap == 0){
		append_ascii_cstr(out, out_len, &off, ".pcap");
	}
	return off;
}

int aic8800_connect_prepare(uint8_t *meta, int meta_len, uint8_t *ssid_out, int ssid_out_len,
                             const uint8_t *target_ssid, int target_ssid_len,
                             const uint8_t *target_bssid, int target_bssid_len,
                             const uint8_t *password, int password_len,
                             const uint8_t *network_ssid, int network_ssid_len){
	int ret = 0;
	int ssid_len = 0;
	int use_network = 0;
	const uint8_t *ssid = NULL;
	uint8_t parsed[ETH_ALEN] = {};
	static const uint8_t hidden[] = {91,104,105,100,100,101,110,93};

	if (meta == NULL || meta_len < 12 || ssid_out == NULL || (target_ssid == NULL && target_ssid_len) || (target_bssid == NULL && target_bssid_len) || (password == NULL && password_len) || (network_ssid == NULL && network_ssid_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	use_network = 0;
	ssid = target_ssid;
	ssid_len = target_ssid_len;

	if (target_bssid_len) {
		if (!parse_mac_text(target_bssid, target_bssid_len, parsed)) {
			put_u32_le(meta, 0, AIC_CONNECT_STATUS_BAD_BSSID);
			ret = 1;
			return ret;
		}
	}

	if (!target_ssid_len && network_ssid_len && !(network_ssid_len == sizeof(hidden) && compare_bytes_lex(network_ssid, hidden, sizeof(hidden)) == 0)) {
		ssid = network_ssid;
		ssid_len = network_ssid_len;
		use_network = 1;
	}
	if (ssid_len == 0) {
		put_u32_le(meta, 0, AIC_CONNECT_STATUS_MISSING_TARGET);
		ret = 1;
		return ret;
	}
	if (ssid_len > ssid_out_len) {
		return ret;
	}
	if (ssid_len > 0) {
		memcpy(ssid_out, ssid, ssid_len);
	}
	put_u32_le(meta, 0, AIC_CONNECT_STATUS_OK);
	put_u32_le(meta, 4, ssid_len);
	meta[8] = use_network ? 1 : 0;
	meta[9] = password_len ? 1 : 0;
	ret = 1;
	return ret;
}

int aic8800_format_connect_accepted(uint8_t *out, int out_len, const uint8_t *ssid, int ssid_len, const uint8_t *bssid, int bssid_len){
	int ret = 0;
	int off = 0;

	if (out == NULL || (ssid == NULL && ssid_len) || (bssid == NULL && bssid_len)) {
		return ret;
	}
	append_ascii_cstr(out, out_len, &off, "[*] connection accepted: ");
	if (ssid_len > 0) {
		append_ascii_cstr(out, out_len, &off, "ssid = ");
		for (int i = 0; i < ssid_len; i++) {
			append_ascii_byte(out, out_len, &off, ssid[i]);
		}
	}else{
		append_ascii_cstr(out, out_len, &off, "bssid = ");
		for (int i = 0; i < bssid_len; i++) {
			append_ascii_byte(out, out_len, &off, bssid[i]);
		}
	}
	ret = off;
	return ret;
}

int aic8800_patch_range_plan(uint8_t *meta, int meta_len, const uint8_t *address_text, int address_text_len,
                              const uint8_t *length_text, int length_text_len, int default_len, int max_len){
	int ret = 0;
	int length = 0;
	int address = 0;

	if (!meta || meta_len < 16 || (!address_text && address_text_len) || (!length_text && length_text_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	length = default_len;
	if (!parse_u32_ascii(address_text, address_text_len, &address)) {
		put_u32_le(meta, 0, 1);
		ret = 1;
		return ret;
	}
	if (length_text_len && !parse_u32_ascii(length_text, length_text_len, &length)) {
		put_u32_le(meta, 0, 2);
		ret = 1;
		return ret;
	}
	if (length == 0 || length > max_len) {
		put_u32_le(meta, 0, 3);
		put_u32_le(meta, 12, max_len);
		ret = 1;
		return ret;
	}
	put_u32_le(meta, 0, 0);
	put_u32_le(meta, 4, address);
	put_u32_le(meta, 8, length);
	put_u32_le(meta, 12, max_len);
	ret = 1;
	return ret;
}

int aic8800_patch_compiled_plan(uint8_t *meta, int meta_len, int address, int bytes_len, int entry_offset){
	int ret = 0;

	if (meta == NULL || meta_len < 16) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (bytes_len == 0) {
		put_u32_le(meta, 0, 1);
		ret = 1;
		return ret;
	}
	if (entry_offset < 0 || (uint32_t)entry_offset > (uint32_t)address) {
		put_u32_le(meta, 0, 2);
		ret = 1;
		return ret;
	}
	put_u32_le(meta, 0, 0);
	put_u32_le(meta, 4, address - entry_offset);
	put_u32_le(meta, 8, address);
	put_u32_le(meta, 12, entry_offset);
	ret = 1;
	return ret;
}

int aic8800_fuzzer_launch_plan(uint8_t *meta, int meta_len, const uint8_t *profile, int profile_len, int captured_count){
	int ret = 0;
	int frame_count = 0;

	if (meta == NULL || meta_len < 8 || (profile == NULL && profile_len)) {
		return ret;
	}
	memset(meta, 0, meta_len);
	frame_count = aic8800_owfuzz_profile_frame_count(profile, profile_len, captured_count);
	put_u32_le(meta, 0, frame_count ? 0 : 1);
	put_u32_le(meta, 4, frame_count);
	ret = 1;
	return ret;
}

/* aic8800_format_fuzzer_init_log: main function used for initializing the fuzzer, prints the state of the fuzzer and its configuration */
int aic8800_format_fuzzer_init_log(uint8_t *out, int out_len,
                                    const uint8_t *mode, int mode_len,
                                    const uint8_t *profile, int profile_len,
                                    const uint8_t *target, int target_len,
                                    const uint8_t *bssid, int bssid_len,
                                    int interval_ms, int count){
	int ret = 0;
	int off = 0;

	if (out == NULL || (mode == NULL && mode_len) || (profile == NULL && profile_len) || target == NULL || target_len < ETH_ALEN || bssid == NULL || bssid_len < ETH_ALEN) {
		return ret;
	}

	append_ascii_cstr(out, out_len, &off, "[*] initializing owfuzz core!\n");
	append_ascii_cstr(out, out_len, &off, "[*] fuzzing interface initialized: mode=");
	for (int i = 0; i < mode_len; i++){
		append_ascii_byte(out, out_len, &off, mode[i]);
	}
	append_ascii_cstr(out, out_len, &off, " profile=");
	for (int i = 0; i < profile_len; i++){
		append_ascii_byte(out, out_len, &off, profile[i]);
	}
	append_ascii_cstr(out, out_len, &off, " target=");
	append_mac_text(out, out_len, &off, target, target_len);
	append_ascii_cstr(out, out_len, &off, " bssid=");
	append_mac_text(out, out_len, &off, bssid, bssid_len);
	append_ascii_cstr(out, out_len, &off, " interval=");
	append_dec_u32(out, out_len, &off, interval_ms);
	append_ascii_cstr(out, out_len, &off, "ms count=");
	if (count){
		append_dec_u32(out, out_len, &off, count);
	}else{
		append_ascii_cstr(out, out_len, &off, "infinite");
	}
	ret = off;
	return ret;
}

/* aic8800_format_fuzzer_launch_log: just print some informative text after the fuzzing had been launched, not really useful but can be used for debugging */
int aic8800_format_fuzzer_launch_log(uint8_t *out, int out_len, const uint8_t *profile, int profile_len, int frame_count, int interval_ms, int count){
	int ret = 0;
	int off = 0;

	if (out == NULL || (profile == NULL && profile_len)) {
		 return ret;
	}
	append_ascii_cstr(out, out_len, &off, "[*] fuzz launch: profile=");
	for (int i = 0; i < profile_len; i++){
		append_ascii_byte(out, out_len, &off, profile[i]);
	}
	append_ascii_cstr(out, out_len, &off, " frames=");
	append_dec_u32(out, out_len, &off, frame_count);
	append_ascii_cstr(out, out_len, &off, " interval=");
	append_dec_u32(out, out_len, &off, interval_ms);
	ret = off;
	return ret;
}

int aic8800_format_fuzzer_stop_log(uint8_t *out, int out_len, const uint8_t *reason, int reason_len, int sent){
	int ret = 0;
	int off = 0;

	if (out == NULL || (!reason && reason_len)) {
		return ret;
	}
	ret = append_ascii_cstr(out, out_len, &off, "[*] fuzz ");
	if(ret == 0){
		return ret;
	}
	if (reason_len) {
		for (int i = 0; i < reason_len; i++){
			append_ascii_byte(out, out_len, &off, reason[i]);
		}
	}
	append_ascii_cstr(out, out_len, &off, ": sent=");
	append_dec_u32(out, out_len, &off, sent);
	ret = off;
	return ret;
}

int aic8800_fw_boot_plan(uint8_t *meta, int meta_len, int system_reg){
	int ret = 0;
	int u01 = 0; /* used to check if the firmware is of type 'u01' */
	int hw_rev = 0;
	int mcu_id = 0;

	if (meta == NULL || meta_len < 12) {
		return ret;
	}
	mcu_id = (system_reg & 0x02000000) ? 0 : 1;
	hw_rev = (system_reg >> 16) & 0xffu;
	u01 = hw_rev == 0x01;
	memset(meta, 0, meta_len);
	meta[0] = (uint8_t)mcu_id;
	meta[1] = (uint8_t)hw_rev;
	meta[2] = (uint8_t)u01;
	meta[3] = (uint8_t)(u01 ? AIC_FW_IMAGE_FMAC_U01 : AIC_FW_IMAGE_FMAC_D80_U02);
	put_u32_le(meta, 4, u01 ? 0x00100000 : 0x00120000);
	put_u32_le(meta, 8, AIC_MAX_BLOCK_WRITE);
	ret = 1;
	return ret;
}

int aic8800_fw_image_name(uint8_t *out, int out_len, int image_id){
	int ret = 0;

	if (image_id == AIC_FW_IMAGE_FMAC_U01) {
		ret = write_ascii_string(out, out_len, "fmacfw.bin");
		return ret;
	}
	if (image_id == AIC_FW_IMAGE_FMAC_D80_U02) {
		ret = write_ascii_string(out, out_len, "fmacfw_8800d80_u02.bin");
		return ret;
	}
	return ret;
}

int aic8800_fw_upload_chunk_plan(uint8_t *meta, int meta_len, int base_address, int image_len, int offset){
	int ret = 0;
	int done = 0;
	int remain = 0;
	int chunk_len = 0;

	if (meta == NULL || meta_len < 20 || offset >= image_len) {
		return ret;
	}
	remain = image_len - offset;
	chunk_len = remain < AIC_MAX_BLOCK_WRITE ? remain : AIC_MAX_BLOCK_WRITE;
	done = offset + chunk_len;
	memset(meta, 0, meta_len);
	put_u32_le(meta, 0, base_address + offset);
	put_u32_le(meta, 4, chunk_len);
	put_u32_le(meta, 8, done);
	put_u32_le(meta, 12, image_len ? (done * 100) / image_len : 100);
	put_u32_le(meta, 16, ((offset & 0x3fffu) == 0 || done == image_len) ? 1 : 0);
	ret = 1;
	return ret;
}

int aic8800_patch_config_initial_reads(uint8_t *out, int out_len, int boot_addr){
	int ret = 0;
	int rd_patch_addr = 0;

	if (out == NULL || out_len < 12) {
		return ret;
	}
	rd_patch_addr = boot_addr + 0x0198;
	put_u32_le(out, 0, rd_patch_addr);
	put_u32_le(out, 4, rd_patch_addr + 8);
	put_u32_le(out, 8, boot_addr + 0x001cu);
	ret = sizeof(u32) * 3;
	return ret;
}

int aic8800_patch_config_extra_read(uint8_t *meta, int meta_len, int boot_addr, int rd_version_val){
	int ret = 0;

	if (meta == NULL || meta_len < 8) {
		return ret;
	}
	memset(meta, 0, meta_len);
	if (rd_version_val > AIC_FW_PATCH_VERSION_SPLIT) {
		put_u32_le(meta, 0, boot_addr + 0x0198 + 12);
		put_u32_le(meta, 4, 1);
	}
	ret = 1;
	return ret;
}

static int append_patch_write_pair(uint8_t *out, int out_len, int *off, int address, int value){
	int ret = 0;

	if (*off + 8 > out_len) {
		return ret;
	}
	put_u32_le(out, *off, address);
	put_u32_le(out, *off + 4, value);
	*off += 8;
	ret = 1;
	return ret;
}

int aic8800_patch_config_write_plan(uint8_t *out, int out_len, int boot_addr, int config_base, int aic8800_patch_str_base, int rd_version_val, int patch_buff_base, int has_patch_buff){
	int ret = 0;
	int off = 0;
	int start_addr = 0;
	int patch_addr = 0;
	static const int block_offsets[] = {48, 52, 56, 60};

	if (out == NULL) {
		return ret;
	}
	start_addr = AIC_PATCH_START_DEFAULT;
	if (rd_version_val > AIC_FW_PATCH_VERSION_SPLIT && has_patch_buff) {
		start_addr = patch_buff_base;
	}
	patch_addr = start_addr;
	append_patch_write_pair(out, out_len, &off, aic8800_patch_str_base + AIC_PATCH_OFF_MAGIC_NATIVE, AIC_PATCH_MAGIC_NATIVE);
	append_patch_write_pair(out, out_len, &off, aic8800_patch_str_base + AIC_PATCH_OFF_MAGIC2_NATIVE, AIC_PATCH_MAGIC2_NATIVE);
	append_patch_write_pair(out, out_len, &off, aic8800_patch_str_base + AIC_PATCH_OFF_PAIR_START_NATIVE, patch_addr);
	append_patch_write_pair(out, out_len, &off, aic8800_patch_str_base + AIC_PATCH_OFF_PAIR_COUNT_NATIVE,
	sizeof(aic8800_d80_patch_table_native) / sizeof(aic8800_d80_patch_table_native[0]));
	for (int i = 0; i < sizeof(aic8800_d80_patch_table_native) / sizeof(aic8800_d80_patch_table_native[0]); i++) {
		append_patch_write_pair(out, out_len, &off, start_addr + 8 * i, config_base + aic8800_d80_patch_table_native[i][0]);
		append_patch_write_pair(out, out_len, &off, start_addr + 8 * i + 4, aic8800_d80_patch_table_native[i][1]);
	}
	for (int i = 0; i < sizeof(block_offsets) / sizeof(block_offsets[0]); i++) {
		append_patch_write_pair(out, out_len, &off, aic8800_patch_str_base + block_offsets[i], 0);
	}
	return off;
}

int aic8800_hex_editor_set_byte(uint8_t *out, int out_len, const uint8_t *input, int input_len, int index, int value){
	int ret = 0;
	int new_len = 0;

	if (out == NULL || (input == NULL && input_len)) {
		return ret;
	}
	new_len = input_len;
	if (index >= new_len) {
		new_len = index + 1;
	}
	if (new_len > out_len) {
		return ret;
	}
	if (input_len) {
		memcpy(out, input, input_len);
	}
	if (new_len > input_len) {
		memset(out + input_len, 0, new_len - input_len);
	}
	out[index] = (uint8_t)(value & 0xffu);
	ret = new_len;
	return ret;
}

int aic8800_hex_editor_remove_byte(uint8_t *out, int out_len, const uint8_t *input, int input_len, int index){
	int ret = 0;
	int new_len = 0;

	if (out == NULL || (input == NULL && input_len)) {
		return ret;
	}
	if (index >= input_len) {
		if (input_len > out_len) {
			return ret;
		}
		if (input_len) {
			memcpy(out, input, input_len);
		}
		ret = input_len;
		return ret;
	}
	new_len = input_len - 1;
	if (new_len > out_len) {
		return ret;
	}
	for (int i = 0; i < index; i++) {
		out[i] = input[i];
	}
	for (int i = index; i < new_len; i++) {
		out[i] = input[i + 1];
	}
	ret = new_len;
	return ret;
}

int aic8800_hex_editor_insert_bytes(uint8_t *out, int out_len, const uint8_t *input, int input_len, int index, const uint8_t *insert, int insert_len){
	int ret = 0;
	int target = 0;
	int new_len = 0;

	if (out == NULL || (input == NULL && input_len) || (insert == NULL && insert_len)) {
		return ret;
	}
	target = index > input_len ? input_len : index;
	new_len = input_len + insert_len;
	if (new_len > out_len) {
		return ret;
	}
	for (int i = 0; i < target; i++) {
		out[i] = input[i];
	}
	if (insert_len) {
		memcpy(out + target, insert, insert_len);
	}
	for (int i = target; i < input_len; i++) {
		out[i + insert_len] = input[i];
	}
	ret = new_len;
	return ret;
}

int aic8800_hex_editor_clean_cell(uint8_t *out, int out_len, const uint8_t *raw, int raw_len){
	int ret = 0;
	int off = 0;

	if (out == NULL || (raw == NULL && raw_len)) {
		return ret;
	}
	for (int i = 0; i < raw_len && off < 2; i++) {
		if (hex_value(raw[i]) >= 0) {
			if (off >= out_len) {
				return ret;
			}
			out[off++] = aic8800_ascii_lower(raw[i]) >= 97 ? (uint8_t)(aic8800_ascii_lower(raw[i]) - 32) : raw[i];
		}
	}
	if(off){
		ret = off;
	}
	return ret;
}

/* option_present_any: search if an option passed to Owfuzz is present or not in our conf */
static int option_present_any(const uint8_t *opts, int opts_len, const char *const *names, int name_count){
	int ret = 0;
	int value_len = 0;
	const uint8_t *value = NULL;

	ret = kv_find_any(opts, opts_len, names, name_count, &value, &value_len);
	return ret;
}

/* aic8800_owfuzz_build_config: called during the initialization part of Owfuzz for building the configuration to use during the fuzzing (remember that we don't have the owfuz.conf file in this setup) */
int aic8800_owfuzz_build_config(uint8_t *meta, int meta_len, uint8_t *strings, int strings_len,
                                 const uint8_t *opts, int opts_len,
                                 const uint8_t *prev_meta, int prev_meta_len,
                                 const uint8_t *prev_strings, int prev_strings_len,
                                 const uint8_t *local_mac, int local_mac_len,
                                 int now_seed){
	int ret = 0;
	int off = 0;
	int flags = 0;
	int mode_len = 0;
	int profile_len = 0;
	int ssid_len = 0;
	int auth_len = 0;
	int channel = 0;
	int freq = 0;
	int freq_channel = 0;
	int count = 0;
	int interval = 0;
	int log_every = 0;
	int seed = 0;
	int capture_max = 0;
	int max_len = 0;
	int prev_channel = 0;
	int prev_freq = 0;
	int prev_count = 0;
	int prev_interval = 0;
	int prev_log = 0;
	int prev_seed = 0;
	int prev_capture_max = 0;
	int prev_max_len = 0;
	int prev_flags = 0;
	uint8_t bssid[ETH_ALEN] = {};
	uint8_t source[ETH_ALEN] = {};
	uint8_t target[ETH_ALEN] = {};
	uint8_t default_source[ETH_ALEN] = {};
	uint8_t default_target[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	uint8_t *mode = NULL;
	uint8_t *ssid = NULL;
	uint8_t *auth = NULL;
	uint8_t *profile = NULL;
	uint8_t *prev_source = NULL;
	uint8_t *prev_target = NULL;
	uint8_t *bssid_fallback = NULL;
	/* parameters present in the owfuz.conf */
	static const char *const mode_names[] = {"mode"};
	static const char *const ssid_names[] = {"ssid"};
	static const char *const auth_names[] = {"auth"};
	static const char *const monitor_names[] = {"monitor"};
	static const char *const profile_names[] = {"profile"};
	static const char *const mutate_names[] = {"mutate", "fuzz"};
	static const char *const bssid_names[] = {"bssid", "bss", "ap"};
	static const char *const capture_names[] = {"capture", "sniff"};
	static const char *const rewrite_names[] = {"rewrite", "rewrite_mac"};
	static const char *const channel_names[] = {"channel", "chan", "c"};
	static const char *const freq_names[] = {"freq", "frequency"};
	static const char *const count_names[] = {"count", "frames", "n"};
	static const char *const log_names[] = {"log_every", "log"};
	static const char *const seed_names[] = {"seed"};
	static const char *const capture_max_names[] = {"capture_max", "templates"};
	static const char *const max_len_names[] = {"max_len", "max"};
	static const char *const interval_names[] = {"interval", "interval_ms", "delay", "rate"};
	static const char *const source_names[] = {"source", "source_mac", "smac", "sa", "mac"};
	static const char *const target_names[] = {"target", "target_mac", "dmac", "da", "dest"};

	if (meta == NULL || meta_len < OWFUZZ_CFG_META_SIZE || strings == NULL){
		return ret;
	}
	memcpy(default_source, local_mac, ETH_ALEN);
	if(prev_meta_len >= OWFUZZ_CFG_META_SIZE){
		prev_source = prev_meta;
		prev_target = prev_meta + 6;
	}else{
		prev_source = default_source;
		prev_target = default_target;
	}
	if (!parse_option_mac_any(opts, opts_len, source_names, sizeof(source_names) / sizeof(source_names[0]), prev_source, source) ||
	    !parse_option_mac_any(opts, opts_len, target_names, sizeof(target_names) / sizeof(target_names[0]), prev_target, target)) {
		return ret;
	}
	if (prev_meta_len >= OWFUZZ_CFG_META_SIZE) {
		bssid_fallback = prev_meta + 12;
	}else if (!aic8800_is_broadcast_mac(target, ETH_ALEN) && !aic8800_is_zero_mac(target, ETH_ALEN)) {
		bssid_fallback = target;
	}else{
		bssid_fallback = source;
	}
	if (!parse_option_mac_any(opts, opts_len, bssid_names, sizeof(bssid_names) / sizeof(bssid_names[0]), bssid_fallback, bssid)) {
		return ret;
	}
	/* retrieve the config parameters */
	prev_channel = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 20) : 1;
	prev_freq = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 24) : aic8800_channel_to_frequency(prev_channel);
	prev_count = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 28) : 128;
	prev_interval = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 32) : 20;
	prev_log = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 36) : 16;
	prev_seed = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 40) : now_seed;
	prev_capture_max = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 44) : 32;
	prev_max_len = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 48) : 2304;
	prev_flags = prev_meta_len >= OWFUZZ_CFG_META_SIZE ? get_u32_le(prev_meta, 52) : (OWFUZZ_CFG_FLAG_CAPTURE | OWFUZZ_CFG_FLAG_MONITOR | OWFUZZ_CFG_FLAG_MUTATE | OWFUZZ_CFG_FLAG_REWRITE);

	parse_option_number_any(opts, opts_len, channel_names, sizeof(channel_names) / sizeof(channel_names[0]), prev_channel, 1, 196, &channel);
	parse_option_number_any(opts, opts_len, freq_names, sizeof(freq_names) / sizeof(freq_names[0]), prev_freq, 1, 7000, &freq);
	parse_option_number_any(opts, opts_len, count_names, sizeof(count_names) / sizeof(count_names[0]), prev_count, 0, 10000000, &count);
	parse_option_number_any(opts, opts_len, interval_names, sizeof(interval_names) / sizeof(interval_names[0]), prev_interval, 1, 60000, &interval);
	parse_option_number_any(opts, opts_len, log_names, sizeof(log_names) / sizeof(log_names[0]), prev_log, 0, 10000000, &log_every);
	parse_option_number_any(opts, opts_len, seed_names, sizeof(seed_names) / sizeof(seed_names[0]), prev_seed, 0, 0xffffffff, &seed);
	parse_option_number_any(opts, opts_len, capture_max_names, sizeof(capture_max_names) / sizeof(capture_max_names[0]), prev_capture_max, 0, 256, &capture_max);
	parse_option_number_any(opts, opts_len, max_len_names, sizeof(max_len_names) / sizeof(max_len_names[0]), prev_max_len, 32, 8192, &max_len);

	if (!option_present_any(opts, opts_len, channel_names, sizeof(channel_names) / sizeof(channel_names[0]))) {
		freq_channel = aic8800_frequency_to_channel(freq);
		if (freq_channel) {
			channel = freq_channel;
		}
	}
	if (parse_option_bool_any(opts, opts_len, capture_names, sizeof(capture_names) / sizeof(capture_names[0]), prev_flags & OWFUZZ_CFG_FLAG_CAPTURE)){
		flags |= OWFUZZ_CFG_FLAG_CAPTURE;
	}
	if (parse_option_bool_any(opts, opts_len, monitor_names, sizeof(monitor_names) / sizeof(monitor_names[0]), prev_flags & OWFUZZ_CFG_FLAG_MONITOR)){
		flags |= OWFUZZ_CFG_FLAG_MONITOR;
	}
	if (parse_option_bool_any(opts, opts_len, mutate_names, sizeof(mutate_names) / sizeof(mutate_names[0]), prev_flags & OWFUZZ_CFG_FLAG_MUTATE)){
		flags |= OWFUZZ_CFG_FLAG_MUTATE;
	}
	if (parse_option_bool_any(opts, opts_len, rewrite_names, sizeof(rewrite_names) / sizeof(rewrite_names[0]), prev_flags & OWFUZZ_CFG_FLAG_REWRITE)){
		flags |= OWFUZZ_CFG_FLAG_REWRITE;
	}
	if (!kv_find_any(opts, opts_len, mode_names, 1, &mode, &mode_len)){
		prev_string_at(prev_strings, prev_strings_len, 0, &mode, &mode_len);
	}
	if (!kv_find_any(opts, opts_len, profile_names, 1, &profile, &profile_len)){
		prev_string_at(prev_strings, prev_strings_len, 1, &profile, &profile_len);
	}
	if (!kv_find_any(opts, opts_len, ssid_names, 1, &ssid, &ssid_len)){
		prev_string_at(prev_strings, prev_strings_len, 2, &ssid, &ssid_len);
	}
	if (!kv_find_any(opts, opts_len, auth_names, 1, &auth, &auth_len)){
		prev_string_at(prev_strings, prev_strings_len, 3, &auth, &auth_len);
	}
	memset(meta, 0, meta_len);
	memcpy(meta, source, ETH_ALEN);
	memcpy(meta + 6, target, ETH_ALEN);
	memcpy(meta + 12, bssid, ETH_ALEN);
	put_u32_le(meta, 20, channel);
	put_u32_le(meta, 24, freq);
	put_u32_le(meta, 28, count);
	put_u32_le(meta, 32, interval);
	put_u32_le(meta, 36, log_every);
	put_u32_le(meta, 40, seed);
	put_u32_le(meta, 44, capture_max);
	put_u32_le(meta, 48, max_len);
	put_u32_le(meta, 52, flags);

	write_string_field(strings, strings_len, &off, mode, mode_len, "sta", 1);
	write_string_field(strings, strings_len, &off, profile, profile_len, "management", 1);
	/* ssid network name used for Owfuzz test */
	write_string_field(strings, strings_len, &off, ssid, ssid_len, "owfuzz_ssid_test", 0);
	/* auth type */
	write_string_field(strings, strings_len, &off, auth, auth_len, "open", 1);
	return off;
}

static int ascii_equal_casefold(const uint8_t *a, int a_len, const uint8_t *b, int b_len){
	int ret = 0;

	if (a_len != b_len) {
		return ret;
	}
	for (int i = 0; i < a_len; i++) {
		if (aic8800_ascii_lower(a[i]) != aic8800_ascii_lower(b[i])) {
			return ret;
		}
	}
	ret = 1;
	return ret;
}

int aic8800_find_network_for_connect(uint8_t *meta, int meta_len,
                                      const uint8_t *target_ssid, int target_ssid_len,
                                      const uint8_t *target_bssid, int target_bssid_len,
                                      const uint8_t *records, int records_len){
	int ret = 0;
	int pos = 0;
	int index = 0;
	int ssid_len = 0;
	int bssid_len = 0;
	int ssid_start = 0;
	int bssid_start = 0;

	if (meta == NULL || meta_len < 4 || (!target_ssid && target_ssid_len)) {
		return ret;
	}
	put_u32_le(meta, 0, 0xffffffff);
	while (pos < records_len) {
		bssid_start = pos;
		while (pos < records_len && records[pos] != 0){
			pos++;
		}
		bssid_len = pos - bssid_start;
		if (pos < records_len) pos++;
			ssid_start = pos;
			while (pos < records_len && records[pos] != 0){
				pos++;
			}
			ssid_len = pos - ssid_start;
			if (pos < records_len){
				pos++;
			}
			if ((target_bssid_len && ascii_equal_casefold(records + bssid_start, bssid_len, target_bssid, target_bssid_len)) || (target_ssid_len && ssid_len == target_ssid_len && compare_bytes_lex(records + ssid_start, target_ssid, ssid_len) == 0)) {
				put_u32_le(meta, 0, index);
				ret = 1;
				return ret;
			}
		index++;
	}
	ret = 1;
	return ret;
}
