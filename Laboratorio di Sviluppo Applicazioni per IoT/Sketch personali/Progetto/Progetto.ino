#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>
#include <WebServer.h>

#define PIN   1
#define PINLEDRED 42
#define PINLEDBLUE 38 
#define PINLUCE 9 
#define PIN_BUTTON 14 

String URL = "http://192.168.196.192/Progetto/sensordb.php";
String URL2 = "http://192.168.196.192/Progetto/statoluce.php";
const char * ssid = "PC di Antonio";
const char * password = "123456789";
const char * accesspoint = "ESP.32-S3 di Antonio";
const char * pass = "password";
WebServer server(80);

int temperatura = 0;
int sensorValue = 0;

unsigned long ultimoInviato = 0;
unsigned long intervallo = 60000; // Intervallo di invio dati in millisecondi

void setup() {
  Serial.begin(115200);
  connectWiFi();
  AccessPoint();
  pinMode(PINLEDRED, OUTPUT);
  pinMode(PINLEDBLUE, OUTPUT);
  pinMode(PINLUCE, OUTPUT); 
  pinMode(PIN_BUTTON, INPUT); 
}

void loop() {
  unsigned long currentMillis = millis();

  if(WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  } 

  // Gestione del pulsante luce
  if (digitalRead(PIN_BUTTON) == LOW) { 
    delay(20); 
  if (digitalRead(PIN_BUTTON) == LOW) { 
    reverseGPIO(PINLUCE); 
  } 
  while (digitalRead(PIN_BUTTON) == LOW); 
    delay(20); 
  while (digitalRead(PIN_BUTTON) == LOW); 
  }
  
  // Lettura del sensore di temperatura e gestione dei LED
  int adcValue = analogRead(PIN);                       
  double voltage = (float)adcValue / 4095.0 * 3.3;                
  double Rt = 10 * voltage / (3.3 - voltage);                     
  double tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0); 
  double tempC = tempK - 273.15;                                  
  int temperatura = (int)tempC; 
  sensorValue = tempC;
  server.handleClient();
  
  if(currentMillis - ultimoInviato >= intervallo) {
  // Invio dei dati al server se è trascorso l'intervallo di invio
    String postData = "temperatura=" + String(temperatura);
    HTTPClient http;
    http.begin(URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(postData);
    String payload = http.getString();

    Serial.printf("Temperatura calcolata : %.2fC\n", tempC);
    Serial.print("URL : "); Serial.println(URL); 
    Serial.print("Data: "); Serial.println(postData);
    Serial.print("httpCode: "); Serial.println(httpResponseCode);
    Serial.print("payload : "); Serial.println(payload);
    Serial.println("--------------------------------------------------");
    delay(500);

    ultimoInviato = currentMillis; // Aggiorniamo il tempo dell'ultimo invio

  }

  if(temperatura <= 22 && temperatura >=0){
    digitalWrite(PINLEDBLUE, LOW);
    digitalWrite(PINLEDRED, HIGH);
  } else if(temperatura <= 40 && temperatura >=25){
    digitalWrite(PINLEDRED, LOW);
    digitalWrite(PINLEDBLUE, HIGH);
  } else{
    digitalWrite(PINLEDBLUE, LOW);
    digitalWrite(PINLEDRED, LOW);
  }

}

void reverseGPIO(int pin) { 
  digitalWrite(pin, !digitalRead(pin)); 
  constrollaStatoLuce();
} 

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("Connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

void constrollaStatoLuce() {
  HTTPClient http;
  Serial.print("Inviando richiesta al server per cambiare stato alla luce 0 ");  
  http.begin(URL2);  // Specifica l'URL del server e dello script PHP
  int httpResponseCode = http.GET();  // Invia una richiesta GET al server
  Serial.println("Cambio stato alla luce 0 ");
  Serial.print("URL : "); Serial.println(URL2); 
  Serial.print("httpCode: "); Serial.println(httpResponseCode);
  Serial.println("--------------------------------------------------");  
  
  http.end();  // Chiudi la connessione
}

void AccessPoint(){
  WiFi.softAP(accesspoint,pass);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("ESP.32-S3 ha indirizzo IP: ");
  Serial.println(IP);

server.on("/", HTTP_GET, [](){
    String pagina = "<html><head><title>SMART HOME CONTROLLER</title></head><body style=\"font-family: Arial, sans-serif;\">";
    pagina += "<h1 style=\"color: #333;\">SMART HOME CONTROLLER</h1>";
    pagina += "<p style=\"margin-top: 20px;\">Benvenuto nel sistema di controllo della tua SMART HOME.</p>";
    pagina += "<p style=\"margin-top: 10px;\">La temperatura attuale e' : <span style=\"font-weight: bold;\" id=\"sensorValue\"></span> °C</p>";
    pagina += "<p style=\"margin-top: 20px;\">Luce della CUCINA</p>";
    pagina += "<div style=\"margin-top: 20px;\"><a href=\"/on\" style=\"text-decoration: none; background-color: #4CAF50; color: white; padding: 10px 20px; border-radius: 5px;\">Accendi Luce</a>&nbsp;";
    pagina += "<a href=\"/off\" style=\"text-decoration: none; background-color: #f44336; color: white; padding: 10px 20px; border-radius: 5px;\">Spegni Luce</a></div>";
    pagina += "<script>function updateSensorValue() {document.getElementById('sensorValue').innerHTML = '" + String(sensorValue) + "';} setInterval(updateSensorValue, 1000);</script>";
    pagina += "</body></html>";
    server.send(200, "text/html", pagina);
});

  server.on("/on", HTTP_GET, [](){
    String pagina = "<html><head><title>Accendi Luce</title></head><body style=\"font-family: Arial, sans-serif;\">";
    pagina += "<h1 style=\"color: #333;\">Accendi Luce</h1>";
    pagina += "<p style=\"margin-top: 20px;\">la luce della CUCINA e' accesa</p>";
    pagina += "<div style=\"margin-top: 20px;\"><a href=\"/\" style=\"text-decoration: none; background-color: #4CAF50; color: white; padding: 10px 20px; border-radius: 5px;\">Indietro</a></div>";
    pagina += "</body></html>";
    reverseGPIO(PINLUCE);
    server.send(200, "text/html", pagina);
});

  server.on("/off", HTTP_GET, [](){
    String pagina = "<html><head><title>Spegni Luce</title></head><body style=\"font-family: Arial, sans-serif;\">";
    pagina += "<h1 style=\"color: #333;\">Spegni Luce</h1>";
    pagina += "<p style=\"margin-top: 20px;\">la luce della CUCINA e' spenta</p>";
    pagina += "<div style=\"margin-top: 20px;\"><a href=\"/\" style=\"text-decoration: none; background-color: #f44336; color: white; padding: 10px 20px; border-radius: 5px;\">Indietro</a></div>";
    pagina += "</body></html>";
    reverseGPIO(PINLUCE);
    server.send(200, "text/html", pagina);
});

  server.begin();
}