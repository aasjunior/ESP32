document.addEventListener("DOMContentLoaded", function() {
    const wifiForm = document.getElementById("wifiForm");

    wifiForm.addEventListener("submit", async function(event) {
        event.preventDefault();

        const ssid = document.getElementById("ssid").value;
        const password = document.getElementById("password").value;

        const response = await fetch("/save", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({ ssid, password })
        });

        if (response.ok) {
            alert("Credenciais salvas. Reinicie o dispositivo.");
        } else {
            alert("Erro ao salvar as credenciais.");
        }
    });
});

async function fetchNetworks() {
    const response = await fetch("/scan");
    const networks = await response.json();
    
    const ssidSelect = document.getElementById("ssid");
    ssidSelect.innerHTML = '<option value="">Selecione uma rede</option>';

    networks.forEach(network => {
        const option = document.createElement("option");
        option.value = network.ssid;
        option.textContent = network.ssid;
        ssidSelect.appendChild(option);
    });
}
