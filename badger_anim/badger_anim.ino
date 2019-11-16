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

Frame song[117] = { 

  // 1
  
  {4, 0, default_r, default_g, default_b},   // ba
  {3, floor( (320-0)/2 ), default_r, default_g, default_b}, // ger
  {4, 320, default_r, default_g, default_b},   // ba
  {3, floor( (708-320)/2 ), default_r, default_g, default_b}, // ger
  {4, 708, default_r, default_g, default_b},   // ba
  {3, floor( (1078-708)/2 ), default_r, default_g, default_b}, // ger
  {4, 1078, default_r, default_g, default_b},   // ba
  {3, floor( (1466-1078)/2 ), default_r, default_g, default_b}, // ger
  {4, 1466, default_r, default_g, default_b},   // ba
  {3, floor( (1803-1466)/2 ), default_r, default_g, default_b}, // ger
  {4, 1803, default_r, default_g, default_b},   // ba
  {3, floor( (2200-1803)/2 ), default_r, default_g, default_b}, // ger
  {4, 2200, default_r, default_g, default_b},   // ba
  {3, floor( (2595-2200)/2 ), default_r, default_g, default_b}, // ger
  {4, 2595, default_r, default_g, default_b},   // ba
  {3, floor( (2932-2595)/2 ), default_r, default_g, default_b}, // ger
  {4, 2932, default_r, default_g, default_b},   // ba
  {3, floor( (3319-2932)/2 ), default_r, default_g, default_b}, // ger
  {4, 3319, default_r, default_g, default_b},   // ba
  {3, floor( (3690-3319)/2 ), default_r, default_g, default_b}, // ger
  {4, 3690, default_r, default_g, default_b},   // ba
  {3, floor( (4027-3690)/2 ), default_r, default_g, default_b}, // ger

  {2, 4027, 255, 0, 0}, // mush
  {1, floor( (4836-4027)/2 ), 255, 0, 0}, // room
  {2, 4836, 255, 0, 0}, // mush
  {1, floor( (5965-4836)/2 ), 255, 0, 0}, // room

  // 2

  {4, 5965, default_r, default_g, default_b},   // ba
  {3, floor( (6302-5965)/2 ), default_r, default_g, default_b}, // ger
  {4, 6302, default_r, default_g, default_b},   // ba
  {3, floor( (6723-6302)/2 ), default_r, default_g, default_b}, // ger
  {4, 6723, default_r, default_g, default_b},   // ba
  {3, floor( (7110-6723)/2 ), default_r, default_g, default_b}, // ger
  {4, 7110, default_r, default_g, default_b},   // ba
  {3, floor( (7447-7110)/2 ), default_r, default_g, default_b}, // ger
  {4, 7447, default_r, default_g, default_b},   // ba
  {3, floor( (7835-7447)/2 ), default_r, default_g, default_b}, // ger
  {4, 7835, default_r, default_g, default_b},   // ba
  {3, floor( (8206-7835)/2 ), default_r, default_g, default_b}, // ger
  {4, 8206, default_r, default_g, default_b},   // ba
  {3, floor( (8576-8206)/2 ), default_r, default_g, default_b}, // ger
  {4, 8576, default_r, default_g, default_b},   // ba
  {3, floor( (8913-8576)/2 ), default_r, default_g, default_b}, // ger
  {4, 8913, default_r, default_g, default_b},   // ba
  {3, floor( (9301-8913)/2 ), default_r, default_g, default_b}, // ger
  {4, 9301, default_r, default_g, default_b},   // ba
  {3, floor( (9722-9301)/2 ), default_r, default_g, default_b}, // ger
  {4, 9722, default_r, default_g, default_b},   // ba
  {3, floor( (10110-9722)/2 ), default_r, default_g, default_b}, // ger

  {2, 10110, 255, 0, 0}, // mush
  {1, floor( (10817-10110)/2 ), 255, 0, 0}, // room
  {2, 10817, 255, 0, 0}, // mush
  {1, floor( (11912-10817)/2 ), 255, 0, 0}, // room

  // 3
  
  {4, 11912, default_r, default_g, default_b},   // ba
  {3, floor( (12334-11912)/2 ), default_r, default_g, default_b}, // ger
  {4, 12334, default_r, default_g, default_b},   // ba
  {3, floor( (12671-12334)/2 ), default_r, default_g, default_b}, // ger
  {4, 12671, default_r, default_g, default_b},   // ba
  {3, floor( (13092-12671)/2 ), default_r, default_g, default_b}, // ger
  {4, 13092, default_r, default_g, default_b},   // ba
  {3, floor( (13446-13092)/2 ), default_r, default_g, default_b}, // ger
  {4, 13446, default_r, default_g, default_b},   // ba
  {3, floor( (13816-13446)/2 ), default_r, default_g, default_b}, // ger
  {4, 13816, default_r, default_g, default_b},   // ba
  {3, floor( (14238-13816)/2 ), default_r, default_g, default_b}, // ger
  {4, 14238, default_r, default_g, default_b},   // ba
  {3, floor( (14575-14238)/2 ), default_r, default_g, default_b}, // ger
  {4, 14575, default_r, default_g, default_b},   // ba
  {3, floor( (14945-14575)/2 ), default_r, default_g, default_b}, // ger
  {4, 14945, default_r, default_g, default_b},   // ba
  {3, floor( (15333-14945)/2 ), default_r, default_g, default_b}, // ger
  {4, 15333, default_r, default_g, default_b},   // ba
  {3, floor( (15704-15333)/2 ), default_r, default_g, default_b}, // ger
  {4, 15704, default_r, default_g, default_b},   // ba
  {3, floor( (16428-15704)/2 ), default_r, default_g, default_b}, // ger

  {2, 16428, 255, 0, 0}, // mush
  {1, floor( (16816-16428)/2 ), 255, 0, 0}, // room
  {2, 16816, 255, 0, 0}, // mush
  {1, floor( (17911-16816)/2 ), 255, 0, 0}, // room

  // 4
  
  {4, 17911, default_r, default_g, default_b},   // ba
  {3, floor( (18332-17911)/2 ), default_r, default_g, default_b}, // ger
  {4, 18332, default_r, default_g, default_b},   // ba
  {3, floor( (18703-18332)/2 ), default_r, default_g, default_b}, // ger
  {4, 18703, default_r, default_g, default_b},   // ba
  {3, floor( (19090-18703)/2 ), default_r, default_g, default_b}, // ger
  {4, 19090, default_r, default_g, default_b},   // ba
  {3, floor( (19427-19090)/2 ), default_r, default_g, default_b}, // ger
  {4, 19427, default_r, default_g, default_b},   // ba
  {3, floor( (19798-19427)/2 ), default_r, default_g, default_b}, // ger
  {4, 19798, default_r, default_g, default_b},   // ba
  {3, floor( (20219-19798)/2 ), default_r, default_g, default_b}, // ger
  {4, 20219, default_r, default_g, default_b},   // ba
  {3, floor( (20607-20219)/2 ), default_r, default_g, default_b}, // ger
  {4, 20607, default_r, default_g, default_b},   // ba
  {3, floor( (20977-20607)/2 ), default_r, default_g, default_b}, // ger
  {4, 20977, default_r, default_g, default_b},   // ba
  {3, floor( (21314-20977)/2 ), default_r, default_g, default_b}, // ger
  {4, 21314, default_r, default_g, default_b},   // ba
  {3, floor( (21736-21314)/2 ), default_r, default_g, default_b}, // ger
  {4, 21736, default_r, default_g, default_b},   // ba
  {3, floor( (22073-21736)/2 ), default_r, default_g, default_b}, // ger

  {0, 22073, 0, 0, 255}, // a snake
  {0, floor( (22831-22073)/2 ), 0, 0, 0},
  {0, 22831, 0, 0, 255}, // a snake
  {0, floor( (23926-22831)/2 ), 0, 0, 0},
  {0, 23926, 255, 0, 0}, // snake
  {0, floor( (24701-23926)/2 ), 0, 0, 0},
  {0, 24701, 255, 0, 0}, // a snake
  {0, floor( (26015-24701)/2 ), 0, 0, 0},
  {0, 26015, 128, 128, 0}, // oh
  {0, floor( (27515-26015)/2 ), 0, 0, 0},
  {0, 27515, 0, 128, 128}, // its
  {0, floor( (27734-27515)/2 ), 0, 0, 0},
  {0, 27734, 128, 128, 0}, // a
  {0, floor( (27936-27734)/2 ), 0, 0, 0},
  {0, 27936, 255, 0, 0}, // snake
  {0, floor( (29250-27936)/2 ), 0, 0, 0},
  {0, 29250, 255, 255, 255} // it's a 

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

  //positionMillis()
  
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
