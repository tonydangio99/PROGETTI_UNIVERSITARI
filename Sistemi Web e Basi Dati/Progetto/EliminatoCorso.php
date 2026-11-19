<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Eliminazione Dipendente</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css"></head>

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

    $eliminaCorso = $_POST['eliminaCorso'];

    $sql="DELETE FROM corsi WHERE idCorso = $eliminaCorso ";
    

    if($connessione->query($sql) === true){
      echo"La registrazione è andata a buon fine! ";
      }else{
          echo"L'eliminazione è andata abuon fine" . $connessione->error;
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
            <th style = "border: 2px solid #dddddd">IdCorso</th> 
            <th style = "border: 2px solid #dddddd">Nome Corso </th>
            <th style = "border: 2px solid #dddddd">Docente Corso </th> 
            <th style = "border: 2px solid #dddddd">Descrizione Corso </th> 
            <th style = "border: 2px solid #dddddd">Prezzo Corso </th> 
            <th style = "border: 2px solid #dddddd">Data Inizio </th>
            <th style = "border: 2px solid #dddddd">Data Fine </th> 
            
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

<form action="EliminaCorsi.php">
            <br></br>
            <button class="btn">Elimina un altro Corso</button>
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
