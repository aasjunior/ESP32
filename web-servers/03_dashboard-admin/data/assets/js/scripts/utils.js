export async function fetchData(url, processDataCallback) {
    /**
     * Função de ordem superior para realizar o fetch e processar os dados.
     * @param {string} url - URL base e Endpoint da API (Ex.: 'http://192.168.1.111/api/chipinfo').
     * @param {function} processDataCallback - Função de callback que processa os dados da API.
    */
    try{
        const response = await fetch(url);
        const data = await response.json();
        processDataCallback(data);
    }catch(error){
        console.error(`Error fetching ${url} info: `, error);
    }
}

export function updateTextContent(elementId, textContent){
    /**
     * Função para atualizar elementos do DOM
     * @param {string} elementId - ID do elemento HTML.
     * @param {string} textContent - Texto para inserir no elemento HTML.
     */
    document.getElementById(elementId).textContent = textContent;
}

export function updateProgressBar(elementId, percentage) {
    /**
     * Função para atualizar a barra de progresso
     * @param {string} elementId - ID do elemento HTML com.
     * @param  {number} percentage - Valor da porcentagem para atualizar o preenchimento da barra de progresso.
     */
    const progressBar = document.getElementById(elementId);
    if(progressBar){
        const percentageValue = parseFloat(percentage).toFixed(1); 
        progressBar.style.width = percentageValue + '%';
    }
}

export function calculatePercentage(portion, total) {
    if(total === 0 || !isNumber(portion) || !isNumber(total)) {
        return 'N/A';
    }
    return ((portion * 100) / total).toFixed(1) + '%';
}

export function calculateSubtraction(a, b) {
    if(!isNumber(a) || !isNumber(b)) {
        return 'N/A';
    }
    return a - b;
}

export function getTempCelsius(temp){
    if(!isNumber(temp)) {
        return 'N/A';
    }
    return temp.toFixed(1) + '°C';
}

export function isNumber(value) { 
    return !isNaN(parseFloat(value)) && isFinite(value); 
}
