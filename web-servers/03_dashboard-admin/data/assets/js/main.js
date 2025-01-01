"use strict";

import { fetchChipInfo, fetchLittleFSInto, fetchHeapInfo, fetchInternalTemp } from "./scripts/espinfo.js";

document.addEventListener('DOMContentLoaded', () => {
    fetchChipInfo();
    fetchLittleFSInto();
    fetchHeapInfo();
    fetchInternalTemp();
});

