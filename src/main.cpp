#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <PubSubClient.h>

#include "config.h"
#include "esp32_utils.hpp"
#include "mqtt.hpp"
#include "esp32_utils_mqtt.hpp"


void setup(void)
{
        Serial.begin(115200);
        SPIFFS.begin();

        connect_wifi_sta(true);

        init_mqtt();
}

void loop()
{
        handle_mqtt();

        publis_mqtt(1, 2);

        delay(1000);
}