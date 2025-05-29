// Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name
// Last Modified: 12/26/2024

#include <cstdint>
#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "Images.h"
#include "Entities.h"
#include "CollisionsAndBullets.h"
#include "sounds/sounds.h"

extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);

#define MAX_ZOMBIES 20
#define MAX_ZOMBIES_PER_WAVE 6
#define NUM_WAVES 2

uint32_t tick_counter = 0;
uint8_t bomb_flag = 0;
bullet_t BulletArray[MAX_BULLETS];
const uint8_t countdown[30] = {
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

uint8_t countdown_timer = 0;

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}
uint8_t RandomMultiple(void) {
    uint8_t index = Random(5) % 5;  // Random index between 0 and 4
    return index * 27;
}


// SlidePot Sensor(1500,0); // copy calibration from Lab 7
SlidePot JoyX(1712, 71);
SlidePot JoyY(1712, 71);

SlidePot Joy2X(1712, 71);
SlidePot Joy2Y(1712, 71);

box_t TestBox;

uint32_t previousPressed1 = 0;
uint32_t previousPressed2 = 0;

uint16_t shootCooldown1 = 0;
uint16_t shootCooldown2 = 0;

uint8_t defuse_now;
uint8_t defuse_prev = 0;

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES

    tick_counter++;
    countdown_timer++;
    if (shootCooldown1 < 14) shootCooldown1++;
    if (shootCooldown2 < 14) shootCooldown2++; 

    ADC1->ULLMEM.MEMCTL[0] = 2;
    uint32_t rawX = JoyX.In();
    JoyX.Save(rawX);

    // Sample Y axis (PA17, ADC1.6)
    ADC1->ULLMEM.MEMCTL[0] = 6;
    uint32_t rawY = JoyY.In();
    JoyY.Save(rawY);

    //PA18
    ADC1->ULLMEM.MEMCTL[0] = 3;
    uint32_t raw2X = Joy2X.In();
    Joy2X.Save(raw2X);

    // Sample Y axis (PB19, ADC1.6)
    ADC1->ULLMEM.MEMCTL[0] = 4;
    uint32_t raw2Y = Joy2Y.In();
    Joy2Y.Save(raw2Y);

    // Read PA15 (0 if pressed)
    uint32_t isPressed2 = (Switch_In() & 0x01);
    uint32_t isPressed1 = (Switch_In() & 0x02);

    if (Player1.health > 0 && isPressed1 != 0 && previousPressed1 == 0 && shootCooldown1 >= 14) {
        Bullet_Init(BulletArray, &Player1);
        previousPressed1 = true;
        Sound_Shoot();
        shootCooldown1 = 0;
    } else if (isPressed1 == 0) {
        // Reset flag when button is released
        previousPressed1 = 0;
    }

    if (Player2.health > 0 && isPressed2 != 0 && previousPressed2 == 0 && shootCooldown2 >= 14) {
        Bullet_Init(BulletArray, &Player2);
        previousPressed2 = true;
        Sound_Shoot();
        shootCooldown2 = 0;
    } else if (isPressed2 == 0) {
        // Reset flag when button is released
        previousPressed2 = 0;
    }

    Player_Update(&Player1);
    Player_Update2(&Player2);
    // if (checkBombCollision(&Player1) && Defuse_Pressed()) {
    //   TestBox.defused = true;
    // }

    // // Update all active zombies
    // for (int i = 0; i < MAX_ZOMBIES; i++) {
    //   if (zombie_sprites_array[i].rendered) {
    //     Zombie_Update(&zombie_sprites_array[i]);
    //   }
    // }

    // // Request to spawn a new zombie every 2 seconds (60 ticks at 30Hz)
    // if (tick_counter % 60 == 0 && spawncount < MAX_ZOMBIES) {
    //     spawn_request = true;
    // }

    // // Process spawn request in the interrupt
    // Zombie_Spawn(); 

    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(int myPhrase=0; myPhrase<= 2; myPhrase++){
    for(int myL=0; myL<= 3; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_SAND);
  // zombie_t test;
  // ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  // ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  // ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  // ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  // ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  // ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  // ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  // ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  // ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  // ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  // for(uint32_t t=500;t>0;t=t-5){
  //   SmallFont_OutVertical(t,104,6); // top left
  //   Clock_Delay1ms(50);              // delay 50 msec
  // }
  // ST7735_FillScreen(0x0000);   // set screen to black
  // ST7735_SetCursor(1, 1);
  // ST7735_OutString((char *)"GAME OVER");
  // ST7735_SetCursor(1, 2);
  // ST7735_OutString((char *)"Nice try,");
  // ST7735_SetCursor(1, 3);
  // ST7735_OutString((char *)"Earthling!");
  // ST7735_SetCursor(2, 4);
  // ST7735_OutUDec(1234);
  while(1){
    // Zombie_Update(testptr);               // move the sprite
    // Zombie_Draw(testptr);

    ST7735_DrawBitmap(50, 50, PlayerWest, 25, 25);
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    // int input = Switch_In();
    // if (input) {
    //   input = 1;
    // }
    // GPIOA->DOUT31_0 = 1 << 16;

    // uint32_t input = Switch_In();
    if (Defuse_Pressed()) {
      GPIOA->DOUTTGL31_0 = (1 << 28);
    }
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    // now = Switch_In(); // one of your buttons
    // if((last == 0)&&(now == 1)){
    //   Sound_Shoot(); // call one of your sounds
    // }
    // if((last == 0)&&(now == 2)){
    //   Sound_Killed(); // call one of your sounds
    // }
    // if((last == 0)&&(now == 4)){
    //   Sound_Explosion(); // call one of your sounds
    // }
    // if((last == 0)&&(now == 8)){
    //   Sound_Fastinvader1(); // call one of your sounds
    // }
    Sound_Shoot();
    while (1) {

    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_SAND);
  JoyX.Init(); // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2); // 40MHz/40/10000 = 100Hz  
  // initialize all data structures
 
  

  //  // Reset global variables
  // tick_counter = 0;
  // spawncount = 0;
  // killcount = 0;
  // spawn_request = false;
  
  // // Initialize all zombies as inactive
  // for (int i = 0; i < MAX_ZOMBIES; i++) {
  //   zombie_sprites_array[i].rendered = false;
  // }
  
  // // Initialize just 4 zombies at the start of the game
  // for (int i = 0; i < 4; i++) {
  //   uint8_t x = 25 + (i * 20); // Space them out evenly
  //   Zombie_Init(&zombie_sprites_array[i], x, 0 + 10*(i%2), 1, zombie_image);
  //   zombie_sprites_array[i].rendered = true;
  //   spawncount++;
  // }
    

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
    uint8_t i = 0;
    Player_Init(&Player2, 30, 30);
    Player_Init(&Player1, 30, 130);
    Box_Init(&TestBox, 30, 50);
    
    ST7735_DrawBitmap(0, 159, MainMenu, 128, 160);
    ST7735_SetRotation(1);
    ST7735_SetCursor(10, 8);
    ST7735_SetTextColor(ST7735_RED);
    printf("ENGLISH");
    ST7735_SetCursor(10, 10);
    ST7735_SetTextColor(ST7735_RED);
    printf("ESPA\xA5OL");
    ST7735_SetRotation(0);  
    GPIOA->DOUTCLR31_0 = (1 << 28);

    while (Switch_In() == 0) {
    
    }

    while (Switch_In() != 0) {
      if (Switch_In() == 2) {
        myLanguage = Spanish;
      } else {
        myLanguage = English;
      }
    }

      __enable_irq();
    
    ST7735_FillScreen(ST7735_SAND);
    // Box 4: from (103, 70) to (102, 122)
    ST7735_FillRect(79, 98, 23, 25, ST7735_BLACK);

    while (Player2.health > 0 && i <= 30 && TestBox.defused == false) {
      Box_Init(&TestBox, 0, 125);
      Box_Draw(&TestBox);
      Player_Draw(&Player1);
      Player_Draw(&Player2);
      // Box 1: from (32, 71) to (63, 73)
      ST7735_FillRect(32, 65, 31, 2, ST7735_BLACK);

      // Box 2: from (0, 112) to (52, 114)
      ST7735_FillRect(0, 112, 52, 2, ST7735_BLACK);

      // Box 3: from (50, 115) to (52, 124)
      ST7735_FillRect(50, 114, 2, 9, ST7735_BLACK);

      //Box4 refresh
      ST7735_FillRect(79, 98, 23, 10, ST7735_BLACK);
      ST7735_FillRect(79, 98, 11, 25, ST7735_BLACK);
      ST7735_FillRect(79, 119, 23, 4, ST7735_BLACK);

      // Box 5: from (84, 34) to (127, 36)
      ST7735_FillRect(84, 34, 43, 2, ST7735_BLACK);
      // Box_Draw(&TestBox);

      Bullet_Update(BulletArray);
      Bullet_Draw(BulletArray);

      if (countdown_timer >= 30) {
        countdown_timer = 0;
        ST7735_SetRotation(1);
        ST7735_SetCursor(18, 3);
        if (i != 30)
          printf("%02d", countdown[i]);
        i = i + 1;
        ST7735_SetRotation(0);
        GPIOA->DOUTTGL31_0 = (1 << 28);
      }

      defuse_now = Defuse_Pressed(); // 1 = pressed, 0 = not pressed

      if (defuse_now && checkBombCollision(&Player2)) {
        // ST7735_SetCursor(0, 2);
        // printf("DEFUSED!");
        (&TestBox)->defused = true;
      }

      defuse_now = 0;
    }

    if (i > 30) {
        Sound_Start(explosion, 2000);
    }
    
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_SetRotation(1);
    if (myLanguage == English) {
      ST7735_SetCursor(3, 5);
      printf("GAME OVER.");
      ST7735_SetCursor(3, 7);
      if (TestBox.defused == true) {
        printf("ATTACKER WINS.");
      }
      else if (Player2.health > 0)
        printf("DEFENDER WINS.");
      else 
        printf("DEFENDER WINS.");
    } else {
      ST7735_SetCursor(3, 5);
      printf("JUEGO TERMINADO.");
      ST7735_SetCursor(3, 7);
      if (TestBox.defused == true) {
        printf("EL ATACANTE GANA.");
      }
      else if (Player2.health > 0)
        printf("EL DEFENSOR GANA.");
      else 
        printf("EL DEFENSOR GANA.");
      ST7735_SetCursor(3, 9);
    }
    ST7735_SetRotation(0);
    TestBox.defused = false;

    __disable_irq();
    GPIOA->DOUTSET31_0 = (1 << 28);
    while (Defuse_Pressed() == 0) {

    }
    while (Defuse_Pressed() != 0) {

    }
    while (Defuse_Pressed() == 0) {

    }
  }
}
