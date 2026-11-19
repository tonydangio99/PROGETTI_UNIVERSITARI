<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Inserimento Corso</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
</head>

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

      
      $NomeCorso = $connessione->real_escape_string($_POST['nomeCorso']);
      $docenteCorso = $connessione->real_escape_string($_POST['docenteCorso']);
      $descrizioneCorso = $connessione->real_escape_string($_POST['descrizioneCorso']);
      $prezzoCorso = $connessione->real_escape_string($_POST['prezzoCorso']);
      $dataInizio = $connessione->real_escape_string($_POST['dataInizio']);
      $dataFine = $connessione->real_escape_string($_POST['dataFine']);


      $sql = "INSERT INTO corsi (NomeCorso,DocenteCorso,DescrizioneCorso,PrezzoCorso,DataInizio,DataFine) 
                VALUES ('$NomeCorso','$docenteCorso','$descrizioneCorso','$prezzoCorso','$dataInizio','$dataFine')";

    
        if($connessione->query($sql) === true){
	        echo"La registrazione è andata a buon fine! ";
	        }else{
	            echo"inserimento non è andato a buon fine" . $connessione->error;
		            }
    $connessione->close();
    
    ?>



<div class="container">

    <?php

    $host = "127.0.0.1";
    $user = "root";
    $password = "";
    $database = "fsc_database";

    $connessione = new mysqli($host,$user,$password,$database);
        if($connessione == false){
            die("errore di connessione: " . $connessione->connect_error);
        }


        $sql="SELECT * FROM corsi";


    if($result = $connessione->query($sql)){
        if($result -> num_rows > 0){
        echo'
            <table style="font-family: arial, sans-serif;
            border-collapse: collapse;
            width: 100%;
            border: 2px solid #dddddd;
            text-align: left;
            padding: 8px;
            background-color: #5c5858;
            ">
            <thead>
            <tr style = "border: 2px solid #dddddd">
            <th style = "border: 2px solid #dddddd">Id Corso </th> 
            <th style = "border: 2px solid #dddddd">Nome Corso </th>
            <th style = "border: 2px solid #dddddd">Docente </th> 
            <th style = "border: 2px solid #dddddd">Descrizione </th> 
            <th style = "border: 2px solid #dddddd">Prezzo </th> 
            <th style = "border: 2px solid #dddddd">Data di Inizio </th> 
            <th style = "border: 2px solid #dddddd">Data di Fine </th> 
            
            </tr></thead><tbody>';
            while($row = $result->fetch_array()){
              echo'
              <tr>
              <td style = "border: 2px solid #dddddd">'. $row['idCorso'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['NomeCorso'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['DocenteCorso'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['DescrizioneCorso'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['PrezzoCorso'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['DataInizio'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['DataFine'] . '</td> 
              </tr>
              ';
            }
            echo'</tbody></table>';
        }else{
        echo'non ci sono elementi nella tabella';
        }
    }else{
  echo'errore nell esecuzione della query' . $sql . $connessione-> error;
    }




    ?>

<form action="Inseriscicorso.php">
            <br></br>
            <button class="btn">Inserisci un altro corso</button>
            <br></br>
            
</form>

<form action="LoggatoAdmin.php">
            <br></br>
            <button class="btn">Torna Indietro</button>
            <br></br>
            
</form>
</div>
</body>
</html>
