<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Future Systems Consulting - Registrazione</title>
    <link rel="icon" type="image/x-icon" href="Favicon.jpg">
    <link rel="stylesheet" href="LoginRegistrazione.css">
    <script type="text/javascript" src="validazioneRegistrazione.js" ></script>

</head>

<body class="body2" >

<div class="container">
    <h1 style="color: rgb(100,100,100); font-style: Verdana, sans-serif;">Registrazione</h1>
    <form name="modulo" action="Registrato.php" method="POST" onSubmit="return validate()">
        <div class="form-control">
         <input type="text" class="nome" id="nome" name="nome" required placeholder="Nome">
        </div>
        <div class="form-control">
            <input type="text" class="cognome" id="cognome" name="cognome" required placeholder="Cognome">
           </div>
           <div class="form-control">
            <input type="email" class="email" id="email" name="email" required placeholder="Indirizzo Email">
           </div>
           <div class="form-control">
            <input type="date" class="date" id="date" name="date" required> <strong>Data di Nascita</strong> 
           </div>
           <div class="form-control">
            <input type="text" class="nascita" id="nascita" name="nascita" required placeholder="Nato a">
           </div>
        <div class="provincia">
            <strong> in Provincia di</strong>
            <select class="provincia" id="provincia" name="provincia" style="color: black;" >
                <option>         </option>
                <option>Agrigento</option>
                <option>Alessandria</option>
                <option>Ancona</option>
                <option>Aosta</option>
                <option>Arezzo</option>
                <option>Ascoli Piceno</option>
                <option>Asti</option>
                <option>Avellino</option>
                <option>Bari</option>
                <option>Barletta-Andria-Trani</option>
                <option>Belluno</option>
                <option>Benevento</option>
                <option>Bergamo</option>
                <option>Biella</option>
                <option>Bologna</option>
                <option>Bolzano</option>
                <option>Brescia</option>
                <option>Brindisi</option>
                <option>Cagliari</option>
                <option>Caltanissetta</option>
                <option>Campobasso</option>
                <option>Caserta</option>
                <option>Catania</option>
                <option>Catanzaro</option>
                <option>Chieti</option>
                <option>Como</option>
                <option>Cosenza</option>
                <option>Cremona</option>
                <option>Crotone</option>
                <option>Cuneo</option>
                <option>Enna</option>
                <option>Fermo</option>
                <option>Ferrara</option>
                <option>Firenze</option>
                <option>Foggia</option>
                <option>Forl&igrave;-Cesena</option>
                <option>Frosinone</option>
                <option>Genova</option>
                <option>Gorizia</option>
                <option>Grosseto</option>
                <option>Imperia</option>
                <option>Isernia</option>
                <option>L'aquila</option>
                <option>La spezia</option>
                <option>Latina</option>
                <option>Lecce</option>
                <option>Lecco</option>
                <option>Livorno</option>
                <option>Lodi</option>
                <option>Lucca</option>
                <option>Macerata</option>
                <option>Mantova</option>
                <option>Massa-Carrara</option>
                <option>Matera</option>
                <option>Messina</option>
                <option>Milano</option>
                <option>Modena</option>
                <option>Monza e Brianza</option>
                <option>Napoli</option>
                <option>Novara</option>
                <option>Nuoro</option>
                <option>Oristano</option>
                <option>Padova</option>
                <option>Palermo</option>
                <option>Parma</option>
                <option>Pavia</option>
                <option>Perugia</option>
                <option>Pesaro e Urbino</option>
                <option>Pescara</option>
                <option>Piacenza</option>
                <option>Pisa</option>
                <option>Pistoia</option>
                <option>Pordenone</option>
                <option>Potenza</option>
                <option>Prato</option>
                <option>Ragusa</option>
                <option>Ravenna</option>
                <option>Reggio Calabria</option>
                <option>Reggio Emilia</option>
                <option>Rieti</option>
                <option>Rimini</option>
                <option>Roma</option>
                <option>Rovigo</option>
                <option>Salerno</option>
                <option>Sassari</option>
                <option>Savona</option>
                <option>Siena</option>
                <option>Siracusa</option>
                <option>Sondrio</option>
                <option>Sud Sardegna</option>
                <option>Taranto</option>
                <option>Teramo</option>
                <option>Terni</option>
                <option>Torino</option>
                <option>Trapani</option>
                <option>Trento</option>
                <option>Treviso</option>
                <option>Trieste</option>
                <option>Udine</option>
                <option>Varese</option>
                <option>Venezia</option>
                <option>Verbano-Cusio-Ossola</option>
                <option>Vercelli</option>
                <option>Verona</option>
                <option>Vibo valentia</option>
                <option>Vicenza</option>
                <option>Viterbo</option>
            </select> 
        </div>
        <div class="form-control">
            <input type="text" class="username" id="username" name="username" required placeholder="Username">
        </div>
        <div class="form-control">
            <input type="password" class="password" id="password" name="password" required placeholder="Password">
        </div>
        <div class="form-control">
            <input type="password" class="confermapass" id="confermapass" name="confermapass" required placeholder="Conferma Password">
        </div>
        <div  style="color:white;"> <strong>Sesso</strong>
            <select class="sesso" id="sesso" name="sesso">
                <option>     </option>
                <option>Maschio</option>
                <option>Femmina</option>
                <option>Altro</option>
            </select>
        </div>
        <br></br>

        <div style="color:white;"> <strong>Sono un:</strong>
            <select class="sono" id="sono" name="sono" >
                <option>     </option>
                <option>Privato </option>
                <option>Titolare Azienda</option>
            </select>
        </div>        
        <br>
        <br>
        <button class="btn">Registrati</button>
    </form>
</div>
</body>
</html>