const int startSwitchPin = 2;
const int stopSwitchPin = 3;
const int resetSwitchPin = 8;
const int potPin = 0;
const int motorPin = 9;

unsigned long previousTime = 0;

int startSwitchState = 0;
int stopSwitchState = 0;
int resetSwitchState = 0;
int potVal;

long Time;

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
  
void loop() 
{ 
// Ausgabe auf dem seriellen Monitor
  potVal = analogRead(potPin);
  Time = map(potVal, 0, 1023, 0, 600000); // Hier wird die Stellung vom Poti in Relation zur max. Zeit gesetzt
  Serial.print("eingestellte Zeit: ");
  Serial.print((Time / 1000) / 60);
  Serial.println(" min");
  
  unsigned long currentTime = millis();
  
  startSwitchState = digitalRead (2);
  stopSwitchState = digitalRead (3);
  resetSwitchState = digitalRead (8);

//Startet den Prozess
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
      
//Beendet den Prozess
  if(stopSwitchState == HIGH){
    startSwitchState = 0; //Start wird zurückgesetzt
    digitalWrite(5, LOW);//Steuerung der LEDs
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);}//Steuerung der Motors

//Prozess zurück setzen    
  if(resetSwitchState == HIGH){
    startSwitchState = 0; //START wird zurückgesetzt
    stopSwitchState = 0, //STOP wird zürückgesetzt
    digitalWrite(5, HIGH);//Steuerung der LEDs
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);}//Steuerung der Motors
}
