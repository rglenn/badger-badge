#include <Adafruit_NeoPixel.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthToneSweep      tonesweep1;     //xy=361,365
AudioMixer4              mixer1;         //xy=676,349
AudioOutputAnalog        dac1;           //xy=881,347
AudioConnection          patchCord1(tonesweep1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, dac1);
// GUItool: end automatically generated code


#define NUMPIXELS      10
Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel_2 = Adafruit_NeoPixel(NUMPIXELS, 14, NEO_GRB + NEO_KHZ800);

void setup() {
  AudioMemory(10);
  Serial.begin(9600);
  // put your setup code here, to run once:
  pixel_1.begin();
  pixel_2.begin();

  for(int i=0;i<NUMPIXELS;i++){
    pixel_1.setPixelColor(i, 0);
    pixel_2.setPixelColor(i, 0);
  }

  pinMode(13, OUTPUT);
  // Mute the amplifier
  digitalWrite(13, LOW);

  dac1.analogReference(INTERNAL);
  mixer1.gain(0, 1.0);

  pixel_1.show();
  pixel_2.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("board1");
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel_1.setPixelColor(i, pixel_1.Color(0,150,0)); // Moderately bright green color.

    pixel_1.show(); // This sends the updated pixel color to the hardware.

    delay(250); // Delay for a period of time (in milliseconds).

  }
  Serial.println("board2");
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel_2.setPixelColor(i, pixel_2.Color(0,150,0)); // Moderately bright green color.

    pixel_2.show(); // This sends the updated pixel color to the hardware.

    delay(250); // Delay for a period of time (in milliseconds).

  }
  Serial.println("sound");
  digitalWrite(13, HIGH);
  tonesweep1.play(1.0, 100, 1000, 5);
  delay(5000);
  digitalWrite(13, LOW);

}
