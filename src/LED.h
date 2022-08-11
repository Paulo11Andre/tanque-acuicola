/*
#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

#define PIN_RED    27 // Leds wifi GIOP27 // Leds funcionamiento GIOP14
#define PIN_GREEN  26 // Leds wifi GIOP26 // Leds funcionamiento GIOP12
#define PIN_BLUE   25 // Leds wifi GIOP25 // Leds funcionamiento GIOP15

void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
}

void loop() {
  // color code #00C9CC (R = 0,   G = 201, B = 204)
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 255);
  analogWrite(PIN_BLUE,  255);

  delay(1000); // keep the color 1 second

  // color code #F7788A (R = 247, G = 120, B = 138)
  analogWrite(PIN_RED,   255);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  255);

  delay(1000); // keep the color 1 second

  // color code #34A853 (R = 52,  G = 168, B = 83)
  analogWrite(PIN_RED,   255);
  analogWrite(PIN_GREEN, 255);
  analogWrite(PIN_BLUE,  0);

  delay(1000); // keep the color 1 second
}
*/