import { fetchData, updateTextContent, calculateSubtraction, calculatePercentage, getTempCelsius } from './utils.js';

// Mapeamento dos endpoints da API de info do Esp32
const espInfoAPI = {
    chipInfo: 'http://192.168.1.111/api/chipinfo',
    littleFSInfo: 'http://192.168.1.111/api/littlefsinfo',
    heapInfo: 'http://192.168.1.111/api/heapinfo',
    internalTemp: 'http://192.168.1.111/api/internaltemp',
};

// Processadores de dados específicos
function processChipInfo(data){
    updateTextContent('chip-model', data.model); 
    updateTextContent('mac-address', data.macId); 
    updateTextContent('sdk-version', data.sdkVersion); 
    updateTextContent('cpu-freq', data.cpuFreq); 
    updateTextContent('flash-size', data.flashSize); 
    updateTextContent('flash-speed', data.flashSpeed); 
    updateTextContent('sketch-size', data.sketchSize);
}

function processLittleFSInfo(data) { 
    updateTextContent('littlefs-total', data.totalBytes); 
    updateTextContent('littlefs-used', data.usedBytes); 
    updateTextContent(
        'littlefs-perc', 
        calculatePercentage(data.usedBytes, data.totalBytes)
    ); 
}

function processHeapInfo(data) { 
    let heapUsed = calculateSubtraction(data.heapSize, data.freeHeapSize); 
    updateTextContent('heap-total', data.heapSize);
    updateTextContent('heap-used', heapUsed); 
    updateTextContent(
        'heap-perc', 
        calculatePercentage(heapUsed, data.heapSize)
    ); 
}

function processInternalTemp(data) { 
    updateTextContent(
        'chip-temp', 
        getTempCelsius(data.internalTemp)
    );
}

// Funções de fetch específicas
export async function fetchChipInfo() {
    await fetchData(espInfoAPI.chipInfo, processChipInfo);
}

export async function fetchLittleFSInto() {
    await fetchData(espInfoAPI.littleFSInfo, processLittleFSInfo);
}

export async function fetchHeapInfo() {
    await fetchData(espInfoAPI.heapInfo, processHeapInfo);
}

export async function fetchInternalTemp() {
    await fetchData(espInfoAPI.internalTemp, processInternalTemp);
}