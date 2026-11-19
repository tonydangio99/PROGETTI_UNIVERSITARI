<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Inserimento Corso</title>
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

      $nome = $connessione->real_escape_string($_POST['nome']);
      $cognome = $connessione->real_escape_string($_POST['cognome']);
      $stipendio = $connessione->real_escape_string($_POST['stipendio']);
      $dipartimento = $connessione->real_escape_string($_POST['dipartimento']);


      $sql = "INSERT INTO dipendenti (Nome,Cognome,Stipendio,Dipartimento) 
                VALUES ('$nome','$cognome','$stipendio','$dipartimento')";


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


        $sql="SELECT * FROM dipendenti";


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
            <th style = "border: 2px solid #dddddd">IdDipendente</th> 
            <th style = "border: 2px solid #dddddd">Nome </th>
            <th style = "border: 2px solid #dddddd">Cognome </th> 
            <th style = "border: 2px solid #dddddd">Stipendio </th> 
            <th style = "border: 2px solid #dddddd">Dipartimento </th> 
            
            </tr></thead><tbody>';
            while($row = $result->fetch_array()){
              echo'
              <tr>
              <td style = "border: 2px solid #dddddd">'. $row['idDipendenti'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Nome'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Cognome'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Stipendio'] . '</td> 
              <td style = "border: 2px solid #dddddd">'. $row['Dipartimento'] . '</td> 
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

<form action="InserisciDipendente.php">
            <br></br>
            <button class="btn">Inseriscine un Altro</button>
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
