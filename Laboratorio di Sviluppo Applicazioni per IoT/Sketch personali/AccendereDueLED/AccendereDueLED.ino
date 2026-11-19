  #define LED 1
  #define BOTTONE 14
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BOTTONE, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BOTTONE) == LOW) { 
    digitalWrite(LED,HIGH); 
  }else{ 
    digitalWrite(LED,LOW);
  }
}
