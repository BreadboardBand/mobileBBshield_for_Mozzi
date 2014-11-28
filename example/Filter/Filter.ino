#include <MozziGuts.h>
#include <StateVariable.h>

#define KNOB_PINA1 1
#define KNOB_PINA2 2

StateVariable <LOWPASS> svf; // can be LOWPASS, BANDPASS, HIGHPASS or NOTCH

void setup(){
  startMozzi();

  svf.setResonance(25.f);
  svf.setCentreFreq(1200.f);
}

void loop(){
  audioHook();
}

void updateControl(){

  int knobA1 = mozziAnalogRead(KNOB_PINA1); 
  int knobA2 = mozziAnalogRead(KNOB_PINA2); 

  knobA2 = map(knobA2, 0, 1023, 1, 255);
  svf.setResonance((float)knobA2);

  knobA1 = map(knob, 0, 1023, 20, 3000);
  float cutoff_freq = (float)knobA1;
  svf.setCentreFreq(cutoff_freq);
}

int updateAudio(){
  // watch output levels, they can distort if too high
  int asig = getAudioInput()-512;
  return svf.next(asig>>1)>>3;
}






