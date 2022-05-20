#include <Arduino.h>
#include <WiFi.h>

#include "wifi_utilities.hpp"

const char *ssid     = "GERSON-WIFI";
const char *password = "\\(privata-reto)/";
const char *hostname = "SMART_IRRIGATION";

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void connect_wifi_sta(bool use_static_ip)
{
        Serial.println("");
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        
        if (use_static_ip)
                WiFi.config(ip, gateway, subnet);
        
        while (WiFi.status() != WL_CONNECTED) { 
                Serial.print('.');
                delay(100);  
        }
 
        Serial.print("\nStarted STA:\t");
        Serial.println(ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP());
}

void connect_wifi_ap(bool use_static_ip)
{ 
        Serial.println("");
        WiFi.mode(WIFI_AP);

        while (!WiFi.softAP(ssid, password)) {
                Serial.println(".");
                delay(100);
        }

        if (use_static_ip)
                WiFi.softAPConfig(ip, gateway, subnet);

        Serial.print("\nStarted AP:\t");
        Serial.println(ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.softAPIP());
}