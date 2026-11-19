<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Normal User</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
</head>


<body>

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

    $username = $connessione->real_escape_string($_POST['username']);
    $password = $connessione->real_escape_string($_POST['password']);

    if($_SERVER["REQUEST_METHOD"] == "POST"){
        $sql = "SELECT * FROM clienti WHERE NomeUtente = '$username'";
            if($result = $connessione->query($sql)){
                if($result->num_rows == 1){
                    $row = $result->fetch_array(MYSQLI_ASSOC);
                        if($password == $row['Password']){
                            session_start();
                            $_SESSION['Loggato'] = true;
                            $_SERVER['id'] = $row['id'];
                            $_SERVER['NomeUtente'] = $row['NomeUtente'];
                            header("location: LoggatoPrivato.php");
                        }else{
                            echo'';
                        }
                }else{
                    echo'';
                }
            }else{
                echo'';
            }
            $connessione->close();
    }
  ?>
        <form action="LoginRegistrazione.php">
            <h1 style="color:white ;">Nome utente o Password errata!</h1>
            <br></br>
            <button class="btn">Ritorna al Login</button>
        </form>
    </div>
</body>
</html>
