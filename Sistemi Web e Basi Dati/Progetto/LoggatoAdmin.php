<?php

    session_start();
    if(!isset($_SESSION['LoggatoAdmin']) && $_SESSION['Loggato'] != true ){
        header("location: LoginAdmin.php");
        exit;
    }
    
?>

<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Admin User</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css"></head>

<body class="body2">


    <div class="container">
        <form action="VisualizzaUtenti.php">
        <h1>Benvenuto nel tuo profilo !</h1>
            <button class="btn">Visualizza la lista dei clienti</button>
        </form>
        <form action="VisualizzaPrenotazioni.php">
            <br></br>
            <button class="btn">Visualizza le prenotazioni</button>
        </form>
        <form action="VisualizzaDipendenti.php">
            <br></br>
            <button class="btn">Visualizza i dipendenti del Centro</button>
        </form>
        <form action="InserisciDipendente.php">
            <br></br>
            <button class="btn">Inserisci un nuovo Dipendente</button>
        </form>
        <form action="InserisciCorso.php">
            <br></br>
            <button class="btn">Inserisci un nuovo Corso</button>
        </form>
        <form action="EliminaDipendente.php">
            <br></br>
            <button class="btn">Elimina un Dipendente</button>
        </form>
        <form action="EliminaCorsi.php">
            <br></br>
            <button class="btn">Elimina un Corso</button>
        </form>
        <form action="Logout.php">
            <br></br>
            <button class="btn">Logout</button>
        </form>
    </div>
</body>
</html>

