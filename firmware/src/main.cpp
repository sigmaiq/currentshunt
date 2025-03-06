
/*
Product         Reference Design Smart Shunt
Copyright                       sigmaIQ 2025
Date                              March 2025
Author                             Jef Brink
*/

#include <Arduino.h>
#include <Wire.h>
#include <INA228.h>


#define SDA                  GPIO_NUM_27
#define SCL                  GPIO_NUM_14 
#define LED1                 GPIO_NUM_18
#define LED2                 GPIO_NUM_22

float  maxCurrent             =     150; // AMPS
float  shuntvalue             = 0.00033; // Resistance
unsigned long updateInterval  =    1000; // mS
unsigned long timeStarted     =       0;

INA228 ina(0x40);

void setup(){

  Serial.begin(115200); // Console UART

  while (!Serial)
  {
    delay(10);
    Serial.print(".");
  }
  Serial.println(".");

  Wire.begin(SDA, SCL);
  delay(150);

  if (!ina.begin())
  {
    Serial.println("Unable to connect to INA228");
  }
  delay(250);

  ina.setMaxCurrentShunt(maxCurrent,shuntvalue);
  ina.setAccumulation(1);
}

void loop(){
  if ((millis() - timeStarted) > updateInterval) { 

   timeStarted = millis();

  Serial.print(" V=");
  Serial.print(ina.getBusVoltage(), 7);
  Serial.print(" P=");
  Serial.print(ina.getPower(), 7);
  Serial.print(" I=");
  Serial.print(ina.getCurrent(), 7);
  Serial.print(" T=");
  Serial.print(ina.getTemperature(), 7);
  Serial.print(" J=");
  Serial.print(ina.getEnergy(), 7);
  Serial.print(" C=");
  Serial.println(ina.getCharge(), 7);
  }

}
