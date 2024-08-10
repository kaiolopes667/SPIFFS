#include <Arduino.h>
#include "SPIFFS.h"

String red;
String green;
String blue;

const int pinRed = 26;
const int pinGreen = 16;
const int pinBlue = 27;

void setup() {
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  Serial.begin(115200);
  while (!Serial){
    delay(1000);
  }
  
  Serial.println("Initializing SPIFFS...");

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open("/rgbColor.txt");
  if (!file) {
    Serial.println("Fail to read the file");
    return;
  }
  
  Serial.println("Reading file:");

  while (file.available()) {
    String line = file.readStringUntil('\n');
    
    if (line.startsWith("vermelho=")) {
      red = line.substring(8);
      Serial.println("Red Light started");
    
      digitalWrite(pinRed, HIGH);
      delay(5000);
      digitalWrite(pinRed, LOW);
    }

    if (line.startsWith("verde=")) {
      green = line.substring(5);
      Serial.println("Green Light started");
    
      digitalWrite(pinGreen, HIGH);
      delay(5000);
      digitalWrite(pinGreen, LOW);
    }
    
    if (line.startsWith("azul=")) {
      blue = line.substring(4); 
      Serial.println("Blue Light started");
    
      digitalWrite(pinBlue, HIGH);
      delay(5000);
      digitalWrite(pinBlue, LOW);
    }
  }
  
  file.close();
  
  Serial.println("Arquivo processado.");
}

void loop() {
}
