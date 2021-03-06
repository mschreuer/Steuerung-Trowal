#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>

//-------------------------------
// Display Setup
//-------------------------------
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

//-------------------------------
// Hardware Setup
//-------------------------------
const int startSwitchPin = 2;
const int stopSwitchPin = 3;
const int resetSwitchPin = 8;
const int potPin = 0;
const int motorPin = 9;

unsigned long previousTime = 0;

//Alle Taster sind beim Start vom Arduino auf null gesetzt
int startSwitchState = 0;
int stopSwitchState = 0;
int resetSwitchState = 0;
int potVal;

long Time;

//-------------------------------
// SETUP
//-------------------------------
void setup() 
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  digitalWrite(5, HIGH);
}
// Display initalisieren 
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}

//-------------------------------
// UNTERPROGRAMME
//-------------------------------

// Prozess Motor START
void ablaufStart (){

  unsigned long currentTime = millis();
  
  if(startSwitchState == HIGH){
    digitalWrite(5, LOW);//Steuerung der LEDs
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(9, HIGH);}//Steuerung der Motors
  else{
    if(currentTime - previousTime > Time){
    previousTime = currentTime;
    digitalWrite(5, HIGH);//Steuerung der LEDs
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);}}//Steuerung der Motors
}

// Prozess Motor NOTSTOP
void ablaufStop (){
  if(stopSwitchState == HIGH){
    startSwitchState = 0; //Start wird zurückgesetzt
    digitalWrite(5, LOW);//Steuerung der LEDs
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);}//Steuerung der Motors
}

// Prozess Motor RESET
void ablaufReset (){
  if(resetSwitchState == HIGH){
    startSwitchState = 0; //START wird zurückgesetzt
    stopSwitchState = 0, //STOP wird zürückgesetzt
    digitalWrite(5, HIGH);//Steuerung der LEDs
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);}//Steuerung der Motors
}

// Start-Taster bis RESET sperren


//-------------------------------
// PROGRAMMSCHLEIFE
//-------------------------------  
void loop() 
{ 
// Ausgabe auf dem seriellen Monitor
  potVal = analogRead(potPin);
  Time = map(potVal, 0, 1023, 0, 600000); // Hier wird die Stellung vom Poti in Relation zur max. Zeit gesetzt
  Serial.print("eingestellte Zeit: "); //Ausgebe der Zeit im seriellen Monitor
  Serial.print((Time / 1000) / 60); //Die Zeit wird von Millisekunden in Minuten umgerechnet
  Serial.println(" min");
  
// Die Taster werden abgefragt  
  startSwitchState = digitalRead (2);
  stopSwitchState = digitalRead (3);
  resetSwitchState = digitalRead (8);

// Die Unterprogramme werden aufgerüfen
  ablaufStart(); //Startet den Prozess 
  ablaufStop (); //Beendet den Prozess   
  ablaufReset(); //Resetet den Prozess
}
