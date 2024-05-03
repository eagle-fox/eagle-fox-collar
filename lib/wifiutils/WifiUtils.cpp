#include "WifiUtils.h"

//            INSTRUCTIONS            //
// Excellent: RSSI greater than -50 dBm
// Good: RSSI between -50 dBm and -60 dBm
// Acceptable: RSSI between -60 dBm and -70 dBm
// Weak: RSSI less than -70 dBm
void showWifiIntense() {
  int rssi = WiFi.RSSI(); 
  Serial.print("Signal strength WiFi (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}


//            INSTRUCTIONS              //
// 82: for a transmitting power of +20 dBm
// 78: for a transmit power of +17 dBm
// 74: for a transmitting power of +14 dBm
// 70: for a transmit power of +11 dBm
// 68: for a transmit power of +8 dBm
// 64: for a transmit power of +5 dBm
// 60: for a transmit power of +2 dBm
// 58: for a transmitting power of -1 dBm
// 56: for a transmit power of -2 dBm
void showTxPower() {
  int txPower = WiFi.getTxPower();
  Serial.print("Transmission power WiFi: ");
  Serial.print(txPower);
  Serial.println(" dBm");
}