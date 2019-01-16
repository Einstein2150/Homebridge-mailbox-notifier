
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

void setup() {

  USE_SERIAL.begin(115200);

//Wakeup: D0 zu Reset verbinden, Wakeup dann durch Reset zu Ground
  WiFi.mode(WIFI_STA);
  USE_SERIAL.println("WIFI");
  WiFi.persistent(false);
  WiFi.forceSleepWake();//notwendig um das WLAN nach einen Tiefschlaf wieder zu aktieren
  WiFi.begin("SSID", "PASSWORD");
  
  // wait for WiFi connection
  if ((WiFi.waitForConnectResult() == WL_CONNECTED)) {
   USE_SERIAL.println("WIFI Connected");
    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin("http://HOMEBRIDGE-IP:WEBHOOKPORT/?accessoryId=sensor1&state=true");//Homebridge-Webhook

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }


  USE_SERIAL.println("deepSleeping ...");
  ESP.deepSleep(0);

}

void loop()
{
}
