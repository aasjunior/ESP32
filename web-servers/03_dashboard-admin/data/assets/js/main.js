"use strict";

const url = 'http://192.168.1.111';

document.addEventListener('DOMContentLoaded', () => {
    fetchChipInfo();
    fetchLittleFSInto();
    fetchHeapInfo();
    fetchInternalTemp();
});

async function fetchChipInfo() {
    try{
        const response = await fetch(`${url}/api/chipinfo`);
        const data = await response.json();

        document.getElementById('chip-model').textContent = data.model;
        document.getElementById('mac-address').textContent = data.macId;
        document.getElementById('sdk-version').textContent = data.sdkVersion;
        document.getElementById('cpu-freq').textContent = data.cpuFreq;
        document.getElementById('flash-size').textContent = data.flashSize;
        document.getElementById('flash-speed').textContent = data.flashSpeed;
        document.getElementById('sketch-size').textContent = data.sketchSize;
    }catch(error){
        console.error('Error fetching chip info: ', error);
    }
}

async function fetchLittleFSInto() {
    try{
        const response = await fetch(`${url}/api/littlefsinfo`);
        const data = await response.json();

        document.getElementById('littlefs-total').textContent = data.totalBytes;
        document.getElementById('littlefs-used').textContent = data.usedBytes;
        document.getElementById('littlefs-perc').textContent = calculatePercentage(data.usedBytes, data.totalBytes);
    }catch(error){
        console.error('Error fetching LittleFS info: ', error);
    }
}

async function fetchHeapInfo() {
    try{
        const response = await fetch(`${url}/api/heapinfo`);
        const data = await response.json();

        document.getElementById('heap-total').textContent = data.heapSize;
        let heapUsed = calculateSubtraction(data.heapSize, data.freeHeapSize);
        console.log(heapUsed);
        document.getElementById('heap-used').textContent = heapUsed;
        document.getElementById('heap-perc').textContent = calculatePercentage(heapUsed, data.heapSize);
    }catch(error){
        console.error('Error fetching Heap info: ', error);
    }
}

async function fetchInternalTemp() {
    try{
        const response = await fetch(`${url}/api/internaltemp`);
        const data = await response.json();
        console.log(data.internalTemp);
        document.getElementById('chip-temp').textContent = getTempCelsius(data.internalTemp);
    }catch(error){
        console.error('Error fetching internal temperature info: ', error);
    }
}

function calculatePercentage(portion, total) {
    if(total === 0 || !isNumber(portion) || !isNumber(total)) {
        return 'N/A';
    }
    return ((portion * 100) / total).toFixed(1) + '%';
}

function calculateSubtraction(a, b) {
    if(!isNumber(a) || !isNumber(b)) {
        return 'N/A';
    }
    return a - b;
}

function getTempCelsius(temp){
    if(!isNumber(temp)) {
        return 'N/A';
    }
    return temp.toFixed(1) + '°C';
}

function isNumber(value) { 
    return !isNaN(parseFloat(value)) && isFinite(value); 
}