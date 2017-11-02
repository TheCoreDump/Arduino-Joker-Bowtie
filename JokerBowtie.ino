#include <power_mgt.h>
#include <platforms.h>
#include <pixeltypes.h>
#include <pixelset.h>
#include <noise.h>
#include <lib8tion.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastspi_types.h>
#include <fastspi_ref.h>
#include <fastspi_nop.h>
#include <fastspi_dma.h>
#include <fastspi_bitbang.h>
#include <fastspi.h>
#include <fastpin.h>
#include <fastled_progmem.h>
#include <fastled_delay.h>
#include <fastled_config.h>
#include <FastLED.h>
#include <dmx.h>
#include <cpp_compat.h>
#include <controller.h>
#include <colorutils.h>
#include <colorpalettes.h>
#include <color.h>
#include <chipsets.h>
#include <bitswap.h>
#include <Adafruit_NeoPixel.h>
#include "BowTie.h"

// Here are the pin assignments
#define BUTTON_PIN 2
#define LED_PIN 8
#define NUM_LEDS 4


// Define some NeoPatterns for the two rings and the stick
//  as well as some completion routines
BowTie Lapel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Initialize everything and prepare to start
void setup()
{
  // Initialize the button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize the LED class
  Lapel.begin();

  // Set the Lapel to "off"
  Lapel.SetMode(OFF);
  //Lapel.SetMode(SOLID_RED);
    
  // Setup the interrupt for the pin
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), OnButtonPressed, RISING);
}


// Stores the last time the interrupt was fired
unsigned long volatile last_interrupt_time = 0;


// Advances the lapel to the next mode.
void OnButtonPressed()
{
 unsigned long interrupt_time = millis();
 
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200)
  Lapel.NextMode();

 last_interrupt_time = interrupt_time; 
}

// Loop is pretty simple - just updates the Bowtie object.
void loop() 
{
  Lapel.Update();
}


