$(document).ready(function () {
    function fetchButtonStatus() {
        $.getJSON("/button/status", function (data) {
            $("#button1-status").text("Botão 1: " + data.button1);
            $("#button2-status").text("Botão 2: " + data.button2);
        }).fail(function () {
            $("#button1-status").text("Erro ao buscar o estado");
            $("#button2-status").text("Erro ao buscar o estado");
        });
    }

    // Atualiza os estados a cada 1 segundo
    setInterval(fetchButtonStatus, 1000);
    fetchButtonStatus();
});
