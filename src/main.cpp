// Proyecto realizado por José Sánchez y Paulo Valarezo.

// Librearías
#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "ThingSpeak.h"

// Datos de la red wifi a conectar
#define WIFI_SSID "TanqueAcuicola"
#define WIFI_PASSWORD "Hola12345"

// Datos en ThingSpeak
unsigned long canal = 1;
const char * myWriteAPIKey = "ISLWANNY4LU9QX94";
WiFiClient  client;

// Pines de led: conexión wifi
#define PIN_RED 27 // GIOP27
#define PIN_GREEN 26 // GIOP26
#define PIN_BLUE 25 // GIOP25

// Pines de led: funcionamiento adecuado
#define PIN_RED2 14 // GIOP14
#define PIN_GREEN2 12 // GIOP12
#define PIN_BLUE2 15 // GIOP15

// Pines de funcionamiento
#define calentador 18 // GIOP18
#define motor 21 //GIOP21

// Pines LM35
#define ADC_VREF_mV 5000.0 // en mV
#define ADC_RESOLUTION 4096.0
#define PIN_LM35 36 // GIOP36 (ADC0) 
#define PIN_LM352 39 // GIOP39 (ADC1) 

LiquidCrystal_I2C lcd0(0x27, 16, 2); // I2C dirección 0x27, 16 columnas y 2 filas

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  pinMode(PIN_RED2, OUTPUT);
  pinMode(PIN_GREEN2, OUTPUT);
  pinMode(PIN_BLUE2, OUTPUT);

  pinMode(calentador, OUTPUT);
  pinMode(motor, OUTPUT);

  Serial.begin(115200); // Inicializador del monitor serial
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Inicializador de la conexión wifi
  Serial.println("\nComenzando conexión");

  WiFi.mode(WIFI_STA);   // Configura el ESP32 como una estación Wi-Fi
  ThingSpeak.begin(client);  // Inicializador de ThingSpeak

  lcd0.init(); // Inicializador del LCD
  lcd0.backlight();
  lcd0.setCursor(0, 0);      // move cursor to   (0, 0)
  lcd0.print("Tanque Acuícola");       // print message at (0, 0)
  lcd0.setCursor(0, 1);      // move cursor to   (0, 1)
  lcd0.print("Proyecto SE"); // print message at (0, 1)
}

bool isConnected = false;
bool tempCorrecta = false;
bool oxiCorrecto = false;
int tiempoDeEspera = 10;
int tiempoDeSubida = 15;
int tempMin = 21;
int tempMax = 25;
int nivelOx = 50;

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
    Serial.println("Conectando...");
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

  int adcVal = analogRead(PIN_LM35); // lee el valor ADC del sensor de temperatura
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION); // convierte el valor ADC a mV
  float tempC = milliVolt / 10; // convierte el voltaje a temperatura en °C

  int adcVal2 = analogRead(PIN_LM352); // lee el valor ADC del sensor de temperatura
  float milliVolt2 = adcVal2 * (ADC_VREF_mV / ADC_RESOLUTION); // convierte el valor ADC a mV
  float tempC2 = milliVolt2 / 10; // convierte el voltaje a temperatura en °C

  float tempCPro = (tempC + tempC2)/2; //Promedio de temperaturas

  if(tempMin<=tempCPro<=tempMax){
    analogWrite(PIN_RED2, 255); // amarillo temperatura cálida
    analogWrite(PIN_GREEN2, 0);
    analogWrite(PIN_BLUE2, 100);
  }

  if(tempCPro<tempMin){
    analogWrite(PIN_RED2, 255); // azul temperatura baja
    analogWrite(PIN_GREEN2, 255);
    analogWrite(PIN_BLUE2, 0);
    digitalWrite(calentador, HIGH);
  }

  if(tempCPro>tempMax){
    analogWrite(PIN_RED2, 0); // rojo alta temperatura
    analogWrite(PIN_GREEN2, 255);
    analogWrite(PIN_BLUE2, 255);
    digitalWrite(calentador, LOW);
  }

  if(nivelOx < 55){
    digitalWrite(motor, HIGH);
  }else{
    digitalWrite(motor, LOW);
  }

  // Escritura en el LCD
  lcd0.clear();
  lcd0.setCursor(0,0);
  lcd0.print("Temperatura:");
  lcd0.setCursor(5,1);
  lcd0.print(String(tempCPro) + " C");

  // Subida de datos a ThingSpeak
  if(WiFi.status() == WL_CONNECTED && tiempoDeSubida==0){

    ThingSpeak.setField(1, tempCPro);
    ThingSpeak.setField(2, nivelOx);

    int x = ThingSpeak.writeFields(canal, myWriteAPIKey);
    if(x == 200 ){
      Serial.println("Canal en ThingSpeak actualizado.");
    }
    else{
      Serial.println("Problema actualizando el canal. Código de error HTTP " + String(x));
    }
    nivelOx = 50;
    tiempoDeSubida = 15;
    
  }else{
    tiempoDeSubida -=1;
    nivelOx +=1;
  }

  delay(1000);
  
}