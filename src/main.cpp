#include <Arduino.h>
#include <Wire.h>
// #include <Adafruit_MiniMLX90614.h>

// Include the Adafruit MLX90614 library
#include <Adafruit_MLX90614.h>

// Create an instance of the MLX90614 sensor
// Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // Create an instance of the MLX90614 sensor

// void setup() {
//   // Initialize serial communication at 115200 baud rate
//   Serial.begin(115200);
//   Wire.begin(8, 9); // Initialize I2C with SDA on pin 8 and SCL on pin 9

//   // Initialize the MLX90614 sensor
//   if (!mlx.begin()) {
//     Serial.println("Error initializing MLX90614 sensor!");
//     while (1); // Halt execution if initialization fails
//   }
// }

// void loop() {
//   // Read the ambient temperature in Celsius
//   double ambientTempC = mlx.readAmbientTempC();
//   // Read the object temperature in Celsius
//   double objectTempC = mlx.readObjectTempC();

//   // Print the temperatures to the serial monitor
//   Serial.print("Ambient Temperature: ");
//   Serial.print(ambientTempC);
//   Serial.println(" °C");

//   Serial.print("Object Temperature: ");
//   Serial.print(objectTempC);
//   Serial.println(" °C");

//   // Wait for a second before the next reading
//   delay(1000);
// }

#include "MAX30105.h"

#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

void loop()
{
  static unsigned long noFingerStart = 0; // Track when no finger is detected
  long irValue = particleSensor.getIR();

  // Only proceed if a finger is detected (IR value above threshold)
  if (irValue > 50000)
  {
    if (checkForBeat(irValue) == true)
    {
      // We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
        rateSpot %= RATE_SIZE; // Wrap variable

        // Take average of readings
        beatAvg = 0;
        for (byte x = 0; x < RATE_SIZE; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
      noFingerStart = 0; // Reset no-finger timer when a beat is detected
    }

    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);
  }
  else
  {
    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(" No finger?");
    if (noFingerStart == 0)
    {
      noFingerStart = millis(); // Start the no-finger timer
    }
    else if (millis() - noFingerStart > 2000)
    {
      // Reset values after 2 seconds of no finger detected
      beatsPerMinute = 0;
      beatAvg = 0;
    }
  }

  Serial.println();
}