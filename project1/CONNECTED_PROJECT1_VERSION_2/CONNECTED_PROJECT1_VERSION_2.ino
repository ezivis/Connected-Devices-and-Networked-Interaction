#include <ArduinoBLE.h>
#include "RTClib.h"
#include "gammaCorrection.h"
#include <FastLED.h>
#define NUM_LEDS 120

RTC_Millis rtc;
DateTime now;

CRGBArray<NUM_LEDS> leds_h;
CRGBArray<NUM_LEDS> leds_m;
CRGBArray<NUM_LEDS> leds_s;

int h = 0;
int m = 0;
int s = 0;
int r[100];
int g[100];
int b[100];
int counter = 0;
int Reset = 4;
int pres = 0;
int prem = 0;
int preh = 0;
int precounter = 0;

CRGB color_h = CRGB(140, 255, 200);
CRGB color_m = CRGB(gamma8[27], gamma8[42], gamma8[60]);
CRGB color_s = CRGB(gamma8[240], gamma8[148], gamma8[56]);

unsigned long previousMillis;


BLEService ledService("26b68f48-bddc-42fa-8a03-38be7b2bfc6e");

BLEUnsignedIntCharacteristic switchCharacteristic("26b68f48-bddc-42fa-8a03-38be7b2bfc6e", BLERead | BLEWrite);

void setup() {
  digitalWrite(Reset, HIGH);
  delay(200);
  pinMode(Reset, OUTPUT);
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, 2>(leds_s, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 7>(leds_m, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 9>(leds_h, NUM_LEDS);

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  now = rtc.now() + TimeSpan(0, 0, 0, 11);
  h = now.hour() % 12;
  m = now.minute();
  s = now.second();
  Serial.print(h, DEC);
  Serial.print(':');
  Serial.print(m, DEC);
  Serial.print(':');
  Serial.print(s, DEC);
  Serial.println();

  static uint8_t brightness = 255;
  for (int i = s * 2; i > s * 2 - 5; i--) {
    brightness -= 50;
    leds_s[i % NUM_LEDS] = color_s;
  }
  brightness = 150;
  for (int j = m * 2; j > m * 2 - 5; j--) {
    brightness -= 30;
    leds_m[j % NUM_LEDS] = color_m;
  }
  FastLED.show();


  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }


  BLE.setLocalName("CLOCK");
  BLE.setAdvertisedService(ledService);

  ledService.addCharacteristic(switchCharacteristic);

  BLE.addService(ledService);

  // assign event handlers for connected, disconnected to peripheral
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);


  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println(("Bluetooth device active, waiting for connections..."));
}

void loop() {
  BLE.poll();

  now = rtc.now() + TimeSpan(0, 0, 0, 11);
  h = now.hour() % 12;
  m = now.minute();
  s = now.second();

  if (m != prem) {
    for (int j = m * 2 ; j > m * 2 - 5; j--) {
      leds_m[(j + 120) % NUM_LEDS] = color_m;
    }
    for (int j = m * 2 - 5 ; j > m * 2 - 8; j--) {
      leds_m[(j + 120) % NUM_LEDS] = CRGB::Black;
    }
    FastLED.show();
    prem = m;
  }

  if (s != pres) {
    for (int i = s * 2 ; i > s * 2 - 5; i--) {
      leds_s[(i + 120) % NUM_LEDS] = color_s;
    }
    for (int i = s * 2 - 5 ; i > s * 2 - 8; i--) {
      leds_s[(i + 120) % NUM_LEDS] = CRGB::Black;
    }
    FastLED.show();
    pres = s;
  }
}

void blePeripheralConnectHandler(BLEDevice central) {
  for (int i = 0; i < 121; i++) {
    leds_s[i % NUM_LEDS] = CRGB::Green;
  }
  FastLED.show();
  delay(200);//milles
  for (int i = 0; i < 121; i++) {
    leds_s[i % NUM_LEDS] = CRGB::Black;
  }
  FastLED.show();
  delay(200);

  for (int i = 0; i < 121; i++) {
    leds_s[i % NUM_LEDS] = CRGB::Green;
  }
  FastLED.show();
  delay(200);
  for (int i = 0; i < 121; i++) {
    leds_s[i % NUM_LEDS] = CRGB::Black;
  }
  FastLED.show();
  /////////////////////////////////////////////////////////////////////////////////////////////////
  now = rtc.now() + TimeSpan(0, 0, 0, 11);
  h = now.hour() % 12;
  m = now.minute();
  s = now.second();
  if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {
  if (counter != precounter) {
    for (int i = s * 2 ; i > s * 2 - 5; i--) {
      leds_s[(i + 120) % NUM_LEDS] = color_s;
    }

    for (int i = s * 2 - 5 ; i > s * 2 - 8; i--) {
      leds_s[(i + 120) % NUM_LEDS] = CRGB::Black;
    }

    for (int j = m * 2 ; j > m * 2 - 5; j--) {
      leds_m[(j + 120) % NUM_LEDS] = color_m;
    }

    for (int j = m * 2 - 5 ; j > m * 2 - 8; j--) {
      leds_m[(j + 120) % NUM_LEDS] = CRGB::Black;
    }

    FastLED.show();
    precounter = counter;
    Serial.println(" second is");
    Serial.println(s);
    Serial.println(" precounter = counte");
  }
 }
}

  if (m != prem) {
    for (int j = m * 2 ; j > m * 2 - 5; j--) {
      leds_m[(j + 120) % NUM_LEDS] = color_m;
    }
    for (int j = m * 2 - 5 ; j > m * 2 - 8; j--) {
      leds_m[(j + 120) % NUM_LEDS] = CRGB::Black;
    }
    FastLED.show();
    prem = m;
  }

  if (s != pres) {
    for (int i = s * 2 ; i > s * 2 - 5; i--) {
      leds_s[(i + 120) % NUM_LEDS] = color_s;
    }
    for (int i = s * 2 - 5 ; i > s * 2 - 8; i--) {
      leds_s[(i + 120) % NUM_LEDS] = CRGB::Black;
    }
    FastLED.show();
    pres = s;
  }
}

void blePeripheralDisconnectHandler(BLEDevice central) {
//  for (int i = 0; i < 121; i++) {
//    leds_s[i % NUM_LEDS] = CRGB::Red;
//  }
//  FastLED.show();
//  delay(200);//milles
//  for (int i = 0; i < 121; i++) {
//    leds_s[i % NUM_LEDS] = CRGB::Black;
//  }
//  FastLED.show();
//  delay(200);
//
//  for (int i = 0; i < 121; i++) {
//    leds_s[i % NUM_LEDS] = CRGB::Red;
//  }
//  FastLED.show();
//  delay(200);
//  for (int i = 0; i < 121; i++) {
//    leds_s[i % NUM_LEDS] = CRGB::Black;
//  }
//  FastLED.show();
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    if (counter < 4) {
      int rgbx = switchCharacteristic.value();
      int red = rgbx % 256;
      r[counter] = red;
      rgbx >>= 8;
      int green = rgbx % 256;
      g[counter] = green;
      rgbx >>= 8;
      int blue = rgbx % 256;
      b[counter] = blue;

      Serial.println("RGBX");
      Serial.println(switchCharacteristic.value());

      Serial.print("1RGB");
      Serial.print(r[0]);
      Serial.print(",");
      Serial.print(g[0]);
      Serial.print(",");
      Serial.println(b[0]);

      Serial.print("2RGB");
      Serial.print(r[1]);
      Serial.print(",");
      Serial.print(g[1]);
      Serial.print(",");
      Serial.println(b[1]);

      Serial.print("3RGB");
      Serial.print(r[2]);
      Serial.print(",");
      Serial.print(g[2]);
      Serial.print(",");
      Serial.println(b[2]);
      counter = counter + 1;

      Serial.print("counter");
      Serial.println(counter);
      
  color_s = CRGB(gamma8[r[0]], gamma8[g[0]], gamma8[b[0]]);
  color_m = CRGB(gamma8[r[1]], gamma8[g[1]], gamma8[b[1]]);
  color_h = CRGB(gamma8[r[2]], gamma8[g[2]], gamma8[b[2]]);
    }
    if (counter > 3) {
      counter = 0;
    }
  }
