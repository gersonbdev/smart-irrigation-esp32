#include <WiFi.h>
#include <SPIFFS.h>
#include <PubSubClient.h>

#include "mqtt.hpp"
#include "esp32_utils_mqtt.hpp"

extern const char *MQTT_BROKER_ADRESS;
extern uint16_t MQTT_PORT;
extern const char *MQTT_CLIENT_NAME;

extern WiFiClient espClient;
extern PubSubClient mqttClient;

void init_mqtt() 
{
        mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
        suscribe_mqtt();
        mqttClient.setCallback(on_mqtt_received);
}


void connect_mqtt()
{
        while (!mqttClient.connected())	{		
                Serial.print("Starting MQTT connection...");

                if (mqttClient.connect(MQTT_CLIENT_NAME)) {
                        suscribe_mqtt();
                } else {
                        Serial.print("Failed MQTT connection, rc=");
                        Serial.print(mqttClient.state());
                        Serial.println(" try again in 5 seconds");

                        delay(5000);
                }
        }
}


void handle_mqtt()
{
        if (!mqttClient.connected()) {
                connect_mqtt();
        }
        mqttClient.loop();
}