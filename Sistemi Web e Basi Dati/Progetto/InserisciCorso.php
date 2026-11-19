<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Inserimento Corso</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
    <script type="text/javascript" src="validazione.js"></script>

</head>

<body  class="body2" >


    <div class="container">
        <form action="InseritoCorso.php" method="POST" name="login">
            <div class="form-control">
                <input type="text" class="nomeCorso" id="nomeCorso" name="nomeCorso" required placeholder="Nome Corso">
            </div>
            <div class="form-control">
                <input type="text" class="docenteCorso" id="docenteCorso" name="docenteCorso" required placeholder="Docente del Corso">
            </div>
            <div class="form-control">
                <input type="text" class="descrizioneCorso" id="descrizioneCorso" name="descrizioneCorso" required placeholder="Descrizione del corso">
            </div>
            <div class="form-control">
                <input type="text" class="prezzoCorso" id="prezzoCorso" name="prezzoCorso" required placeholder="Prezzo">
            </div>
            <div class="form-control">
            <input type="date" class="dataInizio" id="dataInizio" name="dataInizio" required> <strong>Data di Inizio</strong> 
           </div>
           <div class="form-control">
            <input type="date" class="dataFine" id="dataFine" name="dataFine" required> <strong>Data di Inizio</strong> 
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