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

// variable to keep track of the elapsed time
// char array to print time
char printtemp[5];
char printpritisk[6];
char printvisina[6];
char printvlaga[3];
char pikica[2];

void narisiPikico();
int xpos = 0; //dej na 0
int counter = 0;

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
  // static text
  
  
  // increase font size for text in loop()
  ekran.setTextSize(1);

  pinMode(A2, INPUT);
  pinMode(5, OUTPUT); //prizge backlight na zaslonu
  digitalWrite(5, HIGH);
}

void loop(){
  String temp = String(bme.readTemperature());
  String dot = String(".");
  temp.toCharArray(printtemp, 5);
  dot.toCharArray(pikica, 2);

  int ypos = map(bme.readTemperature(), -64, 128, 0, 100);
  
  ekran.stroke(255, 255, 255);
  ekran.text("Termperatura", 0, 2);
  ekran.text(" *C", 95, 2);
  ekran.text(printtemp, 72, 2);
  ekran.text(pikica, xpos, ypos);
  Serial.println(xpos);
  

  delay(10);
 
 ekran.stroke(0, 0, 0);
 ekran.text(printtemp, 72, 2);

  if(counter % 10 == 0)//desetinka sekunde
    xpos++;
  if(xpos == 160) // dej na 128
    {
      ekran.background(0, 0, 0);
      xpos = 0;//dej na 0
    }

  counter++;
}
