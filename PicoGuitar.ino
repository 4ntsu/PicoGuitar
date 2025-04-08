#include <PicoGamepad.h>
#include <WiiChuck.h>

#include "PicoGuitar.h"

Accessory guitar;
PicoGamepad gamepad;

unsigned long lastSliderTime = millis();
uint8_t sliderInterval = 60; // sampling interval in milliseconds (1ms = 1000Hz)

uint8_t lastSliderInput = 123; // resting state

void setup() {
  guitar.begin();
  guitar.type = GuitarHeroController;
}

void loop() {

  guitar.readData(); // read inputs from guitar

  gamepad.SetZ(map(guitar.values[0], 0, 255, ANALOG_MIN, ANALOG_MAX));  // whammy
  gamepad.SetButton(GREEN, guitar.values[10]);                          // green
  gamepad.SetButton(RED, guitar.values[11]);                            // red
  gamepad.SetButton(YELLOW, guitar.values[12]);                         // yellow
  gamepad.SetButton(BLUE, guitar.values[13]);                           // blue
  gamepad.SetButton(ORANGE, guitar.values[14]);                         // orange
  gamepad.SetButton(0, guitar.values[9]);                               // pedal
  gamepad.SetRz(map(guitar.values[7], 0, 255, ANALOG_MIN, ANALOG_MAX)); // strum
//gamepad.SetRx(map(guitar.values[3], 0, 255, ANALOG_MIN, ANALOG_MAX)); // neck slider - WIP, not yet supported by WiiChuck
  if (guitar.values[3] > 0) processSlider(guitar.values[3]);
  gamepad.SetX(map(guitar.values[1],0,255,ANALOG_MIN,ANALOG_MAX));      // joystick X axis
  gamepad.SetY(map(guitar.values[2],0,255,ANALOG_MIN,ANALOG_MAX));      // joystick Y axis
  gamepad.SetButton(8, guitar.values[5]);                               // star power
  gamepad.SetButton(9, guitar.values[6]);                               // plus buttons

  gamepad.send_update(); // send inputs to USB gamepad
}

bool matchesColour(uint8_t value, uint8_t colour){
  return ((uint8_t)(value - sliderMap[colour][START]) <= (uint8_t)(sliderMap[colour][END] - sliderMap[colour][START]));
}

void processSlider(uint8_t input) {
  
  // If any fret buttons are pressed, act as whammy
  if ( guitar.values[10] || guitar.values[11] || guitar.values[12] || guitar.values[13] || guitar.values[14] ) {
    gamepad.SetZ(map(guitar.values[3], 0, 255, ANALOG_MIN, ANALOG_MAX));
  
  // otherwise go into tap mode
  } else {
    // if less time than the minimum interval has passed, repeat the last input
    if ((millis() - lastSliderTime) < sliderInterval) {
      setSliderButtons(lastSliderInput);

    // else remember the current state and apply the input
    } else {
      lastSliderInput = input;
      lastSliderTime = millis();
      setSliderButtons (input);
    }
  }
}

void setSliderButtons(uint8_t input) { 
    if (matchesColour(input, OPEN)) {
      return;
    }
    
    if (matchesColour(input, GREEN) || matchesColour(input, GREEN_RED)) {
      gamepad.SetButton(GREEN, true);
    }
  
    if (matchesColour(input, RED) || matchesColour(input, GREEN_RED) || matchesColour(input, RED_YELLOW)) {
      gamepad.SetButton(RED, true);
    }
  
    if (matchesColour(input, YELLOW) || matchesColour(input, RED_YELLOW) || matchesColour(input, YELLOW_BLUE)) {
      gamepad.SetButton(YELLOW, true);
    }
  
    if (matchesColour(input, BLUE) || matchesColour(input, YELLOW_BLUE) || matchesColour(input, BLUE_ORANGE)) {
      gamepad.SetButton(BLUE, true);
    }
  
    if (matchesColour(input, ORANGE) || matchesColour(input, BLUE_ORANGE)) {
      gamepad.SetButton(ORANGE, true);
    }  
}
