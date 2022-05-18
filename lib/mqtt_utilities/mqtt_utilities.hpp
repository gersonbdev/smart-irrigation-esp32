#ifndef mqtt_utilities_hpp
#define mqtt_utilities_hpp

void init_mqtt();

void connect_mqtt();

void handle_mqtt();

void publish_mqtt(const char *topic, String data);

void on_mqtt_received(char* topic, byte* payload, unsigned int length);

#endif