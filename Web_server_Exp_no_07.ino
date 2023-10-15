//Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

const char* ssid = "xxxxxxxxxxxxxxxx";         //Replace with your SSiD and Pass
const char* password = "yyyyyyyyyyyy";

DHT dht(D4, DHT11); // DHT sensor is connected to GPIO2 (D4)

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define the server routes
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  String html = "<html><body>";
  html += "<h1><center>Temperature and Humidity</center></h1>";
  html += "<p><center><h2>Temperature: " + String(temperature) + " &deg;C</h2><center></p>";
  html += "<p><center><h2>Humidity: " + String(humidity) + " %</h2><center></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}
