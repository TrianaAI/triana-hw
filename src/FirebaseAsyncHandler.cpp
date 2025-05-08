// #include "FirebaseAsyncHandler.h"

// // Initialize static pointer
// FirebaseAsyncHandler* FirebaseAsyncHandler::instancePtr = nullptr;

// FirebaseAsyncHandler::FirebaseAsyncHandler()
//     : user_auth(WEB_API_KEY, USER_EMAIL, USER_PASSWORD),
//       async_client1(ssl_client1),
//       async_client2(ssl_client2),
//       onetimeTest(false) 
//       {
//     instancePtr = this;  // Assign the static instance pointer
//     ssl_client1.setInsecure();
//     ssl_client2.setInsecure();
//     ssl_client1.setTimeout(1000);
//     ssl_client1.setHandshakeTimeout(5);
//     ssl_client2.setTimeout(1000);
//     ssl_client2.setHandshakeTimeout(5);
// }

// // void FirebaseAsyncHandler::begin() {
// //     Serial.begin(115200);

// //     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

// //     Serial.print("Connecting to Wi-Fi");
// //     while (WiFi.status() != WL_CONNECTED) {
// //         Serial.print(".");
// //         delay(300);
// //     }
// //     Serial.println();
// //     Serial.print("Connected with IP: ");
// //     Serial.println(WiFi.localIP());
// //     Serial.println();

// //     ssl_client1.setInsecure();
// //     ssl_client2.setInsecure();

// //     ssl_client1.setTimeout(1000);
// //     ssl_client1.setHandshakeTimeout(5);
// //     ssl_client2.setTimeout(1000);
// //     ssl_client2.setHandshakeTimeout(5);

// //     // ✅ Use static method as callback
// //     // initializeApp(async_client1, app, getAuth(user_auth), staticProcessData, "🔐 authTask");

// //      // 3. Get auth reference before initializing app
// //      auto& auth = getAuth(user_auth);

// //      // 4. Initialize Firebase
// //      initializeApp(async_client1, app, auth, staticProcessData, "🔐 authTask");

// //     // check auth status
// //     // if (user_auth.isAuthenticated()) {
// //     //     Serial.println("User authenticated successfully.");
// //     // } else {
// //     //     Serial.printf("Authentication failed: %s\n", user_auth.error().message().c_str());
// //     // }

// //     app.getApp<RealtimeDatabase>(Database);

// //     Database.url(DATABASE_URL);
// // }

// void FirebaseAsyncHandler::begin() {
//     Serial.begin(115200);
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//     Serial.print("Connecting to Wi-Fi");
//     while (WiFi.status() != WL_CONNECTED) {
//         Serial.print(".");
//         delay(300);
//     }
//     Serial.println();
//     Serial.print("Connected with IP: ");
//     Serial.println(WiFi.localIP());
//     Serial.println();

//     // Initialize Firebase - CRITICAL: Must use staticProcessData here
//     initializeApp(async_client1, app, getAuth(user_auth), staticProcessData, "🔐 authTask");

//     // Wait for authentication
//     unsigned long startTime = millis();
//     while (!app.ready() && millis() - startTime < 10000) {
//         app.loop();
//         delay(100);
//     }

//     if (!app.ready()) {
//         Serial.println("Failed to initialize Firebase");
//         return;
//     }

//     app.getApp<RealtimeDatabase>(Database);
//     Database.url(DATABASE_URL);
// }

// // void FirebaseAsyncHandler::update() {
// //     app.loop();

// //     if (app.ready() && !onetimeTest) {
// //         onetimeTest = true;

// //         Database.set<String>(async_client1, "/examples/BareMinimum/data/set1", "test", staticProcessData, "RealtimeDatabase_SetTask");

// //         Database.set<bool>(async_client1, "/examples/BareMinimum/data/set2", false, dbResult);

// //         bool status = Database.set<double>(async_client2, "/examples/BareMinimum/data/set3", 129.329837492803);
// //         if (status)
// //             Serial.println("Value set complete.");
// //         else
// //             Firebase.printf("Error, msg: %s, code: %d\n", async_client2.lastError().message().c_str(), async_client2.lastError().code());

// //         Database.get(async_client1, "/examples/BareMinimum/data/set1", staticProcessData, false, "RealtimeDatabase_GetTask");

// //         Database.get(async_client1, "/examples/BareMinimum/data/set2", dbResult, false);

// //         String value = Database.get<String>(async_client2, "/examples/BareMinimum/data/set3");
// //         if (async_client2.lastError().code() == 0) {
// //             Serial.println("Value get complete.");
// //             Serial.println(value);
// //         } else
// //             Firebase.printf("Error, msg: %s, code: %d\n", async_client2.lastError().message().c_str(), async_client2.lastError().code());
// //     }

// //     processData(dbResult);
// // }

// void FirebaseAsyncHandler::update() {
//     app.loop();

//     if (app.ready() && !onetimeTest) {
//         onetimeTest = true;
        
//         // Test operations
//         Database.set<String>(async_client1, "/test/path", "hello", staticProcessData, "testTask");
//     }
// }


// // // Static wrapper
// // void FirebaseAsyncHandler::staticProcessData(AsyncResult &aResult) {
// //     Serial.println("staticProcessData called"); // Add this
// //     if (instancePtr != nullptr) {
// //         instancePtr->processData(aResult);
// //     }
// // }

// // // Actual member function
// // void FirebaseAsyncHandler::processData(AsyncResult &aResult) {
// //     if (!aResult.isResult())
// //         return;

// //     if (aResult.isEvent())
// //         Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.eventLog().message().c_str(), aResult.eventLog().code());

// //     if (aResult.isDebug())
// //         Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());

// //     if (aResult.isError())
// //         Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());

// //     if (aResult.available())
// //         Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
// // }

// void FirebaseAsyncHandler::staticProcessData(AsyncResult &aResult) {
//     if (instancePtr) {
//         instancePtr->processData(aResult);
//     }
// }

// void FirebaseAsyncHandler::processData(AsyncResult &aResult) {
//     if (!aResult.isResult()) return;

//     if (aResult.isEvent()) {
//         Firebase.printf("Event task: %s, msg: %s, code: %d\n", 
//                       aResult.uid().c_str(), 
//                       aResult.eventLog().message().c_str(), 
//                       aResult.eventLog().code());
//     }

//     if (aResult.isDebug()) {
//         Firebase.printf("Debug task: %s, msg: %s\n", 
//                       aResult.uid().c_str(), 
//                       aResult.debug().c_str());
//     }

//     if (aResult.isError()) {
//         Firebase.printf("Error task: %s, msg: %s, code: %d\n", 
//                       aResult.uid().c_str(), 
//                       aResult.error().message().c_str(), 
//                       aResult.error().code());
//     }

//     if (aResult.available()) {
//         Firebase.printf("task: %s, payload: %s\n", 
//                       aResult.uid().c_str(), 
//                       aResult.c_str());
//         }
//     }

// void FirebaseAsyncHandler::uploadPulseSensorData(int bpm) {
//     String path = "/sensors/pulse";
//     bool status = Database.set<int>(async_client1, path, bpm);
//     if (status) {
//         Serial.println("Pulse sensor data uploaded successfully.");
//     } else {
//         Firebase.printf("Error uploading pulse sensor data: %s\n", async_client1.lastError().message().c_str());
//     }
// }

// void FirebaseAsyncHandler::uploadMLXData(float ambientTemp, float objectTemp) {
//     String ambientPath = "/sensors/mlx/ambient";
//     String objectPath = "/sensors/mlx/object";

//     bool ambientStatus = Database.set<float>(async_client1, ambientPath, ambientTemp);
//     if (ambientStatus) {
//         Serial.println("Ambient temperature uploaded successfully.");
//     } else {
//         Firebase.printf("Error uploading ambient temperature: %s\n", async_client1.lastError().message().c_str());
//     }

//     bool objectStatus = Database.set<float>(async_client1, objectPath, objectTemp);
//     if (objectStatus) {
//         Serial.println("Object temperature uploaded successfully.");
//     } else {
//         Firebase.printf("Error uploading object temperature: %s\n", async_client1.lastError().message().c_str());
//     }
// }

// // bool FirebaseAsyncHandler::getActivationStatus(const String &sensorKey) {
// //     String path = "/activation/" + sensorKey;
// //     bool status = Database.get<bool>(async_client1, path);
// //     if (async_client1.lastError().code() != 0) {
// //         Firebase.printf("Error getting activation status for %s: %s\n", sensorKey.c_str(), async_client1.lastError().message().c_str());
// //     }
// //     return status;
// // }

// void FirebaseAsyncHandler::getActivationStatus(const String &sensorKey, std::function<void(bool)> callback) {
//     activationCallback = callback;
//     String path = "/activation/" + sensorKey;
//     Database.get(async_client1, path, staticActivationCallback);
// }


// void FirebaseAsyncHandler::staticActivationCallback(AsyncResult &result) {
//     if (!result.isError()) {
//         bool activationStatus = result.to<bool>();
//         if (instancePtr && instancePtr->activationCallback)
//             instancePtr->activationCallback(activationStatus);
//     } else {
//         Serial.printf("Activation status error: %s\n", result.error().message().c_str());
//         if (instancePtr && instancePtr->activationCallback)
//             instancePtr->activationCallback(false); // default to false if failed
//     }
// }


// void FirebaseAsyncHandler::resetActivationStatus(const String &sensorKey) {
//     String path = "/activation/" + sensorKey;
//     bool status = Database.set<bool>(async_client1, path, false);
//     if (!status) {
//         Firebase.printf("Error resetting activation status for %s: %s\n", sensorKey.c_str(), async_client1.lastError().message().c_str());
//     }
// }


#include "FirebaseAsyncHandler.h"

FirebaseAsyncHandler* FirebaseAsyncHandler::instance = nullptr;

FirebaseAsyncHandler::FirebaseAsyncHandler() : 
    user_auth(WEB_API_KEY, USER_EMAIL, USER_PASSWORD),
    async_client1(ssl_client1),
    async_client2(ssl_client2),
    onetimeTest(false) {
    
    instance = this;
    
    // Configure SSL clients (same as working example)
    ssl_client1.setInsecure();
    ssl_client2.setInsecure();
    ssl_client1.setTimeout(1000);
    ssl_client1.setHandshakeTimeout(5);
    ssl_client2.setTimeout(1000);
    ssl_client2.setHandshakeTimeout(5);
}

void FirebaseAsyncHandler::begin() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // Initialize Firebase (identical to working example)
    initializeApp(async_client1, app, getAuth(user_auth), staticProcessData, "🔐 authTask");

    // Set up database (identical to working example)
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);
}

void FirebaseAsyncHandler::update() {
    app.loop();

    // Identical test operations to working example
    if (app.ready() && !onetimeTest) {
        onetimeTest = true;

        Database.set<String>(async_client1, "/examples/BareMinimum/data/set1", "test skjdfkslajl", staticProcessData, "RealtimeDatabase_SetTask");
        Database.set<bool>(async_client1, "/examples/BareMinimum/data/set2", false, dbResult);
        
        bool status = Database.set<double>(async_client2, "/examples/BareMinimum/data/set3", 23498.9034832);
        if (status) {
            Serial.println("Value set complete.");
        } else {
            Firebase.printf("Error, msg: %s, code: %d\n", async_client2.lastError().message().c_str(), async_client2.lastError().code());
        }

        Database.get(async_client1, "/examples/BareMinimum/data/set1", staticProcessData, false, "RealtimeDatabase_GetTask");
        Database.get(async_client1, "/examples/BareMinimum/data/set2", dbResult, false);

        String value = Database.get<String>(async_client2, "/examples/BareMinimum/data/set3");
        if (async_client2.lastError().code() == 0) {
            Serial.println("Value get complete.");
            Serial.println(value);
        } else {
            Firebase.printf("Error, msg: %s, code: %d\n", async_client2.lastError().message().c_str(), async_client2.lastError().code());
        }
    }

    processData(dbResult);
}

void FirebaseAsyncHandler::staticProcessData(AsyncResult &aResult) {
    if (instance) {
        instance->processData(aResult);
    }
}

void FirebaseAsyncHandler::processData(AsyncResult &aResult) {
    if (!aResult.isResult()) return;
    
    if (aResult.isEvent()) {
        Firebase.printf("Event task: %s, msg: %s, code: %d\n", 
                      aResult.uid().c_str(), 
                      aResult.eventLog().message().c_str(), 
                      aResult.eventLog().code());
    }
    
    if (aResult.isDebug()) {
        Firebase.printf("Debug task: %s, msg: %s\n", 
                      aResult.uid().c_str(), 
                      aResult.debug().c_str());
    }
    
    if (aResult.isError()) {
        Firebase.printf("Error task: %s, msg: %s, code: %d\n", 
                      aResult.uid().c_str(), 
                      aResult.error().message().c_str(), 
                      aResult.error().code());
    }
    
    if (aResult.available()) {
        Firebase.printf("task: %s, payload: %s\n", 
                      aResult.uid().c_str(), 
                      aResult.c_str());
    }
}