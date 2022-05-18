#include <WiFi.h>

#include "config.hpp"

const char *ssid     = "GERSON-WIFI";
const char *password = "\\(privata-reto)/";
const char *hostname = "ESP32_1";

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);