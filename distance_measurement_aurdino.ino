#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//                rs e d4 d5 d6  d7
//                rw gnd
#define echoPin 8 //echo pin
#define trigPin 9 //Trigger pin
float time;
float distance_cm;
float distance_in;

// setup code here it will run only once:
void setup(){
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);   // means echo pin is low, initially
  Serial.begin(9600);      // initialize serial communication
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Good Morning");
  lcd.setCursor(0,1);
  lcd.print("Prof. DN Sir");
  delay(7000);
  lcd.clear();
}

void loop(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);    //this pulse of short width will activate the trigger, and transmitter emits ultrasonic signal
  
  time = pulseIn(echoPin, HIGH); // echo pin will get high as signal reaches back receiver, time taken(in us) is stored in variable "time"
                                 
  distance_cm = (time/2) / 29.4; // distance in centimeter = (time/2)/speed of sound in microseconds per cm
  distance_in = (time/2) / 73.914; // distance in inch

  if(distance_cm < 5) {
    lcd.print("STOP !!!!");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("    Distance   ");
    
    lcd.setCursor(0, 1);
    lcd.print(distance_cm);
    lcd.print("cm  ");
    
    lcd.setCursor(9, 1);
    lcd.print(distance_in);
    lcd.print("in  ");
  }
  delay(200); // to complete the previous distance measurement, process the echo pulse, and reset its internal state before receiving the next trigger pulse
}
