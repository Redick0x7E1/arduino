// Program for temp/humidity sensor for bedroom. V0.1
// Created by Nick Redick
// V0.1 will display temp and humidity readouts on the LCD.

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

void setup() {
  // Starup check
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Startup OK!");
  delay(1000);
  lcd.clear();
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

  // Wait 2 minutes (120000) between reads
  delay(120000);
}
