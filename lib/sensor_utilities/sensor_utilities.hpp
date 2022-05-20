#ifndef sensor_utilities_hpp
#define sensor_utilities_hpp

#define Motor 25
#define ADCH 34

uint16_t acquire_humidity();
double PID(uint16_t input);
void set_motor_limit(double *motor_voltage);

#endif