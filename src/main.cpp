#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include "MLX90614Handler.h"
#include "PulseSensorHandler.h"

// BLE UUIDs
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;

// Sensor Handlers
MLX90614Handler mlxHandler;
PulseSensorHandler pulseSensorHandler;

// BLE Server Callbacks
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.println("Device connected");
        BLEDevice::startAdvertising(); // Still allow new connections
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("Device disconnected");
        BLEDevice::startAdvertising(); // Re-advertise for reconnection
    }
};

// BLE Write/Notify Callbacks
class MyCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.empty()) return;

        String command = String(value.c_str());
        command.trim();

        Serial.print("Received BLE command: ");
        Serial.println(command);

        String response;

        if (command == "start pulse") {
            pulseSensorHandler.update();
            response = String(pulseSensorHandler.update());
        } else if (command == "start mlx") {
            mlxHandler.update();
            response = String(mlxHandler.update());
        } else {
            response = "Unknown command: " + command;
        }

        // Send response back over BLE
        pCharacteristic->setValue(response.c_str());
        pCharacteristic->notify();
        Serial.println("Sent response over BLE");
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE + Sensor Server...");

    // Init sensors
    mlxHandler.begin();
    pulseSensorHandler.begin();

    // Init BLE
    BLEDevice::init("ESP32_BLE_Device");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_WRITE_NR
    );

    pCharacteristic->addDescriptor(new BLE2902());
    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

    pCharacteristic->setValue("Ready for commands");
    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    BLEDevice::startAdvertising();

    Serial.println("BLE Server started and advertising");
}

void loop() {
    // Nothing here, handled via callbacks
    delay(1000);
}
