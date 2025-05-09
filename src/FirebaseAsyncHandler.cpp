#include "FirebaseAsyncHandler.h"

FirebaseAsyncHandler* FirebaseAsyncHandler::instance = nullptr;

FirebaseAsyncHandler::FirebaseAsyncHandler() : 
    user_auth(WEB_API_KEY, USER_EMAIL, USER_PASSWORD),
    async_client1(ssl_client1),
    async_client2(ssl_client2) {
    
    instance = this;
    
    // Configure SSL clients
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

    initializeApp(async_client1, app, getAuth(user_auth), staticProcessData, "🔐 authTask");
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);


    Serial.println("Waiting for Firebase to be ready...");
    while (!app.ready()) {
        delay(200);
    }
    // Initialize database structure
    initializeDatabaseStructure();
}

void FirebaseAsyncHandler::initializeDatabaseStructure() {
    if (dbInitialized) return;

    String esp32id = String((uint32_t)ESP.getEfuseMac(), HEX);
    String basePath = "/" + esp32id;

    // MLX Sensor
    // Database.set<bool>(async_client1, basePath + "/mlxSensor/activation", false, staticProcessData, "DB_Init");
    // delay(200); // Prevent flooding the client

    // Database.set<float>(async_client1, basePath + "/mlxSensor/ambient", 0.0, staticProcessData, "DB_Init");
    // delay(200);

    // Database.set<float>(async_client1, basePath + "/mlxSensor/object", 0.0, staticProcessData, "DB_Init");
    // delay(200);

    // Pulse Sensor
    // Database.set<bool>(async_client1, basePath + "/pulseSensor/activation", false, staticProcessData, "DB_Init");
    // delay(200);

    Database.set<float>(async_client1, basePath + "/pulseSensor/heartRateBPM", 0.0, staticProcessData, "DB_Init");
    delay(200);

    dbInitialized = true;
    Serial.println("✅ Database structure initialized under ID: " + esp32id);
}


// void FirebaseAsyncHandler::initializeDatabaseStructure() {
//     if (dbInitialized) return;

//     // Create the initial database structure
//     Database.set<bool>(async_client1, "/activation/mlxSensor", false, staticProcessData, "DB_Init");
//     Database.set<float>(async_client1, "/sensors/mlx/ambient", 0.0, staticProcessData, "DB_Init");
//     Database.set<float>(async_client1, "/sensors/mlx/object", 0.0, staticProcessData, "DB_Init");

//     Database.set<bool>(async_client1, "/activation/pulseSensor", false, staticProcessData, "DB_Init");
//     Database.set<float>(async_client1, "/sensors/pulse/heartRateBPM", 0.0, staticProcessData, "DB_Init");
    
//     dbInitialized = true;
//     Serial.println("Database structure initialized");
// }

void FirebaseAsyncHandler::uploadMLXData(float ambientTemp, float objectTemp) {
    String esp32id = String((uint32_t)ESP.getEfuseMac(), HEX);
    String basePath = "/" + esp32id;

    // Database.set<float>(async_client1, basePath + "/mlxSensor/ambient", ambientTemp, staticProcessData, "MLX_Ambient");
    // delay(200); // Prevent flooding the client

    Database.set<float>(async_client1, basePath + "/mlxSensor/object", objectTemp, staticProcessData, "MLX_Object");
    // delay(200);
}

void FirebaseAsyncHandler::monitorActivation(const String& sensorKey, std::function<void(bool)> callback) {
    activationCallback = callback;
    String path = "/activation/" + sensorKey;
    Database.get(async_client1, path, staticActivationCallback);
}

void FirebaseAsyncHandler::resetActivationStatus(const String& sensorKey) {
    String path = "/activation/" + sensorKey;
    Database.set<bool>(async_client1, path, false, staticProcessData, "Reset_Activation");
}

// Static callback handlers
void FirebaseAsyncHandler::staticProcessData(AsyncResult &aResult) {
    if (instance) {
        instance->processData(aResult);
    }
}

void FirebaseAsyncHandler::staticActivationCallback(AsyncResult &result) {
    if (instance && instance->activationCallback) {
        if (!result.isError()) {
            bool activationStatus = result.to<bool>();
            instance->activationCallback(activationStatus);
        } else {
            instance->activationCallback(false);
        }
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
    
    if (aResult.isError()) {
        Firebase.printf("Error task: %s, msg: %s, code: %d\n", 
                      aResult.uid().c_str(), 
                      aResult.error().message().c_str(), 
                      aResult.error().code());
    }
}