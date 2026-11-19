#define FOTORESISTORE 1 
#define LED 7 
#define CHAN 0 
#define LIGHT_MIN 372 
#define LIGHT_MAX 2048

void setup() {
  ledcSetup(CHAN, 1000, 12); 
  ledcAttachPin(LED, CHAN); 

}

void loop() {
    int adcVal = analogRead(FOTORESISTORE); //read adc 
    int pwmVal = map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 0, 4095);  
    ledcWrite(CHAN, pwmVal); 
    delay(10);

}
