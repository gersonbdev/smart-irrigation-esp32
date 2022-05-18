#include <WiFi.h>
#include <SPIFFS.h>
#include <PubSubClient.h>

#include "mqtt.hpp"

const char *MQTT_BROKER_ADRESS = "192.168.1.102";
uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "ESP32Client_1";

WiFiClient espClient;
PubSubClient mqttClient1(espClient);
PubSubClient mqttClient2(espClient);

void suscribe_mqtt()
{
        mqttClient1.subscribe("hello/ucentral_1");
        mqttClient2.subscribe("hello/ucentral_2");
}

String payload1;
String payload2;

void publis_mqtt(unsigned long data1, unsigned long data2)
{
        payload1 = "";
        payload2 = "";

        payload1 = String(data1);
        payload2 = String(data2);        

        mqttClient1.publish("hello/ucentral_1", (char*)payload1.c_str());
        mqttClient2.publish("hello/ucentral_2", (char*)payload2.c_str());
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