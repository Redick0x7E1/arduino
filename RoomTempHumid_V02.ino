// Program for temp/humidity sensor for bedroom. V0.1
// Created by Nick Redick
// V0.2 Will add LED functionality

#include "DHT.h"
#include <LiquidCrystal.h>

// Setup LCD Display pin variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// initialize LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Setup DHT input/output PIN variables
#define DHTPIN 13 // DigitalPIN 13 default val
#define DHTTYPE DHT11   // DHT 11

//initialize DHT
DHT dht(DHTPIN, DHTTYPE);

// set qucik read LED variables
// green light pin 8
int tempLED = 8;
// red light pin 9
int humidLED = 9;

void setup() {
  // Starup check
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Startup OK!");
  delay(1000);
  lcd.clear();
  // Setup LEDS
  pinMode(tempLED, OUTPUT);
  pinMode(humidLED, OUTPUT);
}

void loop() {

  // Get humidity and temp data
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Reads Celcius? needed?
  float f = dht.readTemperature(true); // Read temp as fahrenheit

// Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//    }

  // Compute head index in F(human percieved heat)
  float hif = dht.computeHeatIndex(f, h);

  // Lets print the data to the display.
  // Format: Temp <Temp>(<RTemp>) | Rtemp is hif
  //         Humidity __ %
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(round(f));
  lcd.print("F (");
  lcd.print((round(hif)));
  lcd.print("F)");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("% "); // extra space inscase humidity drops to single digit

  // if humidity out of range turn on red light.
  if (h < 30 | h > 50){
    digitalWrite(humidLED, HIGH);
  }else{
    digitalWrite(humidLED, LOW);
  }
  
  // If temp OUT OF RANGE turn off green light. 
  digitalWrite(tempLED, HIGH);
  if (hif < 64 | hif > 72){
    digitalWrite(tempLED, LOW);
  }
  // Wait 2 minutes (120000) between reads
  delay(120000);
}
