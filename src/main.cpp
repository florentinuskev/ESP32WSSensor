#include <Arduino.h>

// Wrapper
#include <wrapper.h>

// WiFi Manager
#include <WiFiManager.h>
#define TRIGGER_PIN 5
#define DEEP_SLEEP_DURATION 10
int timeout = 120;
bool wm_nonblocking = true;
WiFiManager wm;

// Sensor
#include <sensor.h>

// LCD
#include <lcd.h>

// Websocket Client
#include <socket.h>
#include <WebSocketsClient.h>
WebSocketsClient webSocket;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.println("\n Starting");
  USE_SERIAL.setDebugOutput(true);

  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  if (wm_nonblocking)
    wm.setConfigPortalBlocking(false);

  wm.setConfigPortalTimeout(timeout);

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("AutoConnectAP"); // password protected ap

  if (!res)
  {
    Serial.println("Failed to connect or hit timeout");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  // Initialize Everything
  initWSConn(webSocket, "10.10.1.4", 1880, "/ws");
  initSensor();
  initLCD();
}

void checkButton()
{
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    // poor mans debounce/press-hold, code not ideal for production
    delay(50);
    if (digitalRead(TRIGGER_PIN) == LOW)
    {
      Serial.println("Button Pressed");
      // still holding button for 3000 ms, reset settings, code not ideaa for production
      delay(3000); // reset delay hold
      if (digitalRead(TRIGGER_PIN) == LOW)
      {
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }

      // start portal w delay
      Serial.println("Starting config portal");
      wm.setConfigPortalTimeout(120);

      if (!wm.startConfigPortal("OnDemandAP"))
      {
        Serial.println("failed to connect or hit timeout");
        delay(3000);
        // ESP.restart();
      }
      else
      {
        // if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
      }
    }
  }
}

void sendAndShowReading()
{
  if (webSocket.isConnected())
  {
    sensorResult res = getSensorReading();
    Serial.printf("Temperature: %.2f , Humidity: %.2f \n", res.temp, res.hum);
    showReading(res.temp, res.hum);
    String jsonMsg = toJSONStr(res);
    webSocket.sendTXT(jsonMsg);
  }
  else
  {
    sensorResult res = getSensorReading();
    Serial.printf("Temperature: %.2f , Humidity: %.2f \n", res.temp, res.hum);
    showReading(res.temp, res.hum);
  }
}

void loop()
{
  if (wm_nonblocking)
    wm.process();

  checkButton();

  // WebSocket loop
  webSocket.loop();

  asyncTimeout(sendAndShowReading, 10000);
}