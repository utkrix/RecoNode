#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char *ssid = "Your SSID";
const char *password = "Your Password";

// Echo and Trigger Pin Setup
const int echoPin = 14;
const int trigPin = 2;


#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void Alert();

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);
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


    // Calculate the distance in cm
    distanceCm = duration * SOUND_SPEED / 2;
    if (distanceCm < 20)
    {
      Alert();
    }

  delay(800);
  // reconnection if wifi connection is lost
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }


}

void Alert()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    HTTPClient http;

    client.setInsecure(); // disabling SSL certificate verification
    http.begin(client, "*YOUR NTFY URL");
    http.addHeader("Content-Type", "text/plain");
    String payload = "YOUR MESSAGE";

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}
