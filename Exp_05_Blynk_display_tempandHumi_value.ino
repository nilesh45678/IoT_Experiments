//Create by nilesh45678

//Replace with your template ID and Auth token
#define BLYNK_TEMPLATE_ID "XXXXXXXXXXXXXXXXXXX"
#define BLYNK_TEMPLATE_NAME "---------------"
#define BLYNK_AUTH_TOKEN "YYYYYYYYYYYYYYYYYYYY"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

//Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//Your wifi credential....
char ssid[] = "xxxxxxxxxxxxxxx";
char pass[] = "yyyyyyyyyyyyyy";

// What digital pin we're connected to
#define DHTPIN 2          // Dht11 data pin connect to D4
#define DHTTYPE DHT11     
#define led 13            // Led is connect to D7
#define fan 0            // fan is connect to D3


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void dhtSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V2, t);
}

BLYNK_WRITE(V0){
  int value = param.asInt();
  value ? digitalWrite(13, HIGH) : digitalWrite(13, LOW);
  }

BLYNK_WRITE(V1){
   int value = param.asInt();
   value ? digitalWrite(0, HIGH) : digitalWrite(0, LOW);
  }

void setup()
{
  
  Serial.begin(115200);
  pinMode(0, OUTPUT);
  pinMode(13, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, dhtSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
