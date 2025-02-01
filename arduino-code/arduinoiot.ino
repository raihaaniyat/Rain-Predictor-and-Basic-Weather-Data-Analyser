#include <DHT.h>

// Pin and sensor type definitions
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

const int MAX_READINGS = 5;                // Number of previous outputs to store
float temperatures[MAX_READINGS] = {0};   // Array for temperatures
float humidities[MAX_READINGS] = {0};     // Array for humidities
String rainPredictions[MAX_READINGS];     // Array for rain predictions

int currentIndex = 0;                     // Index for storing current readings

const unsigned long TIMEOUT_INTERVAL = 5000; // 5 seconds timeout
unsigned long lastDataTime = 0;              // Tracks the last successful data read

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx Test with Timeout and Array Storage!"));
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Timeout check
  if (currentMillis - lastDataTime >= TIMEOUT_INTERVAL) {
    Serial.println(F("Timeout: No data received for 5 seconds."));
    lastDataTime = currentMillis; // Reset the timeout timer
  }

  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Celsius

  // Check if any readings failed
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(2000); // Wait before trying again
    return;
  }

  // If data is valid, reset the timeout and process data
  lastDataTime = millis();

  // Store the current readings in the arrays
  temperatures[currentIndex] = t;
  humidities[currentIndex] = h;

  // Rain prediction logic
  String prediction = (t > 23 && h > 65) ? "Rain Predicted" : "No Rain Predicted";
  rainPredictions[currentIndex] = prediction;

  // Print the current reading
  Serial.println(F("Current Reading:"));
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C, Humidity: "));
  Serial.print(h);
  Serial.print(F("%, Prediction: "));
  Serial.println(prediction);

  // Print the past readings
  Serial.println(F("\nPrevious Readings:"));
  for (int i = 0; i < MAX_READINGS; i++) {
    Serial.print(F("Reading "));
    Serial.print(i + 1);
    Serial.print(F(": Temp: "));
    Serial.print(temperatures[i]);
    Serial.print(F("°C, Hum: "));
    Serial.print(humidities[i]);
    Serial.print(F("%, Prediction: "));
    Serial.println(rainPredictions[i]);
  }
  Serial.println(F("--------------------------"));

  // Update the index for the next reading
  currentIndex = (currentIndex + 1) % MAX_READINGS; // Wrap around to 0 after reaching MAX_READINGS

  // Wait before the next reading
  delay(2000);
}