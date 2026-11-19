<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Visualizza Utenti</title>
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


        $sql="SELECT * FROM clienti";


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
            <th style = "border: 2px solid #dddddd">Id</th> 
            <th style = "border: 2px solid #dddddd">Nome </th>
            <th style = "border: 2px solid #dddddd">Cognome </th> 
            <th style = "border: 2px solid #dddddd">Email Corso </th> 
            <th style = "border: 2px solid #dddddd">Data di Nascita </th> 
            <th style = "border: 2px solid #dddddd">Città Natale </th> 
            <th style = "border: 2px solid #dddddd">Provincia </th>
            <th style = "border: 2px solid #dddddd">Nome Utente </th> 
            <th style = "border: 2px solid #dddddd">Password </th> 
            <th style = "border: 2px solid #dddddd">Sesso Corso </th> 
            <th style = "border: 2px solid #dddddd">Tipo Cliente </th> 
            
            
            </tr></thead><tbody>';
            while($row = $result->fetch_array()){
              echo'
              <tr>
              <td style = "border: 2px solid #dddddd">'. $row['id'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Nome'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Cognome'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Email'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['DataDiNascita'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['CittaNatale'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Provincia'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['NomeUtente'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Password'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Sesso'] . '</td>
              <td style = "border: 2px solid #dddddd">'. $row['SonoUn'] . '</td>
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

<form action="LoggatoAdmin.php">
        <h1></h1>
        
            <button class="btn">Indietro</button>
            <br></br>
</form>

</div>
</body>
</html>
