#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

char valBuffer[8];
char btBuffer[64];
float temperature = 0.0f;
float humidity = 0.0f;
float pressure = 0.0f;

Adafruit_BME280 bme;

void setup() {
  Serial1.begin(9600);
  bool status;
  status = bme.begin();  
  if (!status) {
    Serial1.println("ERROR|ERROR");
    while (1);
  }
}

void readSensors() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0f;
}

void sendReadingsBT() {
  dtostrf(temperature,-1,2,valBuffer);
  snprintf(btBuffer,64,"env_temperature|%s\n",valBuffer);
  Serial1.print(btBuffer);
  dtostrf(humidity,-1,2,valBuffer);
  snprintf(btBuffer,64,"env_humidity|%s\n",valBuffer);
  Serial1.print(btBuffer);
  dtostrf(pressure,-1,2,valBuffer);
  snprintf(btBuffer,64,"env_pressure|%s\n",valBuffer);
  Serial1.print(btBuffer);
}

void loop() {
  readSensors();
  sendReadingsBT();
  delay(24000); 
}