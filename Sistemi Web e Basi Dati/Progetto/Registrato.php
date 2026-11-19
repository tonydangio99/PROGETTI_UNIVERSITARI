<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Registrazione</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
</head>
<body class="body2">
    
    <?php

    $host = "127.0.0.1";
    $user = "root";
    $password = "";
    $database = "fsc_database";
    
    $connessione = new mysqli($host,$user,$password,$database);
      if($connessione == false){
        die("errore di connessione: " . $connessione->connect_error);
      }

      $nome = $connessione->real_escape_string($_REQUEST['nome']);
      $cognome = $connessione->real_escape_string($_REQUEST['cognome']);
      $email = $connessione->real_escape_string($_REQUEST['email']);
      $date = $connessione->real_escape_string($_REQUEST['date']);
      $nascita = $connessione->real_escape_string($_REQUEST['nascita']);
      $provincia = $connessione->real_escape_string($_REQUEST['provincia']);
      $username = $connessione->real_escape_string($_REQUEST['username']);
      $password = $connessione->real_escape_string($_REQUEST['password']);
      $sesso = $connessione->real_escape_string($_REQUEST['sesso']);
      $sono = $connessione->real_escape_string($_REQUEST['sono']);


      $sql = "INSERT INTO clienti (Nome,Cognome,Email,DataDiNascita,CittaNatale,Provincia,NomeUtente,Password,Sesso,SonoUn) 
                VALUES ('$nome','$cognome','$email','$date','$nascita','$provincia','$username','$password','$sesso','$sono')";


    if($connessione->query($sql) === true){
	echo"La registrazione è andata a buon fine! ";
	}else{
	       echo"inserimento non è andato a buon fine" . $connessione->error;
		}
    $connessione->close();
    
    ?>




<div class="container">
    <h1>Grazie per esserti Registrato !</h1>
    
    <form action="Home.html">
            <br></br>
            <button class="btn">Torna alla Home</button>
            <br></br>
    </form>
    <form action="LoginRegistrazione.php">
            <br></br>
            <button class="btn">Accedi</button>
            <br></br>
    </form>

</div>


</body>
</html>