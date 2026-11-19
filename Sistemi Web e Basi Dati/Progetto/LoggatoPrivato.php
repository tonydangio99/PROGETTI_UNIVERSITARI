<?php

    session_start();
    if(!isset($_SESSION['LoggatoPrivato']) && $_SESSION['Loggato'] != true ){
        header("location: LoginRegistrazione.php");
        exit;
    }
    
?>

<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Normal User</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
</head>


<body class="body2">
    
    <div class="container">
    <h1 style="color:white ;" >Benvenuto nel tuo profilo</h1>
    
    <form action="PrenotaCorso.php">
            <br></br>
            <button class="btn">Prenota un Corso</button>
    </form>

    <form action="VisualizzaTuePrenotazioni.php">
            <br></br>
            <button class="btn">Visualizza le tue Prenotazioni</button>
    </form>

    <form action="EliminaTuePrenotazioni.php">
            <br></br>
            <button class="btn">Elimina una Prenotazione</button>
    </form>

    <form action="Logout.php">
            <br></br>
            <button class="btn">Logout</button>
    </form>
    </div>
</body>
</html>