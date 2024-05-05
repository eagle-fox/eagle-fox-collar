#include <WiFi.h>
#include <HTTPClient.h>
#include "App.h"
#include "HTTPClientController.h"
#include "ParseJSON.h"
#include "WifiUtils.h" // Wifi controller utils
#include "HTTPClientController.h"

const char *ssid = "MiFibra-8F98";  // Credentials for a DEVELOPMENT STAGE
const char *password = "Marsbruch133";

const int pinLED = 2;    // Wifi status LED_ESP32_INTERNAL (BLUE) (ONLY FOR DEVELOPMENT) (GPIO 5)
const int pinLED_2 = 5;  // Wifi status LED (BLUE) (ONLY FOR DEVELOPMENT) (GPIO 5)
const int pinLED_3 = 12; // Successfully LED (GREEN) (ONLY FOR DEVELOPMENT) (GPIO 12)
const int pinLED_4 = 13; // Warn LED (ORANGE) (ONLY FOR DEVELOPMENT) (GPIO 13)
const int pinBateria =35;
const int pinButton = 4; // Action Button (ONLY FOR DEVELOPMENT) (GPIO 4)

const char *serverEndpoint = "http://192.168.1.20:3000/ruta"; // Server Backend ENDPOINT (DEVELOPMENT ENDPOINT)
String hostname = "EagleFox Collar";

void setupApp()
{
  Serial.begin(115200);

  int attempts = 0;

  // Connect to Wifi <WiFi.h>
  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("WiFi Connection attempt: ");
    Serial.println(++attempts);
  }

  Serial.println("WiFi Connection Seccessfully !");

  showWifiIntense();
  showTxPower();
  Serial.println(String("Network Gateway: ") + getGatewayAddress().c_str());
  Serial.println(String("MAC: ") + getMacAddress().c_str());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  switchLED(pinLED, true);
  switchLED(pinLED_2, true);

  pinMode(pinButton, INPUT_PULLUP); 

  sendDataServer(parseJSON("data", WiFi.localIP().toString()));

  connectionTest();

}

// This function is always executed in a loop.
void loopApp()
{
  // Read the state of physical button (ONLY FOR DEVELOPMENT)
  if (digitalRead(pinButton) == LOW)
  {
    sendDataServer(parseJSON("data", WiFi.localIP().toString()));
    delay(1000);
  }

}