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
