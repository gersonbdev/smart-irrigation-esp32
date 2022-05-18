#include <Arduino.h>
#include <WiFi.h>

#include "esp32_utils.hpp"

extern const char *ssid;
extern const char *password;
extern const char *hostname;

extern IPAddress ip;
extern IPAddress gateway;
extern IPAddress subnet;

void connect_wifi_sta(bool use_static_ip)
{
        Serial.println("");
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        
        if (use_static_ip)
                WiFi.config(ip, gateway, subnet);
        
        while (WiFi.status() != WL_CONNECTED) { 
                delay(100);  
                Serial.print('.'); 
        }
 
        Serial.println("");
        Serial.print("Iniciado STA:\t");
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

        Serial.println("");
        Serial.print("Iniciado AP:\t");
        Serial.println(ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.softAPIP());
}