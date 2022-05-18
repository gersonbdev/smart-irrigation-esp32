#ifndef mqtt_hpp
#define mqtt_hpp

void suscribe_mqtt();
void publis_mqtt(unsigned long data);
void on_mqtt_received(char* topic, byte* payload, unsigned int length);

#endif