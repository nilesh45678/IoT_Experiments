//Created by nilesh45678  https://github.com/nilesh45678
#include <DHT.h>  //DHT library

#define DHTPIN 2      // Digital pin connected to the DHT sensor  
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);

void setup(){ 
  Serial.begin(9600);  // Initialize Serial monitor at 9600 baud rate
  Serial.println(F("DHT11 test!"));
  dht.begin();    // Initialize DHT sensor.
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  delay(2000);
}
