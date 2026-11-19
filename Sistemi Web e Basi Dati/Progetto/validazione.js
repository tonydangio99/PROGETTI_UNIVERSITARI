function valida() {
    // Variabili associate ai campi del modulo
    var nome = document.login.username.value;
    var password = document.login.password.value;

    if ((nome == "") || (nome == "undefined")) {
        alert("Devi inserire un nome utente valido");
        document.login.username.focus();
        return false;
    }
    // Espressione regolare dell'email
    if (password.length < 6 || (password == "") || (password == "undefined")) {
        alert("La password deve avere almeno 6 caratteri");
        document.login.password.focus();
        return false;
    }

}