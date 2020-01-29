//zaslon
#include <TFT.h> // Hardware-specific library
#include <SPI.h>

#define CS   10
#define DC   8
#define RESET  9  

TFT ekran = TFT(CS, DC, RESET);

//senzor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

int jsButton;
int vrx;
int vry;
int xpos;
int ypos;

void setup(){
  Serial.begin(9600);

  while(!Serial);    // time to get serial running
  Serial.println(F("BME280 test"));

  unsigned status;
  //preverja, če je use okej
  status = bme.begin(0x76);  
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
      Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
      while (1);
  }
   
  ekran.begin();  
  ekran.background(0,0,0); // clears the screen
  ekran.stroke(255,0,255);
  

  pinMode(A2, INPUT);//switch na joysticku
  pinMode(A0, INPUT);//x pozicija
  pinMode(A1, INPUT);//y pozicija
  
  pinMode(5, OUTPUT); //prizge backlight na zaslonu
  digitalWrite(5, HIGH);
}

void loop(){
  vrx = analogRead(A0);
  vry = analogRead(A1);
  jsButton = analogRead(A2);

  xpos = map(vrx, 0, 1023, 0, 160);
  ypos = map(vry, 0, 1023, 0, 160);

  ekran.text("*", xpos, ypos);
    ekran.background(0, 0, 0);
}
