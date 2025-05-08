// #ifndef FIREBASE_ASYNC_HANDLER_H
// #define FIREBASE_ASYNC_HANDLER_H

// #include <Arduino.h>
// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <FirebaseClient.h>
// #include <functional>

// class FirebaseAsyncHandler {
// public:
//     FirebaseAsyncHandler();
//     void begin();
//     void update();

//     // New methods to upload data for Pulse Sensor and MLX tasks
//     void uploadPulseSensorData(int bpm);
//     void uploadMLXData(float ambientTemp, float objectTemp);

//     // bool getActivationStatus(const String &sensorKey);
//     // void getActivationStatus(const String &sensorKey, std::function<void(bool)> callback);
//     // void getActivationStatus(const String &sensorKey);
//     void getActivationStatus(const String &sensorKey, std::function<void(bool)> callback);
//     static void staticActivationCallback(AsyncResult &result);

//     void resetActivationStatus(const String &sensorKey);

// private:
//     static void staticProcessData(AsyncResult &aResult);
//     void processData(AsyncResult &aResult);
//     std::function<void(bool)> activationCallback;

//     static FirebaseAsyncHandler *instancePtr;

//     UserAuth user_auth;
//     FirebaseApp app;
//     WiFiClientSecure ssl_client1, ssl_client2;
//     using AsyncClient = AsyncClientClass;
//     AsyncClient async_client1, async_client2;
//     RealtimeDatabase Database;
//     bool onetimeTest;
//     AsyncResult dbResult;
//     bool latestActivationStatus = false;

//     const String WEB_API_KEY = "AIzaSyBj1jXBSdjY7cuR6NVpBFLnDv6PW6BsD8k";
//     const String DATABASE_URL = "https://triana-29cad-default-rtdb.asia-southeast1.firebasedatabase.app/";
//     const String WIFI_SSID = "BINUS-IoT";
//     const String WIFI_PASSWORD = "Binus-10T!";
//     // const String WIFI_SSID = "saf";
//     // const String WIFI_PASSWORD = "safer123";
//     const String USER_EMAIL = "triana@triana.com";
//     const String USER_PASSWORD = "triana123";
// };

// #endif // FIREBASE_ASYNC_HANDLER_H

#ifndef FIREBASE_ASYNC_HANDLER_H
#define FIREBASE_ASYNC_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

class FirebaseAsyncHandler {
public:
    FirebaseAsyncHandler();
    void begin();
    void update();

    // Data upload methods
    void uploadTestData();
    
private:
    void processData(AsyncResult &aResult);
    static void staticProcessData(AsyncResult &aResult);
    
    // Configuration
    const char* WIFI_SSID = "BINUS-IoT";
    const char* WIFI_PASSWORD = "Binus-10T!";
    const char* WEB_API_KEY = "AIzaSyBj1jXBSdjY7cuR6NVpBFLnDv6PW6BsD8k";
    const char* DATABASE_URL = "https://triana-29cad-default-rtdb.asia-southeast1.firebasedatabase.app/";
    const char* USER_EMAIL = "triana@triana.com";
    const char* USER_PASSWORD = "triana123";

    // Firebase objects
    UserAuth user_auth;
    FirebaseApp app;
    WiFiClientSecure ssl_client1, ssl_client2;
    using AsyncClient = AsyncClientClass;
    AsyncClient async_client1, async_client2;
    RealtimeDatabase Database;
    
    // State management
    bool onetimeTest;
    AsyncResult dbResult;
    
    // Singleton instance for static callback
    static FirebaseAsyncHandler* instance;
};

#endif