#include <Adafruit_NeoPixel.h>

#include <Streaming.h>
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

#define BUTTON_1 9
#define BUTTON_2 10
#define BUTTON_3 11
#define BUTTON_4 12

#define NUMPIXELS      10
Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel_2 = Adafruit_NeoPixel(NUMPIXELS, 14, NEO_GRB + NEO_KHZ800);

long current_time = 0;
long last_frame = 0;
uint16_t current_frame = 0;
uint16_t max_frames = 5;
uint8_t default_r = 0;
uint8_t default_g = 255;
uint8_t default_b = 0;

typedef struct {
  uint8_t panel;
  long start_time;
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Frame;

// lyrics
// source: https://genius.com/Weebl-badger-badger-badger-lyrics
/*
 * Badger, badger, badger
Badger, badger, badger
Badger, badger, badger
Badger, badger, badger
Mushroom, mushroom

A badger, badger
Badger, badger, badger
Badger, badger, badger
Badger, badger, badger
Mushroom, mushroom

A badger, badger
Badger, badger, badger
Badger, badger, badger
Badger, badger, badger
Mush-mushroom

A badger, badger
Badger, badger, badger
Badger, badger, badger
Badger, badger, badger

A snake, a snake
Snaaake! A snaaaake
Oooh, it's a snake
 * 
 */

Frame badger[2] = {
  {4, 80, default_r, default_g, default_b},  // ba
  {3, 80, default_r, default_g, default_b}  // ger
};

Frame mushroom[2] = {
  {2, 80, 128, 128, 0}, // mush
  {1, 80, 128, 128, 0} // room
};

Frame song[5] = { 
  {4, 1000, default_r, default_g, default_b}, 
  {3, 100, default_r, default_g, default_b},
  {2, 100, 255, 0, 0},
  {1, 100, 255, 0, 0},
  {0, 100, 255, 255, 255}
};


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

  current_time = millis();

  
  Frame f = song[current_frame];
  
  if(current_time-last_frame >= f.start_time) {
    Serial << current_frame << " @ " << f.start_time << endl;
    allOff();
    panelOn(f.panel, f.r, f.g, f.b);
    current_frame++;
    last_frame = current_time;
  }

  if(current_frame >= max_frames) current_frame = 0;
  


  /*
   * // note: this was not working
  blinkBadger(3);
  blinkBadger(3);
  blinkBadger(3);
  blinkBadger(3);
  blinkMushroom(2);
  */


}


// teensy audio codec library


void blinkBadger(int count) {

  for(int j=0; j<count; j++) {

    Frame f = badger[current_frame];
  
    if(current_time-last_frame >= f.start_time) {
      Serial << current_frame << " @ " << f.start_time << endl;
      allOff();
      panelOn(f.panel, f.r, f.g, f.b);
      current_frame++;
      last_frame = current_time;
    }
  
    if(current_frame >= 2-1) current_frame = 0;
    
  }
  
}

void blinkMushroom(int count) {

  for(int j=0; j<count; j++) {

    Frame f = mushroom[current_frame];
  
    if(current_time-last_frame >= f.start_time) {
      Serial << current_frame << " @ " << f.start_time << endl;
      allOff();
      panelOn(f.panel, f.r, f.g, f.b);
      current_frame++;
      last_frame = current_time;
    }
  
    if(current_frame >= 2-1) current_frame = 0;
    
  }
  
}




void soundTest() {

  Serial.println("sound");
  digitalWrite(13, HIGH);
  tonesweep1.play(1.0, 100, 1000, 5);
  delay(5000);
  digitalWrite(13, LOW);
  
}


void testBlinky() {
  
  // front to back
  for(int i=4; i>=0; i--) {
    if(i>=0) panelOn(i+1, 0, 0, 0);
    if(i==4) panelOn(0, 0, 0, 0);
    panelOn(i, 0, 255, 0);
    delay(80);
  }

  // back to front
  for(int i=0; i<5; i++) {
    if(i>0) panelOn(i-1, 0, 0, 0);
    if(i==0) panelOn(4, 0, 0, 0);
    panelOn(i, 0, 255, 0);
    delay(80);
  }
  
}


// panel_id: 0 = BACK [...] 4 = FRONT
// pixel_1 = UPPER, pixel_2 = LOWER
void panelOn(uint8_t panel_id, uint8_t r, uint8_t g, uint8_t b) { 

  switch(panel_id) {
    case 0: {
      pixel_1.setPixelColor(0, pixel_1.Color(r,g,b) );
      pixel_1.setPixelColor(1, pixel_1.Color(r,g,b) );
      pixel_2.setPixelColor(0, pixel_2.Color(r,g,b) );
      pixel_2.setPixelColor(1, pixel_2.Color(r,g,b) ); // 1 on panel 2 is borked
      pixel_1.show();
      pixel_2.show();
    }
    break;
    case 1: {
      pixel_1.setPixelColor(2, pixel_1.Color(r,g,b) );
      pixel_1.setPixelColor(3, pixel_1.Color(r,g,b) );
      pixel_2.setPixelColor(2, pixel_2.Color(r,g,b) );
      pixel_2.setPixelColor(3, pixel_2.Color(r,g,b) );
      pixel_1.show();
      pixel_2.show();
    }
    break;
    case 2: {
      pixel_1.setPixelColor(4, pixel_1.Color(r,g,b) );
      pixel_1.setPixelColor(5, pixel_1.Color(r,g,b) );
      pixel_2.setPixelColor(4, pixel_2.Color(r,g,b) );
      pixel_2.setPixelColor(5, pixel_2.Color(r,g,b) );
      pixel_1.show();
      pixel_2.show();
    }
    break;
    case 3: {
      pixel_1.setPixelColor(6, pixel_1.Color(r,g,b) );
      pixel_1.setPixelColor(7, pixel_1.Color(r,g,b) );
      pixel_2.setPixelColor(6, pixel_2.Color(r,g,b) );
      pixel_2.setPixelColor(7, pixel_2.Color(r,g,b) );
      pixel_1.show();
      pixel_2.show();
    }
    break;
    case 4: {
      pixel_1.setPixelColor(8, pixel_1.Color(r,g,b) );
      pixel_1.setPixelColor(9, pixel_1.Color(r,g,b) );
      pixel_2.setPixelColor(8, pixel_2.Color(r,g,b) );
      pixel_2.setPixelColor(9, pixel_2.Color(r,g,b) );
      pixel_1.show();
      pixel_2.show();
    }
    break;
    
  }
  
}


void allOff() {

  for(int i=0; i<NUMPIXELS; i++) {
    pixel_1.setPixelColor(i, pixel_1.Color(0,0,0) );
    pixel_2.setPixelColor(i, pixel_1.Color(0,0,0) );
    pixel_1.show();
    pixel_2.show();
  }
  
}
