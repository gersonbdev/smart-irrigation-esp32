#include <WiFi.h>
#include <SPIFFS.h>
#include <PubSubClient.h>

#include "mqtt.hpp"

const char *MQTT_BROKER_ADRESS = "192.168.1.150";
uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP32Client_1";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void suscribe_mqtt()
{
        mqttClient.subscribe("hello/world");
}

String payload;
void publis_mqtt(unsigned long data)
{
        payload = "";
        payload = String(data);
        mqttClient.publish("hello/world", (char*)payload.c_str());
}

String content = "";
void on_mqtt_received(char* topic, byte* payload, unsigned int length)
{
        Serial.print("Received on ");
        Serial.print(topic);
        Serial.print(": ");

        content = "";	
        for (size_t i = 0; i < length; i++) {
                content.concat((char)payload[i]);
        }
        Serial.print(content);
        Serial.println();
}