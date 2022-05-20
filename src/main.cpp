#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "wifi_utilities.hpp"
#include "mqtt_utilities.hpp"
#include "sensor_utilities.hpp"



void setup(void)
{
        Serial.begin(115200);

        connect_wifi_sta();

        init_mqtt();

        analogReadResolution(10);

        pinMode(ADCH, INPUT);

}

double VoltajeMotor = 0.0;

float promedio = 0.0; // promedio de humedad relativa 
float HumedadT = 0.0; //Calculo de humedad
float HumeV = 0.0;// Humedad en voltios

uint16_t humidity1_percentage;
extern double kp1, ki1, kd1;

void loop()
{       
        handle_mqtt();

        humidity1_percentage = acquire_humidity();


        HumeV = map(humidity1_percentage, 0, 100, 0, 3);

        VoltajeMotor = PID(HumeV);

        set_motor_limit(&VoltajeMotor);

        dacWrite(Motor,VoltajeMotor);  

        Serial.println(HumeV);
        Serial.print(",");
        Serial.println(VoltajeMotor);

        publish_mqtt("/smart_irrigation/humidity1_percentage", String(humidity1_percentage));
        publish_mqtt("/smart_irrigation/humidity1_pid", String(VoltajeMotor));
        publish_mqtt("/smart_irrigation/kp1_in", String(kp1*10));
        publish_mqtt("/smart_irrigation/ki1_out", String(ki1));
        publish_mqtt("/smart_irrigation/kd1_out", String(kd1));

        delay(100);
}