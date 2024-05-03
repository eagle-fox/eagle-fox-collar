#include "ParseJSON.h"

#include <Arduino.h> 

String parseJSON(const String& header, const String& value) {
  return String("{\"") + header + "\":\"" + value + "\"}";
}