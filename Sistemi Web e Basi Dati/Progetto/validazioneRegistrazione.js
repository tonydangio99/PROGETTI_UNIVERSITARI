function validate(){
var nome = document.modulo.nome.value;
var cognome= document.modulo.cognome.value;
var email= document.modulo.email.value;
var username = document.modulo.username.value;
var password = document.modulo.password.value;
var confermapass= document.modulo.confermapass.value;

if((nome == "") || (nome =="undefined")){
    alert("Devi inserire un Nome");
    document.modulo.nome.focus();
    return false;
}
if((cognome == "") || (cognome == "undefined")){
    alert("Devi inserire un Cognome");
    document.modulo.cognome.focus();
    return false;
}

var email_valid = /^([a-zA-Z0-9_.-])+@(([a-zA-Z0-9-]{2,})+.)+([a-zA-Z0-9]{2,})+$/;
   if (!email_valid.test(email) || (email == "") || (email == "undefined")){
    alert("Inserire un indirizzo E-mail valido");
    document.modulo.email.focus();
    return false;
}
if((username == "") || (username =="undefined")){
    alert("Devi inserire un Username valido");
    document.modulo.username.focus();
    return false;
}

if(password.length < 8 || (password=="") ||(password=="undefined")){
    alert("Devi inserire una Password sufficientemente lunga");
    document.modulo.password.focus();
    return false;
}

if(confermapass.length < 8 || (confermapass=="") ||(confermapass=="undefined")){
    alert("Conferma la Password");
    document.modulo.confermapass.focus();
    return false;
}else if(document.modulo.confermapass.value!=document.modulo.password.value){
 alert("Le Password non coincidono");
 return false;
}


}