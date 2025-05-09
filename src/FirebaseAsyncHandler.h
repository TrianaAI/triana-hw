#ifndef FIREBASE_ASYNC_HANDLER_H
#define FIREBASE_ASYNC_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>
#include <functional>

class FirebaseAsyncHandler {
public:
    FirebaseAsyncHandler();
    void begin();
    void update();

    // Database setup
    void initializeDatabaseStructure();
    
    // Sensor data operations
    void uploadMLXData(float ambientTemp, float objectTemp);
    void monitorActivation(const String& sensorKey, std::function<void(bool)> callback);
    void resetActivationStatus(const String& sensorKey);
    
private:
    void processData(AsyncResult &aResult);
    static void staticProcessData(AsyncResult &aResult);
    static void staticActivationCallback(AsyncResult &result);
    
    // Configuration
    const char* WIFI_SSID = "saf";
    const char* WIFI_PASSWORD = "safer123";
    const char* WEB_API_KEY = "AIzaSyBj1jXBSdjY7cuR6NVpBFLnDv6PW6BsD8k";
    const char* DATABASE_URL = "https://triana-29cad-default-rtdb.asia-southeast1.firebasedatabase.app/";
    const char* USER_EMAIL = "triana@triana.com";
    const char* USER_PASSWORD = "triana123";

    String esp32id = String((uint32_t)ESP.getEfuseMac(), HEX);

    // Firebase objects
    UserAuth user_auth;
    FirebaseApp app;
    WiFiClientSecure ssl_client1, ssl_client2;
    using AsyncClient = AsyncClientClass;
    AsyncClient async_client1, async_client2;
    RealtimeDatabase Database;
    
    // State management
    bool dbInitialized = false;
    AsyncResult dbResult;
    std::function<void(bool)> activationCallback;
    
    static FirebaseAsyncHandler* instance;
};

#endif