<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Prenotazione Corso</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css"></head>

<body class="body2" >



    <?php

    $host = "127.0.0.1";
    $user = "root";
    $password = "";
    $database = "fsc_database";
    
    $connessione = new mysqli($host,$user,$password,$database);
      if($connessione == false){
        die("errore di connessione: " . $connessione->connect_error);
      }

      $idCorsoPrenotato = $connessione->real_escape_string($_POST['idCorsoPrenotato']);
      $NomePrenotazione = $connessione->real_escape_string($_POST['NomePrenotazione']);
      $CognomePrenotazione = $connessione->real_escape_string($_POST['CognomePrenotazione']);
      $EmailPrenotazione = $connessione->real_escape_string($_POST['EmailPrenotazione']);


      $sql = "INSERT INTO prenotazioni (idCorsoPrenotato,NomePrenotazione,CognomePrenotazione,EmailPrenotazione) 
      VALUES ('$idCorsoPrenotato','$NomePrenotazione','$CognomePrenotazione','$EmailPrenotazione')";


    if($connessione->query($sql) === true){
	echo"La Prenotazione è andata a buon fine! ";
	}else{
	       echo"la prenotazione non è andata a buon fine" . $connessione->error;
		}
    
    ?>



<div class="container">

   

<form action="PrenotaCorso.php">
            <br></br>
            <h1 style="color: white;">Grazie per la prenotazione!</h1>
            <h2 style="color: white;">Verrai ricontattato per ulteriori dettagli</h2>
            <button class="btn">Prenota un altro corso</button>
            <br></br>
            
</form>

<form action="LoginPrivato.php">
            <button class="btn">Torna Indietro</button>
            <br></br>
            
</form>
</div>
</body>
</html>
