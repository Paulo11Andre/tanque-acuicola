/*
Proyecto realizado por José Sánchez y Paulo Valarezo.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>


// Datos de la red wifi a conectar
#define WIFI_SSID "xxxx"
#define WIFI_PASSWORD "xxxx"

// Pines de led: conexión wifi
#define PIN_RED 27 // GIOP27
#define PIN_GREEN 25 // GIOP25
#define PIN_BLUE 26 // GIOP26

// Pines LM35
#define ADC_VREF_mV 3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35 36 // GIOP36 (ADC0) connected to LM35

LiquidCrystal_I2C lcd0(0x27, 16, 2); // I2C dirección 0x27, 16 column and 2 rows


void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  Serial.begin(9600); // Inicializador del monitor serial
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Inicializador de la conexión wifi
  Serial.println("\nComenzando conexión");

  lcd0.init(); // Inicializador del lcd
  lcd0.backlight();
  lcd0.setCursor(0, 0);      // move cursor to   (0, 0)
  lcd0.print("Hola Mundo");       // print message at (0, 0)
  lcd0.setCursor(0, 1);      // move cursor to   (0, 1)
  lcd0.print("Proyecto"); // print message at (0, 1)
}

bool isConnected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !isConnected) {   // Entra si se realizó una conexión exitosa
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_GREEN, 255); // LED verde si hay conexión wifi
    analogWrite(PIN_BLUE, 0);
    Serial.println("Conectado");
    delay(1000);
    isConnected = true;
  }

  if (WiFi.status() != WL_CONNECTED) {   // Imprimirá puntos hasta que se realice una conexión WiFi
    analogWrite(PIN_RED, 0);
    analogWrite(PIN_GREEN, 0);
    analogWrite(PIN_BLUE, 255); // LED azul si se está conectando
    Serial.println(".");
    delay(1000);
    isConnected = false;
  }

  // read the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  float tempC = milliVolt / 10;
  // convert the °C to °F
  float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
  Serial.print("Temperatura: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  "); // separator between °C and °F
  Serial.print(tempF);   // print the temperature in °F
  Serial.println("°F");

  lcd0.clear();
  lcd0.setCursor(0,0);
  lcd0.print("Temperatura:");
  lcd0.setCursor(5,1);
  lcd0.print(String(tempC) + "C");
  delay(1500);
  
}
 
