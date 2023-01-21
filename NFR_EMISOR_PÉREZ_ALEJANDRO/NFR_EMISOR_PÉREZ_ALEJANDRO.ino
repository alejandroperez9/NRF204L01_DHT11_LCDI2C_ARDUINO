#include <DHT.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
#define DHTPIN 2
#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE);
 
const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);
 
byte direccion[5] ={'c','a','n','a','l'};

float datos[2];


void setup() {
  Serial.begin(9600); 
  dht.begin();
  radio.begin();
  radio.openWritingPipe(direccion);
}
 
void loop() {
  delay(5000);
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  if ( isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  datos[0] = h;
  datos[1] = t; 

  bool ok = radio.write(datos, sizeof (datos));

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");

  delay(1000);
 
}