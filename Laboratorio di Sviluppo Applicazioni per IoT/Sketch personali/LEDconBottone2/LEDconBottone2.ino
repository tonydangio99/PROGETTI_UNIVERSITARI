  #define LED 1
  #define BOTTONE 14


void setup() {

  pinMode(LED, OUTPUT);
  pinMode(BOTTONE, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BOTTONE) == LOW) { 
  delay(20); 
    if (digitalRead(BOTTONE) == LOW) { 
        reverseGPIO(LED); 
    } 
  while (digitalRead(BOTTONE) == LOW); 
    delay(20); 
  while (digitalRead(BOTTONE) == LOW); 
  }
}

void reverseGPIO(int pin) { 
digitalWrite(pin,!digitalRead(pin)); 
}
