#include <Arduino.h>

void setup() {
  Serial.begin(9600);               // Start der seriellen Kommunikation
}
void loop() {
  int sensorWert = analogRead(A0);  // Auslesen des aktuellen Sensorwertes
  Serial.println(sensorWert);       // Ausgabe des Wertes
  delay(10);                        // kurze Pause
}