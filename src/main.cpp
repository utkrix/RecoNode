#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char *ssid = "ekbattalalmohan";
const char *password = "mitholalmohan";

const int echoPin = 14;
const int trigPin = 2;
const int ledPin = 15; // LED for visuals

#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void blinkLED();

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, pulseIn() returns length of the pulse) in microseconds
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout of 30 milliseconds

  // Check if the duration is zero, indicating no echo was received
  if (duration == 0)
  {
    Serial.println("No pulse received within the timeout period.");
  }
  else
  {

    // Calculate the distance in cm
    distanceCm = duration * SOUND_SPEED / 2;
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");

    if (distanceCm < 20)
    {
      blinkLED();
    }
  }

  delay(800);


}

void blinkLED()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    HTTPClient http;

    client.setInsecure(); // disabling SSL certificate verification
    http.begin(client, "**YOUR NTFY URL");
    http.addHeader("Content-Type", "text/plain");
    String payload = "YOUR MESSAGE";

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}
