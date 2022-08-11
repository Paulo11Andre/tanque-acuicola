/*
#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

//Datos de la red wifi a conectar
#define WIFI_SSID "xx"
#define WIFI_PASSWORD "xx"

// Pines de led: conexión wifi
#define PIN_RED 27 // GIOP27
#define PIN_GREEN 26 // GIOP26
#define PIN_BLUE 25 // GIOP25

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nComenzando conexión");
}

bool isConnected = false;
int tiempoDeEspera = 10;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !isConnected && tiempoDeEspera>0) {   // Entra si se realizó una conexión exitosa
    analogWrite(PIN_RED, 255);
    analogWrite(PIN_GREEN, 0); // LED verde si hay conexión wifi
    analogWrite(PIN_BLUE, 255);
    Serial.println("Conectado");
    delay(1000);
    isConnected = true;
  }

  if (WiFi.status() != WL_CONNECTED && tiempoDeEspera>0) {   // Imprimirá puntos hasta que se realice una conexión WiFi
    analogWrite(PIN_RED, 255);
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE, 0); // LED azul si se está conectando
    Serial.println(".");
    delay(1000);
    isConnected = false;
    tiempoDeEspera -=1;
  }

  if (tiempoDeEspera == 0 ){
    analogWrite(PIN_RED, 0); // LED rojo si no hay wifi
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE, 255);
    Serial.println("No hay conexión wifi");
    isConnected = true;
  }
}

*/
