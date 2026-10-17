#include <stdio.h>
#include <math.h> 
#include <avr/interrupt.h> 

// Variabile volatile condivisa con l'ISR.
volatile unsigned long CONTORE_IMPULSI = 0; 

#define PPR 96.0 // PPR: Poli per Rivoluzione. Numero di magneti presenti nel cuscinetto 
#define TEMPO_CAMPIONAMENTO 0.01 // TEMPO_CAMPIONAMENTO: Intervallo di tempo per la lettura. 
#define RAGGIO_GOMMA_M 0.33 // Raggio della gomma in metri
#define CUT_CONST 8
#define ABS_CONST 6
#define VALORE_IDEALE_AC 0.1
#define VALORE_IDEALE_BR -0.1 


void setup() {
    Serial.begin(9600); //inizializzo il seriale nel caso volessi visualizzare qualcuno dei dati raccolti 
}

float get_Omega() {
    
    unsigned long impulsi_attuali;
    
    cli(); // DISABILITA TUTTI GLI INTERRUPT GLOBALI
    impulsi_attuali = CONTORE_IMPULSI; // LEGGI il dato grezzo in sicurezza
    CONTORE_IMPULSI = 0;               // AZZERA il contatore
    sei(); // RIABILITA GLI INTERRUPT

    // === 2. ELABORAZIONE (Calcoli di Conversione) ===
    // a. Calcolo della Frequenza (Hz)
    float frequenza_hz = (float)impulsi_attuali / TEMPO_CAMPIONAMENTO;
    // b. Calcolo della Velocità Angolare (rad/s)
    float rad_per_impulso = (2.0 * M_PI) / PPR;
    float velocita_rad_s = frequenza_hz * rad_per_impulso;

    return velocita_rad_s;

}

float get_Vx() {

    float velocita_lineare_ms = readLinearSpeedSensor(); // funzione che ritorna il valore della velocità lineare
    return velocita_lineare_ms;

}

void TC_cut(int livelloTC,float slip_ratio_ac){

    int throttle_status = analogRead(THROTTLE_PIN); //leggo la % di acceleratore 
    float taglio = (slip_ratio_ac*CUT_CONST*livelloTC); //CUT_CONST = 8 
    float aux = (throttle_status - taglio); // variabile ausiliaria da imporre come potenza al motore
    aux = constrain(aux,0,100); // limito la potenza dopo il taglio a stare tra 0 e 100%
    analogWrite(ENGINE_PIN,aux); //do il valore di potenza al motore

}

void ABS_on(int livelloABS, float slip_ratio_br) {

    int brake_status = analogRead(BRAKE_PIN); // leggo la % di freno
    float rilascio = (slip_ratio_br*ABS_CONST*livelloABS); // riduzione forza frenante
    float aux = (brake_status - rilascio); // nuova forza frenante
    aux = constrain(aux, 0, 100); // limito tra 0 e 100%
    analogWrite(BRAKE_OUT_PIN, aux); // applico la forza frenante al sistema

}


void loop() {

    int TC_analogico = analogRead(TC_PIN); //valore letto dal potenziometro del TC (può andare da 0 a 1023)
    float TC_mappato = map(TC_analogico, 0, 1023, 0, 11); //il valore letto viene mappato
    livelloTC = (int)TC_mappato; //cast per leggere un intero 
    livelloTC = constrain(livelloTC,0,11); //limita la variabile a stare in una specifico range

    int ABS_analogico = analogRead(ABS_PIN); //valore letto dal potenziometro dell'ABS (può andare da 0 a 1023)
    float ABS_mappato = map(ABS_analogico,0,1023,0,11);
    livelloABS = (int)ABS_mappato;
    livelloABS = constrain(livelloABS,0,11);

    int throttle_analogico = analogRead(THROTTLE_PIN); //valore letto dal potenziometro dell'acceleratore (può andare da 0 a 1023)
    float throttle_mappato = map(throttle_analogico,0,1023,0,100);
    throttle = (int)throttle_mappato;
    throttle = constrain(throttle,0,100);

    int brake_analogico = analogRead(BRAKE_PIN); // valore letto dal potenziometro del freno (puo andare da 0 a 1023)
    float brake_mappato = map(brake_analogico, 0, 1023, 0, 100);
    brake = (int)brake_mappato;
    brake = constrain(brake, 0, 100);

    int engine_analogico = analogRead(ENGINE_PIN); //valore letto dallo stato del motore (può andare da 0 a 1023)
    float engine_mappato = map(engine_analogico,0,1023,0,100);
    engine = (int)engine_mappato;
    engine = constrain(engine,0,100);

    int pressione_brake_analogico = analogRead(BRAKE_OUT_PIN); 
    float pressione_mappato = map(pressione_brake_analogico,0,1023,0,100);
    pressione = (int)pressione_brake_analogico;
    pressione = constrain(pressione,0,100); 

    float Omega = get_Omega(); // mi prendo la velocità angolare
    float Vx = get_Vx(); // mi prendo la velocità lineare 
    
    float slip_ratio_ac = ((RAGGIO_GOMMA_M*Omega)-(Vx))/(RAGGIO_GOMMA_M*Omega); //slip ratio in accelerazione, servirà per il TC
    float slip_ratio_br = ((RAGGIO_GOMMA_M*Omega)-(Vx))/(Vx); //slip ratio in frenata, servirà per l'ABS

    if(slip_ratio_ac > VALORE_IDEALE_AC){
         
        TC_cut(livelloTC,slip_ratio_ac);

    }

    if(slip_ratio_br < VALORE_IDEALE_BR){
        
        ABS_on(livelloABS,slip_ratio_br);

    }

}
