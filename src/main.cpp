// Proyecto realizado por José Sánchez y Paulo Valarezo.

#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>


// Datos de la red wifi a conectar
#define WIFI_SSID "NETLIFE-CANO"
#define WIFI_PASSWORD "Nuria260470@"

// Pines de led: conexión wifi
#define PIN_RED 27 // GIOP27
#define PIN_GREEN 26 // GIOP26
#define PIN_BLUE 25 // GIOP25

// Pines de led: funcionamiento adecuado
#define PIN_RED2 14 // GIOP14
#define PIN_GREEN2 12 // GIOP12
#define PIN_BLUE2 15 // GIOP15

// Pies de funcionamiento
#define calentador 18 // GIOP18
#define motor 21 //GIOP21

// Pines LM35
#define ADC_VREF_mV 3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35 36 // GIOP36 (ADC0) connected to LM35 // otro LM35 GIOP39

LiquidCrystal_I2C lcd0(0x27, 16, 2); // I2C dirección 0x27, 16 column and 2 rows


void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  pinMode(PIN_RED2, OUTPUT);
  pinMode(PIN_GREEN2, OUTPUT);
  pinMode(PIN_BLUE2, OUTPUT);

  pinMode(calentador, OUTPUT);
  pinMode(motor, OUTPUT);

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
int tempMin = 15;
int tempMax = 30;

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

  if (tiempoDeEspera == 0 && isConnected == false){ // Entra si no hay conexión wifi
    analogWrite(PIN_RED, 0); // LED rojo si no hay wifi
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE, 255);
    Serial.println("No hay conexión wifi");
    isConnected = true;
  }

  int adcVal = analogRead(PIN_LM35); // read the ADC value from the temperature sensor
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION); // convert the ADC value to voltage in millivolt
  float tempC = milliVolt / 10; // convert the voltage to the temperature in °C
  float tempF = tempC * 9 / 5 + 32; // convert the °C to °F

  if(tempMin<=tempC<=tempMax){
    analogWrite(PIN_RED2, 255); // amarillo temperatura cálida
    analogWrite(PIN_GREEN2, 0);
    analogWrite(PIN_BLUE2, 0);
  }

  if(tempC<tempMin){
    analogWrite(PIN_RED2, 255); // azul temperatura baja
    analogWrite(PIN_GREEN2, 255);
    analogWrite(PIN_BLUE2, 0);
    //digitalWrite(calentador, HIGH);
  }

  if(tempC>tempMax){
    analogWrite(PIN_RED2, 0); // rojo alta temperatura
    analogWrite(PIN_GREEN2, 255);
    analogWrite(PIN_BLUE2, 255);
    //digitalWrite(calentador, LOW);
  }

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