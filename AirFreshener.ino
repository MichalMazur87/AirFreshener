 
#include "LowPower.h" //Library to reduce current
int sensor = A1;   //analog A1 connected to photoresistor
 
void setup() {
  Serial.begin(9600);        //init serial monitor
  Serial.println("----  Air Freshener  ----");
  pinMode(13, OUTPUT);      //output 13 LED diode - indicator
  pinMode(9, OUTPUT);       //output 9 connceted to MOSFET - splash ON 

  //test splash
  Serial.println("----  Test splash after start  ----");
  digitalWrite(13, HIGH);
  digitalWrite(9, HIGH);
  Serial.println("----  Wait 8 sec  ----");
  delay(8000); 
  Serial.println("----  Turn off splash  ----");
  digitalWrite(13, LOW);
  digitalWrite(9, LOW);
  delay(1000); 
  for ( int i=0 ; i<20 ; i++) {
    digitalWrite(13, HIGH);
    delay(30); 
    digitalWrite(13, LOW);
    delay(30); 
  };
  Serial.println("----  Starting photoresistor readings  ----");
}
 
void loop() {
  int var = analogRead(sensor);      //read A1 value
  Serial.print(var);//print A1 on monitor
  Serial.println();
  int level = 115;  //Level of photoresistor checked experimentally
  if (var > level)  //if sensor value is over this level, LED output 13 is on and splash output 9 is on
  {
    Serial.print("Over level ");
    Serial.print(level);
    Serial.print(", splash for 8 sec is on");  
    digitalWrite(13, HIGH);
    digitalWrite(9, HIGH);
    delay(8000);
    digitalWrite(13, LOW);
    digitalWrite(9, LOW);
    Serial.println("After splash deep sleep for 30 minutes");
    for ( int i=0 ; i<225 ; i++) {
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    };
  }
  else
  {
    Serial.println("Less than 115 spimy 8 sekund");
    Serial.print(level);
    Serial.print(", deep sleep 8 sec");
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  }
  Serial.println();
}
 
