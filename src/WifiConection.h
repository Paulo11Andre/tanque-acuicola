/*
#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

//Datos de la red wifi a conectar
#define WIFI_SSID "NETLIFE-CANO"
#define WIFI_PASSWORD "Nuria260470@"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nComenzando conexión");
}

bool isConnected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !isConnected) {
    Serial.println("Conectado");
    isConnected = true;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(1000);
    isConnected = false;
  }
}
*/
