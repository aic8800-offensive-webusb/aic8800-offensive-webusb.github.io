"use strict";

const TCC_ASSET_CACHE_BUSTER = "20260823-tcc-barethumb1";
importScripts("assets/tcc-arm32/arm_tcc.js?v=" + TCC_ASSET_CACHE_BUSTER);

const DEFAULT_WASM_URL = "assets/tcc-arm32/tcc-wasm.wasm?v=" + TCC_ASSET_CACHE_BUSTER;
const DEFAULT_AIC8800_HEADER_URL = "assets/ettore_header/aic8800d80.h";
const AIC8800_HEADER_INCLUDE_RE = /^[ \t]*#[ \t]*include[ \t]*[<"]aic8800d80\.h[>"][^\n]*(?:\n|$)/m;
/* put the aic8800d80.h header inline inside the arm32 worker */
const TCC_AIC8800D80_HEADER = `
/* aic8800d80.h, written by Edoardo Mantovani, 2026
 * the function address defined in this header are the result of my research engineering
 * efforts in the 'fmacfw_8800d80_u02.bin'
 */

#define u8	unsigned char
#define u16	unsigned short
#define u32	unsigned int

#define s8	signed char
#define s16	signed short
#define s32	signed int

#define bool    unsigned char
#define true	1
#define false	0
#define NULL    ((void *)0)

#define	EPERM	 1	/* Operation not permitted */
#define	ENOENT	 2	/* No such file or directory */
#define	ESRCH	 3	/* No such process */
#define	EINTR	 4	/* Interrupted system call */
#define	EIO	 5	/* I/O error */
#define	ENXIO	 6	/* No such device or address */
#define	E2BIG	 7	/* Argument list too long */
#define	ENOEXEC	 8	/* Exec format error */
#define	EBADF	 9	/* Bad file number */
#define	ECHILD	10	/* No child processes */
#define	EAGAIN	11	/* Try again */
#define	ENOMEM	12	/* Out of memory */
#define	EACCES	13	/* Permission denied */
#define	EFAULT	14	/* Bad address */
#define	ENOTBLK	15	/* Block device required */
#define	EBUSY	16	/* Device or resource busy */
#define	EEXIST	17	/* File exists */
#define	EXDEV	18	/* Cross-device link */
#define	ENODEV	19	/* No such device */
#define	ENOTDIR	20	/* Not a directory */
#define	EISDIR	21	/* Is a directory */
#define	EINVAL	22	/* Invalid argument */
#define	ENFILE	23	/* File table overflow */
#define	EMFILE	24	/* Too many open files */
#define	ENOTTY	25	/* Not a typewriter */
#define	ETXTBSY	26	/* Text file busy */
#define	EFBIG	27	/* File too large */
#define	ENOSPC	28	/* No space left on device */
#define	ESPIPE	29	/* Illegal seek */
#define	EROFS	30	/* Read-only file system */
#define	EMLINK	31	/* Too many links */
#define	EPIPE	32	/* Broken pipe */
#define	EDOM	33	/* Math argument out of domain of func */
#define	ERANGE	34	/* Math result not representable */

#define ke_state_t u16
#define ke_msg_id_t u16
#define ke_task_id_t u16

/* remember to use this macro BEFORE every frame declaration, this will permits to have in a single patch both the code + frame data */
#define ETTORE_FRAME	__attribute__((section(".text"))) static const u8

/*
 * Structure containing the parameters of the @ref DBG_START_NPC_REQ message.
 * taken from: Sample firmware and code for testing/8800m40-aic8800-sdk-6.5.7/wifi/macif/msg.h#L2757
 */
struct dbg_start_npc_req {
    /* Start adress to boot */
    u32 bootaddr;
    /* NPC index */
    u16 bootidx;
};

/* tx frame macros taken from many Github leaked repos like https://github.com/hongshui3000/Alios_SDK/blob/mxchip/platform/mcu/moc108/mx108/mx378/ip/mac/mac_frame.h#L185 */

/* MIC Header Length -> DA (6 bytes) + SA (6 bytes) + Priority (4 bytes) */
#define MIC_HDR_LEN     (16)
/* IV Length */
#define IV_LEN          (4)
/* EIV Length */
#define EIV_LEN         (4)
/* MIC Length */
#define MIC_LEN         (8)
/* ICV Length */
#define ICV_LEN         (4)
/* WPI IV length */
#define WPI_IV_LEN      (18)
/* WPI MIC length */
#define WPI_MIC_LEN     (16)
/* Word 1 of CCMP IV */
#define EIV_PRESENT     (0x2000)

/*
 * MAC HEADER LENGTH DEFINITIONS
 ****************************************************************************************
 */
/* Long MAC Header length (with QoS control field and HT control field) */
#define MAC_LONG_QOS_HTC_MAC_HDR_LEN   36
/* Long MAC Header length (with QoS control field) */
#define MAC_LONG_QOS_MAC_HDR_LEN       32
/* Long MAC Header length (without QoS control field) */
#define MAC_LONG_MAC_HDR_LEN           30
/* Short MAC Header length (with QoS control field and HT control field) */
#define MAC_SHORT_QOS_HTC_MAC_HDR_LEN  30
/* Short MAC Header length (with QoS control field) */
#define MAC_SHORT_QOS_MAC_HDR_LEN      26
/* Short MAC Header length (without QoS control field) */
#define MAC_SHORT_MAC_HDR_LEN          24

/* QoS Control Field Length */
#define MAC_HDR_QOS_CTRL_LEN           2

/* Longest possible MAC Header */
#define MAC_HDR_LEN_MAX                MAC_LONG_QOS_HTC_MAC_HDR_LEN

/* Long control frame header length */
#define MAC_LONG_CTRLFRAME_LEN         16
/* Short control frame header length (ACK/CTS) */
#define MAC_SHORT_CTRLFRAME_LEN        10

/*
 * MAC HEADER definitions and OFFSETS
 ****************************************************************************************
 */
#define MAC_HEAD_FCTRL_OFT              0
#define MAC_HEAD_DURATION_OFT           2
#define MAC_HEAD_DURATION_CFP      0x8000
#define MAC_HEAD_ADDR1_OFT              4
#define MAC_HEAD_ADDR2_OFT             10
#define MAC_HEAD_ADDR3_OFT             16
#define MAC_HEAD_CTRL_OFT              22
#define MAC_HEAD_ADDR4_OFT             24
#define MAC_HEAD_SHORT_QOS_OFT         24
#define MAC_HEAD_LONG_QOS_OFT          30
#define MAC_ORIGINAL_ETHTYPE_OFT       36

/* FRAME CONTROL MASK
 * The type information in the header of a frame consists of the Type and Subtype fields
 * When using the term "frame type" in the code, we refer to the type field and not to
 * the combined type+subtype information.
 */
#define MAC_FCTRL_LEN                   2

#define MAC_FRAME_CTRL_BEACON           0x0080

#define MAC_FCTRL_PROTOCOLVERSION_MASK  0x0003
#define MAC_FCTRL_TYPE_MASK             0x000C
#define MAC_FCTRL_MGT_T                 0x0000
#define MAC_FCTRL_CTRL_T                0x0004
#define MAC_FCTRL_DATA_T                0x0008
#define MAC_FCTRL_RSV_T                 0x000c

#define MAC_FCTRL_SUBT_MASK             0x00F0
/* Management SubType */
#define MAC_FCTRL_ASSOCREQ_ST           0x0000
#define MAC_FCTRL_ASSOCRSP_ST           0x0010
#define MAC_FCTRL_REASSOCREQ_ST         0x0020
#define MAC_FCTRL_REASSOCRSP_ST         0x0030
#define MAC_FCTRL_PROBEREQ_ST           0x0040
#define MAC_FCTRL_PROBERSP_ST           0x0050
#define MAC_FCTRL_BEACON_ST             0x0080
#define MAC_FCTRL_ATIM_ST               0x0090
#define MAC_FCTRL_DISASSOC_ST           0x00A0
#define MAC_FCTRL_AUTHENT_ST            0x00B0
#define MAC_FCTRL_DEAUTHENT_ST          0x00C0
#define MAC_FCTRL_ACTION_ST             0x00D0
#define MAC_FCTRL_ACTION_NO_ACK_ST      0x00E0
/* Control SubTypes */
#define MAC_FCTRL_BFM_REPORT_POLL_ST    0x0040
#define MAC_FCTRL_VHT_NDPA_ST           0x0050
#define MAC_FCTRL_CTRL_WRAPPER_ST       0x0070
#define MAC_FCTRL_BAR_ST                0x0080
#define MAC_FCTRL_BA_ST                 0x0090
#define MAC_FCTRL_PSPOLL_ST             0x00A0
#define MAC_FCTRL_RTS_ST                0x00B0
#define MAC_FCTRL_CTS_ST                0x00C0
#define MAC_FCTRL_ACK_ST                0x00D0
#define MAC_FCTRL_CFEND_ST              0x00E0
#define MAC_FCTRL_CFEND_CFACK_ST        0x00F0

/* FRAME CONTROL : Type information including Type and SubType */
#define MAC_FCTRL_TYPESUBTYPE_MASK      (MAC_FCTRL_TYPE_MASK | MAC_FCTRL_SUBT_MASK)
#define MAC_FCTRL_ASSOCREQ              (MAC_FCTRL_MGT_T     | MAC_FCTRL_ASSOCREQ_ST)
#define MAC_FCTRL_ASSOCRSP              (MAC_FCTRL_MGT_T     | MAC_FCTRL_ASSOCRSP_ST)
#define MAC_FCTRL_REASSOCREQ            (MAC_FCTRL_MGT_T     | MAC_FCTRL_REASSOCREQ_ST)
#define MAC_FCTRL_REASSOCRSP            (MAC_FCTRL_MGT_T     | MAC_FCTRL_REASSOCRSP_ST)
#define MAC_FCTRL_PROBEREQ              (MAC_FCTRL_MGT_T     | MAC_FCTRL_PROBEREQ_ST)
#define MAC_FCTRL_PROBERSP              (MAC_FCTRL_MGT_T     | MAC_FCTRL_PROBERSP_ST)
#define MAC_FCTRL_BEACON                (MAC_FCTRL_MGT_T     | MAC_FCTRL_BEACON_ST)
#define MAC_FCTRL_ATIM                  (MAC_FCTRL_MGT_T     | MAC_FCTRL_ATIM_ST)
#define MAC_FCTRL_DISASSOC              (MAC_FCTRL_MGT_T     | MAC_FCTRL_DISASSOC_ST)
#define MAC_FCTRL_AUTHENT               (MAC_FCTRL_MGT_T     | MAC_FCTRL_AUTHENT_ST)
#define MAC_FCTRL_DEAUTHENT             (MAC_FCTRL_MGT_T     | MAC_FCTRL_DEAUTHENT_ST)
#define MAC_FCTRL_ACTION                (MAC_FCTRL_MGT_T     | MAC_FCTRL_ACTION_ST)
#define MAC_FCTRL_ACTION_NO_ACK         (MAC_FCTRL_MGT_T     | MAC_FCTRL_ACTION_NO_ACK_ST)
#define MAC_FCTRL_BFM_REPORT_POLL       (MAC_FCTRL_CTRL_T    | MAC_FCTRL_BFM_REPORT_POLL_ST)
#define MAC_FCTRL_VHT_NDPA              (MAC_FCTRL_CTRL_T    | MAC_FCTRL_VHT_NDPA_ST)
#define MAC_FCTRL_BA                    (MAC_FCTRL_CTRL_T    | MAC_FCTRL_BA_ST)
#define MAC_FCTRL_BAR                   (MAC_FCTRL_CTRL_T    | MAC_FCTRL_BAR_ST)
#define MAC_FCTRL_PSPOLL                (MAC_FCTRL_CTRL_T    | MAC_FCTRL_PSPOLL_ST)
#define MAC_FCTRL_RTS                   (MAC_FCTRL_CTRL_T    | MAC_FCTRL_RTS_ST)
#define MAC_FCTRL_CTS                   (MAC_FCTRL_CTRL_T    | MAC_FCTRL_CTS_ST)
#define MAC_FCTRL_ACK                   (MAC_FCTRL_CTRL_T    | MAC_FCTRL_ACK_ST)
#define MAC_FCTRL_CFEND                 (MAC_FCTRL_CTRL_T    | MAC_FCTRL_CFEND_ST)
#define MAC_FCTRL_CFEND_CFACK           (MAC_FCTRL_CFEND     | MAC_CFACK_ST_BIT)
#define MAC_FCTRL_DATA_CFACK            (MAC_FCTRL_DATA_T    | MAC_CFACK_ST_BIT)
#define MAC_FCTRL_DATA_CFPOLL           (MAC_FCTRL_DATA_T    | MAC_CFPOLL_ST_BIT)
#define MAC_FCTRL_DATA_CFACKPOLL        (MAC_FCTRL_DATA_T    | MAC_FCTRL_DATACFACKPOLL_ST)
#define MAC_FCTRL_NULL_FUNCTION         (MAC_FCTRL_DATA_T    | MAC_NODATA_ST_BIT)
#define MAC_FCTRL_NULL_CFACK            (MAC_FCTRL_NULL_FUNCTION  | MAC_CFACK_ST_BIT)
#define MAC_FCTRL_NULL_CFPOLL           (MAC_FCTRL_NULL_FUNCTION  | MAC_CFPOLL_ST_BIT)
#define MAC_FCTRL_NULL_CFACKPOLL        (MAC_FCTRL_NULL_FUNCTION  | MAC_FCTRL_DATACFACKPOLL_ST)
#define MAC_FCTRL_QOS_DATA              (MAC_FCTRL_DATA_T    | MAC_QOS_ST_BIT)
#define MAC_FCTRL_QOS_DATA_CFACK        (MAC_FCTRL_QOS_DATA  | MAC_CFACK_ST_BIT)
#define MAC_FCTRL_QOS_DATA_CFPOLL       (MAC_FCTRL_QOS_DATA  | MAC_CFPOLL_ST_BIT)
#define MAC_FCTRL_QOS_DATA_CFACKPOLL    (MAC_FCTRL_QOS_DATA  | MAC_FCTRL_DATACFACKPOLL_ST)
#define MAC_FCTRL_QOS_NULL              (MAC_FCTRL_QOS_DATA  | MAC_NODATA_ST_BIT)
#define MAC_FCTRL_QOS_NULL_CFACK        (MAC_FCTRL_QOS_DATA  | MAC_FCTRL_NULL_CFACK)
#define MAC_FCTRL_QOS_NULL_CFPOLL       (MAC_FCTRL_QOS_DATA  | MAC_FCTRL_NULL_CFPOLL)
#define MAC_FCTRL_QOS_NULL_CFACKPOLL    (MAC_FCTRL_QOS_DATA  | MAC_FCTRL_NULL_CFACKPOLL)

/* iq dumping enums, still need to reverse engineer the firmware a little bit more */
#define DUMP_ADC			2
#define DUMP_RX_DATA			3
#define DUMP_RC_ADC			0x1e
#define DUMP_DCCANCEL			0x1f
#define DUMP_PRE_DGC			0x20
#define DUMP_NOTCH			0x21
#define DUMP_RC_IN			4
#define DUMP_RC_OUT			5

/* Type of transmission parameters */
enum {
    /* Default TX parameters for 2.4GHz - 1Mbps, no protection */
    TX_DEFAULT_24G,
    /* Default TX parameters for 5GHz - 6Mbps, no protection */
    TX_DEFAULT_5G,
    /* Default TX parameters for NDPA and BRP transmissions */
    TX_DEFAULT_NDPA_BRP,
    /* Default TX parameters for NDP transmissions */
    TX_DEFAULT_NDP,
    /* Custom TX parameters */
    TX_CUSTOM
};

/* Type of frame descriptor */
enum {
    /* Internal frame descriptor, i.e part of the generic frame module */
    TX_INT,
    /* External frame descriptor */
    TX_EXT
};

/* Access Category enumeration */
enum {
    /* Background */
    AC_BK = 0,
    /* Best-effort */
    AC_BE,
    /* Video */
    AC_VI,
    /* Voice */
    AC_VO,
    /* Number of access categories */
    AC_MAX
};

/* MAC address length in bytes. */
#define MAC_ADDR_LEN  6

/* MAC address structure. */
struct mac_addr {
    /* Array of 16-bit words that make up the MAC address. */
    u16 array[MAC_ADDR_LEN / 2];
} __attribute__((packed));

/* structure of a list element header */
struct co_list_hdr {
    /* Pointer to the next element in the list */
    struct co_list_hdr *next;
};

/* Pointer to confirmation function */
typedef void (*cfm_func_ptr)(void *, u32);

/* TX frame confirmation descriptor */
struct txl_frame_cfm_tag{
    /* Function to be called when TX has been completed */
    cfm_func_ptr cfm_func;
    /* Void pointer to be passed to the confirmation function after TX completion */
    void *env;
};

struct dma_desc {
	u32 src;
	u32 dest;
	u16 length;
	u16 ctrl;
	u32 next;
};

struct tx_pbd {
	u32 upatterntx;
	u32 next;
	u32 datastartptr;
	u32 dataendptr;
	u32 bufctrlinfo;
};

struct txl_buffer_tag {
	u32 length;
	u32 flags;
	struct txl_buffer_tag *next;
	struct txdesc *txdesc;
	struct dma_desc dma_desc;
	struct dma_desc dma_desc_pat;
	struct tx_pbd tbd;
	u32 payload[0];
};

/* Descriptor filled by the LMAC */
struct lmacdesc {
    /* Pointer to the optional Aggregation descriptor */
    struct tx_agg_desc *agg_desc;
    #if NX_AMSDU_TX
    /* Pointer to the embedded buffers */
    struct txl_buffer_tag *buffer[NX_TX_PAYLOAD_MAX];
    #else
    /* Pointer to the embedded buffer */
    struct txl_buffer_tag *buffer;
    #endif //(NX_AMSDU_TX)
    #if (RW_BFMER_EN)
    /* BFR Node used for the transmission */
    struct bfr_mem_node *p_bfr_node;
    #endif //(RW_BFMER_EN)
    /* Pointer to the TX confirmation structure */
    struct tx_hw_desc_s *hw_desc;
};

/* attention: aic8800 uses a more compact hostdesc struct */
#if 0
/* Descriptor filled by the Host */
struct hostdesc {
    #if NX_AMSDU_TX
    u32 orig_addr[NX_TX_PAYLOAD_MAX];
    /* Pointers to packet payloads */
    u32 packet_addr[NX_TX_PAYLOAD_MAX];
    /* Sizes of the MPDU/MSDU payloads*/
    u16 packet_len[NX_TX_PAYLOAD_MAX];
    /* Number of payloads forming the MPDU */
    u8 packet_cnt;
    #else
    u32 orig_addr;
    /* Pointer to packet payload */
    u32 packet_addr;
    /* Size of the payload */
    u16 packet_len;
    #endif //(NX_AMSDU_TX)
    /* Address of the status descriptor in host memory (used for confirmation upload) */
    u32 status_desc_addr;
    /* Destination Address */
    struct mac_addr eth_dest_addr;
    /* Source Address */
    struct mac_addr eth_src_addr;
    /* Ethernet Type */
    u16 ethertype;
    /* PN that was used for first transmission of this MPDU */
    u16 pn[4];
    /* Sequence Number used for first transmission of this MPDU */
    u16 sn;
    /* Timestamp of first transmission of this MPDU */
    u16 timestamp;
    /* Packet TID */
    u8 tid;
    /* VIF index */
    u8 vif_idx;
    /* Station Id (0xFF if station is unknown)*/
    u8 staid;

    #if RW_MUMIMO_TX_EN
    /* MU-MIMO information (GroupId and User Position in the group) - The GroupId
     * is located on bits 0-5 and the User Position on bits 6-7. The GroupId value is set
     * to 63 if MU-MIMO shall not be used
     */
    u8 mumimo_info;
    #endif
    /* TX flags*/
    u16 flags;
};

#endif
struct hostdesc {
    u16 packet_len;             // +0x00
    u16 flags_ext;              // +0x02
    u32 status_desc_addr;       // +0x04

    struct mac_addr dest;       // +0x08
    struct mac_addr src;        // +0x0e

    u16 ethertype;              // +0x14
    u8 ac;                      // +0x16
    u8 tid;                     // +0x17
    u8 vif_idx;                 // +0x18
    u8 staid;                   // +0x19
    u16 flags;                  // +0x1a
};

/* Descriptor filled by the UMAC */
struct umacdesc {
    #if (RW_BFMER_EN)
    /*
     * Flags from UMAC which do not fit with tx_hd.macctrlinfo2 format
     *      Bit 0 - Indicate if frame can be beamformed when sent as a singleton
     */
    u16 tx_flags;
    #endif //(RW_BFMER_EN)
    #if NX_AMPDU_TX
    /*First Sequence Number of the BlockAck window */
    u16 sn_win;
    /* Flags from UMAC (match tx_hd.macctrlinfo2 format) */
    u32 flags;
    /* PHY related flags field - nss, rate, GI type, BW type - filled by driver */
    u32 phy_flags;
    #endif //(NX_AMPDU_TX)
    /* Pointer to the buffer control to use */
    struct txl_buffer_control *buf_control;
    /* Buffer data offset for DMA Download */
    u32 buff_offset;
    /* Length of the payload */
    u16 payl_len;
    /* Header length (MAC + IV + EIV + 802.2 Header) */
    u8 head_len;
    /* 802.2 header length */
    u8 hdr_len_802_2;
    /* Tail length (MIC + ICV) */
    u8 tail_len;
    #if (RW_MESH_EN)
    /* Indicate if Mesh Control field is present in the sent frame */
    bool has_mesh_ctrl;
    /* Number of External Addresses to be inserted in the Mesh Control field */
    u8 nb_ext_addr;
    /* Index of the path to be used */
    u8 path_idx;
    /* Index of the proxy information to be used */
    u8 proxy_idx;
    #endif //(RW_MESH_EN)
};

struct txdesc{
    /* Pointer to the next element in the queue */
    struct co_list_hdr list_hdr;
    /* Information provided by Host */
    struct hostdesc host;
    /* Information provided by UMAC */
    struct umacdesc umac;
    /* Information provided by LMAC */
    struct lmacdesc lmac;
    u32 status;
};

struct txl_frame_desc_tag {
    /* "Normal" descriptor of the TX path */
    struct txdesc txdesc;
    /* Confirmation descriptor used after TX completion to report the status */
    struct txl_frame_cfm_tag cfm;
    /* Type of the frame descriptor (TX_INT or TX_EXT) */
    u8 type;
    /* Indicate if frame transmission has been postponed (valid only if type is TX_INT) */
    bool postponed;
    /* Indicate if frame descriptor can be freed */
    bool keep_desc;
};

/// Structure of a short control frame MAC header
struct mac_hdr_ctrl_short {
    /// Frame control
    u16 fctl;
    /// Duration/ID
    u16 durid;
    /// Address 1
    struct mac_addr addr1;
}__attribute__((packed));

/// Structure of a long control frame MAC header
struct mac_hdr_ctrl {
    /// Frame control
    u16 fctl;
    /// Duration/ID
    u16 durid;
    /// Address 1
    struct mac_addr addr1;
    /// Address 2
    struct mac_addr addr2;
}__attribute__((packed));

/// Structure of a long control frame MAC header
struct mac_hdr {
    /// Frame control
    u16 fctl;
    /// Duration/ID
    u16 durid;
    /// Address 1
    struct mac_addr addr1;
    /// Address 2
    struct mac_addr addr2;
    /// Address 3
    struct mac_addr addr3;
    /// Sequence control
    u16 seq;
}__attribute__((packed));

struct preq_frame {
    /// MAC Header
    struct mac_hdr h;
    /// Rest of the payload
    u8 payload[];
}__attribute__((packed));

/* function callbacks addresses for transmitting data over the air, taken from the reverse engineered aic8800d80 firmware */

typedef void *(*memcpy_cb)(void *s1, const void *s2, int n);
memcpy_cb memcpy = (void *)0x00163339;

/*
 ****************************************************************************************
 * @brief Add an element as last on the list.
 *
 * @param[in] list           Pointer to the list structure
 * @param[in] list_hdr       Pointer to the header to add at the end of the list
 ****************************************************************************************
 */
typedef void (*co_list_push_back_cb)(struct co_list *list, struct co_list_hdr *list_hdr);
co_list_push_back_cb co_list_push_back = (void *)0x0014d085;

/*
 ****************************************************************************************
 * @brief Get a TX frame descriptor.
 * This function is called by any module that needs to transmit a packet generated
 * internally. The caller can choose whether it prefers to let the TX frame module
 * configure automatically the TX parameters to their default values or to configure
 * manually those parameters.
 *
 * @param[in] type      Flag indicating if the sender wants to fully control the TX
 *                      parameters or use default parameters.
 *                      The values that can be put here are @ref TX_DEFAULT_24G,
 *                      @ref TX_DEFAULT_5G or @ref TX_CUSTOM.
 * @param[in] len       Length of the packet to be transmitted (including FCS length)
 *
 * @return A pointer to the allocated TX frame descriptor, or NULL if no descriptors are
 * available anymore.
 *
 ****************************************************************************************
 */
typedef struct txl_frame_desc_tag *(*txl_frame_get_cb)(int type, int len);
txl_frame_get_cb txl_frame_get = (void *)0x00139499;

/*
 ****************************************************************************************
 * @brief Push a TX frame descriptor.
 * This function is called by any module after a call to txl_frame_get. It takes the
 * descriptor returned by this call as parameter.
 *
 * @param[in] desc      Pointer to the descriptor previously returned by @ref txl_frame_get
 * @param[in] ac        Access category on which the frame shall be transmitted
 *
 ****************************************************************************************
 */
typedef bool (*txl_frame_push_cb)(struct txl_frame_desc_tag *desc, u8 ac);
txl_frame_push_cb txl_frame_push = (void *)0x001394c9;

/*
 ****************************************************************************************
 * @brief Push a TX descriptor in the TX frame confirmation queue
 * This function is called under interrupt by the TX control module once the frame has
 * been transmitted.
 *
 * @param[in] txdesc            TX descriptor to be pushed in the confirmation queue
 *
 ****************************************************************************************
 */
typedef void (*txl_frame_cfm_cb)(struct txdesc *txdesc);
txl_frame_cfm_cb txl_frame_cfm = (void *)0x00139535;

/* low level rx dump mode not present in any leaked SDK, detected only in the aic8800d80 firmware */
typedef int (*rx_low_level_dump_cb)(u8 mode);
rx_low_level_dump_cb rx_low_level_dump = (void *)0x001239f4;

/* companion mode used for getting the low level rx dump results */
typedef void (*rx_low_level_get_data_cb)(void);
rx_low_level_get_data_cb rx_low_level_get_data = (void *)0x00123c7c;

/* those functions are declared as 'inline', it is just a memory acces, luckily */
inline u8 co_read8p(u32 addr){
    return (*(u8 *)addr);
}

/*
 ****************************************************************************************
 * @brief Write a 8 bits word.
 * @param[in] addr The address of the first byte of the 8 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline  void co_write8p(u32 addr, u8 value){
    *(u8 *)addr = value;
}


/*
 ****************************************************************************************
 * @brief Read a packed 16 bits word.
 * @param[in] addr The address of the first byte of the 16 bits word.
 * @return The 16 bits value.
 ****************************************************************************************
 */
static inline u16 co_read16p(u32 addr){
    struct co_read16_struct {
        __attribute__((packed)) u16 val;
    } *ptr = (struct co_read16_struct *)addr;
    return ptr->val;
}

/*
 ****************************************************************************************
 * @brief Get the pointer to the buffer control structure
 *
 * @param[in]   txdesc The pointer to the TX descriptor
 *
 * @return    The pointer to the buffer control structure
 *
 ****************************************************************************************
 */
static inline struct txl_buffer_tag *txl_buffer_get(struct txdesc *txdesc){
    struct txl_buffer_tag *buffer = NULL;

    buffer = txdesc->lmac.buffer;
    return buffer;
}

static inline void txl_frame_release(struct txdesc *txdesc, bool postponed){
    struct txl_frame_desc_tag *p_frame = NULL;

    p_frame = (struct txl_frame_desc_tag *)txdesc;
    /* If the descriptor was not statically allocated, push it back in the list of free descriptors */
    if (p_frame->type == TX_INT){
        /* Push the descriptor into the confirmation queue */
        co_list_push_back((void *)0x00188458/* -> this address is the equivalent of &txl_frame_env.desc_free */, &txdesc->list_hdr);
    }
    /* If frame is released after being postponed, call the associated callback */
    if (postponed == true){
        /* Call the callback if any */
        if (p_frame->cfm.cfm_func != NULL){
            /* Status bits show that the frame has not been sent */
            p_frame->cfm.cfm_func(p_frame->cfm.env, 0);
        }
    }
}
`;

const decoder = new TextDecoder();

const USE_LEGACY_ETTORE_THUMB_PATCH = false;

/* unused bytecode: first test from codex, it didn't work fine, at the end building tcc with arm thumb support was the only available option */
const LEGACY_ETTORE_THUMB_PATCH = Uint8Array.from([
	0x30, 0xb5, 0x00, 0x20, 0x39, 0x21, 0x1f, 0x4b, 0x98, 0x47, 0x04, 0x46, 0x00, 0x2c, 0x01, 0xd1,
	0x10, 0x20, 0x30, 0xbd, 0xa5, 0x6c, 0x15, 0xf1, 0x28, 0x00, 0x0b, 0xa1, 0x39, 0x22, 0x1a, 0x4b,
	0x98, 0x47, 0x00, 0x20, 0x2f, 0x21, 0x21, 0x44, 0x08, 0x70, 0xff, 0x20, 0x30, 0x21, 0x21, 0x44,
	0x08, 0x70, 0x20, 0x46, 0x02, 0x21, 0x15, 0x4b, 0x98, 0x47, 0x00, 0x28, 0x01, 0xd1, 0x20, 0x20,
	0x30, 0xbd, 0x42, 0x20, 0x30, 0xbd, 0x00, 0xbf, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x02, 0x11, 0x22, 0x33, 0x44, 0x55, 0x02, 0x11, 0x22, 0x33, 0x44, 0x55, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x01, 0x00, 0x00, 0x06, 0x45, 0x54, 0x54, 0x4f,
	0x52, 0x45, 0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24, 0x03, 0x01, 0x01, 0x00,
	0x00, 0xbf, 0x99, 0x94, 0x13, 0x00, 0x39, 0x33, 0x16, 0x00, 0xc9, 0x94, 0x13, 0x00,
]);

function wantsLegacyEttoreThumbPatch(code, loadAddress) {
  return USE_LEGACY_ETTORE_THUMB_PATCH &&
    (loadAddress >>> 0) === 0x0014eac4 &&
    /patch_entry/.test(code) &&
    /ETTORE/.test(code) &&
    /txl_frame_get/.test(code) &&
    /txl_frame_push/.test(code);
}

function legacyEttoreThumbPatchResult(loadAddress) {
  const bytes = new Uint8Array(LEGACY_ETTORE_THUMB_PATCH);
  return {
    bytes,
    section: ".legacy-thumb-stub",
    entryOffset: 0,
    loadAddress: loadAddress >>> 0,
    entryAddress: loadAddress >>> 0,
    eflags: 0x05000000,
    log: "legacy hand-built Thumb ETTORE patch stub",
  };
}

let compilerModule = null;
let compileProgram = null;
let readCompilerLog = null;
let wasmKeyLoaded = "";
let compilerLog = "";
let aic8800HeaderKey = "";
let aic8800HeaderText = "";


async function loadWasmBytes(request) {
  if (request.wasmBytes) {
    return new Uint8Array(request.wasmBytes);
  }
  const wasmUrl = request.wasmUrl || DEFAULT_WASM_URL;
  let response;
  try {
    response = await fetch(wasmUrl);
  } catch (error) {
    throw new Error("ARM32 TCC WASM cannot be fetched at " + wasmUrl);
  }
  if (!response.ok) {
    throw new Error("ARM32 TCC WASM not found at " + wasmUrl);
  }
  return new Uint8Array(await response.arrayBuffer());
}

async function instantiateCompiler(request) {
  const wasmKey = request.wasmBytes ? "embedded:" + request.wasmBytes.byteLength : (request.wasmUrl || DEFAULT_WASM_URL);
  if (compilerModule && wasmKeyLoaded === wasmKey) {
    return;
  }
  if (typeof ArmTccModule !== "function") {
    throw new Error("ARM32 TCC loader is missing from the patch worker");
  }

  const wasmBytes = await loadWasmBytes(request);
  compilerLog = "";
  compilerModule = await ArmTccModule({
    instantiateWasm(imports, receiveInstance) {
      const module = new WebAssembly.Module(wasmBytes);
      const instance = new WebAssembly.Instance(module, imports);
      receiveInstance(instance);
      return instance.exports;
    },
    locateFile(path) {
      return request.wasmUrl || DEFAULT_WASM_URL;
    },
    print(text) {
      if (text) compilerLog += text + "\n";
    },
    printErr(text) {
      if (text) compilerLog += text + "\n";
    },
  });

  if (!compilerModule || !compilerModule.HEAPU8 || typeof compilerModule.cwrap !== "function") {
    throw new Error("ARM32 TCC module exports are incomplete");
  }
  compileProgram = compilerModule.cwrap("compile_program", "number", ["string", "string"]);
  readCompilerLog = compilerModule.cwrap("compiler_log", "string", []);
  wasmKeyLoaded = wasmKey;
}

async function loadTextAsset(url, label) {
  let response;
  try {
    response = await fetch(url);
  } catch (error) {
    throw new Error(label + " cannot be fetched at " + url);
  }
  if (!response.ok) {
    throw new Error(label + " not found at " + url);
  }
  return await response.text();
}

async function loadAic8800Header(request) {
  if (request.virtualFiles && typeof request.virtualFiles["aic8800d80.h"] === "string") {
    return request.virtualFiles["aic8800d80.h"];
  }
  if (request.useFullAic8800Header) {
    const headerUrl = request.aic8800HeaderUrl || DEFAULT_AIC8800_HEADER_URL;
    if (aic8800HeaderText && aic8800HeaderKey === headerUrl) {
      return aic8800HeaderText;
    }
    aic8800HeaderText = await loadTextAsset(headerUrl, "aic8800d80.h");
    aic8800HeaderKey = headerUrl;
    return aic8800HeaderText;
  }
  return TCC_AIC8800D80_HEADER;
}

function writeVirtualFile(path, text) {
  if (!compilerModule || !compilerModule.FS || typeof compilerModule.FS.writeFile !== "function") {
    return false;
  }
  compilerModule.FS.writeFile(path, text);
  return true;
}

function installAic8800Header(headerText) {
  if (!compilerModule || !compilerModule.FS) {
    return false;
  }
  try {
    compilerModule.FS.mkdir("/include");
  } catch (error) {
  }
  let written = false;
  try {
    written = writeVirtualFile("/include/aic8800d80.h", headerText) || written;
  } catch (error) {
  }
  try {
    written = writeVirtualFile("/aic8800d80.h", headerText) || written;
  } catch (error) {
  }
  return written;
}

function normalizePatchSourceForTcc(code) {
  return String(code || "")
    .replace(/struct\s+txl_frame_desc_tag\s+\*f\s*=\s*NULL\s*;/g, "struct txl_frame_desc_tag *f;")
    .replace(/\n[ \t]*if\s*\(f\s*==\s*NULL\)\s*\{\s*\n[ \t]*ret\s*=\s*-ENOMEM\s*;\s*\n[ \t]*return\s+ret\s*;\s*\n[ \t]*\}/g, "")
    .replace(/\n[ \t]*if\s*\(!txl_frame_push\(f,\s*AC_BE\)\)\s*\{\s*\n[\s\S]*?\n[ \t]*\}\s*\n[ \t]*return\s+ret\s*;/m, "\n\ttxl_frame_push(f, AC_VO);\n\treturn ret;");
}

async function preparePatchSource(request) {
  const normalizedCode = normalizePatchSourceForTcc(request.code || "");
  if (!AIC8800_HEADER_INCLUDE_RE.test(normalizedCode)) {
    return normalizedCode;
  }

  const headerText = await loadAic8800Header(request);
  installAic8800Header(headerText);

  // The bundled TCC wrapper currently hard-codes compiler options, so inline the
  // virtual header too. This keeps #include <aic8800d80.h> working without
  // requiring a rebuilt TCC WASM.
  return normalizedCode.replace(AIC8800_HEADER_INCLUDE_RE, headerText + "\n");
}

function getCompilerLog() {
  let nativeLog = "";
  try {
    nativeLog = readCompilerLog ? readCompilerLog() : "";
  } catch (error) {
  }
  return [compilerLog, nativeLog].filter(Boolean).join("\n").trim();
}

function readCompilerOutput(ptr) {
  const log = getCompilerLog();
  if (!ptr) {
    throw new Error("TCC returned no output" + (log ? ": " + log : ""));
  }
  const heap = compilerModule.HEAPU8;
  if (ptr + 4 > heap.length) {
    throw new Error("TCC returned an invalid output pointer" + (log ? ": " + log : ""));
  }
  const len = heap[ptr] | (heap[ptr + 1] << 8) | (heap[ptr + 2] << 16) | (heap[ptr + 3] << 24);
  if (!len) {
    throw new Error("TCC returned an empty output" + (log ? ": " + log : ""));
  }
  if (ptr + 4 + len > heap.length) {
    throw new Error("TCC output exceeds WASM memory" + (log ? ": " + log : ""));
  }
  return heap.subarray(ptr + 4, ptr + 4 + len).slice();
}

function getCString(bytes, offset) {
  let end = offset;
  while (end < bytes.length && bytes[end] !== 0) {
    end += 1;
  }
  return decoder.decode(bytes.subarray(offset, end));
}

function alignTo(value, alignment) {
  alignment = alignment >>> 0;
  if (!alignment || alignment <= 1) {
    return value >>> 0;
  }
  return ((value + alignment - 1) & ~(alignment - 1)) >>> 0;
}

function applyThumbBranchReloc(view, offset, place, target) {
  if (offset + 4 > view.byteLength) {
    return false;
  }
  const h1 = view.getUint16(offset, true);
  const h2 = view.getUint16(offset + 2, true);
  let delta = ((target & ~1) - (place + 4)) | 0;
  if ((delta & 1) !== 0 || delta < -0x1000000 || delta > 0x0fffffe) {
    return false;
  }
  const s = (delta >> 24) & 1;
  const i1 = (delta >> 23) & 1;
  const i2 = (delta >> 22) & 1;
  const imm10 = (delta >> 12) & 0x03ff;
  const imm11 = (delta >> 1) & 0x07ff;
  const j1 = (~(i1 ^ s)) & 1;
  const j2 = (~(i2 ^ s)) & 1;
  view.setUint16(offset, (h1 & 0xf800) | (s << 10) | imm10, true);
  view.setUint16(offset + 2, (h2 & 0xd000) | (j1 << 13) | (j2 << 11) | imm11, true);
  return true;
}


function decodeThumbBranchTarget(view, offset, place) {
  if (offset + 4 > view.byteLength) {
    return null;
  }
  const h1 = view.getUint16(offset, true);
  const h2 = view.getUint16(offset + 2, true);
  if ((h1 & 0xf800) !== 0xf000 || (h2 & 0x8000) === 0) {
    return null;
  }

  const s = (h1 >> 10) & 1;
  const imm10 = h1 & 0x03ff;
  const j1 = (h2 >> 13) & 1;
  const j2 = (h2 >> 11) & 1;
  const imm11 = h2 & 0x07ff;
  const i1 = (~(j1 ^ s)) & 1;
  const i2 = (~(j2 ^ s)) & 1;
  let imm25 = (s << 24) | (i1 << 23) | (i2 << 22) | (imm10 << 12) | (imm11 << 1);
  if (s) {
    imm25 |= 0xfe000000;
  }
  return ((place + 4 + (imm25 | 0)) >>> 0);
}

const AIC8800_FIRMWARE_THUMB_CALL_TARGETS = Object.freeze([
  { address: 0x00139498, name: "txl_frame_get" },
  { address: 0x00163338, name: "memcpy" },
  { address: 0x001394c8, name: "txl_frame_push" },
  { address: 0x0014d084, name: "co_list_push_back" },
]);

function fixTccAbsoluteThumbCalls(view, baseAddress) {
  // This Thumb TCC backend sometimes fails to emit R_ARM_THM_JUMP24 relocations
  // for absolute firmware calls. The broken branch decodes as:
  //   loaded_target = image_base + firmware_target + instruction_offset
  // Repair that into a real branch to firmware_target.
  const applied = [];
  for (let offset = 0; offset + 4 <= view.byteLength; offset += 2) {
    const place = (baseAddress + offset) >>> 0;
    const target = decodeThumbBranchTarget(view, offset, place);
    if (target === null) {
      continue;
    }
    const intended = (target - baseAddress - offset) >>> 0;
    const fixup = AIC8800_FIRMWARE_THUMB_CALL_TARGETS.find((item) => item.address === intended);
    if (fixup && applyThumbBranchReloc(view, offset, place, fixup.address)) {
      applied.push({
        offset,
        badTarget: target >>> 0,
        target: fixup.address >>> 0,
        name: fixup.name,
      });
    }
  }
  return applied;
}

function parseElf32ArmObject(bytes, loadAddress) {
  if (bytes.length < 52 ||
      bytes[0] !== 0x7f || bytes[1] !== 0x45 || bytes[2] !== 0x4c || bytes[3] !== 0x46) {
    throw new Error("[!] TCC output is not an ELF object" + (compilerLog ? ": " + compilerLog.trim() : ""));
  }
  if (bytes[4] !== 1 || bytes[5] !== 1) {
    throw new Error("TCC output is not ELF32 little-endian");
  }

  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const machine = view.getUint16(18, true);
  if (machine !== 40) {
    throw new Error("TCC output is not ARM32");
  }

  const shoff = view.getUint32(32, true);
  const shentsize = view.getUint16(46, true);
  const shnum = view.getUint16(48, true);
  const shstrndx = view.getUint16(50, true);
  if (!shoff || shentsize < 40 || shstrndx >= shnum) {
    throw new Error("ELF section table is invalid");
  }

  const sections = [];
  for (let index = 0; index < shnum; index += 1) {
    const off = shoff + index * shentsize;
    sections.push({
      index,
      nameOff: view.getUint32(off, true),
      type: view.getUint32(off + 4, true),
      flags: view.getUint32(off + 8, true),
      addr: view.getUint32(off + 12, true),
      offset: view.getUint32(off + 16, true),
      size: view.getUint32(off + 20, true),
      link: view.getUint32(off + 24, true),
      info: view.getUint32(off + 28, true),
      addralign: view.getUint32(off + 32, true),
      entsize: view.getUint32(off + 36, true),
    });
  }

  const shstr = sections[shstrndx];
  const shstrBytes = bytes.subarray(shstr.offset, shstr.offset + shstr.size);
  for (const section of sections) {
    section.name = getCString(shstrBytes, section.nameOff);
  }

  const textSection = sections.find((section) => section.name === ".text.patch" && section.size) ||
                      sections.find((section) => section.name === ".text" && section.size);
  if (!textSection) {
    throw new Error("TCC output has no .text section");
  }

  const loadable = [textSection];
  for (const section of sections) {
    if (section === textSection) {
      continue;
    }
    const alloc = (section.flags & 0x2) !== 0;
    const loadType = section.type === 1 || section.type === 8;
    if (alloc && loadType && section.size) {
      loadable.push(section);
    }
  }

  const sectionOffsets = new Map();
  let imageSize = 0;
  for (const section of loadable) {
    imageSize = alignTo(imageSize, section.addralign || 1);
    sectionOffsets.set(section.index, imageSize);
    imageSize += section.size;
  }
  if (!imageSize) {
    throw new Error("TCC output has no loadable patch bytes");
  }

  let entryOffset = 0;
  const symbols = [];
  const symtab = sections.find((section) => section.type === 2 && section.entsize >= 16 && section.link < sections.length);
  if (symtab) {
    const strtab = sections[symtab.link];
    const strBytes = bytes.subarray(strtab.offset, strtab.offset + strtab.size);
    const count = Math.floor(symtab.size / symtab.entsize);
    for (let index = 0; index < count; index += 1) {
      const off = symtab.offset + index * symtab.entsize;
      const name = getCString(strBytes, view.getUint32(off, true));
      const value = view.getUint32(off + 4, true) >>> 0;
      const shndx = view.getUint16(off + 14, true);
      symbols.push({ name, value, shndx });
      if (name === "patch_entry" && sectionOffsets.has(shndx)) {
        entryOffset = (sectionOffsets.get(shndx) + (value & ~1)) >>> 0;
      }
    }
  }

  const image = new Uint8Array(imageSize);
  for (const section of loadable) {
    const outOff = sectionOffsets.get(section.index);
    if (section.type === 1) {
      image.set(bytes.subarray(section.offset, section.offset + section.size), outOff);
    }
  }

  const imageView = new DataView(image.buffer, image.byteOffset, image.byteLength);
  const unresolvedRelocs = [];
  const entryAddress = loadAddress >>> 0;
  const baseAddress = (entryAddress - entryOffset) >>> 0;
  const absoluteSection = 0xfff1;

  function symbolAddress(symbol, keepThumbBit) {
    if (!symbol) {
      return null;
    }
    if (symbol.shndx === absoluteSection) {
      return symbol.value >>> 0;
    }
    if (!sectionOffsets.has(symbol.shndx)) {
      return null;
    }
    const value = keepThumbBit ? symbol.value : (symbol.value & ~1);
    return (baseAddress + sectionOffsets.get(symbol.shndx) + value) >>> 0;
  }

  for (const relocSection of sections.filter((section) => (section.type === 9 || section.type === 4) && section.size)) {
    const targetSection = sections[relocSection.info];
    if (!targetSection || !sectionOffsets.has(targetSection.index)) {
      unresolvedRelocs.push(relocSection.name);
      continue;
    }
    if (!symtab || relocSection.entsize < 8) {
      unresolvedRelocs.push(relocSection.name);
      continue;
    }
    const targetBase = sectionOffsets.get(targetSection.index);
    const count = Math.floor(relocSection.size / relocSection.entsize);
    for (let index = 0; index < count; index += 1) {
      const off = relocSection.offset + index * relocSection.entsize;
      const relOffset = view.getUint32(off, true) >>> 0;
      const relInfo = view.getUint32(off + 4, true) >>> 0;
      const relType = relInfo & 0xff;
      const symIndex = relInfo >>> 8;
      const symbol = symbols[symIndex];
      const imageRelOffset = targetBase + relOffset;
      if (imageRelOffset + 4 > image.length) {
        unresolvedRelocs.push(relocSection.name);
        continue;
      }
      const explicitAddend = relocSection.type === 4 && relocSection.entsize >= 12 ? view.getInt32(off + 8, true) : 0;
      if (relType === 2) {
        const target = symbolAddress(symbol, true);
        if (target === null) {
          unresolvedRelocs.push(relocSection.name);
          continue;
        }
        const addend = relocSection.type === 4 ? explicitAddend : imageView.getUint32(imageRelOffset, true);
        imageView.setUint32(imageRelOffset, (target + addend) >>> 0, true);
      } else if (relType === 10 || relType === 30) {
        const target = symbolAddress(symbol, false);
        if (target === null) {
          unresolvedRelocs.push(relocSection.name);
          continue;
        }
        const place = (baseAddress + imageRelOffset) >>> 0;
        if (!applyThumbBranchReloc(imageView, imageRelOffset, place, target)) {
          unresolvedRelocs.push(relocSection.name);
        }
      } else if (relType === 1) {
        const target = symbolAddress(symbol, false);
        if (target === null) {
          unresolvedRelocs.push(relocSection.name);
          continue;
        }
        const instruction = imageView.getUint32(imageRelOffset, true) >>> 0;
        let addend = instruction & 0x00ffffff;
        if (addend & 0x00800000) {
          addend |= 0xff000000;
        }
        addend = (addend << 2) >> 0;
        const place = (baseAddress + imageRelOffset) >>> 0;
        const branch = ((target + addend - place) >> 2) & 0x00ffffff;
        imageView.setUint32(imageRelOffset, (instruction & 0xff000000) | branch, true);
      } else {
        unresolvedRelocs.push(relocSection.name + ":" + relType);
      }
    }
  }

  if (unresolvedRelocs.length) {
    throw new Error("TCC output still has relocations: " + Array.from(new Set(unresolvedRelocs)).join(", "));
  }

  const thumbCallFixupDetails = fixTccAbsoluteThumbCalls(imageView, baseAddress);
  const thumbCallFixups = thumbCallFixupDetails.length;

  return {
    bytes: image,
    section: loadable.map((section) => section.name).join("+"),
    entryOffset,
    loadAddress: baseAddress,
    entryAddress,
    eflags: view.getUint32(36, true),
    thumbCallFixups,
    thumbCallFixupDetails,
  };
}

async function compilePatch(request) {
  compilerLog = "";
  const rawCode = String(request.code || "");
  if (wantsLegacyEttoreThumbPatch(rawCode, request.loadAddress || 0)) {
    return legacyEttoreThumbPatchResult(request.loadAddress || 0);
  }

  await instantiateCompiler(request);

  const options = request.options || [
    "-nostdinc",
    "-nostdlib",
    "-ffreestanding",
  ];

  const code = await preparePatchSource(request);
  if (wantsLegacyEttoreThumbPatch(code, request.loadAddress || 0)) {
    return legacyEttoreThumbPatchResult(request.loadAddress || 0);
  }
  const outputPtr = compileProgram(JSON.stringify(options), code);
  compilerLog = getCompilerLog();
  const elf = readCompilerOutput(outputPtr);
  if (outputPtr && compilerModule._free) {
    try {
      compilerModule._free(outputPtr);
    } catch (error) {
    }
  }
  const parsed = parseElf32ArmObject(elf, request.loadAddress || 0);
  return {
    bytes: parsed.bytes,
    section: parsed.section,
    entryOffset: parsed.entryOffset,
    loadAddress: parsed.loadAddress,
    entryAddress: parsed.entryAddress,
    eflags: parsed.eflags,
    thumbCallFixups: parsed.thumbCallFixups,
    thumbCallFixupDetails: parsed.thumbCallFixupDetails,
    log: compilerLog.trim(),
  };
}

self.onmessage = async (event) => {
  const id = event.data && event.data.id;
  try {
    if (!event.data || event.data.type !== "compile") {
      throw new Error("unknown worker command");
    }
    const result = await compilePatch(event.data);
    self.postMessage({
      id,
      ok: true,
      result: {
        bytes: result.bytes.buffer,
        size: result.bytes.byteLength,
        section: result.section,
        entryOffset: result.entryOffset,
        loadAddress: result.loadAddress,
        entryAddress: result.entryAddress,
        eflags: result.eflags,
        thumbCallFixups: result.thumbCallFixups,
        thumbCallFixupDetails: result.thumbCallFixupDetails,
        log: result.log,
      },
    }, [result.bytes.buffer]);
  } catch (error) {
    self.postMessage({
      id,
      ok: false,
      error: error && error.message ? error.message : String(error),
      log: compilerLog.trim(),
    });
  }
};
