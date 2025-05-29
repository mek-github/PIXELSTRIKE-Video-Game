// Sound.cpp
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// your name
// your data 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"
 

const uint8_t *SoundDataPt;
uint32_t SoundCount = 0;

void SysTick_IntArm(uint32_t period, uint32_t priority){
  // write this
  SysTick->CTRL = 0;                   // disable SysTick during setup
  SysTick->LOAD = period - 1;         // reload value for 11kHz
  SysTick->VAL = 0;                   // any write to VAL clears it
  NVIC_SetPriority(SysTick_IRQn, priority); // set interrupt priority
  SysTick->CTRL = 0x00000007;         // enable SysTick with core clock and interrupts
}
// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void){
// write this
  // write this
  DAC5_Init();                        // Initialize 5-bit DAC 
  SysTick_IntArm(10909, 2);           // 11kHz = 1/11000s => 10909 cycles at 12MHz
  SysTick->CTRL = 0;                  // Turn off SysTick until sound starts
  SoundCount = 0;
  SoundDataPt = 0;
 
 
}
extern "C" void SysTick_Handler(void);
void SysTick_Handler(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
    // output one value to DAC if a sound is active
  if(SoundCount > 0){
      DAC5_Out(*SoundDataPt);           // output to DAC
      SoundDataPt++;                    // next sample
      SoundCount--;
    }else{
      SysTick->CTRL = 0;                // turn off SysTick when done
    }
}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Sound_Start(const uint8_t *pt, uint32_t count){
// write this
if(count == 0 || pt == 0){
 return;   // do nothing if invalid
}
  SoundDataPt = pt;                  // set pointer to start of sound
  SoundCount = count;                // set how many samples to play
  SysTick->VAL = 0;                  // clear current count
  SysTick->CTRL = 0x00000007;        // enable SysTick with interrupts
  
}

void Sound_Shoot(void){
// write this
  Sound_Start(GoodShot, 27660);
}
void Sound_Killed(void){
// write this

}
void Sound_Explosion(void){
// write this

}

void Sound_Fastinvader1(void){

}
void Sound_Fastinvader2(void){

}
void Sound_Fastinvader3(void){

}
void Sound_Fastinvader4(void){

}
void Sound_Highpitch(void){
}
