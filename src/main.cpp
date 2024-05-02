#include <WiFi.h>
#include <HTTPClient.h>
#include "./interfaces/LEDControl.h" // Cotroller for pin led alerts
#include "./interfaces/ParseJSON.h"
#include "./interfaces/WifiUtils.h" // Wifi controller utils
#include "./interfaces/HTTPClientController.h"

// Note: For the battery-powered system, you cannot use the (3V3)
// connector, you must use the (VIN) connector which accepts a variable
// voltage. You have to do it this way because the batteries never
// deliver the voltage they set, it varies with time and battery life.

// Wifi connection credentials (Testing credentials)
const char *ssid = "MiFibra-8F98";
const char *password = "Marsbruch133";

const int pinLED = 2;    // Wifi status LED_ESP32_INTERNAL (BLUE) (ONLY FOR DEVELOPMENT) (GPIO 5)
const int pinLED_2 = 5;  // Wifi status LED (BLUE) (ONLY FOR DEVELOPMENT) (GPIO 5)
const int pinLED_3 = 12; // Successfully LED (GREEN) (ONLY FOR DEVELOPMENT) (GPIO 12)
const int pinLED_4 = 13; // Warn LED (ORANGE) (ONLY FOR DEVELOPMENT) (GPIO 13)
const int pinButton = 4; // Action Button (ONLY FOR DEVELOPMENT) (GPIO 4)

const char *serverEndpoint = "http://192.168.1.20:3000/ruta"; // Server Backend ENDPOINT (DEVELOPMENT ENDPOINT)
String hostname = "EagleFox Collar";

void setup()
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

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  switchLED(pinLED, true);
  switchLED(pinLED_2, true);

  pinMode(pinButton, INPUT_PULLUP); 

  sendDataServer(parseJSON("data", WiFi.localIP().toString()));

  connectionTest();
}

// This function is always executed in a loop.
void loop()
{

  // Read the state of physical button (ONLY FOR DEVELOPMENT)
  if (digitalRead(pinButton) == LOW)
  {
    sendDataServer(parseJSON("data", WiFi.localIP().toString()));
    delay(1000);
  }
}

