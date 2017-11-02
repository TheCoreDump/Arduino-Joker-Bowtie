#include <Adafruit_NeoPixel.h>

#ifndef BowTie_h
#define BowTie_h

// Pattern types supported:
enum BowTieMode { JOKER, JOKER_HEARTBEAT, SOLID_RED, SOLID_BLUE, SOLID_GREEN, DRIP, OFF };

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class BowTie : public Adafruit_NeoPixel
{
    public:

    // Public Constructors
    BowTie::BowTie(uint16_t pixels, uint8_t pin, uint8_t type);
    

    // Member Variables:  
    BowTieMode CurrentMode;  // Current light mode
    
    unsigned long Interval;   // milliseconds between updates
    unsigned long lastUpdate; // last update of position
    
    uint32_t Color1, Color2;  // What colors are in use
    uint16_t TotalSteps;  // total number of steps in the pattern
    uint16_t Index;  // current step within the pattern


    // Public Methods    

    // Sets the mode for the bowtie.
    void SetMode(BowTieMode newMode);

    // Update the pattern
    void Update();

    // Switch to the next mode in the line.
    void NextMode();


protected: 

    // Protected Methods
    void InitializeState(unsigned long interval, uint16_t totalSteps);
    
    // Increment the pattern
    void Increment();

    // Update Joker
    void UpdateJoker();

    // Update Joker Heartbeat
    void UpdateJokerHeartbeat();

    // Update Drip
    void UpdateDrip();

    void ColorSet(uint32_t color);

    // Calculate 50% dimmed version of a color (used by ScannerUpdate)
    uint32_t DimColor(uint32_t color);

    // Returns the Red component of a 32-bit color
    uint8_t Red(uint32_t color);

    // Returns the Green component of a 32-bit color
    uint8_t Green(uint32_t color);

    // Returns the Blue component of a 32-bit color
    uint8_t Blue(uint32_t color);

    // Get a color based on the hue value.
    uint32_t Wheel(byte WheelPos);
};

#endif
