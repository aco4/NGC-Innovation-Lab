// Northrop Grumman Innovation Lab
// East Coast
// December 2023

/******************************************************
 * name:Flammable Gas Detection
 * function:ignite a lighter. Then the sensor detects the gas emitted. Thus, the LED on the gas sensor and that attached to pin 13 on the SunFounder Uno board will light up. Also you can see the value at A0 and D0 printed on Serial Monitor. 
 * connection:
 * MQ-2 gas sensor            Uno R3
 * D0                         7
 * A0                         A0
 * GND                        GND
 * VCC                        5V
 *******************************************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

//https://docs.sunfounder.com/projects/sensorkit-v2-arduino/en/latest/lesson_10.html


const int ledPin = 13; //the led attach to pin13
const int analogPin = A1; //the DO on the Module attach to Pin7 on the SunFounder 
const int digitalPin = 7; //the D0 attach to pin7
int Astate = 0;
boolean Dstate = 0;

void setup() 
{
  //set the pins state 
  pinMode (digitalPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
} 

void loop()
{  
  Astate=analogRead(analogPin); //read the value of A0
  Serial.println(Astate); //print 
  Dstate=digitalRead(digitalPin); //read the value of D0
  Serial.println(Dstate); //print

  if( Dstate==HIGH ) //if the value of D0 is HIGH
  {
    digitalWrite(ledPin,LOW);//turn off the LED
  }

  if( Dstate==LOW) //else
  {
    digitalWrite(ledPin,HIGH);//turn on the LED
  }

  delay(200); //delay 200ms

}
