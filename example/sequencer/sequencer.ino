#include <MsTimer2.h>

#include "pitches.h"
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <ADSR.h>
#include <AudioDelay.h>
#include <tables/cos2048_int8.h> // wavetable
#include <tables/triangle_analogue512_int8.h> // wavetable
#include <tables/triangle512_int8.h> // wavetable
// use: Oscil <table_size, update_rate> oscilName (wavetable)
Oscil <TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aSin(TRIANGLE_ANALOGUE512_DATA);
Oscil<TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aCarrier(TRIANGLE_ANALOGUE512_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kFreq(COS2048_DATA);
AudioDelay <1024> aDel;
ADSR <CONTROL_RATE, CONTROL_RATE> envelope;
// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please
// constants
static const int BeatInputPin = 0;
static const int ToneOutputPin = 6;
static const int AnalogValuePin = 5;
static const int NumberOfArpeggioPotentiometers = 5;



// dorian
#if 0
static const uint8_t NumberOfNotes = 43;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_D2,  NOTE_DS2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_AS2, 
  NOTE_C3, NOTE_D3,  NOTE_DS3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3,
  NOTE_C4, NOTE_D4,  NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4,
  NOTE_C5, NOTE_D5,  NOTE_DS5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_AS5,
  NOTE_C6, NOTE_D6,  NOTE_DS6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_AS6,
  NOTE_C7, NOTE_D7,  NOTE_DS7, NOTE_F7, NOTE_G7, NOTE_A7, NOTE_AS7,
};
#endif

// major penta
#if 1
static const uint8_t NumberOfNotes = 36;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C1, NOTE_D1,  NOTE_E1, NOTE_G1, NOTE_A1, 
  NOTE_C2, NOTE_D2,  NOTE_E2, NOTE_G2, NOTE_A2, 
  NOTE_C3, NOTE_D3,  NOTE_E3, NOTE_G3, NOTE_A3,
  NOTE_C4, NOTE_D4,  NOTE_E4, NOTE_G4, NOTE_A4,
  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_G5, NOTE_A5,
  NOTE_C6, NOTE_D6,  NOTE_E6, NOTE_G6, NOTE_A6,
  NOTE_C7, NOTE_D7,  NOTE_E7, NOTE_G7, NOTE_A7,
};
#endif


// bass line
#if 0
static const uint8_t NumberOfNotes = 19;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_G2, NOTE_AS2, 
  NOTE_C3, NOTE_G3, NOTE_AS3,
  NOTE_C4, NOTE_G4, NOTE_AS4,
  NOTE_C5, NOTE_G5, NOTE_AS5,
  NOTE_C6, NOTE_G6, NOTE_AS6,
  NOTE_C7, NOTE_G7, NOTE_AS7,
};
#endif

// japanese
#if 0
static const uint8_t NumberOfNotes = 31;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_CS2, NOTE_F2, NOTE_G2, NOTE_AS2, 
  NOTE_C3, NOTE_CS2, NOTE_F3, NOTE_G3, NOTE_AS3, 
  NOTE_C4, NOTE_CS4, NOTE_F4, NOTE_G4, NOTE_AS4, 
  NOTE_C5, NOTE_CS5, NOTE_F5, NOTE_G5, NOTE_AS5, 
  NOTE_C6, NOTE_CS6, NOTE_F6, NOTE_G6, NOTE_AS6, 
  NOTE_C7, NOTE_CS7, NOTE_F7, NOTE_G7, NOTE_AS7, 
};
#endif

// minor blues
#if 0
static const uint8_t NumberOfNotes = 31;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_DS2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_AS2, 
  NOTE_C3, NOTE_DS3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_AS3, 
  NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_AS4, 
  NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_AS5, 
  NOTE_C6, NOTE_DS6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_AS6,  
};
#endif
// values
uint16_t arpeggioPotentiometers[NumberOfArpeggioPotentiometers] = { 0 };
uint8_t currentBeat = 0;
int8_t direction = 1; // 1 or -1
bool needUpdate = false;

// function prototypes
void newBeat();
void timer() {
  newBeat();
}

// implementations
void setup()
{
        MsTimer2::set(120, timer); 
        MsTimer2::start();
	pinMode(BeatInputPin, INPUT);
	pinMode(ToneOutputPin, OUTPUT);
	attachInterrupt(BeatInputPin, newBeat, RISING);

	for (int i = 0; i < NumberOfArpeggioPotentiometers; ++i)
	{
		arpeggioPotentiometers[i] = 0;
	}

        startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
        envelope.setADLevels(255,255);
        aSin.setFreq(440);
}

void loop()
{
	if (needUpdate)
	{
		const uint16_t adValue = mozziAnalogRead(currentBeat);
		const uint8_t noteIndex = map(adValue, 0, 1023, 0, NumberOfNotes);
		uint16_t duration = mozziAnalogRead(AnalogValuePin) >> 1;
                
                duration = duration == 0 ? 1 : duration;
		needUpdate = false;
                const int freq = (int)NoteNumbers[noteIndex];
                aSin.setFreq(freq);
                const long carrierFreq = (freq << 1) - 10;
                aCarrier.setFreq(freq << 1);
                envelope.setTimes(0u,duration,duration,0);  // "u" means unsigned int
                envelope.noteOn();
	}

        audioHook(); // required here
}

void newBeat()
{

	currentBeat += direction;

	if (currentBeat >= NumberOfArpeggioPotentiometers || currentBeat < 0)
	{

		direction *= -1;

		currentBeat += direction;
		currentBeat += direction;
	}

	needUpdate = true;
}

void updateControl(){
  envelope.update();
}

int writeIndex = 0;
int readIndex = 1;

char delayBuffer[1024];
int updateAudio(){
   char sig =  (int) (envelope.next() * (aSin.next() >> 1) + (aCarrier.next() >> 1)   )>>8;   
   // sig = sig < 0 ? -127 : 127;
   return sig;
}

