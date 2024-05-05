#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <WiFi.h>
#include <Arduino.h>

bool checkWifiConnection();
void showWifiIntense();
void showTxPower();
std::string getGatewayAddress();
std::string getMacAddress();

#endif

