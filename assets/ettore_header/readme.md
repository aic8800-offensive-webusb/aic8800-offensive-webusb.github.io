================================================================================
AIC8800D80 Wi-Fi Firmware TX Path
Reverse-engineering notes
================================================================================

Purpose
-------

This document describes the transmit path observed in the AIC8800D80 Wi-Fi
firmware and correlates the decompiled firmware with RivieraWaves/NXMAC TXL
source code.

The objective is educational: to understand how a packet travels from the USB
host interface through the firmware, through the UMAC/TXU and LMAC/TXL layers,
into the NXMAC hardware queues, and finally back through the TX confirmation
path.

Target firmware:
    fmacfw_8800d80_u02

Architecture:
    Host driver
        |
        v
    USB transport
        |
        v
    Firmware IPC / host descriptor
        |
        v
    TX software queues
        |
        v
    TXU / UMAC
        |
        v
    TXL / LMAC
        |
        v
    NXMAC hardware descriptors
        |
        v
    MAC/PHY
        |
        v
    RF / air


================================================================================
1. HIGH-LEVEL TX PATH
================================================================================

The complete path reconstructed so far is:

HOST

    rwnx_start_xmit_vif()
        |
        v
    rwnx_build_txdesc()
        |
        v
    aicwf_usb_bus_txdata()
        |
        v
    USB bulk OUT

            USB packet:
            +-----------------------+
            | 4-byte USB TX header  |
            +-----------------------+
            | 28-byte hostdesc      |
            +-----------------------+
            | packet payload        |
            +-----------------------+

FIRMWARE

    handle_usb_rx()
        0x00132558
        |
        v
    tx_txdesc_get()
        0x00136980
        |
        v
    copy 28-byte host descriptor
        |
        v
    enqueue firmware TX descriptor
        |
        v
    replenish_send()
        0x0012e300
        |
        v
    TXU / upper-MAC preparation
        FUN_0015a770
        |
        +--> Ethernet -> 802.11 header conversion
        |
        +--> LLC/SNAP
        |
        +--> sequence number
        |
        +--> security header
        |
        +--> rate / station / VIF information
        |
        v
    TXL preparation
        FUN_00137ecc
        |
        v
    TX HW descriptor setup
        |
        v
    THD / PBD setup
        |
        v
    txl_frame_exchange_chain()
        0x00137318
        |
        +-------------------------------+
        |                               |
        v                               v
    txl_cntrl_newhead()          txl_cntrl_newtail()
        0x0013702c                   0x00136c34
        |                               |
        +---------------+---------------+
                        |
                        v
                    NXMAC
                        |
                        v
                     PHY
                        |
                        v
                      AIR


COMPLETION

    TX trigger / descriptor completion
        |
        v
    txl_frame_exchange_done()
        0x001379dc
        |
        v
    txl_cfm_evt()
        0x00138978
        |
        v
    txu_cntrl_cfm()
        0x0015ab48
        |
        v
    host confirmation / descriptor release


================================================================================
2. USB HOST TX FORMAT
================================================================================

The host supplies a firmware TX descriptor followed by the packet payload.

Observed USB transfer format:

    offset  size    description
    ------  ----    --------------------------------------------
    0x00    2       USB transfer length
    0x02    1       packet type = 0x01 (TX data)
    0x03    1       reserved / zero
    0x04    28      firmware hostdesc
    0x20    ...     packet payload


The firmware-facing host descriptor is:

    struct hostdesc
    {
        uint16_t packet_len;          // +0x00
        uint16_t flags_ext;           // +0x02
        uint32_t status_desc_addr;    // +0x04

        uint8_t  eth_dest_addr[6];    // +0x08
        uint8_t  eth_src_addr[6];     // +0x0E

        uint16_t ethertype;           // +0x14

        uint8_t  ac;                  // +0x16
        uint8_t  tid;                 // +0x17
        uint8_t  vif_idx;             // +0x18
        uint8_t  staid;               // +0x19

        uint16_t flags;               // +0x1A
    };

    sizeof(hostdesc) = 0x1C = 28 bytes


================================================================================
3. FIRMWARE USB TX INGRESS
================================================================================

Function:

    0x00132558
    proposed name: handle_usb_rx

Confidence:
    very high

This function is one of the first firmware-side consumers of host TX data.

Important observed accesses:

    hostdesc +0x16    access category
    hostdesc +0x18    VIF index
    hostdesc +0x19    station index
    hostdesc +0x1A    TX flags

The firmware checks:

    staid < NX_REMOTE_STA_MAX

NX_REMOTE_STA_MAX appears to be:

    32


The firmware allocates an internal TX descriptor using:

    0x00136980
    tx_txdesc_get()


It then copies the complete host descriptor into the internal descriptor:

    memcpy(internal_txdesc + 4,
           hostdesc,
           0x1C);

Therefore the host descriptor is preserved almost verbatim inside the firmware
TX descriptor.


================================================================================
4. INTERNAL FIRMWARE TX DESCRIPTOR
================================================================================

The internal descriptor pool uses objects of approximately:

    0x58 bytes

Initialization:

    0x001368E0
    proposed name: tx_txdesc_init

Allocation:

    0x00136980
    proposed name: tx_txdesc_get

Release:

    0x001369BC
    proposed name: tx_txdesc_release


One important pointer inside the internal descriptor is:

    txdesc + 0x4C

This points to a hardware TX descriptor associated with the software descriptor.

Observed allocation pattern:

    hardware descriptor size:
        0x50 bytes

Therefore the architecture is approximately:

    firmware txdesc
        size 0x58
            |
            +---- hostdesc
            |
            +---- TXU state
            |
            +---- buffer pointer
            |
            +---- HW descriptor pointer
                      |
                      v
               0x50-byte TX HW descriptor


The firmware also preserves a reference to the original USB receive backing
buffer around:

    txdesc + 0x48

This allows the firmware to keep the host packet memory alive until TX
completion.


================================================================================
5. NORMAL DATA VS NATIVE MANAGEMENT TX
================================================================================

The firmware distinguishes between normal Ethernet-oriented TX and native
management TX.

An important flag is:

    TXU_CNTRL_MGMT_NATIVE
        bit 3

Conceptually:

    flags & BIT(3)

selects the native management path.


NORMAL DATA PATH

The host provides:

    Ethernet metadata
    Ethernet payload

The firmware later constructs:

    802.11 MAC header
    LLC/SNAP
    security header
    sequence control


NATIVE MANAGEMENT PATH

The host provides:

    an already formatted 802.11 management frame

The firmware does not perform the normal Ethernet-to-802.11 conversion.

The native management packet is placed in a separate firmware queue and is
typically transmitted using the management/voice-style scheduling path.

This eventually converges with the normal TX path at TXL.


Conceptual path:

    host-provided 802.11 frame
        |
        v
    TXU_CNTRL_MGMT_NATIVE
        |
        v
    management TX queue
        |
        v
    replenish_send()
        |
        v
    TXL
        |
        v
    NXMAC


================================================================================
6. SOFTWARE TX QUEUES
================================================================================

The firmware has multiple TX access-category queues.

Observed number:

    NX_TXQ_CNT = 5

Typical mapping:

    queue 0     AC_BK
    queue 1     AC_BE
    queue 2     AC_VI
    queue 3     AC_VO
    queue 4     beacon


Host-side descriptor pool sizes seen in the related driver are:

    AC0     8
    AC1     64
    AC2     64
    AC3     32
    AC4     8


The native management queue is handled separately from the ordinary
per-VIF/per-AC data queues.


================================================================================
7. TX SCHEDULER
================================================================================

Function:

    0x0012E300
    proposed name: replenish_send

Confidence:
    very high


This routine drains pending software TX queues.

Approximate behavior:

    1. service native/management TX queue
    2. iterate ordinary access-category queues
    3. check station validity
    4. check power-save conditions
    5. check retransmission/requeue state
    6. call TXU preparation


The main TXU entry called by the scheduler is:

    0x0015A770

Proposed name:

    txu_prepare_and_push

or:

    txu_cntrl_push


================================================================================
8. TXU / UPPER-MAC PROCESSING
================================================================================

The TXU stage prepares the MAC-level representation of the frame.

Main function:

    0x0015A770
    FUN_0015a770


This stage is responsible for several things:

    - VIF validation
    - station validation
    - rate selection context
    - QoS information
    - sequence number assignment
    - 802.11 header construction
    - LLC/SNAP insertion
    - security header preparation
    - native-management handling


Important helper functions:


8.1 Header and sequence computation

    0x0015A21C

This routine computes information including:

    MAC header length
    sequence number
    security/header lengths

Observed MAC header sizes include values such as:

    0x18
    0x1A

with additional bytes depending on:

    QoS
    four-address mode
    security


8.2 Security header length

    0x0015A0F0

Recovered string:

    txu_cntrl_sechdr_len_compute


This routine computes security-related header lengths and associated metadata.


8.3 Security header append

    0x0015A548

Recovered string:

    txu_cntrl_sec_hdr_append


8.4 MAC header construction

    0x0015A738

Proposed name:

    txu_build_mac_header


For normal Ethernet packets this routine creates the outgoing 802.11 header.

It also handles LLC/SNAP encapsulation for Ethernet protocol values requiring
802.11 SNAP encapsulation.


For native management frames this conversion is skipped because the host
already supplied the 802.11 frame.


================================================================================
9. TXL BUFFER MANAGEMENT
================================================================================

The RivieraWaves TXL layer manages payload buffers before handing descriptors
to the MAC hardware.

Important structure:

    struct txl_buffer_tag

contains:

    length
    flags
    next
    txdesc
    tx_pbd
    user_idx
    padding
    payload[]


The TX payload descriptor is:

    struct tx_pbd


The payload buffer is prepared by:

    txl_buffer_alloc()


For ordinary data frames, after a buffer has been allocated, TXL calls:

    txu_cntrl_frame_build(...)

to let the UMAC format the 802.11 packet header.

For management frames:

    TXU_CNTRL_MGMT

causes the frame to be treated as an already formatted MAC frame.

Management frames are intentionally kept contiguous in the TX buffer.


================================================================================
10. THD AND PBD DESCRIPTORS
================================================================================

The NXMAC transmit engine works with at least two important descriptor types:

    THD
        TX Header Descriptor

    PBD
        Payload Buffer Descriptor


The PBD describes a contiguous portion of transmitted data.

Typical fields include:

    upatterntx
    datastartptr
    dataendptr
    next
    bufctrlinfo


TXL creates the descriptor chain approximately as:

    THD
     |
     +--> first_pbd_ptr
             |
             v
            PBD
             |
             +--> next PBD
                     |
                     v
                    ...


For a simple frame:

    THD
     |
     +--> single PBD
             |
             v
          payload


The function:

    txl_buffer_update_thd()

sets:

    thd->first_pbd_ptr

and configures the payload start/end pointers.


================================================================================
11. TX HEADER DESCRIPTOR INITIALIZATION
================================================================================

Before payload download, TXL initializes the THD.

Conceptually:

    txl_hwdesc_config_pre()


Important initialized fields:

    txhd->frmlen
    txhd->upatterntx
    txhd->nextmpdudesc_ptr
    txhd->nextfrmexseq_ptr
    txhd->first_pbd_ptr
    txhd->policyentryaddr
    txhd->macctrlinfo2
    txhd->datastartptr
    txhd->dataendptr
    txhd->frmlifetime
    txhd->statinfo


After payload preparation:

    txl_hwdesc_config_post()

fills:

    PHY control information
    MAC control information
    policy table pointer
    acknowledgment policy
    aggregation state
    security-related settings


Management frames receive special handling.

For management frames:

    multicast/group destination
        -> EXPECTED_ACK_NO_ACK

    unicast destination
        -> EXPECTED_ACK_NORMAL_ACK


================================================================================
12. POLICY TABLE
================================================================================

The NXMAC TX engine uses a policy table associated with the THD.

Important structure:

    struct tx_policy_tbl


It carries information including:

    PHY control
    MAC control
    retry limits
    rate control
    TX power


Example default policy initialization uses:

    6 Mbps OFDM

for normal 5 GHz/default control paths.


The THD contains:

    policyentryaddr

which points to the selected policy table.


================================================================================
13. TXL FRAME PREPARATION
================================================================================

The reverse-engineered firmware contains the following sequence:

    FUN_00137ECC
        |
        v
    FUN_001375C4
        |
        v
    FUN_0013742C
        |
        v
    FUN_00136C9C


Approximate roles:

    FUN_00137ECC
        TXL enqueue / preparation boundary

    FUN_001375C4
        hardware descriptor preparation

    FUN_0013742C
        frame preparation

    FUN_00136C9C
        THD/PBD / buffer descriptor setup


FUN_00136C9C contains diagnostic references related to:

    txl_buffer_machdr_get
    thd->first_pbd_ptr


This strongly associates the routine with final NXMAC descriptor construction.


================================================================================
14. FRAME EXCHANGE CHAINING
================================================================================

Function:

    0x00137318

Recovered name:

    txl_frame_exchange_chain


This function chains a new frame exchange into the NXMAC TX queue.

It examines:

    txl_cntrl_env.txlist[access_category].last_frame_exch


Two cases exist.


CASE 1 - TX queue currently empty

    last_frame_exch == NULL

The first THD becomes the queue head.

TXL calls:

    txl_cntrl_newhead()


CASE 2 - TX queue already active

    last_frame_exch != NULL

The new frame exchange is appended:

    previous_thd->nextfrmexseq_ptr = new_thd

Then TXL calls:

    txl_cntrl_newtail()


This distinction is important because it represents the final software queue
operation immediately before NXMAC begins consuming descriptors.


================================================================================
15. NXMAC NEW HEAD
================================================================================

Function:

    0x0013702C

Recovered name:

    txl_cntrl_newhead


This is one of the most important points in the TX path.

It is effectively the firmware -> MAC hardware boundary.


Its job is:

    1. write the first THD pointer into the appropriate NXMAC TX queue register
    2. set the "NEW HEAD" command bit
    3. configure the queue timeout


Conceptual code:

    nxmac_tx_ac_N_head_ptr_set(thd);
    nxmac_dma_cntrl_set(NXMAC_TX_AC_N_NEW_HEAD_BIT);


Queue mapping:

    AC_BK   -> hardware TX AC0
    AC_BE   -> hardware TX AC1
    AC_VI   -> hardware TX AC2
    AC_VO   -> hardware TX AC3
    AC_BCN  -> beacon queue


Once NEW_HEAD is asserted, NXMAC owns the descriptor chain.


================================================================================
16. NXMAC NEW TAIL
================================================================================

Function:

    0x00136C34

Recovered name:

    txl_cntrl_newtail


When the queue is already active, the firmware does not rewrite the head
pointer.

Instead it:

    1. updates the previous THD next-frame pointer
    2. signals NXMAC that the queue has a new tail


Conceptually:

    nxmac_dma_cntrl_set(NXMAC_TX_AC_N_NEW_TAIL_BIT);


This allows NXMAC to continue consuming the newly extended descriptor chain.


================================================================================
17. HARDWARE TX BOUNDARY
================================================================================

The most accurate firmware/hardware boundary is:

    txl_cntrl_newhead()

and:

    txl_cntrl_newtail()


Everything before these functions is software-controlled descriptor
preparation.

Everything after these functions is mostly handled by NXMAC hardware.


NXMAC then performs functionality such as:

    EDCA
    CCA
    contention/backoff
    RTS/CTS if configured
    ACK processing
    retransmission
    BlockAck handling
    AMPDU transmission
    PHY modulation
    DMA descriptor consumption


The firmware does not manually toggle the radio to transmit each packet.
Instead it describes the transmission to NXMAC and activates the corresponding
hardware queue.


================================================================================
18. INTERNAL FIRMWARE-GENERATED FRAMES
================================================================================

Not every transmitted packet comes from the USB host.

The firmware also generates frames internally.

The RivieraWaves TX frame module uses:

    txl_frame_get()
    txl_frame_push()


Examples include:

    NULL frames
    QoS NULL frames
    BAR frames
    TDLS frames
    beacon-related frames


Internally generated frames already contain complete 802.11 MAC frames.

They therefore bypass the Ethernet-to-802.11 conversion stage but converge on
the same TXL path:

    internal frame
        |
        v
    txl_frame_push()
        |
        v
    txl_cntrl_push_int()
        |
        v
    TXL
        |
        v
    THD
        |
        v
    txl_frame_exchange_chain()
        |
        v
    NXMAC


================================================================================
19. TX COMPLETION
================================================================================

After NXMAC finishes a transmission, status information is written into the
hardware descriptors.

The firmware then processes the TX completion.


Reverse-engineered function:

    0x001379DC

Recovered diagnostic name:

    txl_frame_exchange_done


This routine walks completed TX frame exchanges and examines descriptor status.


The next important stage is:

    0x00138978

Recovered name:

    txl_cfm_evt


The confirmation path handles:

    successful TX
    failed TX
    ACK status
    retry status
    BlockAck status
    rate-control feedback
    software requeue
    descriptor release


================================================================================
20. TXU CONFIRMATION
================================================================================

Function:

    0x0015AB48

Recovered name:

    txu_cntrl_cfm


This function translates the LMAC/NXMAC result into upper-MAC state.

The TX confirmation flow is approximately:

    NXMAC descriptor status
        |
        v
    TXL completion
        |
        v
    txl_cfm_push()
        |
        v
    txl_cfm_evt()
        |
        v
    rate-control update
        |
        v
    txu_cntrl_cfm()
        |
        v
    host confirmation


For singleton MPDUs, the confirmation path calls rate-control feedback first:

    me_tx_cfm_singleton(txdesc)

followed by:

    txu_cntrl_cfm(txdesc)


For AMPDU transmissions, the BlockAck bitmap can be inspected to determine
which individual MPDUs were acknowledged.


================================================================================
21. BLOCK ACK / AMPDU
================================================================================

The TXL confirmation subsystem contains dedicated handling for aggregated
transmissions.

Important concepts:

    A-MPDU
    BAR
    BlockAck
    MPDU sequence numbers
    BA bitmap


The firmware validates a received BlockAck using:

    station index
    TID
    sequence number window


Individual MPDU ACK state is extracted from the BA bitmap before each MPDU is
confirmed to the upper MAC.


================================================================================
22. DESCRIPTOR RELEASE
================================================================================

After completion, the firmware eventually releases:

    payload buffers
    hardware descriptors
    internal software txdesc
    original USB backing buffer


The internal TX descriptor is returned to its free list using:

    0x001369BC
    tx_txdesc_release


This closes the lifetime of the packet.


================================================================================
23. COMPLETE NORMAL DATA PATH
================================================================================

A normal Ethernet frame follows this approximate sequence:

    host Ethernet packet
        |
        v
    hostdesc
        |
        v
    USB bulk OUT
        |
        v
    handle_usb_rx()
        |
        v
    tx_txdesc_get()
        |
        v
    firmware software queue
        |
        v
    replenish_send()
        |
        v
    TXU
        |
        +--> determine station/VIF
        |
        +--> assign sequence number
        |
        +--> construct 802.11 MAC header
        |
        +--> add LLC/SNAP
        |
        +--> add encryption/security metadata
        |
        v
    TXL
        |
        v
    allocate txl_buffer
        |
        v
    construct PBD
        |
        v
    construct THD
        |
        v
    attach policy table
        |
        v
    txl_frame_exchange_chain()
        |
        +--> NEW_HEAD if queue idle
        |
        +--> NEW_TAIL if queue active
        |
        v
    NXMAC DMA
        |
        v
    MAC scheduler
        |
        v
    PHY
        |
        v
    RF
        |
        v
    air


================================================================================
24. COMPLETE NATIVE MANAGEMENT PATH
================================================================================

A host-supplied native 802.11 management frame follows:

    host complete 802.11 frame
        |
        v
    hostdesc.flags |= TXU_CNTRL_MGMT_NATIVE
        |
        v
    USB TX
        |
        v
    handle_usb_rx()
        |
        v
    native management software queue
        |
        v
    replenish_send()
        |
        v
    TXU
        |
        |  Ethernet-to-802.11 conversion skipped
        |
        v
    TXL buffer
        |
        v
    THD/PBD
        |
        v
    txl_frame_exchange_chain()
        |
        v
    txl_cntrl_newhead/newtail
        |
        v
    NXMAC
        |
        v
    PHY
        |
        v
    air


================================================================================
25. IMPORTANT FUNCTIONS FOR GHIDRA
================================================================================

Address       Proposed name                         Confidence
-----------   -----------------------------------   ----------
0x00132558    handle_usb_rx                         very high
0x001326C0    usb_rx_evt                            very high
0x00132CB0    ipc_rx_evt                            very high

0x001368E0    tx_txdesc_init                        very high
0x00136980    tx_txdesc_get                         very high
0x001369BC    tx_txdesc_release                     high

0x0012E300    replenish_send                        very high

0x0015A770    txu_prepare_and_push                  high
0x0015A21C    txu_header_seq_prepare                high
0x0015A0F0    txu_cntrl_sechdr_len_compute         very high
0x0015A548    txu_cntrl_sec_hdr_append             very high
0x0015A738    txu_build_mac_header                  high

0x00137ECC    txl_enqueue_or_prepare                medium/high
0x001375C4    txl_hwdesc_prepare                    medium/high
0x0013742C    txl_frame_prepare                     medium/high
0x00136C9C    txl_buffer_hwdesc_build               high

0x00137318    txl_frame_exchange_chain              very high
0x0013702C    txl_cntrl_newhead                     very high
0x00136C34    txl_cntrl_newtail                     very high

0x001379DC    txl_frame_exchange_done               very high
0x00138978    txl_cfm_evt                           very high
0x0015AB48    txu_cntrl_cfm                         very high


================================================================================
26. BEST PLACES TO INSTRUMENT THE TX PATH
================================================================================

For firmware tracing, four particularly useful locations are:


1. USB ingress

    0x00132558
    handle_usb_rx

Shows exactly what the host submitted.


2. TXU boundary

    0x0015A770

Shows:

    native vs normal packet
    VIF
    STA
    rate decisions
    MAC-header preparation


3. Final frame-exchange chaining

    0x00137318
    txl_frame_exchange_chain

Shows the final THD chain immediately before hardware scheduling.


4. NXMAC handoff

    0x0013702C
    txl_cntrl_newhead

This is the cleanest point to observe the firmware -> NXMAC transition.


Useful completion instrumentation:

    0x001379DC
    0x00138978
    0x0015AB48


================================================================================
27. IMPORTANT RIVIERAWAVES STRUCTURES
================================================================================

The following structures are useful when creating Ghidra types:

    struct txdesc
    struct hostdesc
    struct tx_hd
    struct tx_pbd
    struct tx_policy_tbl
    struct tx_hw_desc_s
    struct txl_buffer_tag
    struct txl_buffer_control
    struct txl_list
    struct txl_cntrl_env_tag
    struct txl_cfm_env_tag


The two most important hardware-facing structures are:

    struct tx_hd
    struct tx_pbd


The most important software-facing structure is:

    struct txdesc


================================================================================
28. SOFTWARE / HARDWARE RESPONSIBILITY SPLIT
================================================================================

Firmware software performs:

    USB parsing
    station/VIF lookup
    QoS classification
    software queueing
    sequence allocation
    MAC-header construction
    LLC/SNAP construction
    security preparation
    rate-policy preparation
    THD/PBD construction
    queue chaining


NXMAC hardware performs:

    descriptor DMA
    EDCA scheduling
    channel access
    backoff
    retransmissions
    ACK processing
    BlockAck operation
    aggregation execution
    PHY timing
    PHY transmission


This separation explains why txl_cntrl_newhead() is such an important boundary:
before it, the frame is software data; after it, the frame has effectively been
submitted to the MAC accelerator.


================================================================================
29. SOURCE CORRELATION
================================================================================

The reconstructed firmware behavior correlates strongly with RivieraWaves
LMAC source modules:

    txl_buffer.c
        TX payload buffer handling
        THD/PBD payload pointers

    txl_buffer.h
        txl_buffer_tag
        txl_buffer_control

    txl_cntrl.c
        main LMAC TX path
        frame exchange chaining
        NEW_HEAD
        NEW_TAIL
        aggregation
        hardware queue handling

    txl_cntrl.h
        txl_list
        txl_cntrl_env_tag
        queue definitions

    txl_hwdesc.c
        TX HW descriptor initialization
        aggregation descriptors

    txl_frame.c
        internally generated frames

    txl_cfm.c
        TX completion and confirmation handling


================================================================================
30. FINAL SUMMARY
================================================================================

The AIC8800D80 TX architecture is based on the RivieraWaves split-MAC model.

The packet crosses four major firmware layers:

    IPC / USB
        |
        v
    TX software queue
        |
        v
    TXU / upper MAC
        |
        v
    TXL / lower MAC
        |
        v
    NXMAC hardware


The most important transition is:

    txl_frame_exchange_chain()
        |
        v
    txl_cntrl_newhead()
        or
    txl_cntrl_newtail()
        |
        v
    NXMAC


That point represents the final firmware scheduling decision before the MAC
hardware takes control of the frame.


================================================================================
END
================================================================================
