<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Visualizza prenotazioni</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
    <script type="text/javascript" src="validazione.js"></script>

</head>
<body class="body2">


    <div class="container">
        <form action="EliminateTuePrenotazioni.php" method="POST" name="login">
            <div class="form-control">
                <input type="text" class="eliminaEmail" id="eliminaEmail" name="eliminaEmail" required placeholder="Inserisci la Mail della Prenotazione ">
            </div>
            <div class="form-control">
                <input type="text" class="eliminaidPrenotazione" id="eliminaidPrenotazione" name="eliminaidPrenotazione" required placeholder="Inserisci l'id della prenotazione ">
            </div>
            <button class="btn">Visualizza</button>
                <br></br>
        </form>

        <form action="LoggatoPrivato.php">
            <button class="btn">Indietro</button>
        </form>


    </div>

</body>
</html>