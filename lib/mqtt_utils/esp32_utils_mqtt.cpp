#include <WiFi.h>
#include <SPIFFS.h>
#include <PubSubClient.h>

#include "mqtt.hpp"
#include "esp32_utils_mqtt.hpp"

extern const char *MQTT_BROKER_ADRESS;
extern uint16_t MQTT_PORT;
extern const char *MQTT_CLIENT_NAME;

extern WiFiClient espClient;
extern PubSubClient mqttClient1;
extern PubSubClient mqttClient2;

void init_mqtt() 
{
        mqttClient1.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
        mqttClient2.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
        suscribe_mqtt();
        mqttClient1.setCallback(on_mqtt_received);
        mqttClient2.setCallback(on_mqtt_received);
}


void connect_mqtt()
{
        while (!mqttClient1.connected())	{		
                Serial.print("Starting MQTT connection...");

                if (mqttClient1.connect(MQTT_CLIENT_NAME)) {
                        suscribe_mqtt();
                } else {
                        Serial.print("Failed MQTT connection, rc=");
                        Serial.print(mqttClient1.state());
                        Serial.println(" try again in 5 seconds");

                        delay(5000);
                }
        }

        while (!mqttClient2.connected())	{		
                Serial.print("Starting MQTT connection...");

                if (mqttClient2.connect(MQTT_CLIENT_NAME)) {
                        suscribe_mqtt();
                } else {
                        Serial.print("Failed MQTT connection, rc=");
                        Serial.print(mqttClient2.state());
                        Serial.println(" try again in 5 seconds");

                        delay(5000);
                }
        }
}


void handle_mqtt()
{
        if (!mqttClient1.connected()) {
                connect_mqtt();
        }
        if (!mqttClient2.connected()) {
                connect_mqtt();
        }
        mqttClient1.loop();
}