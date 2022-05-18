#include <WiFi.h>
#include <PubSubClient.h>

#include "mqtt_utilities.hpp"

const char *MQTT_BROKER_ADRESS = "192.168.1.102";//"broker.hivemq.com";
uint16_t MQTT_PORT = 1883;
const char *MQTT_CLIENT_NAME = "SMART_IRRIGATION";

WiFiClient espClient;
PubSubClient mqttClient(espClient);


void init_mqtt() 
{
        mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
        mqttClient.setCallback(on_mqtt_received);
}


void connect_mqtt()
{
        Serial.println("\nStarting connection...");

        while (!mqttClient.connected())	{
                if (mqttClient.connect(MQTT_CLIENT_NAME)) {
                        Serial.print("\nEstablished connection with:\t");
                        Serial.println(MQTT_BROKER_ADRESS);
                        Serial.print("Port:\t");
                        Serial.println(MQTT_PORT);
                        Serial.print("Client:\t");
                        Serial.println(MQTT_CLIENT_NAME);
                        
                        mqttClient.subscribe("/smart_irrigation/commands");
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


void publish_mqtt(const char *topic, String data)
{ 
        if (mqttClient.publish(topic, data.c_str())) {
                Serial.print("Posted in ");
                Serial.print(topic);
                Serial.print(":\t");
                Serial.println(data);
        }
}


String content = "";
void on_mqtt_received(char* topic, byte* payload, unsigned int length)
{
        Serial.print("Received on ");
        Serial.print(topic);
        Serial.print(":\t");

        content = "";
        for (size_t i = 0; i < length; i++) {
                content.concat((char)payload[i]);
        }

        Serial.print(content);
        Serial.println();
}
