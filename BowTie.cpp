#include "BowTie.h"


// Constructors
BowTie::BowTie(uint16_t pixels, uint8_t pin, uint8_t type) : Adafruit_NeoPixel(pixels, pin, type) 
{ 
  CurrentMode = OFF;
}


void BowTie::NextMode()
{
  if (CurrentMode == OFF)
  {
    SetMode(JOKER);
  }
  else
  {
    SetMode((BowTieMode) (CurrentMode + 1));
  }
}

void BowTie::SetMode(BowTieMode newMode)
{
  CurrentMode = newMode;
  
  switch (newMode)
  {
    case JOKER:
      InitializeState(250, 2);    
      UpdateJoker();
      break;
    case JOKER_HEARTBEAT:
      InitializeState(25, 2);    
      UpdateJokerHeartbeat();
      break;
    case DRIP:
      InitializeState(50, 8);    
      UpdateDrip();
      break;
    case SOLID_RED:
      ColorSet(Color(255, 0, 0));
      break;
    case SOLID_BLUE:
      ColorSet(Color(0, 0, 255));
      break;
    case SOLID_GREEN:
      ColorSet(Color(0, 255, 0));
      break;
    case OFF:
      ColorSet(Color(0, 0, 0));
      break;
  }
}


void BowTie::InitializeState(unsigned long interval, uint16_t totalSteps)
{
  Interval = interval;
  TotalSteps = totalSteps;
  Index = 0;
  lastUpdate = millis();
}

// Update the pattern
void BowTie::Update()
{
    // Check to see if it is time to update
    if((millis() - lastUpdate) > Interval) 
    {
        lastUpdate = millis();
        Increment();

        switch(CurrentMode)
        {
            case JOKER:
                UpdateJoker();
                break;
        }
    }
}


// Increment the internal counter
void BowTie::Increment()
{
  Index++;
   
  if (Index >= TotalSteps)
  {
    Index = 0;
  }
}


void BowTie::UpdateJoker()
{
  for (int i = 0; i < numPixels(); i++)
  {
    if (i % 2 == (Index % 2)) 
      setPixelColor(i, Color(85, 26, 139));  // Purple
    else
      setPixelColor(i, Color(0, 255, 0));    // Green
  }
  
  show();
}

void BowTie::UpdateJokerHeartbeat()
{


  
}

void BowTie::UpdateDrip()
{
  for (int i = Index; i >= 0; i--)
  {
    
  }
}

/*
 * Helper Functions
 */


// Set all pixels to a color (synchronously)
void BowTie::ColorSet(uint32_t color)
{
    for (int i = 0; i < numPixels(); i++)
    {
        setPixelColor(i, color);
    }

    show();
}


// Calculate 50% dimmed version of a color (used by ScannerUpdate)
uint32_t BowTie::DimColor(uint32_t color)
{
  // Shift R, G and B components one bit to the right
  uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
  return dimColor;
}

// Returns the Red component of a 32-bit color
uint8_t BowTie::Red(uint32_t color)
{
  return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t BowTie::Green(uint32_t color)
{
  return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t BowTie::Blue(uint32_t color)
{
  return color & 0xFF;
}
    
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t BowTie::Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  
  if(WheelPos < 85)
  {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if(WheelPos < 170)
  {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


