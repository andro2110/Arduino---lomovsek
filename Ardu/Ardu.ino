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
int counter = 0;
// char array to print time
char printtemp[5];
char printpritisk[6];
char printvisina[6];
char printvlaga[3];

int jsButt;

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
  // static text
  ekran.text("Temperatura:",0,2);
  ekran.text(" *C", 92, 2);
  
  ekran.text("Pritisk:", 0, 12);
  ekran.text(" hPa", 74, 12);

  ekran.text("Visina:", 0, 22);
  ekran.text(" m", 70, 22);

  ekran.text("Vlaznost: ", 0, 32);
  ekran.text(" %", 61, 32);
  
  // increase font size for text in loop()
  ekran.setTextSize(1);

  pinMode(A2, INPUT);
  pinMode(5, OUTPUT); //prizge backlight na zaslonu
  digitalWrite(5, HIGH);
}

void loop(){
  jsButt = analogRead(A2);
  Serial.println(jsButt);

  if(jsButt == 0)
  {
    tone(4, 500, 100);
  }
  
  values();
}

void values(){
    //zbere podatke in jih pretvori v string za vsako stvar
    String temp = String(bme.readTemperature());
    String pritisk = String(bme.readPressure() / 100.0F);
    String visina = String(bme.readAltitude(SEALEVELPRESSURE_HPA));
    String vlaga = String(bme.readHumidity());
    
    //podatke pošlje v globalno deklarirani string (char [])
    temp.toCharArray(printtemp, 5);
    pritisk.toCharArray(printpritisk, 6);
    visina.toCharArray(printvisina, 6);
    vlaga.toCharArray(printvlaga, 3);

    //napiše podatke na ekran
    ekran.stroke(255, 255, 255); //barva
    ekran.text(printtemp, 72, 2); //(spremenljivka, xpos, ypos)
    ekran.text(printpritisk, 48, 12);
    ekran.text(printvisina, 43, 22);
    ekran.text(printvlaga, 54, 32);
    
    //zbriše podatke in refresha zaslon
    delay(10);
    ekran.stroke(0, 0, 0);
    ekran.text(printtemp, 72, 2);
    ekran.text(printpritisk, 48, 12);
    ekran.text(printvisina, 43, 22);
    ekran.text(printvlaga, 54, 32);
}
