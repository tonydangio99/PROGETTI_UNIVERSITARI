<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Inserimento Dipendente</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
    <script type="text/javascript" src="validazione.js"></script>

</head>

<body class="body2" >


    <div class="container">
        <h1>Inserimento nuovo dipendente</h1>
        <form action="InseritoDipendente.php" method="POST" name="login">
            <div class="form-control">
                <input type="text" class="nome" id="nome" name="nome" required placeholder="Nome">
            </div>
            <div class="form-control">
                <input type="text" class="cognome" id="cognome" name="cognome" required placeholder="Cognome">
            </div>
            <div class="form-control">
                <input type="text" class="stipendio" id="stipendio" name="stipendio" required placeholder="Stipendio">
            </div>
            <div class="form-control">
                <input type="text" class="dipartimento" id="dipartimento" name="dipartimento" required placeholder="Dipartimento">
            </div>
            <button class="btn">Aggiungi</button>
        </form>
        <form action="LoggatoAdmin.php">
        <h1></h1>
        
            <button class="btn">Indietro</button>
            <br></br>
        </form>
    </div>
</body>
</html>