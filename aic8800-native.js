(function () {
  "use strict";

  const AIC8800_NATIVE_VERSION = "20260907";
  const WASM_URL = "aic8800-native.wasm?v=" + AIC8800_NATIVE_VERSION;
  const state = {
    api: null,
    error: null,
    ready: null,
  };

  function asExport(exports, name) {
    return exports[name] || exports["_" + name];
  }

  function makeImports() {
    return {
      env: {
        abort: function () {
          throw new Error("aic8800 native core aborted");
        },
        emscripten_notify_memory_growth: function () {
        },
      },
      wasi_snapshot_preview1: {
        proc_exit: function (code) {
          throw new Error("aic8800 native core exited: " + code);
        },
        fd_write: function () {
          return 0;
        },
        fd_close: function () {
          return 0;
        },
        fd_seek: function () {
          return 0;
        },
	args_get: function() {
	  return 0;
	},
	args_sizes_get: function () {
        return 0;
	},
	clock_res_get: function () {
	  return 0;
	},
	clock_time_get: function () {
	  return 0;
	},
	fd_fdstat_get: function () {
	  return 0;
	},
      },
    };
  }

  function readU16LE(bytes, offset) {
    return bytes[offset] | (bytes[offset + 1] << 8);
  }

  function readU32LE(bytes, offset) {
    return (bytes[offset] | (bytes[offset + 1] << 8) | (bytes[offset + 2] << 16) | (bytes[offset + 3] << 24)) >>> 0;
  }

  function writeU32LE(bytes, offset, value) {
    const v = value >>> 0;
    bytes[offset] = v & 0xff;
    bytes[offset + 1] = (v >>> 8) & 0xff;
    bytes[offset + 2] = (v >>> 16) & 0xff;
    bytes[offset + 3] = (v >>> 24) & 0xff;
  }

  function makeApi(exports) {
    const memory = exports.memory;
    const malloc = asExport(exports, "malloc");
    const free = asExport(exports, "free");
    if (!memory || !malloc || !free) {
      throw new Error("aic8800 native core missing memory allocator exports");
    }

    const functions = {
      buildTxPowerLevelV3: asExport(exports, "aic8800_build_tx_power_level_v3"),
      buildMeChanConfig: asExport(exports, "aic8800_build_me_chan_config"),
      buildScanRequest: asExport(exports, "aic8800_build_scan_request"),
      buildAddInterfaceRequest: asExport(exports, "aic8800_build_add_interface_request"),
      buildKeyAddRequest: asExport(exports, "aic8800_build_key_add_request"),
      buildControlPortRequest: asExport(exports, "aic8800_build_control_port_request"),
      buildMeStaAddRequest: asExport(exports, "aic8800_build_me_sta_add_request"),
      decodeMeStaAddConfirm: asExport(exports, "aic8800_decode_me_sta_add_cfm"),
      buildMeStaDelRequest: asExport(exports, "aic8800_build_me_sta_del_request"),
      buildRfCalibRequest: asExport(exports, "aic8800_build_rf_calib_request"),
      buildStartRequest: asExport(exports, "aic8800_build_start_request"),
      buildMemBlockWriteRequest: asExport(exports, "aic8800_build_mem_block_write_request"),
      buildDbgStartNpcRequest: asExport(exports, "aic8800_build_dbg_start_npc_request"),
      fwBootPlan: asExport(exports, "aic8800_fw_boot_plan"),
      fwStepLabel: asExport(exports, "aic8800_fw_step_label"),
      buildStackStartParams: asExport(exports, "aic8800_build_stack_start_params"),
      decodeFwVersionText: asExport(exports, "aic8800_decode_fw_version_text"),
      selectMacFromConfirm: asExport(exports, "aic8800_select_mac_from_cfm"),
      decodeAddIfConfirm: asExport(exports, "aic8800_decode_add_if_cfm"),
      decodeStatusConfirm: asExport(exports, "aic8800_decode_status_cfm"),
      fwImageName: asExport(exports, "aic8800_fw_image_name"),
      fwUploadChunkPlan: asExport(exports, "aic8800_fw_upload_chunk_plan"),
      patchConfigInitialReads: asExport(exports, "aic8800_patch_config_initial_reads"),
      patchConfigExtraRead: asExport(exports, "aic8800_patch_config_extra_read"),
      patchConfigWritePlan: asExport(exports, "aic8800_patch_config_write_plan"),
      decodeMemRwConfirm: asExport(exports, "aic8800_decode_mem_rw_cfm"),
      decodeConnectInd: asExport(exports, "aic8800_decode_connect_ind"),
      packU32: asExport(exports, "aic8800_pack_u32"),
      memReadWordBytes: asExport(exports, "aic8800_mem_read_word_bytes"),
      parseShellCommand: asExport(exports, "aic8800_parse_shell_command"),
      shellCommandAction: asExport(exports, "aic8800_shell_command_action"),
      shellHelpText: asExport(exports, "aic8800_shell_help_text"),
      shellStatusLine: asExport(exports, "aic8800_shell_status_line"),
      hexEditorSetByte: asExport(exports, "aic8800_hex_editor_set_byte"),
      hexEditorRemoveByte: asExport(exports, "aic8800_hex_editor_remove_byte"),
      hexEditorInsertBytes: asExport(exports, "aic8800_hex_editor_insert_bytes"),
      hexEditorCleanCell: asExport(exports, "aic8800_hex_editor_clean_cell"),
      buildLmacMessage: asExport(exports, "aic8800_build_lmac_message"),
      lmacResponseRoute: asExport(exports, "aic8800_lmac_response_route"),
      lmacConfirmCanWait: asExport(exports, "aic8800_lmac_confirm_can_wait"),
      lmacConfirmMessage: asExport(exports, "aic8800_lmac_confirm_message"),
      networkMergePlan: asExport(exports, "aic8800_network_merge_plan"),
      formatNetworkLine: asExport(exports, "aic8800_format_network_line"),
      buildUsbTxData: asExport(exports, "aic8800_build_usb_tx_data"),
      parseRxAggregate: asExport(exports, "aic8800_parse_rx_aggregate"),
      parseLmacResponse: asExport(exports, "aic8800_parse_lmac_response"),
      decodeStaDataFrame: asExport(exports, "aic8800_decode_sta_data_frame"),
      decodeDhcpRequest: asExport(exports, "aic8800_decode_dhcp_request"),
      buildDhcpReplyFrame: asExport(exports, "aic8800_build_dhcp_reply_frame"),
      decodeArpRequest: asExport(exports, "aic8800_decode_arp_request"),
      buildArpReplyFrame: asExport(exports, "aic8800_build_arp_reply_frame"),
      decodePortalIpv4: asExport(exports, "aic8800_decode_portal_ipv4"),
      buildPortalDnsReplyFrame: asExport(exports, "aic8800_build_portal_dns_reply_frame"),
      buildPortalTcpReplyFrame: asExport(exports, "aic8800_build_portal_tcp_reply_frame"),
      decodeApMgmtFrame: asExport(exports, "aic8800_decode_ap_mgmt_frame"),
      decodeScanResult: asExport(exports, "aic8800_decode_scan_result"),
      buildPcapFile: asExport(exports, "aic8800_build_pcap_file"),
      parseU32: asExport(exports, "aic8800_parse_u32"),
      parseHexBytes: asExport(exports, "aic8800_parse_hex_bytes"),
      parseMacAddress: asExport(exports, "aic8800_parse_mac_address"),
      usbIsKnownVendor: asExport(exports, "aic8800_usb_is_known_vendor"),
      usbIsStorageProduct: asExport(exports, "aic8800_usb_is_storage_product"),
      usbIsRomProduct: asExport(exports, "aic8800_usb_is_rom_product"),
      usbDeviceModeCode: asExport(exports, "aic8800_usb_device_mode_code"),
      usbDeviceModeString: asExport(exports, "aic8800_usb_device_mode_string"),
      usbModeMatches: asExport(exports, "aic8800_usb_mode_matches"),
      usbDeviceModeScore: asExport(exports, "aic8800_usb_device_mode_score"),
      usbIsVendorAlternate: asExport(exports, "aic8800_usb_is_vendor_alternate"),
      usbInterfaceScore: asExport(exports, "aic8800_usb_interface_score"),
      usbSelectBestInterface: asExport(exports, "aic8800_usb_select_best_interface"),
      usbProductName: asExport(exports, "aic8800_usb_product_name"),
      defaultMac: asExport(exports, "aic8800_default_mac"),
      buildScsiSwitchCommand: asExport(exports, "aic8800_build_scsi_switch_command"),
      startAppBootType: asExport(exports, "aic8800_start_app_boot_type"),
      maxBlockWrite: asExport(exports, "aic8800_max_block_write"),
      patchDecompileDefaultLength: asExport(exports, "aic8800_patch_decompile_default_length"),
      patchDecompileMaxLength: asExport(exports, "aic8800_patch_decompile_max_length"),
      defaultPatchSource: asExport(exports, "aic8800_default_patch_source"),
      patchScriptCount: asExport(exports, "aic8800_patch_script_count"),
      patchScriptName: asExport(exports, "aic8800_patch_script_name"),
      patchScriptSource: asExport(exports, "aic8800_patch_script_source"),
      formatEndpoint: asExport(exports, "aic8800_format_endpoint"),
      isHexDigit: asExport(exports, "aic8800_is_hex_digit"),
      bytesEqual: asExport(exports, "aic8800_bytes_equal"),
      isBroadcastMac: asExport(exports, "aic8800_is_broadcast_mac"),
      isZeroMac: asExport(exports, "aic8800_is_zero_mac"),
      isUsableUnicastMac: asExport(exports, "aic8800_is_usable_unicast_mac"),
      deriveInterfaceMac: asExport(exports, "aic8800_derive_interface_mac"),
      channelToFrequency: asExport(exports, "aic8800_channel_to_frequency"),
      frequencyToChannel: asExport(exports, "aic8800_frequency_to_channel"),
      buildMeshStartRequest: asExport(exports, "aic8800_build_mesh_start_request"),
      buildMonitorConfigRequest: asExport(exports, "aic8800_build_monitor_config_request"),
      buildSetFilterRequest: asExport(exports, "aic8800_build_set_filter_request"),
      decodeMonitorConfirm: asExport(exports, "aic8800_decode_monitor_cfm"),
      buildApBeaconRequest: asExport(exports, "aic8800_build_ap_beacon_request"),
      buildInjectBeaconFrame: asExport(exports, "aic8800_build_inject_beacon_frame"),
      buildApStartRequest: asExport(exports, "aic8800_build_ap_start_request"),
      decodeApStartConfirm: asExport(exports, "aic8800_decode_ap_start_cfm"),
      buildApStopRequest: asExport(exports, "aic8800_build_ap_stop_request"),
      buildApAuthResponse: asExport(exports, "aic8800_build_ap_auth_response"),
      buildApAssocResponse: asExport(exports, "aic8800_build_ap_assoc_response"),
      buildConnectRequest: asExport(exports, "aic8800_build_connect_request"),
      buildOwfuzzLe16: asExport(exports, "aic8800_build_owfuzz_le16"),
      buildOwfuzzFrameHeader: asExport(exports, "aic8800_build_owfuzz_frame_header"),
      buildDeauthFrame: asExport(exports, "aic8800_build_deauth_frame"),
      buildOwfuzzGeneratedFrame: asExport(exports, "aic8800_build_owfuzz_generated_frame"),
      buildOwfuzzCapturedFrame: asExport(exports, "aic8800_build_owfuzz_captured_frame"),
      owfuzzCanonicalFrameType: asExport(exports, "aic8800_owfuzz_canonical_frame_type"),
      owfuzzIsCapturedProfile: asExport(exports, "aic8800_owfuzz_is_captured_profile"),
      owfuzzProfileTypes: asExport(exports, "aic8800_owfuzz_profile_types"),
      owfuzzLooksHexPayload: asExport(exports, "aic8800_owfuzz_looks_hex_payload"),
      owfuzzParseBool: asExport(exports, "aic8800_owfuzz_parse_bool"),
      owfuzzParseNumber: asExport(exports, "aic8800_owfuzz_parse_number"),
      owfuzzMutationPlan: asExport(exports, "aic8800_owfuzz_mutation_plan"),
      owfuzzMutationLabel: asExport(exports, "aic8800_owfuzz_mutation_label"),
      owfuzzNextSeq: asExport(exports, "aic8800_owfuzz_next_seq"),
      owfuzzSelectNextFrame: asExport(exports, "aic8800_owfuzz_select_next_frame"),
      owfuzzFrameBuildPlan: asExport(exports, "aic8800_owfuzz_frame_build_plan"),
      owfuzzBuildConfig: asExport(exports, "aic8800_owfuzz_build_config"),
      sha1: asExport(exports, "aic8800_sha1"),
      hmacSha1: asExport(exports, "aic8800_hmac_sha1"),
      deriveWpaPmk: asExport(exports, "aic8800_wpa_derive_pmk"),
      wpaPrf512: asExport(exports, "aic8800_wpa_prf512"),
      buildWpaKeyEapol: asExport(exports, "aic8800_build_wpa_key_eapol"),
      buildWpaApMessage1: asExport(exports, "aic8800_build_wpa_ap_message1"),
      buildWpaMessage2: asExport(exports, "aic8800_build_wpa_message2"),
      buildWpaMessage4: asExport(exports, "aic8800_build_wpa_message4"),
      validateWpa2Context: asExport(exports, "aic8800_validate_wpa2_context"),
      wpaPrepareContext: asExport(exports, "aic8800_wpa_prepare_context"),
      wpaBuildMessage1Material: asExport(exports, "aic8800_wpa_build_message1_material"),
      wpaBuildMessage3Material: asExport(exports, "aic8800_wpa_build_message3_material"),
      wpaApBuildMessage3Material: asExport(exports, "aic8800_wpa_ap_build_message3_material"),
      wpaApVerifyMessage4: asExport(exports, "aic8800_wpa_ap_verify_message4"),
      wpaEapolAction: asExport(exports, "aic8800_wpa_eapol_action"),
      buildEapolEthFrame: asExport(exports, "aic8800_build_eapol_eth_frame"),
      findNetworkForConnect: asExport(exports, "aic8800_find_network_for_connect"),
      aesKeyUnwrap: asExport(exports, "aic8800_aes_key_unwrap"),
      findGtkKde: asExport(exports, "aic8800_find_gtk_kde"),
      decodeWpaKeyEapol: asExport(exports, "aic8800_decode_wpa_key_eapol"),
      verifyWpaKeyMic: asExport(exports, "aic8800_verify_wpa_key_mic"),
      frameTypeToString: asExport(exports, "aic8800_frame_type_to_string"),
      formatHexU32: asExport(exports, "aic8800_format_hex_u32"),
      formatMac: asExport(exports, "aic8800_format_mac"),
      formatHexPreview: asExport(exports, "aic8800_format_hex_preview"),
      formatHexdump: asExport(exports, "aic8800_format_hexdump"),
      formatAsciiPreview: asExport(exports, "aic8800_format_ascii_preview"),
      formatMemoryPreview: asExport(exports, "aic8800_format_memory_preview"),
      rxFrameOffset: asExport(exports, "aic8800_rx_frame_offset"),
      rxClassifyRecord: asExport(exports, "aic8800_rx_classify_record"),
      decodeFwPrintText: asExport(exports, "aic8800_decode_fw_print_text"),
      formatInvalidRxDetail: asExport(exports, "aic8800_format_invalid_rx_detail"),
      formatRxDumpHeader: asExport(exports, "aic8800_format_rx_dump_header"),
      formatMonitorDumpHeader: asExport(exports, "aic8800_format_monitor_dump_header"),
      prepareEthernetTx: asExport(exports, "aic8800_prepare_ethernet_tx"),
      prepareMonitorTx: asExport(exports, "aic8800_prepare_monitor_tx"),
      prepareMgmtTx: asExport(exports, "aic8800_prepare_mgmt_tx"),
      formatTxEthLog: asExport(exports, "aic8800_format_tx_eth_log"),
      formatTxMonitorLog: asExport(exports, "aic8800_format_tx_monitor_log"),
      scanGuard: asExport(exports, "aic8800_scan_guard"),
      autoScanShouldRun: asExport(exports, "aic8800_auto_scan_should_run"),
      pcapRetentionShouldEvict: asExport(exports, "aic8800_pcap_retention_should_evict"),
      pcapDownloadName: asExport(exports, "aic8800_pcap_download_name"),
      connectPrepare: asExport(exports, "aic8800_connect_prepare"),
      formatConnectAccepted: asExport(exports, "aic8800_format_connect_accepted"),
      patchRangePlan: asExport(exports, "aic8800_patch_range_plan"),
      patchCompiledPlan: asExport(exports, "aic8800_patch_compiled_plan"),
      fuzzerLaunchPlan: asExport(exports, "aic8800_fuzzer_launch_plan"),
      formatFuzzerInitLog: asExport(exports, "aic8800_format_fuzzer_init_log"),
      formatFuzzerLaunchLog: asExport(exports, "aic8800_format_fuzzer_launch_log"),
      formatFuzzerStopLog: asExport(exports, "aic8800_format_fuzzer_stop_log"),
      owfuzzTickDecision: asExport(exports, "aic8800_owfuzz_tick_decision"),
      owfuzzShouldLogTx: asExport(exports, "aic8800_owfuzz_should_log_tx"),
      owfuzzCaptureLogNeeded: asExport(exports, "aic8800_owfuzz_capture_log_needed"),
      owfuzzTemplateKey: asExport(exports, "aic8800_owfuzz_template_key"),
      owfuzzTemplateMeta: asExport(exports, "aic8800_owfuzz_template_meta"),
      owfuzzStatus: asExport(exports, "aic8800_owfuzz_status"),
      version: asExport(exports, "aic8800_native_version"),
    };

    for (const [name, fn] of Object.entries(functions)) {
      if (typeof fn !== "function") {
        throw new Error("aic8800 native core missing export: " + name);
      }
    }

    function heapU8() {
      return new Uint8Array(memory.buffer);
    }

    function allocBytes(bytes) {
      const ptr = malloc(bytes.length || 1);
      if (!ptr) {
        throw new Error("aic8800 native core allocation failed");
      }
      if (bytes.length) {
        heapU8().set(bytes, ptr);
      }
      return ptr;
    }

    function callOut(size, fn, label = "aic8800 native core call") {
      const ptr = malloc(size || 1);
      if (!ptr) {
        throw new Error("aic8800 native core allocation failed");
      }
      try {
        heapU8().fill(0, ptr, ptr + size);
        const written = fn(ptr, size) >>> 0;
        if (!written || written > size) {
          throw new Error(label + " failed (written=" + written + " size=" + size + ")");
        }
        return heapU8().slice(ptr, ptr + written);
      } finally {
        free(ptr);
      }
    }

    function callOutGrowing(initialSize, maxSize, fn, label = "aic8800 native core call") {
      let size = Math.max(1, initialSize >>> 0);
      const limit = Math.max(size, maxSize >>> 0);
      let lastWritten = 0;
      while (size <= limit) {
        const ptr = malloc(size);
        if (!ptr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, ptr, ptr + size);
          const written = fn(ptr, size) >>> 0;
          lastWritten = written;
          if (written && written <= size) {
            return heapU8().slice(ptr, ptr + written);
          }
        } finally {
          free(ptr);
        }
        size *= 2;
      }
      throw new Error(label + " failed (written=" + lastWritten + " size=" + limit + ")");
    }

    function callFixedMeta(size, fn) {
      const ptr = malloc(size || 1);
      if (!ptr) {
        throw new Error("aic8800 native core allocation failed");
      }
      try {
        heapU8().fill(0, ptr, ptr + size);
        const ok = fn(ptr, size) >>> 0;
        if (!ok) {
          throw new Error("aic8800 native core call failed");
        }
        return heapU8().slice(ptr, ptr + size);
      } finally {
        free(ptr);
      }
    }

    function withInput(bytes, fn) {
      const ptr = allocBytes(bytes);
      try {
        return fn(ptr, bytes.length >>> 0);
      } finally {
        free(ptr);
      }
    }

    function withOptionalInput(bytes, fn) {
      if (!bytes || bytes.length === 0) {
        return fn(0, 0);
      }
      return withInput(bytes, fn);
    }

    function allocMaybe(bytes) {
      if (!bytes || bytes.length === 0) {
        return { ptr: 0, len: 0 };
      }
      return { ptr: allocBytes(bytes), len: bytes.length >>> 0 };
    }

    function freeMaybe(entry) {
      if (entry && entry.ptr) {
        free(entry.ptr);
      }
    }

    function callMeta(input, metaSize, nativeFn, decode) {
      return withInput(input, (inputPtr, inputLen) => {
        const metaPtr = malloc(metaSize);
        if (!metaPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          const ok = nativeFn(inputPtr, inputLen, metaPtr, metaSize) >>> 0;
          if (!ok) {
            return null;
          }
          return decode(heapU8().slice(metaPtr, metaPtr + metaSize));
        } finally {
          free(metaPtr);
        }
      });
    }

    const textEncoder = new TextEncoder();

    function encodeText(value) {
      return textEncoder.encode(String(value === undefined || value === null ? "" : value));
    }

    function decodeAscii(bytes) {
      return new TextDecoder().decode(bytes).replace(/[\x00-\x09\x0b-\x1f\x7f]/g, ".");
    }


    function encodeNullStrings(values) {
      const bytes = [];
      for (const value of values) {
        const encoded = encodeText(value || "");
        for (const byte of encoded) {
          bytes.push(byte);
        }
        bytes.push(0);
      }
      return new Uint8Array(bytes);
    }

    function decodeNullStrings(bytes) {
      const text = new TextDecoder().decode(bytes);
      const strings = text.split("\0");
      if (strings.length && strings[strings.length - 1] === "") {
        strings.pop();
      }
      return strings;
    }

    function macText(mac) {
      if (!mac || mac.length < 6) {
        return "";
      }
      const tmp = [];
      for (let i = 0; i < 6; i += 1) {
        tmp.push((mac[i] >>> 0).toString(16).padStart(2, "0"));
      }
      return tmp.join(":");
    }

    function encodeKvObject(options) {
      const bytes = [];
      const object = options || {};
      for (const key of Object.keys(object)) {
        const value = object[key];
        if (value === undefined || value === null) {
          continue;
        }
        const encodedKey = encodeText(key.toLowerCase());
        const encodedValue = encodeText(value instanceof Uint8Array ? macText(value) : String(value));
        for (const byte of encodedKey) bytes.push(byte);
        bytes.push(0);
        for (const byte of encodedValue) bytes.push(byte);
        bytes.push(0);
      }
      return new Uint8Array(bytes);
    }

    function packOwfuzzPreviousConfig(config) {
      if (!config) {
        return { meta: new Uint8Array(0), strings: new Uint8Array(0) };
      }
      const meta = new Uint8Array(64);
      if (config.source) meta.set(config.source.subarray ? config.source.subarray(0, 6) : new Uint8Array(config.source).subarray(0, 6), 0);
      if (config.target) meta.set(config.target.subarray ? config.target.subarray(0, 6) : new Uint8Array(config.target).subarray(0, 6), 6);
      if (config.bssid) meta.set(config.bssid.subarray ? config.bssid.subarray(0, 6) : new Uint8Array(config.bssid).subarray(0, 6), 12);
      writeU32LE(meta, 20, config.channel >>> 0);
      writeU32LE(meta, 24, (config.freq !== undefined ? config.freq : config.frequency) >>> 0);
      writeU32LE(meta, 28, config.count >>> 0);
      writeU32LE(meta, 32, config.intervalMs >>> 0);
      writeU32LE(meta, 36, config.logEvery >>> 0);
      writeU32LE(meta, 40, config.seed >>> 0);
      writeU32LE(meta, 44, config.captureMax >>> 0);
      writeU32LE(meta, 48, config.maxLen >>> 0);
      let flags = 0;
      if (config.capture) flags |= 1;
      if (config.monitor) flags |= 2;
      if (config.mutate) flags |= 4;
      if (config.rewriteCaptured) flags |= 8;
      writeU32LE(meta, 52, flags >>> 0);
      return {
        meta,
        strings: encodeNullStrings([config.mode || "", config.profile || "", config.ssid || "", config.auth || ""]),
      };
    }

    function parseDecimal(value, fallback) {
      const number = Number.parseInt(String(value === undefined || value === null ? "" : value), 10);
      return Number.isFinite(number) ? number >>> 0 : fallback >>> 0;
    }

    function parseDecimalMaybe(value) {
      const number = Number.parseInt(String(value === undefined || value === null ? "" : value), 10);
      return Number.isFinite(number) ? { valid: true, value: number >>> 0 } : { valid: false, value: 0 };
    }

    function boolOption(value) {
      const normalized = String(value === undefined || value === null ? "" : value).toLowerCase();
      return normalized === "1" || normalized === "true";
    }

    function replayCounterBytes(value) {
      const out = new Uint8Array(8);
      let v = BigInt(value || 0);
      for (let i = 7; i >= 0; i -= 1) {
        out[i] = Number(v & 0xffn);
        v >>= 8n;
      }
      return out;
    }

    function readReplayCounter(bytes, offset) {
      let value = 0n;
      for (let i = 0; i < 8; i += 1) {
        value = (value << 8n) | BigInt(bytes[offset + i]);
      }
      return value;
    }

    function callInputOutput(input, outSize, nativeFn) {
      return withInput(input, (inputPtr, inputLen) => {
        const outPtr = malloc(outSize || 1);
        if (!outPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + outSize);
          const written = nativeFn(inputPtr, inputLen, outPtr, outSize) >>> 0;
          if (!written || written > outSize) {
            return null;
          }
          return heapU8().slice(outPtr, outPtr + written);
        } finally {
          free(outPtr);
        }
      });
    }

    return {
      version: function () {
        return functions.version() >>> 0;
      },
      buildTxPowerLevelV3: function () {
        return callOut(105, (ptr, size) => functions.buildTxPowerLevelV3(ptr, size));
      },
      buildMeChanConfig: function (include5g) {
        return callOut(254, (ptr, size) => functions.buildMeChanConfig(ptr, size, include5g ? 1 : 0));
      },
      buildScanRequest: function (vifIndex, include5g) {
        return callOut(376, (ptr, size) => functions.buildScanRequest(ptr, size, vifIndex >>> 0, include5g ? 1 : 0));
      },
      buildAddInterfaceRequest: function (type, mac, p2p) {
        return withInput(mac, (macPtr, macLen) => callOut(10, (ptr, size) => functions.buildAddInterfaceRequest(ptr, size, type >>> 0, macPtr, macLen, p2p ? 1 : 0)));
      },
      buildKeyAddRequest: function (vifIdx, staIdx, pairwise, key, keyIdx) {
        return withInput(key, (keyPtr, keyLen) => callOut(44, (ptr, size) => functions.buildKeyAddRequest(ptr, size, vifIdx >>> 0, staIdx >>> 0, pairwise ? 1 : 0, keyPtr, keyLen, keyIdx >>> 0)));
      },
      buildControlPortRequest: function (staIdx, opened) {
        return callOut(2, (ptr, size) => functions.buildControlPortRequest(ptr, size, staIdx >>> 0, opened ? 1 : 0));
      },
      buildMeStaAddRequest: function (vifIndex, mac, aid, qos) {
        return withInput(mac, (macPtr, macLen) => callOut(160, (ptr, size) => functions.buildMeStaAddRequest(ptr, size, vifIndex >>> 0, macPtr, macLen, aid >>> 0, qos ? 1 : 0)));
      },
      decodeMeStaAddConfirm: function (params) {
        const input = params || new Uint8Array(0);
        const paramsIn = allocMaybe(input);
        const metaPtr = malloc(4);
        if (!metaPtr) {
          freeMaybe(paramsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 4);
          const ok = functions.decodeMeStaAddConfirm(metaPtr, 4, paramsIn.ptr, paramsIn.len) >>> 0;
          if (!ok) {
            throw new Error("short ME_STA_ADD_CFM");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 4);
          return { status: meta[0], staIdx: meta[1], pmState: meta[2], aligned: meta[3] };
        } finally {
          free(metaPtr);
          freeMaybe(paramsIn);
        }
      },
      buildMeStaDelRequest: function (staIdx) {
        return callOut(2, (ptr, size) => functions.buildMeStaDelRequest(ptr, size, staIdx >>> 0));
      },
      buildRfCalibRequest: function (band5g) {
        return callOut(24, (ptr, size) => functions.buildRfCalibRequest(ptr, size, band5g ? 1 : 0));
      },
      buildStartRequest: function () {
        return callOut(72, (ptr, size) => functions.buildStartRequest(ptr, size));
      },
      buildMemBlockWriteRequest: function (address, bytes) {
        let payload = bytes || new Uint8Array(0);
        if (!(payload instanceof Uint8Array)) {
          payload = new Uint8Array(payload);
        }
        return withOptionalInput(payload, (bytesPtr, bytesLen) => callOut(8 + payload.length, (ptr, size) => functions.buildMemBlockWriteRequest(ptr, size, address >>> 0, bytesPtr, bytesLen)));
      },

      fwBootPlan: function (systemReg) {
        const metaPtr = malloc(12);
        if (!metaPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 12);
          const ok = functions.fwBootPlan(metaPtr, 12, systemReg >>> 0) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native firmware boot plan failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 12);
          return {
            chipMcuId: meta[0],
            chipHwRev: meta[1],
            u01: meta[2] !== 0,
            imageId: meta[3],
            bootAddr: readU32LE(meta, 4),
            maxBlockWrite: readU32LE(meta, 8),
          };
        } finally {
          free(metaPtr);
        }
      },
      fwStepLabel: function (step) {
        return decodeAscii(callOut(32, (ptr, size) => functions.fwStepLabel(ptr, size, step >>> 0)));
      },
      buildStackStartParams: function (useVendorInfoBit) {
        return callOut(4, (ptr, size) => functions.buildStackStartParams(ptr, size, useVendorInfoBit ? 1 : 0));
      },
      decodeFwVersionText: function (params) {
        const input = params || new Uint8Array(0);
        if (!input.length) {
          return null;
        }
        return withInput(input, (paramsPtr, paramsLen) => {
          const outPtr = malloc(64);
          if (!outPtr) {
            throw new Error("aic8800 native core allocation failed");
          }
          try {
            heapU8().fill(0, outPtr, outPtr + 64);
            const written = functions.decodeFwVersionText(outPtr, 64, paramsPtr, paramsLen) >>> 0;
            if (!written) {
              return "";
            }
            return decodeAscii(heapU8().slice(outPtr, outPtr + written));
          } finally {
            free(outPtr);
          }
        });
      },
      selectMacFromConfirm: function (params) {
        const input = params || new Uint8Array(0);
        const paramsIn = allocMaybe(input);
        const outPtr = malloc(6);
        const metaPtr = malloc(4);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(paramsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + 6);
          heapU8().fill(0, metaPtr, metaPtr + 4);
          const written = functions.selectMacFromConfirm(outPtr, 6, metaPtr, 4, paramsIn.ptr, paramsIn.len) >>> 0;
          if (written !== 6) {
            throw new Error("aic8800 native MAC selection failed");
          }
          return { mac: heapU8().slice(outPtr, outPtr + 6), efuse: readU32LE(heapU8(), metaPtr) !== 0 };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(paramsIn);
        }
      },
      decodeAddIfConfirm: function (params) {
        const input = params || new Uint8Array(0);
        const paramsIn = allocMaybe(input);
        const metaPtr = malloc(8);
        if (!metaPtr) {
          freeMaybe(paramsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 8);
          const ok = functions.decodeAddIfConfirm(metaPtr, 8, paramsIn.ptr, paramsIn.len) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native add-if decode failed");
          }
          return { status: readU32LE(heapU8(), metaPtr), vifIndex: readU32LE(heapU8(), metaPtr + 4) };
        } finally {
          free(metaPtr);
          freeMaybe(paramsIn);
        }
      },
      decodeStatusConfirm: function (params) {
        const input = params || new Uint8Array(0);
        const paramsIn = allocMaybe(input);
        const metaPtr = malloc(4);
        if (!metaPtr) {
          freeMaybe(paramsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 4);
          const ok = functions.decodeStatusConfirm(metaPtr, 4, paramsIn.ptr, paramsIn.len) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native status decode failed");
          }
          return readU32LE(heapU8(), metaPtr);
        } finally {
          free(metaPtr);
          freeMaybe(paramsIn);
        }
      },
      fwImageName: function (imageId) {
        return decodeAscii(callOut(40, (ptr, size) => functions.fwImageName(ptr, size, imageId >>> 0)));
      },
      fwUploadChunkPlan: function (baseAddress, imageLen, offset) {
        const metaPtr = malloc(20);
        if (!metaPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 20);
          const ok = functions.fwUploadChunkPlan(metaPtr, 20, baseAddress >>> 0, imageLen >>> 0, offset >>> 0) >>> 0;
          if (!ok) {
            return null;
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 20);
          return {
            address: readU32LE(meta, 0),
            length: readU32LE(meta, 4),
            nextOffset: readU32LE(meta, 8),
            progress: readU32LE(meta, 12),
            log: readU32LE(meta, 16) !== 0,
          };
        } finally {
          free(metaPtr);
        }
      },
      patchConfigInitialReads: function (bootAddr) {
        const raw = callOut(12, (ptr, size) => functions.patchConfigInitialReads(ptr, size, bootAddr >>> 0));
        return [readU32LE(raw, 0), readU32LE(raw, 4), readU32LE(raw, 8)];
      },
      patchConfigExtraRead: function (bootAddr, versionValue) {
        const metaPtr = malloc(8);
        if (!metaPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 8);
          const ok = functions.patchConfigExtraRead(metaPtr, 8, bootAddr >>> 0, versionValue >>> 0) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native patch read plan failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 8);
          return { address: readU32LE(meta, 0), needed: readU32LE(meta, 4) !== 0 };
        } finally {
          free(metaPtr);
        }
      },
      patchConfigWritePlan: function (options) {
        const opts = options || {};
        const raw = callOut(128, (ptr, size) => functions.patchConfigWritePlan(
          ptr,
          size,
          opts.bootAddr >>> 0,
          opts.configBase >>> 0,
          opts.aicPatchStrBase >>> 0,
          opts.versionValue >>> 0,
          opts.patchBuffBase >>> 0,
          opts.hasPatchBuff ? 1 : 0
        ));
        const pairs = [];
        for (let offset = 0; offset + 8 <= raw.length; offset += 8) {
          pairs.push({ address: readU32LE(raw, offset), value: readU32LE(raw, offset + 4) });
        }
        return pairs;
      },
      buildDbgStartNpcRequest: function (bootaddr, bootidx) {
        return callOut(8, (ptr, size) => functions.buildDbgStartNpcRequest(ptr, size, bootaddr >>> 0, bootidx >>> 0), "aic8800_build_dbg_start_npc_request");
      },
      decodeMemRwConfirm: function (params) {
        return callMeta(params, 8, functions.decodeMemRwConfirm, (meta) => ({
          address: readU32LE(meta, 0),
          value: readU32LE(meta, 4),
        }));
      },
      decodeConnectInd: function (params) {
        return callMeta(params, 12, functions.decodeConnectInd, (meta) => ({
          status: readU16LE(meta, 0),
          bssidBytes: meta.slice(2, 8),
          vifIdx: meta[8],
          apIdx: meta[9],
        }));
      },
      packU32: function (...values) {
        if (values.length > 2) {
          throw new Error("native packU32 supports up to two values");
        }
        return callOut(values.length * 4, (ptr, size) => functions.packU32(ptr, size, values[0] >>> 0, values[1] >>> 0, values.length >>> 0));
      },

      memReadWordBytes: function (value, take) {
        const count = Math.max(0, Math.min(4, take >>> 0));
        if (!count) {
          return new Uint8Array(0);
        }
        return callOut(count, (ptr, size) => functions.memReadWordBytes(ptr, size, value >>> 0, count));
      },
      parseShellCommand: function (raw) {
        const input = encodeText(raw || "");
        if (!input.length) {
          return null;
        }
        return withInput(input, (inputPtr, inputLen) => {
          const metaPtr = malloc(4);
          const outSize = Math.max(64, input.length * 4 + 16);
          const outPtr = malloc(outSize);
          if (!metaPtr || !outPtr) {
            if (metaPtr) free(metaPtr);
            if (outPtr) free(outPtr);
            throw new Error("aic8800 native core allocation failed");
          }
          try {
            heapU8().fill(0, metaPtr, metaPtr + 4);
            heapU8().fill(0, outPtr, outPtr + outSize);
            const written = functions.parseShellCommand(inputPtr, inputLen, metaPtr, 4, outPtr, outSize) >>> 0;
            if (!written || written > outSize) {
              return null;
            }
            const meta = heapU8().slice(metaPtr, metaPtr + 4);
            const partCount = readU16LE(meta, 0);
            const kvCount = readU16LE(meta, 2);
            const strings = new TextDecoder().decode(heapU8().slice(outPtr, outPtr + written)).split("\0");
            if (strings.length && strings[strings.length - 1] === "") {
              strings.pop();
            }
            let index = 0;
            const name = strings[index++] || "";
            const argText = strings[index++] || "";
            const parts = strings.slice(index, index + partCount);
            index += partCount;
            const args = {};
            for (let i = 0; i < kvCount; i += 1) {
              const key = strings[index++] || "";
              const value = strings[index++] || "";
              if (key) {
                args[key] = value;
              }
            }
            return { name, argText, parts, args };
          } finally {
            free(outPtr);
            free(metaPtr);
          }
        });
      },
      shellCommandAction: function (parsed) {
        const command = parsed || {};
        const parts = Array.isArray(command.parts) ? command.parts : [];
        const args = command.args || {};
        const nameIn = allocMaybe(encodeText(command.name || ""));
        const subIn = allocMaybe(encodeText(parts[1] || ""));
        const argIn = allocMaybe(encodeText(command.argText || ""));
        try {
          return functions.shellCommandAction(
            nameIn.ptr,
            nameIn.len,
            subIn.ptr,
            subIn.len,
            argIn.ptr,
            argIn.len,
            args.data || args.payload ? 1 : 0
          ) >>> 0;
        } finally {
          freeMaybe(argIn);
          freeMaybe(subIn);
          freeMaybe(nameIn);
        }
      },
      shellHelpText: function () {
        return decodeAscii(callOutGrowing(2048, 16384, (ptr, size) => functions.shellHelpText(ptr, size), "aic8800_shell_help_text"));
      },
      shellStatusLine: function (options) {
        const opts = options || {};
        const modeIn = allocMaybe(encodeText(opts.mode || "unknown"));
        const macIn = allocMaybe(opts.mac || null);
        try {
          return decodeAscii(callOut(256, (ptr, size) => functions.shellStatusLine(
            ptr,
            size,
            modeIn.ptr,
            modeIn.len,
            opts.fwVersion >>> 0,
            opts.staVifIndex >>> 0,
            opts.meshVifIndex >>> 0,
            opts.p2pVifIndex >>> 0,
            opts.monitorVifIndex >>> 0,
            opts.apVifIndex >>> 0,
            macIn.ptr,
            macIn.len,
            opts.networks >>> 0,
            opts.pcapFrames >>> 0,
            opts.pcapBytes >>> 0
          )));
        } finally {
          freeMaybe(macIn);
          freeMaybe(modeIn);
        }
      },

      hexEditorSetByte: function (bytes, index, value) {
        const input = bytes instanceof Uint8Array ? bytes : new Uint8Array(bytes || []);
        const outSize = Math.max(input.length, (index >>> 0) + 1);
        return withOptionalInput(input, (inputPtr, inputLen) => callOut(outSize, (ptr, size) => functions.hexEditorSetByte(ptr, size, inputPtr, inputLen, index >>> 0, value >>> 0)));
      },
      hexEditorRemoveByte: function (bytes, index) {
        const input = bytes instanceof Uint8Array ? bytes : new Uint8Array(bytes || []);
        if (!input.length) {
          return new Uint8Array(0);
        }
        if ((index >>> 0) >= input.length) {
          return new Uint8Array(input);
        }
        if (input.length === 1) {
          return new Uint8Array(0);
        }
        return withInput(input, (inputPtr, inputLen) => callOut(input.length - 1, (ptr, size) => functions.hexEditorRemoveByte(ptr, size, inputPtr, inputLen, index >>> 0)));
      },
      hexEditorInsertBytes: function (bytes, index, insertBytes) {
        const input = bytes instanceof Uint8Array ? bytes : new Uint8Array(bytes || []);
        const inserted = insertBytes instanceof Uint8Array ? insertBytes : new Uint8Array(insertBytes || []);
        if (!inserted.length) {
          return new Uint8Array(input);
        }
        const outSize = input.length + inserted.length;
        const inputIn = allocMaybe(input);
        const insertIn = allocMaybe(inserted);
        try {
          return callOut(outSize, (ptr, size) => functions.hexEditorInsertBytes(ptr, size, inputIn.ptr, inputIn.len, index >>> 0, insertIn.ptr, insertIn.len));
        } finally {
          freeMaybe(insertIn);
          freeMaybe(inputIn);
        }
      },
      hexEditorCleanCell: function (raw) {
        const input = encodeText(raw || "");
        return withInput(input, (inputPtr, inputLen) => {
          const outPtr = malloc(2);
          if (!outPtr) {
            throw new Error("aic8800 native core allocation failed");
          }
          try {
            heapU8().fill(0, outPtr, outPtr + 2);
            const written = functions.hexEditorCleanCell(outPtr, 2, inputPtr, inputLen) >>> 0;
            if (written > 2) {
              throw new Error("aic8800 native hex cell parse failed");
            }
            return decodeAscii(heapU8().slice(outPtr, outPtr + written));
          } finally {
            free(outPtr);
          }
        });
      },
      buildLmacMessage: function (options) {
        const opts = options || {};
        let params = opts.params || new Uint8Array(0);
        if (!(params instanceof Uint8Array)) {
          params = new Uint8Array(params);
        }
        if (params.length > 0xffff - 8) {
          throw new Error("LMAC message parameters too large");
        }
        return withOptionalInput(params, (paramsPtr, paramsLen) => callOut(16 + params.length, (ptr, size) => functions.buildLmacMessage(
          ptr,
          size,
          opts.id >>> 0,
          opts.destId >>> 0,
          opts.srcId >>> 0,
          paramsPtr,
          paramsLen
        )));
      },
      lmacResponseRoute: function (id) {
        return functions.lmacResponseRoute(id >>> 0) >>> 0;
      },
      lmacConfirmCanWait: function (confirmId, alreadyPending) {
        return Boolean(functions.lmacConfirmCanWait(confirmId >>> 0, alreadyPending ? 1 : 0) >>> 0);
      },
      lmacConfirmMessage: function (kind, confirmId) {
        return decodeAscii(callOut(96, (ptr, size) => functions.lmacConfirmMessage(ptr, size, kind >>> 0, confirmId >>> 0)));
      },
      networkMergePlan: function (previousSsid, newSsid) {
        const prevIn = allocMaybe(encodeText(previousSsid || ""));
        const newIn = allocMaybe(encodeText(newSsid || ""));
        const metaPtr = malloc(8);
        if (!metaPtr) {
          freeMaybe(newIn);
          freeMaybe(prevIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 8);
          const ok = functions.networkMergePlan(metaPtr, 8, prevIn.ptr, prevIn.len, newIn.ptr, newIn.len) >>> 0;
          if (!ok) {
            return { usePreviousSsid: false, logChange: true };
          }
          return { usePreviousSsid: readU32LE(heapU8(), metaPtr) !== 0, logChange: readU32LE(heapU8(), metaPtr + 4) !== 0 };
        } finally {
          free(metaPtr);
          freeMaybe(newIn);
          freeMaybe(prevIn);
        }
      },
      formatNetworkLine: function (network, scanPrefix) {
        const item = network || {};
        const ssidIn = allocMaybe(encodeText(item.ssid || ""));
        const bssidIn = allocMaybe(encodeText(item.bssid || ""));
        try {
          return decodeAscii(callOut(256, (ptr, size) => functions.formatNetworkLine(
            ptr,
            size,
            ssidIn.ptr,
            ssidIn.len,
            bssidIn.ptr,
            bssidIn.len,
            item.freq >>> 0,
            item.rssi | 0,
            scanPrefix ? 1 : 0
          )));
        } finally {
          freeMaybe(bssidIn);
          freeMaybe(ssidIn);
        }
      },
      buildUsbTxData: function (desc, payload) {
        if (!desc || desc.length !== 28) {
          throw new Error("invalid tx descriptor");
        }
        let payloadBytes = payload || new Uint8Array(0);
        if (!(payloadBytes instanceof Uint8Array)) {
          payloadBytes = new Uint8Array(payloadBytes);
        }
        const usbLen = 4 + 28 + payloadBytes.length;
        if (usbLen > 0x0fff) {
          throw new Error("tx frame too large");
        }
        let outSize = usbLen;
        if (outSize % 512 === 0) {
          outSize += 1;
        }
        return withInput(desc, (descPtr, descLen) => withOptionalInput(payloadBytes, (payloadPtr, payloadLen) => callOut(outSize, (ptr, size) => functions.buildUsbTxData(
          ptr,
          size,
          descPtr,
          descLen,
          payloadPtr,
          payloadLen
        ), "aic8800_build_usb_tx_data")));
      },
      parseRxAggregate: function (bytes) {
        if (!bytes || bytes.length < 4) {
          return [];
        }
        return withInput(bytes, (bytesPtr, bytesLen) => {
          const recordSize = 20;
          const capacity = Math.max(1, Math.floor(bytesLen / 4));
          const metaSize = capacity * recordSize;
          const metaPtr = malloc(metaSize);
          if (!metaPtr) {
            throw new Error("aic8800 native core allocation failed");
          }
          try {
            heapU8().fill(0, metaPtr, metaPtr + metaSize);
            const count = functions.parseRxAggregate(bytesPtr, bytesLen, metaPtr, metaSize) >>> 0;
            const raw = heapU8().slice(metaPtr, metaPtr + count * recordSize);
            const records = [];
            for (let offset = 0; offset + recordSize <= raw.length; offset += recordSize) {
              const flags = raw[offset + 19];
              records.push({
                offset: readU32LE(raw, offset),
                blockLen: readU32LE(raw, offset + 4),
                adjustLen: readU32LE(raw, offset + 8),
                remaining: readU32LE(raw, offset + 12),
                pktLen: readU16LE(raw, offset + 16),
                type: raw[offset + 18],
                cfg: (flags & 1) !== 0,
                invalid: (flags & 2) !== 0,
              });
            }
            return records;
          } finally {
            free(metaPtr);
          }
        });
      },
      parseLmacResponse: function (block) {
        return callMeta(block, 16, functions.parseLmacResponse, (meta) => {
          const paramStart = readU32LE(meta, 8);
          const paramEnd = readU32LE(meta, 12);
          return {
            id: readU16LE(meta, 0),
            paramLen: readU16LE(meta, 2),
            pattern: readU32LE(meta, 4),
            paramStart,
            paramEnd,
            params: block.slice(paramStart, paramEnd),
          };
        });
      },
      parseU32: function (text) {
        const out = callInputOutput(encodeText(text), 4, functions.parseU32);
        return out ? readU32LE(out, 0) : null;
      },
      parseHexBytes: function (text) {
        const input = encodeText(text);
        return callInputOutput(input, Math.max(1, Math.ceil(input.length / 2)), functions.parseHexBytes);
      },
      parseMacAddress: function (text) {
        return callInputOutput(encodeText(text), 6, functions.parseMacAddress);
      },

      usbIsKnownVendor: function (vendorId) {
        return Boolean(functions.usbIsKnownVendor(vendorId >>> 0) >>> 0);
      },
      usbIsStorageProduct: function (productId) {
        return Boolean(functions.usbIsStorageProduct(productId >>> 0) >>> 0);
      },
      usbIsRomProduct: function (productId) {
        return Boolean(functions.usbIsRomProduct(productId >>> 0) >>> 0);
      },
      usbDeviceModeCode: function (vendorId, productId) {
        return functions.usbDeviceModeCode(vendorId >>> 0, productId >>> 0) >>> 0;
      },
      usbDeviceModeString: function (vendorId, productId) {
        return decodeAscii(callOut(16, (ptr, size) => functions.usbDeviceModeString(ptr, size, vendorId >>> 0, productId >>> 0)));
      },
      usbModeMatches: function (vendorId, productId, preferredMode) {
        return withInput(encodeText(preferredMode || "any"), (ptr, len) => Boolean(functions.usbModeMatches(vendorId >>> 0, productId >>> 0, ptr, len) >>> 0));
      },
      usbDeviceModeScore: function (vendorId, productId, preferredMode) {
        return withInput(encodeText(preferredMode || "any"), (ptr, len) => functions.usbDeviceModeScore(vendorId >>> 0, productId >>> 0, ptr, len) >>> 0);
      },
      usbIsVendorAlternate: function (alternate) {
        const alt = alternate || {};
        return Boolean(functions.usbIsVendorAlternate(alt.interfaceClass >>> 0, alt.interfaceSubclass >>> 0, alt.interfaceProtocol >>> 0) >>> 0);
      },
      usbInterfaceScore: function (alternate, inCount, outCount, preferStorage) {
        const alt = alternate || {};
        return functions.usbInterfaceScore(alt.interfaceClass >>> 0, alt.interfaceSubclass >>> 0, alt.interfaceProtocol >>> 0, inCount >>> 0, outCount >>> 0, preferStorage ? 1 : 0) >>> 0;
      },
      usbSelectBestInterface: function (records, productId, ramMode) {
        const list = Array.isArray(records) ? records : [];
        const raw = new Uint8Array(list.length * 32);
        for (let i = 0; i < list.length; i += 1) {
          const rec = list[i] || {};
          const off = i * 32;
          writeU32LE(raw, off, rec.interfaceNumber >>> 0);
          writeU32LE(raw, off + 4, rec.alternateIndex >>> 0);
          writeU32LE(raw, off + 8, rec.interfaceClass >>> 0);
          writeU32LE(raw, off + 12, rec.interfaceSubclass >>> 0);
          writeU32LE(raw, off + 16, rec.interfaceProtocol >>> 0);
          writeU32LE(raw, off + 20, rec.inCount >>> 0);
          writeU32LE(raw, off + 24, rec.outCount >>> 0);
        }
        const rawIn = allocMaybe(raw);
        const metaPtr = malloc(16);
        if (!metaPtr) {
          freeMaybe(rawIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 16);
          functions.usbSelectBestInterface(metaPtr, 16, rawIn.ptr, rawIn.len, productId >>> 0, ramMode ? 1 : 0) >>> 0;
          const status = readU32LE(heapU8(), metaPtr);
          const indexRaw = readU32LE(heapU8(), metaPtr + 4);
          return {
            status,
            index: indexRaw === 0xffffffff ? -1 : indexRaw,
            score: readU32LE(heapU8(), metaPtr + 8),
            vendor: readU32LE(heapU8(), metaPtr + 12) !== 0,
          };
        } finally {
          free(metaPtr);
          freeMaybe(rawIn);
        }
      },
      usbProductName: function (productId) {
        const ptr = malloc(32);
        if (!ptr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          const written = functions.usbProductName(ptr, 32, productId >>> 0) >>> 0;
          if (!written) {
            return null;
          }
          return decodeAscii(heapU8().slice(ptr, ptr + written));
        } finally {
          free(ptr);
        }
      },
      defaultMac: function () {
        return callOut(6, (ptr, size) => functions.defaultMac(ptr, size));
      },
      buildScsiSwitchCommand: function () {
        return callOut(32, (ptr, size) => functions.buildScsiSwitchCommand(ptr, size));
      },
      startAppBootType: function () {
        return functions.startAppBootType() >>> 0;
      },
      maxBlockWrite: function () {
        return functions.maxBlockWrite() >>> 0;
      },
      patchDecompileDefaultLength: function () {
        return functions.patchDecompileDefaultLength() >>> 0;
      },
      patchDecompileMaxLength: function () {
        return functions.patchDecompileMaxLength() >>> 0;
      },
      defaultPatchSource: function () {
        return decodeAscii(callOutGrowing(256, 4096, (ptr, size) => functions.defaultPatchSource(ptr, size), "aic8800_default_patch_source"));
      },
      patchScriptCount: function () {
        return functions.patchScriptCount() >>> 0;
      },
      patchScriptName: function (index) {
        return decodeAscii(callOutGrowing(32, 256, (ptr, size) => functions.patchScriptName(ptr, size, index >>> 0), "aic8800_patch_script_name"));
      },
      patchScriptSource: function (index) {
        return decodeAscii(callOutGrowing(4096, 65536, (ptr, size) => functions.patchScriptSource(ptr, size, index >>> 0), "aic8800_patch_script_source"));
      },
      patchScripts: function () {
        const count = functions.patchScriptCount() >>> 0;
        const scripts = [];
        for (let i = 0; i < count; i += 1) {
          scripts.push({ index: i, name: decodeAscii(callOutGrowing(32, 256, (ptr, size) => functions.patchScriptName(ptr, size, i), "aic8800_patch_script_name")) });
        }
        return scripts;
      },
      formatEndpoint: function (endpoint) {
        if (!endpoint) {
          return decodeAscii(callOut(1, (ptr, size) => functions.formatEndpoint(ptr, size, 0, 0, 0)));
        }
        const isIn = endpoint.direction === "in";
        return decodeAscii(callOut(10, (ptr, size) => functions.formatEndpoint(ptr, size, endpoint.endpointNumber >>> 0, isIn ? 1 : 0, 1)));
      },
      rxFrameOffset: function (blockLen) {
        return functions.rxFrameOffset(blockLen >>> 0) >>> 0;
      },
      rxClassifyRecord: function (record, monitorMode) {
        const rec = record || {};
        const meta = callFixedMeta(8, (ptr, size) => functions.rxClassifyRecord(ptr, size, rec.type >>> 0, rec.cfg ? 1 : 0, monitorMode ? 1 : 0));
        return {
          event: readU32LE(meta, 0),
          cleanType: meta[4],
          cfg: meta[5] !== 0,
          monitor: meta[6] !== 0,
        };
      },
      decodeFwPrintText: function (block, pktLen) {
        const input = block || new Uint8Array(0);
        const outSize = Math.max(1, Math.min(pktLen >>> 0, input.length > 4 ? input.length - 4 : 0));
        return withInput(input, (blockPtr, blockLen) => {
          const outPtr = malloc(outSize);
          if (!outPtr) {
            throw new Error("aic8800 native core allocation failed");
          }
          try {
            heapU8().fill(0, outPtr, outPtr + outSize);
            const written = functions.decodeFwPrintText(outPtr, outSize, blockPtr, blockLen, pktLen >>> 0) >>> 0;
            if (written > outSize) {
              throw new Error("aic8800 native firmware print decode failed");
            }
            return written ? decodeAscii(heapU8().slice(outPtr, outPtr + written)) : "";
          } finally {
            free(outPtr);
          }
        });
      },
      formatInvalidRxDetail: function (record) {
        const rec = record || {};
        return decodeAscii(callOut(96, (ptr, size) => functions.formatInvalidRxDetail(
          ptr,
          size,
          rec.blockLen >>> 0,
          rec.adjustLen >>> 0,
          rec.remaining >>> 0,
          rec.type >>> 0
        )));
      },
      formatRxDumpHeader: function (frameLen, previewLen) {
        return decodeAscii(callOut(64, (ptr, size) => functions.formatRxDumpHeader(ptr, size, frameLen >>> 0, previewLen >>> 0)));
      },
      formatMonitorDumpHeader: function (frame, count, blockLen, pktLen) {
        const input = frame || new Uint8Array(0);
        return withOptionalInput(input, (framePtr, frameLen) => decodeAscii(callOut(128, (ptr, size) => functions.formatMonitorDumpHeader(
          ptr,
          size,
          framePtr,
          frameLen,
          count >>> 0,
          blockLen >>> 0,
          pktLen >>> 0
        ))));
      },
      prepareEthernetTx: function (frame, staVif, staAp) {
        const input = frame instanceof Uint8Array ? frame : new Uint8Array(frame || []);
        const frameIn = allocMaybe(input);
        const descPtr = malloc(28);
        const metaPtr = malloc(32);
        if (!descPtr || !metaPtr) {
          if (descPtr) free(descPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(frameIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, descPtr, descPtr + 28);
          heapU8().fill(0, metaPtr, metaPtr + 32);
          const ok = functions.prepareEthernetTx(descPtr, 28, metaPtr, 32, frameIn.ptr, frameIn.len, staVif >>> 0, staAp >>> 0) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native ethernet tx planner failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 32);
          return {
            status: readU32LE(meta, 0),
            payloadOffset: readU32LE(meta, 4),
            payloadLength: readU32LE(meta, 8),
            frameLength: readU32LE(meta, 12),
            vif: readU32LE(meta, 16),
            sta: readU32LE(meta, 20),
            ethertype: readU32LE(meta, 24),
            statusDescAddr: readU32LE(meta, 28),
            desc: heapU8().slice(descPtr, descPtr + 28),
          };
        } finally {
          freeMaybe(frameIn);
          free(descPtr);
          free(metaPtr);
        }
      },
      prepareMonitorTx: function (frame, monitorVif, monitorActive) {
        const input = frame instanceof Uint8Array ? frame : new Uint8Array(frame || []);
        const frameIn = allocMaybe(input);
        const descPtr = malloc(28);
        const metaPtr = malloc(32);
        if (!descPtr || !metaPtr) {
          if (descPtr) free(descPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(frameIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, descPtr, descPtr + 28);
          heapU8().fill(0, metaPtr, metaPtr + 32);
          const ok = functions.prepareMonitorTx(descPtr, 28, metaPtr, 32, frameIn.ptr, frameIn.len, monitorVif >>> 0, monitorActive ? 1 : 0) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native monitor tx planner failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 32);
          return {
            status: readU32LE(meta, 0),
            payloadOffset: readU32LE(meta, 4),
            payloadLength: readU32LE(meta, 8),
            frameLength: readU32LE(meta, 12),
            vif: readU32LE(meta, 16),
            flags: readU32LE(meta, 20),
            desc: heapU8().slice(descPtr, descPtr + 28),
          };
        } finally {
          freeMaybe(frameIn);
          free(descPtr);
          free(metaPtr);
        }
      },
      prepareMgmtTx: function (frame, vifIndex, staIndex) {
        const input = frame instanceof Uint8Array ? frame : new Uint8Array(frame || []);
        const frameIn = allocMaybe(input);
        const descPtr = malloc(28);
        const metaPtr = malloc(32);
        if (!descPtr || !metaPtr) {
          if (descPtr) free(descPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(frameIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, descPtr, descPtr + 28);
          heapU8().fill(0, metaPtr, metaPtr + 32);
          const ok = functions.prepareMgmtTx(descPtr, 28, metaPtr, 32, frameIn.ptr, frameIn.len, vifIndex >>> 0, staIndex >>> 0) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native management tx planner failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 32);
          return {
            status: readU32LE(meta, 0),
            payloadOffset: readU32LE(meta, 4),
            payloadLength: readU32LE(meta, 8),
            frameLength: readU32LE(meta, 12),
            vif: readU32LE(meta, 16),
            flags: readU32LE(meta, 20),
            sta: readU32LE(meta, 24),
            desc: heapU8().slice(descPtr, descPtr + 28),
          };
        } finally {
          freeMaybe(frameIn);
          free(descPtr);
          free(metaPtr);
        }
      },
      formatTxEthLog: function (plan) {
        const tx = plan || {};
        return decodeAscii(callOut(96, (ptr, size) => functions.formatTxEthLog(ptr, size, tx.frameLength >>> 0, tx.vif >>> 0, tx.sta >>> 0)));
      },
      formatTxMonitorLog: function (frame, plan) {
        const input = frame || new Uint8Array(0);
        const tx = plan || {};
        return withOptionalInput(input, (framePtr, frameLen) => decodeAscii(callOut(128, (ptr, size) => functions.formatTxMonitorLog(ptr, size, framePtr, frameLen, tx.vif >>> 0))));
      },
      scanGuard: function (staReady, scanBusy) {
        return functions.scanGuard(staReady ? 1 : 0, scanBusy ? 1 : 0) >>> 0;
      },
      autoScanShouldRun: function (connected, staReady, scanBusy, actionBusy) {
        return Boolean(functions.autoScanShouldRun(connected ? 1 : 0, staReady ? 1 : 0, scanBusy ? 1 : 0, actionBusy ? 1 : 0) >>> 0);
      },
      pcapRetentionShouldEvict: function (frameCount, byteCount, maxFrames, maxBytes) {
        return Boolean(functions.pcapRetentionShouldEvict(frameCount >>> 0, byteCount >>> 0, maxFrames >>> 0, maxBytes >>> 0) >>> 0);
      },
      pcapDownloadName: function (filename, stamp) {
        const nameIn = allocMaybe(encodeText(filename || ""));
        const stampIn = allocMaybe(encodeText(stamp || ""));
        try {
          return decodeAscii(callOut(256, (ptr, size) => functions.pcapDownloadName(ptr, size, nameIn.ptr, nameIn.len, stampIn.ptr, stampIn.len)));
        } finally {
          freeMaybe(nameIn);
          freeMaybe(stampIn);
        }
      },
      connectPrepare: function (target, network) {
        const tgt = target || {};
        const net = network || {};
        const ssidIn = allocMaybe(encodeText(tgt.ssid || ""));
        const bssidIn = allocMaybe(encodeText(tgt.bssid || ""));
        const passIn = allocMaybe(encodeText(tgt.password || ""));
        const netSsidIn = allocMaybe(encodeText(net.ssid || ""));
        const metaPtr = malloc(12);
        const ssidPtr = malloc(64);
        if (!metaPtr || !ssidPtr) {
          if (metaPtr) free(metaPtr);
          if (ssidPtr) free(ssidPtr);
          freeMaybe(ssidIn);
          freeMaybe(bssidIn);
          freeMaybe(passIn);
          freeMaybe(netSsidIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 12);
          heapU8().fill(0, ssidPtr, ssidPtr + 64);
          const ok = functions.connectPrepare(metaPtr, 12, ssidPtr, 64, ssidIn.ptr, ssidIn.len, bssidIn.ptr, bssidIn.len, passIn.ptr, passIn.len, netSsidIn.ptr, netSsidIn.len) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native connect planner failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 12);
          const ssidLen = readU32LE(meta, 4);
          return {
            status: readU32LE(meta, 0),
            ssidText: ssidLen ? decodeAscii(heapU8().slice(ssidPtr, ssidPtr + ssidLen)) : "",
            useNetworkSsid: meta[8] !== 0,
            hasPassword: meta[9] !== 0,
          };
        } finally {
          freeMaybe(ssidIn);
          freeMaybe(bssidIn);
          freeMaybe(passIn);
          freeMaybe(netSsidIn);
          free(metaPtr);
          free(ssidPtr);
        }
      },
      formatConnectAccepted: function (target) {
        const tgt = target || {};
        const ssidIn = allocMaybe(encodeText(tgt.ssid || ""));
        const bssidIn = allocMaybe(encodeText(tgt.bssid || ""));
        try {
          return decodeAscii(callOut(256, (ptr, size) => functions.formatConnectAccepted(ptr, size, ssidIn.ptr, ssidIn.len, bssidIn.ptr, bssidIn.len)));
        } finally {
          freeMaybe(ssidIn);
          freeMaybe(bssidIn);
        }
      },
      patchRangePlan: function (addressText, lengthText, defaultLen, maxLen) {
        const addressIn = allocMaybe(encodeText(addressText || ""));
        const lengthIn = allocMaybe(encodeText(lengthText || ""));
        try {
          const meta = callFixedMeta(16, (ptr, size) => functions.patchRangePlan(ptr, size, addressIn.ptr, addressIn.len, lengthIn.ptr, lengthIn.len, defaultLen >>> 0, maxLen >>> 0));
          return {
            status: readU32LE(meta, 0),
            address: readU32LE(meta, 4),
            length: readU32LE(meta, 8),
            maxLength: readU32LE(meta, 12),
          };
        } finally {
          freeMaybe(addressIn);
          freeMaybe(lengthIn);
        }
      },
      patchCompiledPlan: function (address, bytesLen, entryOffset) {
        const meta = callFixedMeta(16, (ptr, size) => functions.patchCompiledPlan(ptr, size, address >>> 0, bytesLen >>> 0, entryOffset >>> 0));
        return {
          status: readU32LE(meta, 0),
          address: readU32LE(meta, 4),
          entry: readU32LE(meta, 8),
          entryOffset: readU32LE(meta, 12),
        };
      },
      fuzzerLaunchPlan: function (profile, capturedCount) {
        return withInput(encodeText(profile || ""), (profilePtr, profileLen) => {
          const meta = callFixedMeta(8, (ptr, size) => functions.fuzzerLaunchPlan(ptr, size, profilePtr, profileLen, capturedCount >>> 0));
          return { status: readU32LE(meta, 0), frameCount: readU32LE(meta, 4) };
        });
      },
      formatFuzzerInitLog: function (config) {
        const cfg = config || {};
        const modeIn = allocMaybe(encodeText(cfg.mode || ""));
        const profileIn = allocMaybe(encodeText(cfg.profile || ""));
        const targetIn = allocMaybe(cfg.target || null);
        const bssidIn = allocMaybe(cfg.bssid || null);
        try {
          return decodeAscii(callOut(256, (ptr, size) => functions.formatFuzzerInitLog(
            ptr,
            size,
            modeIn.ptr,
            modeIn.len,
            profileIn.ptr,
            profileIn.len,
            targetIn.ptr,
            targetIn.len,
            bssidIn.ptr,
            bssidIn.len,
            cfg.intervalMs >>> 0,
            cfg.count >>> 0
          )));
        } finally {
          freeMaybe(modeIn);
          freeMaybe(profileIn);
          freeMaybe(targetIn);
          freeMaybe(bssidIn);
        }
      },
      formatFuzzerLaunchLog: function (profile, frameCount, intervalMs, count) {
        return withInput(encodeText(profile || ""), (profilePtr, profileLen) => decodeAscii(callOut(160, (ptr, size) => functions.formatFuzzerLaunchLog(ptr, size, profilePtr, profileLen, frameCount >>> 0, intervalMs >>> 0, count >>> 0))));
      },
      formatFuzzerStopLog: function (reason, sent) {
        return withInput(encodeText(reason || ""), (reasonPtr, reasonLen) => decodeAscii(callOut(96, (ptr, size) => functions.formatFuzzerStopLog(ptr, size, reasonPtr, reasonLen, sent >>> 0))));
      },
      isHexDigit: function (value) {
        const code = typeof value === "number" ? value : String(value || "").charCodeAt(0);
        return Number.isFinite(code) && Boolean(functions.isHexDigit(code >>> 0));
      },
      bytesEqual: function (a, b) {
        if (!a || !b || a.length !== b.length) {
          return false;
        }
        return withInput(a, (aPtr, aLen) => withInput(b, (bPtr, bLen) => Boolean(functions.bytesEqual(aPtr, aLen, bPtr, bLen) >>> 0)));
      },
      isBroadcastMac: function (mac) {
        return Boolean(mac && withInput(mac, (ptr, len) => functions.isBroadcastMac(ptr, len) >>> 0));
      },
      isZeroMac: function (mac) {
        return Boolean(!mac || withInput(mac, (ptr, len) => functions.isZeroMac(ptr, len) >>> 0));
      },
      isUsableUnicastMac: function (mac) {
        return Boolean(mac && withInput(mac, (ptr, len) => functions.isUsableUnicastMac(ptr, len) >>> 0));
      },
      deriveInterfaceMac: function (base, slot) {
        return withInput(base, (basePtr, baseLen) => callOut(6, (ptr, size) => functions.deriveInterfaceMac(ptr, size, basePtr, baseLen, slot >>> 0)));
      },
      channelToFrequency: function (channel) {
        return functions.channelToFrequency(channel >>> 0) >>> 0;
      },
      frequencyToChannel: function (freq) {
        return functions.frequencyToChannel(freq >>> 0) >>> 0;
      },
      buildMeshStartRequest: function (vifIndex, options) {
        const opts = options || {};
        const freq = parseDecimal(opts.freq !== undefined ? opts.freq : opts.frequency, 2412);
        const dtim = parseDecimal(opts.dtim, 1);
        const beacon = parseDecimal(opts.beacon !== undefined ? opts.beacon : opts.bcn, 100);
        const useWpa2 = Boolean(opts.useWpa2 || opts.password || opts.pass || opts.psk || opts.key);
        const meshIdText = opts.id || opts.mesh_id || opts.meshid || "aic8800-mesh";
        const meshId = encodeText(meshIdText);
        return withInput(meshId, (meshPtr, meshLen) => callOut(76, (ptr, size) => functions.buildMeshStartRequest(
          ptr,
          size,
          vifIndex >>> 0,
          freq,
          dtim,
          beacon,
          boolOption(opts.user_mpm) ? 1 : 0,
          boolOption(opts.auth) ? 1 : 0,
          parseDecimal(opts.auth_id, 0),
          meshPtr,
          meshLen
        )));
      },
      buildMonitorConfigRequest: function (options) {
        const opts = options || {};
        const parsedFreq = parseDecimalMaybe(opts.freq !== undefined ? opts.freq : (opts.frequency !== undefined ? opts.frequency : "2412"));
        const width = parseDecimal(opts.width, 20);
        const center1 = parseDecimal(opts.center1 !== undefined ? opts.center1 : opts.center_freq1, parsedFreq.value);
        const center2 = parseDecimal(opts.center2 !== undefined ? opts.center2 : opts.center_freq2, 0);
        if (!parsedFreq.valid || (width !== 20 && width !== 40 && width !== 80 && width !== 160)) {
          throw new Error("invalid monitor channel definition");
        }
        const request = callOut(14, (ptr, size) => functions.buildMonitorConfigRequest(ptr, size, parsedFreq.value, 1, width, center1, center2, boolOption(opts.uf) ? 1 : 0, boolOption(opts.auto_reply) ? 1 : 0));
        if (!request) {
          throw new Error("unsupported monitor channel definition");
        }
        return request;
      },
      buildSetFilterRequest: function (rxFilter) {
        return callOut(4, (ptr, size) => functions.buildSetFilterRequest(ptr, size, rxFilter >>> 0));
      },
      decodeMonitorConfirm: function (params) {
        const input = params || new Uint8Array(0);
        const paramsIn = allocMaybe(input);
        const metaPtr = malloc(12);
        if (!metaPtr) {
          freeMaybe(paramsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 12);
          const ok = functions.decodeMonitorConfirm(metaPtr, 12, paramsIn.ptr, paramsIn.len) >>> 0;
          if (!ok) {
            throw new Error("short ME_CONFIG_MONITOR_CFM");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 12);
          return {
            chanIndex: meta[0],
            band: meta[1],
            width: meta[2],
            txPower: meta[3] > 127 ? meta[3] - 256 : meta[3],
            primary: readU16LE(meta, 4),
            center1: readU16LE(meta, 6),
            center2: readU16LE(meta, 8),
            flags: meta[10],
          };
        } finally {
          free(metaPtr);
          freeMaybe(paramsIn);
        }
      },
      buildApBeaconRequest: function (vifIndex, mac, options) {
        const opts = options || {};
        const ssidText = String(opts.ssid !== undefined ? opts.ssid : (opts.name !== undefined ? opts.name : "default_network"));
        const ssid = encodeText(ssidText);
        const freq = parseDecimal(opts.freq !== undefined ? opts.freq : opts.frequency, 2412);
        const dtim = parseDecimal(opts.dtim, 2);
        const beacon = parseDecimal(opts.beacon !== undefined ? opts.beacon : opts.bcn, 100);
        const useWpa2 = Boolean(opts.useWpa2 || opts.password || opts.pass || opts.psk || opts.key);
        const macIn = allocMaybe(mac || null);
        const ssidIn = allocMaybe(ssid);
        const outPtr = malloc(520);
        const metaPtr = malloc(16);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(ssidIn);
          freeMaybe(macIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + 520);
          heapU8().fill(0, metaPtr, metaPtr + 16);
          const written = functions.buildApBeaconRequest(outPtr, 520, metaPtr, 16, vifIndex >>> 0, macIn.ptr, macIn.len, ssidIn.ptr, ssidIn.len, freq >>> 0, dtim >>> 0, beacon >>> 0, useWpa2 ? 1 : 0) >>> 0;
          if (!written || written > 520) {
            throw new Error("invalid AP beacon settings");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 16);
          return {
            params: heapU8().slice(outPtr, outPtr + written),
            ssid: ssidText,
            freq: readU16LE(meta, 8),
            beaconLength: readU16LE(meta, 0),
            timOffset: readU16LE(meta, 2),
            timLength: meta[4],
            band: meta[5],
            beaconInterval: readU16LE(meta, 6),
            dtim: meta[10],
            useWpa2,
            security: useWpa2 ? "wpa2-psk" : "open",
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(ssidIn);
          freeMaybe(macIn);
        }
      },
      buildInjectBeaconFrame: function (mac, options) {
        const opts = options || {};
        const ssidText = String(opts.ssid !== undefined ? opts.ssid : (opts.name !== undefined ? opts.name : "test_network"));
        const ssid = encodeText(ssidText);
        const freq = parseDecimal(opts.freq !== undefined ? opts.freq : opts.frequency, 2412);
        const dtim = parseDecimal(opts.dtim, 2);
        const beacon = parseDecimal(opts.beacon !== undefined ? opts.beacon : opts.bcn, 100);
        const useWpa2 = Boolean(opts.useWpa2 || opts.password || opts.pass || opts.psk || opts.key);
        const macIn = allocMaybe(mac || null);
        const ssidIn = allocMaybe(ssid);
        const outPtr = malloc(512);
        const metaPtr = malloc(16);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(ssidIn);
          freeMaybe(macIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + 512);
          heapU8().fill(0, metaPtr, metaPtr + 16);
          const written = functions.buildInjectBeaconFrame(outPtr, 512, metaPtr, 16, macIn.ptr, macIn.len, ssidIn.ptr, ssidIn.len, freq >>> 0, dtim >>> 0, beacon >>> 0, useWpa2 ? 1 : 0) >>> 0;
          if (!written || written > 512) {
            throw new Error("invalid beacon injection settings");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 16);
          return {
            frame: heapU8().slice(outPtr, outPtr + written),
            ssid: ssidText,
            freq: readU16LE(meta, 8),
            beaconLength: readU16LE(meta, 0),
            timOffset: readU16LE(meta, 2),
            timLength: meta[4],
            band: meta[5],
            beaconInterval: readU16LE(meta, 6),
            dtim: meta[10],
            channel: meta[11],
            useWpa2,
            security: useWpa2 ? "wpa2-psk" : "open",
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(ssidIn);
          freeMaybe(macIn);
        }
      },
      buildApStartRequest: function (vifIndex, plan) {
        const ap = plan || {};
        const request = callOut(64, (ptr, size) => functions.buildApStartRequest(
          ptr,
          size,
          vifIndex >>> 0,
          ap.freq >>> 0,
          ap.beaconLength >>> 0,
          ap.timOffset >>> 0,
          ap.timLength >>> 0,
          ap.beaconInterval >>> 0,
          ap.useWpa2 ? 1 : 0
        ));
        if (!request) {
          throw new Error("APM_START_REQ build failed");
        }
        return request;
      },
      decodeApStartConfirm: function (params) {
        const input = params || new Uint8Array(0);
        const paramsIn = allocMaybe(input);
        const metaPtr = malloc(4);
        if (!metaPtr) {
          freeMaybe(paramsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 4);
          const ok = functions.decodeApStartConfirm(metaPtr, 4, paramsIn.ptr, paramsIn.len) >>> 0;
          if (!ok) {
            throw new Error("short APM_START_CFM");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 4);
          return { status: meta[0], vifIndex: meta[1], chIndex: meta[2], bcmcIndex: meta[3] };
        } finally {
          free(metaPtr);
          freeMaybe(paramsIn);
        }
      },
      buildApStopRequest: function (vifIndex) {
        return callOut(4, (ptr, size) => functions.buildApStopRequest(ptr, size, vifIndex >>> 0));
      },
      buildConnectRequest: function (vifIndex, target, network) {
        const tgt = target || {};
        const net = network || null;
        const ssidText = tgt.ssid || (net ? net.ssid : "") || "";
        const ssid = encodeText(ssidText);
        const bssid = encodeText(tgt.bssid || (net ? net.bssid : "") || "");
        const freqSource = tgt.freq !== undefined ? tgt.freq : (tgt.frequency !== undefined ? tgt.frequency : (net ? net.freq : ""));
        const parsedFreq = parseDecimalMaybe(freqSource);
        return withInput(ssid, (ssidPtr, ssidLen) => withInput(bssid, (bssidPtr, bssidLen) => callOut(320, (ptr, size) => functions.buildConnectRequest(
          ptr,
          size,
          vifIndex >>> 0,
          ssidPtr,
          ssidLen,
          bssidPtr,
          bssidLen,
          parsedFreq.value,
          parsedFreq.valid ? 1 : 0,
          tgt.password ? 1 : 0
        ))));
      },
      buildOwfuzzLe16: function (value) {
        return callOut(2, (ptr, size) => functions.buildOwfuzzLe16(ptr, size, value >>> 0));
      },
      buildOwfuzzFrameHeader: function (type, flags, duration, addr1, addr2, addr3, seq) {
        return withInput(addr1, (addr1Ptr, addr1Len) => withInput(addr2, (addr2Ptr, addr2Len) => withInput(addr3, (addr3Ptr, addr3Len) => callOut(24, (ptr, size) => functions.buildOwfuzzFrameHeader(
          ptr,
          size,
          type >>> 0,
          flags >>> 0,
          duration >>> 0,
          addr1Ptr,
          addr1Len,
          addr2Ptr,
          addr2Len,
          addr3Ptr,
          addr3Len,
          seq >>> 0
        )))));
      },
      buildDeauthFrame: function (bssid, target, reason = 7) {
        const bssidBytes = bssid instanceof Uint8Array ? bssid : new Uint8Array(bssid || []);
        const targetBytes = target instanceof Uint8Array ? target : new Uint8Array(target || []);
        return withInput(bssidBytes, (bssidPtr, bssidLen) => withInput(targetBytes, (targetPtr, targetLen) => callOut(26, (ptr, size) => functions.buildDeauthFrame(
          ptr,
          size,
          bssidPtr,
          bssidLen,
          targetPtr,
          targetLen,
          reason >>> 0
        ))));
      },
      buildApAuthResponse: function (apMac, staMac, seq) {
        const apBytes = apMac instanceof Uint8Array ? apMac : new Uint8Array(apMac || []);
        const staBytes = staMac instanceof Uint8Array ? staMac : new Uint8Array(staMac || []);
        return withInput(apBytes, (apPtr, apLen) => withInput(staBytes, (staPtr, staLen) => callOut(30, (ptr, size) => functions.buildApAuthResponse(
          ptr,
          size,
          apPtr,
          apLen,
          staPtr,
          staLen,
          seq >>> 0
        ), "aic8800_build_ap_auth_response")));
      },
      buildApAssocResponse: function (apMac, staMac, aid, seq, useWpa2, qos, status) {
        const apBytes = apMac instanceof Uint8Array ? apMac : new Uint8Array(apMac || []);
        const staBytes = staMac instanceof Uint8Array ? staMac : new Uint8Array(staMac || []);
        return withInput(apBytes, (apPtr, apLen) => withInput(staBytes, (staPtr, staLen) => callOut(128, (ptr, size) => functions.buildApAssocResponse(
          ptr,
          size,
          apPtr,
          apLen,
          staPtr,
          staLen,
          aid >>> 0,
          seq >>> 0,
          useWpa2 ? 1 : 0,
          qos ? 1 : 0,
          status >>> 0
        ), "aic8800_build_ap_assoc_response")));
      },
      buildOwfuzzGeneratedFrame: function (options) {
        const opts = options || {};
        const maxLen = Math.max(1, Math.min(8192, opts.maxLen >>> 0 || 2304));
        const ssidBytes = opts.ssid instanceof Uint8Array ? opts.ssid : encodeText(opts.ssid || "");
        const sourceIn = allocMaybe(opts.source);
        const targetIn = allocMaybe(opts.target);
        const bssidIn = allocMaybe(opts.bssid);
        const ssidIn = allocMaybe(ssidBytes);
        const outPtr = malloc(maxLen);
        const metaPtr = malloc(8);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(ssidIn);
          freeMaybe(bssidIn);
          freeMaybe(targetIn);
          freeMaybe(sourceIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + maxLen);
          heapU8().fill(0, metaPtr, metaPtr + 8);
          const written = functions.buildOwfuzzGeneratedFrame(
            outPtr,
            maxLen,
            metaPtr,
            8,
            opts.frameType >>> 0,
            opts.modeAp ? 1 : 0,
            opts.authWpa ? 1 : 0,
            opts.channel >>> 0,
            maxLen,
            opts.seq >>> 0,
            opts.timestampLow >>> 0,
            opts.timestampHigh >>> 0,
            opts.rngState >>> 0,
            opts.mutate ? 1 : 0,
            opts.mutationIeId >>> 0,
            opts.mutationStep >>> 0,
            opts.mutationValue >>> 0,
            opts.mutationExtId >>> 0,
            opts.mutationMin >>> 0,
            opts.mutationMax >>> 0,
            sourceIn.ptr,
            sourceIn.len,
            targetIn.ptr,
            targetIn.len,
            bssidIn.ptr,
            bssidIn.len,
            ssidIn.ptr,
            ssidIn.len
          ) >>> 0;
          if (!written || written > maxLen) {
            throw new Error("aic8800 native fuzz frame build failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 8);
          return {
            frame: heapU8().slice(outPtr, outPtr + written),
            rngState: readU32LE(meta, 0),
            mutationLength: readU16LE(meta, 4),
            nativeLength: readU16LE(meta, 6),
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(ssidIn);
          freeMaybe(bssidIn);
          freeMaybe(targetIn);
          freeMaybe(sourceIn);
        }
      },
      buildOwfuzzCapturedFrame: function (options) {
        const opts = options || {};
        const template = opts.frame || opts.template;
        if (!template || template.length === 0) {
          throw new Error("missing captured fuzz template");
        }
        const kind = template[0] & 0x0c;
        const maxLen = Math.max(1, Math.min(8192, opts.maxLen >>> 0 || 2304));
        const outSize = kind === 0x00 ? maxLen : Math.max(template.length, maxLen);
        const frameIn = allocMaybe(template);
        const sourceIn = allocMaybe(opts.source);
        const targetIn = allocMaybe(opts.target);
        const bssidIn = allocMaybe(opts.bssid);
        const outPtr = malloc(outSize);
        const metaPtr = malloc(8);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(bssidIn);
          freeMaybe(targetIn);
          freeMaybe(sourceIn);
          freeMaybe(frameIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + outSize);
          heapU8().fill(0, metaPtr, metaPtr + 8);
          const written = functions.buildOwfuzzCapturedFrame(
            outPtr,
            outSize,
            metaPtr,
            8,
            frameIn.ptr,
            frameIn.len,
            opts.modeAp ? 1 : 0,
            opts.rewriteCaptured ? 1 : 0,
            opts.mutate ? 1 : 0,
            maxLen,
            opts.seq >>> 0,
            opts.rngState >>> 0,
            opts.mutationIeId >>> 0,
            opts.mutationStep >>> 0,
            opts.mutationValue >>> 0,
            opts.mutationExtId >>> 0,
            opts.mutationMin >>> 0,
            opts.mutationMax >>> 0,
            sourceIn.ptr,
            sourceIn.len,
            targetIn.ptr,
            targetIn.len,
            bssidIn.ptr,
            bssidIn.len
          ) >>> 0;
          if (!written || written > outSize) {
            throw new Error("aic8800 native captured fuzz frame build failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 8);
          return {
            frame: heapU8().slice(outPtr, outPtr + written),
            rngState: readU32LE(meta, 0),
            mutationLength: readU16LE(meta, 4),
            nativeLength: readU16LE(meta, 6),
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(bssidIn);
          freeMaybe(targetIn);
          freeMaybe(sourceIn);
          freeMaybe(frameIn);
        }
      },

      owfuzzCanonicalFrameType: function (name) {
        const value = withInput(encodeText(name || ""), (ptr, len) => functions.owfuzzCanonicalFrameType(ptr, len) >>> 0);
        return value === 0xffffffff ? null : value;
      },
      owfuzzIsCapturedProfile: function (profile) {
        return withInput(encodeText(profile || ""), (ptr, len) => Boolean(functions.owfuzzIsCapturedProfile(ptr, len) >>> 0));
      },
      owfuzzProfileTypes: function (profile) {
        const out = callInputOutput(encodeText(profile || ""), 64, functions.owfuzzProfileTypes);
        return out || new Uint8Array(0);
      },
      owfuzzLooksHexPayload: function (text) {
        return withInput(encodeText(text || ""), (ptr, len) => Boolean(functions.owfuzzLooksHexPayload(ptr, len) >>> 0));
      },
      owfuzzParseBool: function (value, fallback) {
        return withInput(encodeText(value === undefined || value === null ? "" : value), (ptr, len) => Boolean(functions.owfuzzParseBool(ptr, len, fallback ? 1 : 0) >>> 0));
      },
      owfuzzParseNumber: function (value, min, max) {
        return withInput(encodeText(value === undefined || value === null ? "" : value), (inputPtr, inputLen) => {
          const metaPtr = malloc(4);
          if (!metaPtr) {
            throw new Error("aic8800 native core allocation failed");
          }
          try {
            heapU8().fill(0, metaPtr, metaPtr + 4);
            const ok = functions.owfuzzParseNumber(inputPtr, inputLen, metaPtr, 4, min >>> 0, max >>> 0) >>> 0;
            if (!ok) {
              return null;
            }
            return readU32LE(heapU8(), metaPtr);
          } finally {
            free(metaPtr);
          }
        });
      },
      owfuzzMutationPlan: function (options) {
        const opts = options || {};
        const metaPtr = malloc(16);
        if (!metaPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 16);
          const ok = functions.owfuzzMutationPlan(
            metaPtr,
            16,
            opts.frameType >>> 0,
            opts.mutate ? 1 : 0,
            opts.ieIndex >>> 0,
            opts.extIndex >>> 0,
            opts.stepIndex >>> 0,
            opts.valueIndex >>> 0,
            opts.captured ? 1 : 0
          ) >>> 0;
          if (!ok) {
            return null;
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 16);
          return {
            active: meta[0] !== 0,
            ieId: meta[1],
            stepIndex: meta[2],
            valueIndex: meta[3],
            extId: meta[4],
            min: meta[5],
            max: meta[6],
            targetCount: meta[7],
            nextIeIndex: readU16LE(meta, 8),
            nextExtIndex: readU16LE(meta, 10),
            nextStepIndex: readU16LE(meta, 12),
            nextValueIndex: readU16LE(meta, 14),
          };
        } finally {
          free(metaPtr);
        }
      },
      owfuzzMutationLabel: function (ieId, stepIndex, valueIndex, mutationLength) {
        return decodeAscii(callOut(96, (ptr, size) => functions.owfuzzMutationLabel(ptr, size, ieId >>> 0, stepIndex >>> 0, valueIndex >>> 0, mutationLength >>> 0)));
      },
      owfuzzNextSeq: function (current) {
        const metaPtr = malloc(4);
        if (!metaPtr) {
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 4);
          const ok = functions.owfuzzNextSeq(metaPtr, 4, current >>> 0) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native sequence update failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 4);
          return { seq: readU16LE(meta, 0), next: readU16LE(meta, 2) };
        } finally {
          free(metaPtr);
        }
      },
      owfuzzSelectNextFrame: function (profile, capturedCount, sent) {
        return withInput(encodeText(profile || ""), (profilePtr, profileLen) => {
          const meta = callFixedMeta(16, (ptr, size) => functions.owfuzzSelectNextFrame(ptr, size, profilePtr, profileLen, capturedCount >>> 0, sent >>> 0));
          return {
            action: readU32LE(meta, 0),
            frameType: readU32LE(meta, 4),
            capturedIndex: readU32LE(meta, 8),
            frameCount: readU32LE(meta, 12),
          };
        });
      },
      owfuzzFrameBuildPlan: function (options) {
        const opts = options || {};
        const templateIn = allocMaybe(opts.template || opts.frame || null);
        try {
          const meta = callFixedMeta(68, (ptr, size) => functions.owfuzzFrameBuildPlan(
            ptr,
            size,
            opts.action >>> 0,
            opts.frameType >>> 0,
            opts.seqCurrent >>> 0,
            opts.mutate ? 1 : 0,
            opts.ieIndex >>> 0,
            opts.extIndex >>> 0,
            opts.stepIndex >>> 0,
            opts.valueIndex >>> 0,
            templateIn.ptr,
            templateIn.len
          ));
          return {
            action: readU32LE(meta, 0),
            frameType: readU32LE(meta, 4),
            seq: readU32LE(meta, 8),
            nextSeq: readU32LE(meta, 12),
            mutate: readU32LE(meta, 16) !== 0,
            mutationIeId: readU32LE(meta, 20),
            mutationStep: readU32LE(meta, 24),
            mutationValue: readU32LE(meta, 28),
            mutationExtId: readU32LE(meta, 32),
            mutationMin: readU32LE(meta, 36),
            mutationMax: readU32LE(meta, 40),
            mutationTargetCount: readU32LE(meta, 44),
            nextIeIndex: readU32LE(meta, 48),
            nextExtIndex: readU32LE(meta, 52),
            nextStepIndex: readU32LE(meta, 56),
            nextValueIndex: readU32LE(meta, 60),
            mutationRequested: readU32LE(meta, 64) !== 0,
          };
        } finally {
          freeMaybe(templateIn);
        }
      },
      owfuzzTickDecision: function (state) {
        if (!state) {
          return { action: 0, delayMs: 0 };
        }
        const config = state.config || {};
        const meta = callFixedMeta(8, (ptr, size) => functions.owfuzzTickDecision(
          ptr,
          size,
          state.running ? 1 : 0,
          config.count >>> 0,
          state.sent >>> 0,
          state.txBusy ? 1 : 0,
          config.intervalMs >>> 0
        ));
        return { action: readU32LE(meta, 0), delayMs: readU32LE(meta, 4) };
      },
      owfuzzShouldLogTx: function (sentAfter, logEvery) {
        return Boolean(functions.owfuzzShouldLogTx(sentAfter >>> 0, logEvery >>> 0) >>> 0);
      },
      owfuzzCaptureLogNeeded: function (capturedAfter) {
        return Boolean(functions.owfuzzCaptureLogNeeded(capturedAfter >>> 0) >>> 0);
      },
      owfuzzTemplateKey: function (frame) {
        if (!frame || frame.length < 10) {
          return null;
        }
        return withInput(frame, (framePtr, frameLen) => decodeAscii(callOut(32, (ptr, size) => functions.owfuzzTemplateKey(ptr, size, framePtr, frameLen))));
      },
      owfuzzTemplateMeta: function (frame, captureEnabled, capturedCount, captureMax) {
        const input = frame || new Uint8Array(0);
        return withOptionalInput(input, (framePtr, frameLen) => {
          const meta = callFixedMeta(16, (ptr, size) => functions.owfuzzTemplateMeta(
            ptr,
            size,
            framePtr,
            frameLen,
            captureEnabled ? 1 : 0,
            capturedCount >>> 0,
            captureMax >>> 0
          ));
          return {
            active: meta[0] !== 0,
            type: meta[1],
            shouldLog: meta[2] !== 0,
            frameLen: readU32LE(meta, 4),
            capturedAfter: readU32LE(meta, 8),
          };
        });
      },
      owfuzzStatus: function (state) {
        if (!state) {
          return "fuzz: not initialized";
        }
        const config = state.config || {};
        const profileIn = allocMaybe(encodeText(state.profile || "management"));
        const targetIn = allocMaybe(config.target || null);
        const bssidIn = allocMaybe(config.bssid || null);
        try {
          return decodeAscii(callOut(256, (ptr, size) => functions.owfuzzStatus(
            ptr,
            size,
            state.running ? 1 : 0,
            profileIn.ptr,
            profileIn.len,
            state.sent >>> 0,
            state.capturedFrames ? state.capturedFrames.length >>> 0 : 0,
            targetIn.ptr,
            targetIn.len,
            bssidIn.ptr,
            bssidIn.len,
            config.intervalMs >>> 0
          )));
        } finally {
          freeMaybe(bssidIn);
          freeMaybe(targetIn);
          freeMaybe(profileIn);
        }
      },


      buildOwfuzzConfig: function (options, previousConfig, localMac, nowSeed) {
        const optsBytes = encodeKvObject(options || {});
        const previous = packOwfuzzPreviousConfig(previousConfig || null);
        const local = localMac instanceof Uint8Array ? localMac : new Uint8Array(localMac || []);
        const optsIn = allocMaybe(optsBytes);
        const prevMetaIn = allocMaybe(previous.meta);
        const prevStringsIn = allocMaybe(previous.strings);
        const localIn = allocMaybe(local);
        const metaPtr = malloc(64);
        const stringsPtr = malloc(512);
        if (!metaPtr || !stringsPtr) {
          if (metaPtr) free(metaPtr);
          if (stringsPtr) free(stringsPtr);
          freeMaybe(localIn);
          freeMaybe(prevStringsIn);
          freeMaybe(prevMetaIn);
          freeMaybe(optsIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 64);
          heapU8().fill(0, stringsPtr, stringsPtr + 512);
          const written = functions.owfuzzBuildConfig(
            metaPtr,
            64,
            stringsPtr,
            512,
            optsIn.ptr,
            optsIn.len,
            prevMetaIn.ptr,
            prevMetaIn.len,
            prevStringsIn.ptr,
            prevStringsIn.len,
            localIn.ptr,
            localIn.len,
            nowSeed >>> 0
          ) >>> 0;
          if (!written || written > 512) {
            throw new Error("invalid fuzz config");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 64);
          const strings = decodeNullStrings(heapU8().slice(stringsPtr, stringsPtr + written));
          const flags = readU32LE(meta, 52);
          const freq = readU32LE(meta, 24);
          return {
            source: meta.slice(0, 6),
            target: meta.slice(6, 12),
            bssid: meta.slice(12, 18),
            mode: strings[0] || "sta",
            profile: strings[1] || "management",
            ssid: strings[2] || "owfuzz",
            auth: strings[3] || "open",
            channel: readU32LE(meta, 20),
            freq,
            frequency: freq,
            count: readU32LE(meta, 28),
            intervalMs: readU32LE(meta, 32),
            logEvery: readU32LE(meta, 36),
            seed: readU32LE(meta, 40),
            captureMax: readU32LE(meta, 44),
            maxLen: readU32LE(meta, 48),
            capture: (flags & 1) !== 0,
            monitor: (flags & 2) !== 0,
            mutate: (flags & 4) !== 0,
            rewriteCaptured: (flags & 8) !== 0,
            uf: options ? options.uf : undefined,
            auto_reply: options ? options.auto_reply : undefined,
          };
        } finally {
          free(stringsPtr);
          free(metaPtr);
          freeMaybe(localIn);
          freeMaybe(prevStringsIn);
          freeMaybe(prevMetaIn);
          freeMaybe(optsIn);
        }
      },
      sha1: function (data) {
        return withInput(data, (dataPtr, dataLen) => callOut(20, (ptr, size) => functions.sha1(ptr, size, dataPtr, dataLen)));
      },
      hmacSha1: function (key, data) {
        return withInput(key, (keyPtr, keyLen) => withInput(data, (dataPtr, dataLen) => callOut(20, (ptr, size) => functions.hmacSha1(ptr, size, keyPtr, keyLen, dataPtr, dataLen))));
      },
      deriveWpaPmk: function (passphrase, ssidBytes) {
        const passBytes = encodeText(passphrase);
        return withInput(passBytes, (passPtr, passLen) => withInput(ssidBytes, (ssidPtr, ssidLen) => callOut(32, (ptr, size) => functions.deriveWpaPmk(ptr, size, passPtr, passLen, ssidPtr, ssidLen))));
      },
      wpaPrf512: function (pmk, amac, smac, anonce, snonce) {
        const pmkIn = allocMaybe(pmk);
        const amacIn = allocMaybe(amac);
        const smacIn = allocMaybe(smac);
        const anonceIn = allocMaybe(anonce);
        const snonceIn = allocMaybe(snonce);
        try {
          return callOut(64, (ptr, size) => functions.wpaPrf512(
            ptr,
            size,
            pmkIn.ptr,
            pmkIn.len,
            amacIn.ptr,
            amacIn.len,
            smacIn.ptr,
            smacIn.len,
            anonceIn.ptr,
            anonceIn.len,
            snonceIn.ptr,
            snonceIn.len
          ));
        } finally {
          freeMaybe(snonceIn);
          freeMaybe(anonceIn);
          freeMaybe(smacIn);
          freeMaybe(amacIn);
          freeMaybe(pmkIn);
        }
      },
      buildWpaKeyEapol: function (options) {
        const opts = options || {};
        const replayIn = allocMaybe(replayCounterBytes(opts.replayCounter));
        const nonceIn = allocMaybe(opts.nonce || null);
        const keyDataIn = allocMaybe(opts.keyData || null);
        const kckIn = allocMaybe(opts.kck || null);
        const total = 99 + keyDataIn.len;
        try {
          return callOut(total, (ptr, size) => functions.buildWpaKeyEapol(
            ptr,
            size,
            opts.keyInfo >>> 0,
            replayIn.ptr,
            replayIn.len,
            nonceIn.ptr,
            nonceIn.len,
            keyDataIn.ptr,
            keyDataIn.len,
            kckIn.ptr,
            kckIn.len
          ));
        } finally {
          freeMaybe(kckIn);
          freeMaybe(keyDataIn);
          freeMaybe(nonceIn);
          freeMaybe(replayIn);
        }
      },

      buildWpaApMessage1: function (options) {
        const opts = options || {};
        const replayIn = allocMaybe(replayCounterBytes(opts.replayCounter));
        const anonceIn = allocMaybe(opts.anonce || null);
        try {
          return callOut(99, (ptr, size) => functions.buildWpaApMessage1(ptr, size, replayIn.ptr, replayIn.len, anonceIn.ptr, anonceIn.len));
        } finally {
          freeMaybe(anonceIn);
          freeMaybe(replayIn);
        }
      },

      buildWpaMessage2: function (options) {
        const opts = options || {};
        const replayIn = allocMaybe(replayCounterBytes(opts.replayCounter));
        const snonceIn = allocMaybe(opts.snonce || opts.nonce || null);
        const kckIn = allocMaybe(opts.kck || null);
        try {
          return callOut(121, (ptr, size) => functions.buildWpaMessage2(ptr, size, replayIn.ptr, replayIn.len, snonceIn.ptr, snonceIn.len, kckIn.ptr, kckIn.len));
        } finally {
          freeMaybe(kckIn);
          freeMaybe(snonceIn);
          freeMaybe(replayIn);
        }
      },
      buildWpaMessage4: function (options) {
        const opts = options || {};
        const replayIn = allocMaybe(replayCounterBytes(opts.replayCounter));
        const kckIn = allocMaybe(opts.kck || null);
        try {
          return callOut(99, (ptr, size) => functions.buildWpaMessage4(ptr, size, replayIn.ptr, replayIn.len, kckIn.ptr, kckIn.len));
        } finally {
          freeMaybe(kckIn);
          freeMaybe(replayIn);
        }
      },

      validateWpa2Context: function (ssidText, passphrase) {
        const ssid = encodeText(ssidText || "");
        const pass = encodeText(passphrase || "");
        return withInput(ssid, (ssidPtr, ssidLen) => withInput(pass, (passPtr, passLen) => functions.validateWpa2Context(ssidPtr, ssidLen, passPtr, passLen) >>> 0));
      },
      wpaPrepareContext: function (target, network) {
        const tgt = target || {};
        const ssidText = tgt.ssid || (network ? network.ssid : "") || "";
        const passphrase = String(tgt.password || "");
        const ssid = encodeText(ssidText);
        const pass = encodeText(passphrase);
        const bssid = encodeText(tgt.bssid || (network ? network.bssid : "") || "");
        const ssidIn = allocMaybe(ssid);
        const passIn = allocMaybe(pass);
        const bssidIn = allocMaybe(bssid);
        const metaPtr = malloc(16);
        if (!metaPtr) {
          freeMaybe(bssidIn);
          freeMaybe(passIn);
          freeMaybe(ssidIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 16);
          const ok = functions.wpaPrepareContext(metaPtr, 16, ssidIn.ptr, ssidIn.len, passIn.ptr, passIn.len, bssidIn.ptr, bssidIn.len) >>> 0;
          if (!ok) {
            throw new Error("aic8800 native WPA context preparation failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 16);
          return {
            validation: readU32LE(meta, 0),
            ssidText,
            ssidBytes: ssid,
            passphrase,
            bssid: meta[14] ? meta.slice(8, 14) : null,
          };
        } finally {
          free(metaPtr);
          freeMaybe(bssidIn);
          freeMaybe(passIn);
          freeMaybe(ssidIn);
        }
      },
      wpaBuildMessage1Material: function (options) {
        const opts = options || {};
        const ssidIn = allocMaybe(opts.ssidBytes || null);
        const passIn = allocMaybe(encodeText(opts.passphrase || ""));
        const apIn = allocMaybe(opts.apMac || null);
        const localIn = allocMaybe(opts.localMac || null);
        const eapolIn = allocMaybe(opts.eapol || null);
        const snonceIn = allocMaybe(opts.snonce || null);
        const outPtr = malloc(281);
        const metaPtr = malloc(32);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(snonceIn);
          freeMaybe(eapolIn);
          freeMaybe(localIn);
          freeMaybe(apIn);
          freeMaybe(passIn);
          freeMaybe(ssidIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + 281);
          heapU8().fill(0, metaPtr, metaPtr + 32);
          const written = functions.wpaBuildMessage1Material(
            outPtr,
            281,
            metaPtr,
            32,
            ssidIn.ptr,
            ssidIn.len,
            passIn.ptr,
            passIn.len,
            apIn.ptr,
            apIn.len,
            localIn.ptr,
            localIn.len,
            eapolIn.ptr,
            eapolIn.len,
            snonceIn.ptr,
            snonceIn.len
          ) >>> 0;
          if (!written) {
            throw new Error("aic8800 native WPA message 1 handling failed");
          }
          const out = heapU8().slice(outPtr, outPtr + written);
          const meta = heapU8().slice(metaPtr, metaPtr + 32);
          const msg2Off = readU32LE(meta, 16);
          const msg2Len = readU32LE(meta, 20);
          return {
            anonce: out.slice(readU32LE(meta, 0), readU32LE(meta, 0) + 32),
            snonce: out.slice(readU32LE(meta, 4), readU32LE(meta, 4) + 32),
            pmk: out.slice(readU32LE(meta, 8), readU32LE(meta, 8) + 32),
            ptk: out.slice(readU32LE(meta, 12), readU32LE(meta, 12) + 64),
            message2: out.slice(msg2Off, msg2Off + msg2Len),
            replayCounter: readReplayCounter(meta, 24),
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(snonceIn);
          freeMaybe(eapolIn);
          freeMaybe(localIn);
          freeMaybe(apIn);
          freeMaybe(passIn);
          freeMaybe(ssidIn);
        }
      },
      wpaBuildMessage3Material: function (eapol, ptk) {
        const eapolIn = allocMaybe(eapol || null);
        const ptkIn = allocMaybe(ptk || null);
        const outPtr = malloc(256);
        const metaPtr = malloc(24);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(ptkIn);
          freeMaybe(eapolIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + 256);
          heapU8().fill(0, metaPtr, metaPtr + 24);
          const written = functions.wpaBuildMessage3Material(outPtr, 256, metaPtr, 24, eapolIn.ptr, eapolIn.len, ptkIn.ptr, ptkIn.len) >>> 0;
          if (!written) {
            throw new Error("aic8800 native WPA message 3 handling failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 24);
          const status = readU32LE(meta, 0);
          const gtkOff = readU32LE(meta, 8);
          const gtkLen = readU32LE(meta, 12);
          const msg4Off = readU32LE(meta, 16);
          const msg4Len = readU32LE(meta, 20);
          const out = heapU8().slice(outPtr, outPtr + written);
          return {
            status,
            hasGtk: meta[4] !== 0,
            gtkKeyIndex: meta[5],
            gtk: gtkLen ? out.slice(gtkOff, gtkOff + gtkLen) : new Uint8Array(0),
            message4: msg4Len ? out.slice(msg4Off, msg4Off + msg4Len) : new Uint8Array(0),
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(ptkIn);
          freeMaybe(eapolIn);
        }
      },
      wpaApBuildMessage3Material: function (options) {
        const opts = options || {};
        const ssidIn = allocMaybe(opts.ssidBytes || null);
        const passIn = allocMaybe(encodeText(opts.passphrase || opts.password || ""));
        const apIn = allocMaybe(opts.apMac || null);
        const staIn = allocMaybe(opts.staMac || null);
        const eapolIn = allocMaybe(opts.eapol || null);
        const anonceIn = allocMaybe(opts.anonce || null);
        const gtkIn = allocMaybe(opts.gtk || null);
        const replayIn = allocMaybe(replayCounterBytes(opts.replayCounter));
        const outPtr = malloc(512);
        const metaPtr = malloc(32);
        if (!outPtr || !metaPtr) {
          if (outPtr) free(outPtr);
          if (metaPtr) free(metaPtr);
          freeMaybe(replayIn);
          freeMaybe(gtkIn);
          freeMaybe(anonceIn);
          freeMaybe(eapolIn);
          freeMaybe(staIn);
          freeMaybe(apIn);
          freeMaybe(passIn);
          freeMaybe(ssidIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + 512);
          heapU8().fill(0, metaPtr, metaPtr + 32);
          const written = functions.wpaApBuildMessage3Material(
            outPtr,
            512,
            metaPtr,
            32,
            ssidIn.ptr,
            ssidIn.len,
            passIn.ptr,
            passIn.len,
            apIn.ptr,
            apIn.len,
            staIn.ptr,
            staIn.len,
            eapolIn.ptr,
            eapolIn.len,
            anonceIn.ptr,
            anonceIn.len,
            gtkIn.ptr,
            gtkIn.len,
            opts.gtkKeyIndex >>> 0,
            replayIn.ptr,
            replayIn.len
          ) >>> 0;
          if (!written) {
            throw new Error("aic8800 native WPA AP message 3 handling failed");
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 32);
          const out = heapU8().slice(outPtr, outPtr + written);
          const status = readU32LE(meta, 0);
          const ptkOff = readU32LE(meta, 4);
          const ptkLen = readU32LE(meta, 8);
          const msg3Off = readU32LE(meta, 12);
          const msg3Len = readU32LE(meta, 16);
          return {
            status,
            ptk: status === 0 && ptkLen ? out.slice(ptkOff, ptkOff + ptkLen) : new Uint8Array(0),
            message3: status === 0 && msg3Len ? out.slice(msg3Off, msg3Off + msg3Len) : new Uint8Array(0),
            wrappedKeyDataLength: readU32LE(meta, 20),
            gtkKeyIndex: meta[24],
          };
        } finally {
          free(metaPtr);
          free(outPtr);
          freeMaybe(replayIn);
          freeMaybe(gtkIn);
          freeMaybe(anonceIn);
          freeMaybe(eapolIn);
          freeMaybe(staIn);
          freeMaybe(apIn);
          freeMaybe(passIn);
          freeMaybe(ssidIn);
        }
      },
      wpaApVerifyMessage4: function (eapol, ptk, replayCounter) {
        const eapolIn = allocMaybe(eapol || null);
        const ptkIn = allocMaybe(ptk || null);
        const replayIn = allocMaybe(replayCounterBytes(replayCounter));
        try {
          return functions.wpaApVerifyMessage4(eapolIn.ptr, eapolIn.len, ptkIn.ptr, ptkIn.len, replayIn.ptr, replayIn.len) >>> 0;
        } finally {
          freeMaybe(replayIn);
          freeMaybe(ptkIn);
          freeMaybe(eapolIn);
        }
      },
      wpaEapolAction: function (decoded, localMac, stateFlags) {
        const flags = stateFlags || {};
        const daIn = allocMaybe(decoded ? decoded.da : null);
        const localIn = allocMaybe(localMac || null);
        const eapolIn = allocMaybe(decoded ? decoded.payload : null);
        const metaPtr = malloc(36);
        if (!metaPtr) {
          freeMaybe(eapolIn);
          freeMaybe(localIn);
          freeMaybe(daIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 36);
          const ok = functions.wpaEapolAction(
            metaPtr,
            36,
            daIn.ptr,
            daIn.len,
            localIn.ptr,
            localIn.len,
            eapolIn.ptr,
            eapolIn.len,
            flags.associated ? 1 : 0,
            flags.completed ? 1 : 0,
            flags.busy ? 1 : 0
          ) >>> 0;
          if (!ok) {
            return null;
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 36);
          const action = meta[0];
          if (!action) {
            return null;
          }
          const keyMeta = meta.subarray(4, 36);
          return {
            action,
            key: {
              eapolLength: readU32LE(keyMeta, 0),
              keyInfo: readU16LE(keyMeta, 4),
              keyDataLength: readU16LE(keyMeta, 6),
              keyDataOffset: readU32LE(keyMeta, 8),
              keyDataEnd: readU32LE(keyMeta, 12),
              replayCounter: readReplayCounter(keyMeta, 16),
              descVersion: keyMeta[24],
              isPairwise: keyMeta[25] !== 0,
              hasAck: keyMeta[26] !== 0,
              hasMic: keyMeta[27] !== 0,
              encrypted: keyMeta[28] !== 0,
              secure: keyMeta[29] !== 0,
            },
          };
        } finally {
          free(metaPtr);
          freeMaybe(eapolIn);
          freeMaybe(localIn);
          freeMaybe(daIn);
        }
      },
      buildEapolEthFrame: function (bssid, localMac, eapol) {
        const bssidIn = allocMaybe(bssid);
        const localIn = allocMaybe(localMac);
        const eapolIn = allocMaybe(eapol);
        try {
          return callOut(14 + eapolIn.len, (ptr, size) => functions.buildEapolEthFrame(ptr, size, bssidIn.ptr, bssidIn.len, localIn.ptr, localIn.len, eapolIn.ptr, eapolIn.len), "aic8800_build_eapol_eth_frame");
        } finally {
          freeMaybe(eapolIn);
          freeMaybe(localIn);
          freeMaybe(bssidIn);
        }
      },

      findNetworkForConnect: function (target, networks) {
        const list = Array.isArray(networks) ? networks : Array.from(networks || []);
        const records = [];
        for (const network of list) {
          for (const byte of encodeText(network && network.bssid ? network.bssid : "")) records.push(byte);
          records.push(0);
          for (const byte of encodeText(network && network.ssid ? network.ssid : "")) records.push(byte);
          records.push(0);
        }
        const ssidIn = allocMaybe(encodeText(target && target.ssid ? target.ssid : ""));
        const bssidIn = allocMaybe(encodeText(target && target.bssid ? target.bssid : ""));
        const recordsIn = allocMaybe(new Uint8Array(records));
        const metaPtr = malloc(4);
        if (!metaPtr) {
          freeMaybe(recordsIn);
          freeMaybe(bssidIn);
          freeMaybe(ssidIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 4);
          const ok = functions.findNetworkForConnect(metaPtr, 4, ssidIn.ptr, ssidIn.len, bssidIn.ptr, bssidIn.len, recordsIn.ptr, recordsIn.len) >>> 0;
          if (!ok) {
            return -1;
          }
          const index = readU32LE(heapU8(), metaPtr);
          return index === 0xffffffff ? -1 : index;
        } finally {
          free(metaPtr);
          freeMaybe(recordsIn);
          freeMaybe(bssidIn);
          freeMaybe(ssidIn);
        }
      },
      aesKeyUnwrap: function (kek, wrapped) {
        if (!wrapped || wrapped.length < 16 || wrapped.length % 8 !== 0) {
          throw new Error("invalid AES key wrap length");
        }
        const kekIn = allocMaybe(kek);
        const wrappedIn = allocMaybe(wrapped);
        const outSize = wrapped.length - 8;
        const outPtr = malloc(outSize || 1);
        if (!outPtr) {
          freeMaybe(wrappedIn);
          freeMaybe(kekIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          const written = functions.aesKeyUnwrap(outPtr, outSize, kekIn.ptr, kekIn.len, wrappedIn.ptr, wrappedIn.len) >>> 0;
          if (!written || written > outSize) {
            throw new Error("invalid AES key unwrap integrity value");
          }
          return heapU8().slice(outPtr, outPtr + written);
        } finally {
          free(outPtr);
          freeMaybe(wrappedIn);
          freeMaybe(kekIn);
        }
      },
      findGtkKde: function (buf) {
        return callMeta(buf, 8, functions.findGtkKde, (meta) => {
          const keyOffset = readU32LE(meta, 1);
          const keyLen = readU16LE(meta, 5);
          return {
            keyIndex: meta[0] & 0x03,
            key: buf.slice(keyOffset, keyOffset + keyLen),
          };
        });
      },
      decodeWpaKeyEapol: function (eapol) {
        return callMeta(eapol, 32, functions.decodeWpaKeyEapol, (meta) => ({
          eapolLength: readU32LE(meta, 0),
          keyInfo: readU16LE(meta, 4),
          keyDataLength: readU16LE(meta, 6),
          keyDataOffset: readU32LE(meta, 8),
          keyDataEnd: readU32LE(meta, 12),
          replayCounter: readReplayCounter(meta, 16),
          descVersion: meta[24],
          isPairwise: meta[25] !== 0,
          hasAck: meta[26] !== 0,
          hasMic: meta[27] !== 0,
          encrypted: meta[28] !== 0,
          secure: meta[29] !== 0,
        }));
      },
      verifyWpaKeyMic: function (eapol, kck) {
        return withInput(eapol, (eapolPtr, eapolLen) => withInput(kck, (kckPtr, kckLen) => functions.verifyWpaKeyMic(eapolPtr, eapolLen, kckPtr, kckLen) !== 0));
      },
      frameTypeToString: function (frame) {
        return withInput(frame || new Uint8Array(0), (framePtr, frameLen) => decodeAscii(callOut(32, (ptr, size) => functions.frameTypeToString(ptr, size, framePtr, frameLen))));
      },
      formatHexU32: function (value, width) {
        const size = Math.max(1, Math.min(8, width >>> 0));
        return decodeAscii(callOut(size, (ptr, outSize) => functions.formatHexU32(ptr, outSize, value >>> 0, size)));
      },
      formatMac: function (mac) {
        return withInput(mac, (macPtr, macLen) => decodeAscii(callOut(17, (ptr, size) => functions.formatMac(ptr, size, macPtr, macLen))));
      },
      formatHexPreview: function (bytes) {
        if (!bytes || bytes.length === 0) {
          return "";
        }
        const outSize = bytes.length * 3 - 1;
        return withInput(bytes, (bytesPtr, bytesLen) => decodeAscii(callOut(outSize, (ptr, size) => functions.formatHexPreview(ptr, size, bytesPtr, bytesLen))));
      },
      formatHexdump: function (bytes) {
        const input = bytes || new Uint8Array(0);
        const rows = input.length ? Math.ceil(input.length / 16) : 0;
        const outSize = input.length ? rows * 74 - 1 : 13;
        return withInput(input, (bytesPtr, bytesLen) => decodeAscii(callOut(outSize, (ptr, size) => functions.formatHexdump(ptr, size, bytesPtr, bytesLen))).split("\n"));
      },
      formatAsciiPreview: function (bytes, width) {
        const input = bytes || new Uint8Array(0);
        const outSize = Math.max(0, width >>> 0);
        return withOptionalInput(input, (bytesPtr, bytesLen) => decodeAscii(callOut(outSize, (ptr, size) => functions.formatAsciiPreview(ptr, size, bytesPtr, bytesLen, outSize))));
      },
      formatMemoryPreview: function (bytes, address, entryOffset, includeEntry) {
        const input = bytes || new Uint8Array(0);
        const rows = input.length ? Math.ceil(input.length / 16) : 0;
        const outSize = 96 + (includeEntry ? 24 : 0) + rows * 80;
        return withOptionalInput(input, (bytesPtr, bytesLen) => decodeAscii(callOut(outSize, (ptr, size) => functions.formatMemoryPreview(
          ptr,
          size,
          bytesPtr,
          bytesLen,
          address >>> 0,
          entryOffset >>> 0,
          includeEntry ? 1 : 0
        ))));
      },
      decodeStaDataFrame: function (block) {
        return callMeta(block, 28, functions.decodeStaDataFrame, (meta) => {
          const payloadOffset = readU32LE(meta, 16);
          const payloadLen = readU32LE(meta, 20);
          return {
            da: meta.slice(0, 6),
            sa: meta.slice(6, 12),
            etherType: readU16LE(meta, 12),
            payload: block.subarray(payloadOffset, payloadOffset + payloadLen),
          };
        });
      },
      decodeDhcpRequest: function (payload) {
        const input = payload instanceof Uint8Array ? payload : new Uint8Array(payload || []);
        if (!input.length) {
          return null;
        }
        return withInput(input, (inputPtr, inputLen) => {
          const meta = callFixedMeta(16, (metaPtr, metaLen) => functions.decodeDhcpRequest(metaPtr, metaLen, inputPtr, inputLen));
          const status = readU32LE(meta, 0);
          if (!status) {
            return null;
          }
          const dhcpOffset = readU32LE(meta, 8);
          const dhcpLength = readU32LE(meta, 12);
          if (dhcpOffset > input.length || dhcpLength > input.length - dhcpOffset) {
            return null;
          }
          return {
            messageType: readU32LE(meta, 4),
            dhcpOffset,
            dhcpLength,
            dhcp: input.subarray(dhcpOffset, dhcpOffset + dhcpLength),
          };
        });
      },
      buildDhcpReplyFrame: function (apMac, requestDhcp, messageType) {
        const apBytes = apMac instanceof Uint8Array ? apMac : new Uint8Array(apMac || []);
        const reqBytes = requestDhcp instanceof Uint8Array ? requestDhcp : new Uint8Array(requestDhcp || []);
        const apIn = allocMaybe(apBytes);
        const reqIn = allocMaybe(reqBytes);
        try {
          return callOut(620, (ptr, size) => functions.buildDhcpReplyFrame(
            ptr,
            size,
            apIn.ptr,
            apIn.len,
            reqIn.ptr,
            reqIn.len,
            messageType >>> 0
          ), "aic8800 DHCP reply build");
        } finally {
          freeMaybe(reqIn);
          freeMaybe(apIn);
        }
      },
      decodeArpRequest: function (payload) {
        const input = payload instanceof Uint8Array ? payload : new Uint8Array(payload || []);
        if (!input.length) {
          return null;
        }
        return withInput(input, (inputPtr, inputLen) => {
          const meta = callFixedMeta(8, (metaPtr, metaLen) => functions.decodeArpRequest(metaPtr, metaLen, inputPtr, inputLen));
          if (!readU32LE(meta, 0)) {
            return null;
          }
          return { senderIp: readU32LE(meta, 4) };
        });
      },
      buildArpReplyFrame: function (apMac, requestArp) {
        const apBytes = apMac instanceof Uint8Array ? apMac : new Uint8Array(apMac || []);
        const reqBytes = requestArp instanceof Uint8Array ? requestArp : new Uint8Array(requestArp || []);
        const apIn = allocMaybe(apBytes);
        const reqIn = allocMaybe(reqBytes);
        try {
          return callOut(42, (ptr, size) => functions.buildArpReplyFrame(ptr, size, apIn.ptr, apIn.len, reqIn.ptr, reqIn.len), "aic8800 ARP reply build");
        } finally {
          freeMaybe(reqIn);
          freeMaybe(apIn);
        }
      },
      decodePortalIpv4: function (payload) {
        const input = payload instanceof Uint8Array ? payload : new Uint8Array(payload || []);
        if (!input.length) {
          return null;
        }
        return withInput(input, (inputPtr, inputLen) => {
          const meta = callFixedMeta(40, (metaPtr, metaLen) => functions.decodePortalIpv4(metaPtr, metaLen, inputPtr, inputLen));
          if (!readU32LE(meta, 0)) {
            return null;
          }
          const payloadOffset = readU32LE(meta, 28);
          const payloadLength = readU32LE(meta, 32);
          if (payloadOffset > input.length || payloadLength > input.length - payloadOffset) {
            return null;
          }
          return {
            protocol: readU32LE(meta, 4),
            sourcePort: readU32LE(meta, 8),
            destinationPort: readU32LE(meta, 12),
            sequence: readU32LE(meta, 16),
            acknowledgement: readU32LE(meta, 20),
            flags: readU32LE(meta, 24),
            payloadOffset,
            payloadLength,
            sourceIp: readU32LE(meta, 36),
            payload: input.subarray(payloadOffset, payloadOffset + payloadLength),
            ip: input,
          };
        });
      },
      buildPortalDnsReplyFrame: function (apMac, clientMac, requestIp) {
        const apIn = allocMaybe(apMac || null);
        const clientIn = allocMaybe(clientMac || null);
        const requestIn = allocMaybe(requestIp || null);
        try {
          return callOut(1600, (ptr, size) => functions.buildPortalDnsReplyFrame(
            ptr,
            size,
            apIn.ptr,
            apIn.len,
            clientIn.ptr,
            clientIn.len,
            requestIn.ptr,
            requestIn.len
          ), "aic8800 portal DNS reply build");
        } finally {
          freeMaybe(requestIn);
          freeMaybe(clientIn);
          freeMaybe(apIn);
        }
      },
      buildPortalTcpReplyFrame: function (apMac, clientMac, requestIp, sequence, acknowledgement, flags, payload) {
        const body = payload instanceof Uint8Array ? payload : new Uint8Array(payload || []);
        const apIn = allocMaybe(apMac || null);
        const clientIn = allocMaybe(clientMac || null);
        const requestIn = allocMaybe(requestIp || null);
        const payloadIn = allocMaybe(body);
        try {
          return callOut(54 + body.length, (ptr, size) => functions.buildPortalTcpReplyFrame(
            ptr,
            size,
            apIn.ptr,
            apIn.len,
            clientIn.ptr,
            clientIn.len,
            requestIn.ptr,
            requestIn.len,
            sequence >>> 0,
            acknowledgement >>> 0,
            flags >>> 0,
            payloadIn.ptr,
            payloadIn.len
          ), "aic8800 portal TCP reply build");
        } finally {
          freeMaybe(payloadIn);
          freeMaybe(requestIn);
          freeMaybe(clientIn);
          freeMaybe(apIn);
        }
      },

      decodeApMgmtFrame: function (block, apMac, ssidBytes) {
        const input = block instanceof Uint8Array ? block : new Uint8Array(block || []);
        const apBytes = apMac instanceof Uint8Array ? apMac : new Uint8Array(apMac || []);
        const ssid = ssidBytes instanceof Uint8Array ? ssidBytes : encodeText(ssidBytes || "");
        const blockIn = allocMaybe(input);
        const apIn = allocMaybe(apBytes);
        const ssidIn = allocMaybe(ssid);
        const metaPtr = malloc(64);
        if (!metaPtr) {
          freeMaybe(ssidIn);
          freeMaybe(apIn);
          freeMaybe(blockIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, metaPtr, metaPtr + 64);
          const ok = functions.decodeApMgmtFrame(metaPtr, 64, blockIn.ptr, blockIn.len, apIn.ptr, apIn.len, ssidIn.ptr, ssidIn.len) >>> 0;
          if (!ok) {
            return null;
          }
          const meta = heapU8().slice(metaPtr, metaPtr + 64);
          const action = meta[0] >>> 0;
          return {
            action,
            type: action === 1 ? "auth" : action === 2 ? "assoc" : action === 3 ? "reassoc" : "unknown",
            subtype: meta[1] >>> 0,
            qos: Boolean(meta[2]),
            frameOffset: readU32LE(meta, 4),
            frameLength: readU32LE(meta, 8),
            seqControl: readU16LE(meta, 12),
            capability: readU16LE(meta, 14),
            listenInterval: readU16LE(meta, 16),
            authAlgorithm: readU16LE(meta, 18),
            authSequence: readU16LE(meta, 20),
            status: readU16LE(meta, 22),
            iesOffset: readU32LE(meta, 24),
            iesLength: readU32LE(meta, 28),
            ssidLength: readU16LE(meta, 32),
            da: meta.slice(36, 42),
            sa: meta.slice(42, 48),
            bssid: meta.slice(48, 54),
          };
        } finally {
          free(metaPtr);
          freeMaybe(ssidIn);
          freeMaybe(apIn);
          freeMaybe(blockIn);
        }
      },
      decodeScanResult: function (params) {
        return callMeta(params, 48, functions.decodeScanResult, (meta) => {
          const ssidLen = meta[40];
          const ssid = ssidLen ? decodeAscii(meta.subarray(8, 8 + ssidLen)) : "[hidden]";
          return {
            ssid,
            bssidBytes: meta.slice(0, 6),
            freq: readU16LE(meta, 42),
            band: meta[44],
            rssi: meta[45] << 24 >> 24,
          };
        });
      },

      buildPcapFile: function (frames, snaplen) {
        const list = Array.isArray(frames) ? frames : [];
        const limit = Math.max(1, Math.min(65535, snaplen >>> 0 || 65535));
        let dataTotal = 0;
        let outTotal = 24;
        for (const entry of list) {
          const bytes = entry && entry.bytes ? entry.bytes : new Uint8Array(0);
          const capLen = Math.min(bytes.length, limit);
          dataTotal += capLen;
          outTotal += 16 + capLen;
        }
        const data = new Uint8Array(dataTotal);
        const meta = new Uint8Array(list.length * 20);
        let dataOff = 0;
        for (let i = 0; i < list.length; i += 1) {
          const entry = list[i] || {};
          const bytes = entry.bytes || new Uint8Array(0);
          const capLen = Math.min(bytes.length, limit);
          const tsMs = Math.max(0, Math.trunc(entry.timestampMs || 0));
          data.set(bytes.subarray(0, capLen), dataOff);
          const metaOff = i * 20;
          writeU32LE(meta, metaOff, dataOff);
          writeU32LE(meta, metaOff + 4, capLen);
          writeU32LE(meta, metaOff + 8, bytes.length >>> 0);
          writeU32LE(meta, metaOff + 12, Math.trunc(tsMs / 1000) >>> 0);
          writeU32LE(meta, metaOff + 16, ((tsMs % 1000) * 1000) >>> 0);
          dataOff += capLen;
        }
        const dataIn = allocMaybe(data);
        const metaIn = allocMaybe(meta);
        const outPtr = malloc(outTotal || 1);
        if (!outPtr) {
          freeMaybe(metaIn);
          freeMaybe(dataIn);
          throw new Error("aic8800 native core allocation failed");
        }
        try {
          heapU8().fill(0, outPtr, outPtr + outTotal);
          const written = functions.buildPcapFile(outPtr, outTotal, dataIn.ptr, dataIn.len, metaIn.ptr, metaIn.len) >>> 0;
          if (!written || written > outTotal) {
            throw new Error("aic8800 native pcap build failed");
          }
          return heapU8().slice(outPtr, outPtr + written);
        } finally {
          free(outPtr);
          freeMaybe(metaIn);
          freeMaybe(dataIn);
        }
      },
    };
  }

  async function init() {
    try {
      const response = await fetch(WASM_URL);
      if (!response.ok) {
        throw new Error("HTTP " + response.status + " while loading " + WASM_URL);
      }
      const bytes = await response.arrayBuffer();
      const result = await WebAssembly.instantiate(bytes, makeImports());
      if (typeof result.instance.exports._initialize === "function") {
        result.instance.exports._initialize();
      }
      state.api = makeApi(result.instance.exports);
      return state.api;
    } catch (error) {
      state.error = error;
      if (typeof console !== "undefined" && console.warn) {
        console.warn("AIC8800 native C/WASM core unavailable; native driver operations will fail until it loads.", error);
      }
      return null;
    }
  }

  state.ready = init();

  window.Aic8800Native = {
    version: AIC8800_NATIVE_VERSION,
    ready: state.ready,
    get: function () {
      return state.api;
    },
    error: function () {
      return state.error;
    },
  };
})();
