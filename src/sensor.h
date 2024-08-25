#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino_JSON.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13 // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
// #define DHTTYPE    DHT11     // DHT 11
// #define DHTTYPE    DHT22     // DHT 22 (AM2302)
#define DHTTYPE DHT21 // DHT 21 (AM2301)

//   https://learn.adafruit.com/dht/overview

struct sensorResult
{
    float temp, hum;
};

void initSensor();
void loopSensor();
sensorResult getSensorReading();
String toJSONStr(sensorResult res);

#endif