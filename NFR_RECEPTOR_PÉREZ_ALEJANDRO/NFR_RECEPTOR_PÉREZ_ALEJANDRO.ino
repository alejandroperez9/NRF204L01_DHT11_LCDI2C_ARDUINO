#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

const int pinCE = 8;
const int pinCSN = 53;
RF24 radio(pinCE, pinCSN);

byte direccion[5] ={'c','a','n','a','l'}; 

float datos[2];

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  radio.begin();
  radio.openReadingPipe(1, direccion);
  radio.startListening();
}

void loop() {
  uint8_t numero_canal;
  if (radio.available()){
    radio.read(datos, sizeof (datos));
    
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(datos[1]);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humedad: ");
    lcd.print(datos[0]);
    lcd.print("%");

  }
}
