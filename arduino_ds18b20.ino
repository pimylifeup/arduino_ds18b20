/*
  Arduino DS18B20

  Created: 04/20/2016
  By Gus
  Modified N/A
  By Gus

  https://arduinomylifeup.com/arduino-ds18b20-temperature-sensor
*/
#include <OneWire.h>
#include <DallasTemperature.h>

int greenLedPin = 2;           // Pin Green LED is connected to
int yellowLedPin = 3;          // Pin Yellow LED is connected to
int redLedPin = 4;             // Pin Red LED is connected to

int temp_sensor = 5;       // Pin DS18B20 Sensor is connected to

float temperature = 0;			//Variable to store the temperature in
int lowerLimit = 15;			//define the lower threshold for the temperature
int higherLimit = 35;			//define the upper threshold for the temperature

OneWire oneWirePin(temp_sensor);

DallasTemperature sensors(&oneWirePin);

void setup(void){
  Serial.begin(9600);
  
  //Setup the LEDS to act as outputs
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);
  pinMode(yellowLedPin,OUTPUT);
  
  sensors.begin();
}

void loop(){
  Serial.print("Requesting Temperatures from sensors: ");
  sensors.requestTemperatures(); 
  Serial.println("DONE");
  
  temperature = sensors.getTempCByIndex(0);
    
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  
  Serial.print("Temperature is ");
  Serial.print(temperature);
  
  //Setup the LEDS to act as outputs
  if(temperature <= lowerLimit){
    Serial.println(", Yellow LED is Activated");
    digitalWrite(yellowLedPin, HIGH);
  }
  else if(temperature > lowerLimit && temperature < higherLimit){
    Serial.println(", Green LED is Activated");
    digitalWrite(greenLedPin, HIGH);
  }
  else if(temperature >= higherLimit){
    Serial.println(", Red LED is Activated");
    digitalWrite(redLedPin, HIGH);
  }
  delay(500);
}