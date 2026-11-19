<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Visualizza Prenotazioni</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css"></head>

<body class="body2">
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


      $emailPrenotazione = $_POST['EmailPrenotazione'];
      $sql="SELECT * FROM prenotazioni WHERE EmailPrenotazione = '$emailPrenotazione'";


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
            <th style = "border: 2px solid #dddddd">IdCorso</th> 
            <th style = "border: 2px solid #dddddd">IdPrenotazione</th>
            <th style = "border: 2px solid #dddddd">Nome </th> 
            <th style = "border: 2px solid #dddddd">Cognome </th> 
            <th style = "border: 2px solid #dddddd">Email </th> 

            </tr></thead><tbody>';
            while($row = $result->fetch_array()){
              echo'
              <tr>
              <td style = "border: 2px solid #dddddd">'. $row['idCorsoPrenotato'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['idPrenotazione'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['NomePrenotazione'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['CognomePrenotazione'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['EmailPrenotazione'] . '</td> 
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

<form action="LoggatoPrivato.php">
        <h1></h1>
        
            <button class="btn">Indietro</button>
            <br></br>
</form>            

</div>
</body>
</html>
