#include <Arduino.h>

#include "sensor_utilities.hpp"

// Ganancias PID;
double kp1 = 0.5, ki1 = 2.0, kd1 = 0;
// Variable Humedad y humedad  deseada
float  setPoint = 1.0; ///// SET POINT HUMEDAD 2VOlITOS
// Variables PID
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError, cumError, rateError;
double outPut;



uint16_t acquire_humidity()
{
        uint16_t sensor_reading = 0;
        
        sensor_reading = map(analogRead(ADCH), 0, 1023, 100, 0);

        return sensor_reading;
}

double PID(uint16_t input)
{ 
        // Se guarda el tempo actual 
        currentTime = millis();
        // Se calcula el tiempo transcurrido
        elapsedTime = currentTime - previousTime;

        // Se obtiene el error de posición
        error = setPoint - input;
        // Se calcula la integral del error
        cumError += error * elapsedTime;
        // Se calcula la derivada del error
        rateError = (error - lastError) / elapsedTime;
        // Se calcula la salida del controlador
        outPut = kp1 * error + ki1 * cumError + kd1 * rateError;

        // El error actual se convierte en el error pasado
        lastError = error;
        // El tiempo actual se convierte en el tiempo pasado
        previousTime = currentTime;

        // Se regresa la salida del controlador
        return outPut;
}


void set_motor_limit(double *motor_voltage)
{ 
        // Si la humedad pasa de 3.3V -> rrango maximo que la menternga en 3.3
        if (*motor_voltage > 3.3) {
                *motor_voltage = 3.3;
        } else if (*motor_voltage < 0) {
                *motor_voltage = 0.1;
        }
}