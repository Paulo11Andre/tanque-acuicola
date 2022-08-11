/*
// Proyecto realizado por José Sánchez y Paulo Valarezo.

#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>


// Datos de la red wifi a conectar
#define WIFI_SSID "xx"
#define WIFI_PASSWORD "xx"

// Pines de led: conexión wifi
#define PIN_RED 27 // GIOP27
#define PIN_GREEN 26 // GIOP26
#define PIN_BLUE 25 // GIOP25

// Pines de led: funcionamiento adecuado
#define PIN_RED2 14 // GIOP14
#define PIN_GREEN2 12 // GIOP12
#define PIN_BLUE2 15 // GIOP15

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
bool tempCorrecta = false;
bool oxiCorrecto = false;
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

  if (tiempoDeEspera == 0 && isConnected == false){
    analogWrite(PIN_RED, 0); // LED rojo si no hay wifi
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE, 255);
    Serial.println("No hay conexión wifi");
    isConnected = true;
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
  lcd0.print(String(tempC) + " C");
  delay(1000);
  
}
*/
