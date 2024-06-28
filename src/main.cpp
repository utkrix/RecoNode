#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char *ssid = "** SSID HERE";
const char *password = "** PASSWORD HERE";

const int echoPin = 14;
const int trigPin = 2;
const int ledPin  = 15;// LED for visuals

#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void blinkLED(float);
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
  digitalWrite(ledPin, HIGH); // Turn on LED to visualize trigger pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(ledPin, LOW); // Turn off LED after pulse

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds
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
      blinkLED(distanceCm);
    }
  }

  // Wait a bit before next measurement
  delay(500);
}

void blinkLED(float distance)
{
  int n = 20;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  for (int i = 0; i < n; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
