<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Login Admin</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
    <script type="text/javascript" src="validazione.js" ></script>

</head>

<body class="body2">

    <div class="container">
        <h1>Login Admin</h1>
        <form action="VerificaLoginAdmin.php" method="POST" onSubmit="return valida()" name="login" >
            <div class="form-control">
                <input type="text" class="username" id="username" name="username" required placeholder="Username">
            </div>
            <div class="form-control">
                <input type="password" class="password" id="password" name="password" required placeholder="Password">
            </div>
            <button class="btn">Accedi</button>
            <br>
            <br>
        </form>
    </div>
</body>
</html>