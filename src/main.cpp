#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "mqtt_utilities.hpp"
#include "wifi_utilities.hpp"


void setup(void)
{
        Serial.begin(115200);

        connect_wifi_sta();

        init_mqtt();
}

void loop()
{       
        handle_mqtt();

        publish_mqtt("/smart_irrigation/commands",String(3.1416));

        delay(1000);
}