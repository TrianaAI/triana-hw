#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>

class MQTTHandler {
public:
    MQTTHandler(Client& networkClient, const char* server, uint16_t port);
    void begin();
    void loop();
    void publish(const char* topic, const char* payload);
    void subscribe(const char* topic);

private:
    PubSubClient mqttClient;
    const char* mqttServer;
    uint16_t mqttPort;

    void reconnect();
};

#endif // MQTT_HANDLER_H