// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/26/2024


#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "sounds/sounds.h"
#include "../inc/ADC.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
#include "Random.h"


// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t drawFlag = 0;
uint32_t gear = 0;
int32_t survivalTicks = 0;
int32_t enemyX = 64; // enemy x 
int32_t enemyY = 0;  // enemy y 
uint32_t lane = 0; // enemy 1 lane
uint32_t lane2 = 0; // enemy 2 lane
uint32_t speed = 2; // base speed
int32_t enemy2X = 32; // enemy 2 x 
int32_t enemy2Y = 0; // enemy 2 y 
int32_t carY = 0; // character y pos

// games  engine runs at 30Hz
// this handler is for the gears
void TIMG12_IRQHandler(void){
  if ((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge interrupt
    GPIOB->DOUTTGL31_0 = GREEN;
    // Game engine tick — don't do LCD here
    drawFlag = 1;
  uint8_t prevButtonState = 0;
  uint32_t button = Switch_In(); // gear input 
  if (button == 15 && prevButtonState != 15) {
  gear = (gear + 1) % 3; // goes through the gears to see how fast u want to go
  }
  prevButtonState = button;
  survivalTicks++; // timer
  GPIOB->DOUTTGL31_0 = GREEN;
  }
}

 uint8_t enemyUpdateFlag = 0;
 uint8_t spawnFlag = 0;

// this handler is for the enemy vehicles
void TIMG0_IRQHandler(void){
  if((TIMG0->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27
if (enemyX <= -50){
  enemyX = 128;  // starts enemy from the right
  uint32_t newLane;
  newLane = Random() % 3; // finds the lane
  while (newLane == lane2) {// 
    newLane = Random() % 3; 
  }
  lane = newLane;
  // puts the enemy is one of the 3 options
  if (lane == 0) {
    enemyY = 155;
  }
  else if (lane == 1) {
    enemyY = 105;
  }
  else {
    enemyY = 53;
  }
}

if (enemy2X <= -50){
    enemy2X = 128;  // starts enemy2 from the right
  uint32_t newLane2 = Random() % 3; // finds the lane
  while (newLane2 == lane) {
    newLane2 = Random() % 3;
  }
  lane2 = newLane2;
  // puts the enemy in one of the 3 options
  if (lane2 == 0) {
    enemy2Y = 155;
  }
  else if (lane2 == 1) {
    enemy2Y = 105;
  }
  else {
    enemy2Y = 53;
  }
}

// this is the speed of the car
if (gear == 0){
    speed = 2;
  }
  else if (gear == 1){
    speed = 5;
  }
  else if (gear == 2){
    speed = 8;
  }
    spawnFlag = 1;
 }
}

uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED;
  while(1){
  uint32_t test = ADCin();
    // write code to test switche
  }
}
// use main4 to test sound outputs
int main4(void){ 
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  ADCinit();
  DAC5_Init();
 
  __enable_irq();
  //while(1){
    /*
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
    */
 // }
}




// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main(void){ // final main
  speed = 50;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  ST7735_InvertDisplay(1);
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  Random_Init(ADCin());
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG0_IntArm(80000000, 100, 1);
  TimerG12_IntArm(80000000/speed,0);
  // initialize all data structures
  DAC_Init();
  ADCinit();
  __enable_irq();

  int32_t OldCarX = 0; // old x of car
  int32_t OldCarY = 0; // old y of car
  int32_t oldenemyX = 0; // old x of enemy 1
  int32_t oldenemyY = 0; // old y of enemy 1
  uint32_t enemyFrameCnt = 0; // determines when we will display the enemy
 
  int32_t oldenemy2X = 0; // old x of enemy 2
  int32_t oldenemy2Y = 0; // old y of enemy 2
  int32_t carX = 0; 
  int32_t offset = 0;

  int32_t english = 0; // this for handler
  int32_t seconds = 0; // counter

  ST7735_DrawBitmap(0, 160, startScreen, 128, 160); // this displays the start screen and shows option of english or spansih

  while(1){
    while(1){
    if (Switch_In() == 31) {
    english = 1;
    break;
    }
    else if(Switch_In() == 18){
    english = 0;
    break;
    }
    }
    // displays red yellow green led with sound indicated the start of the game
    LED_On(26);
    Sound_Tick(); // tick tick led 
    Clock_Delay1ms(1000);
    LED_Off(26);
    Clock_Delay1ms(1000);
    LED_On(28);
    Sound_Tick();
    Clock_Delay1ms(1000);
    LED_Off(28);
    Clock_Delay1ms(1000);
    LED_On(27);
    Sound_Tick();
    Clock_Delay1ms(1000);
    LED_Off(27);
    ST7735_DrawBitmap(offset, 160, road4, 127, 159);
    Sound_Car(); // this starts the engine
    break;
    }
  survivalTicks = 0;
  while(1) {
    if (drawFlag == 1){
    // this is for the time 
    ST7735_FillRect(122, 60,  5,  30, 0x0000);  
    ST7735_SetRotation(1);
    ST7735_SetCursor(10,0);
    seconds = survivalTicks / 30;  
    // determines if english or spanish was selected
    if (english == 1){
    ST7735_OutString("Time:");
    }
    else{
    ST7735_OutString("Tiempo:");
    }
    // displays the time
    ST7735_OutUDec((seconds));
    ST7735_OutChar('s');
    ST7735_SetRotation(0);

  ST7735_DrawBitmapTransparent(offset, 160, road4, 127, 159); // displays the road
  ST7735_DrawBitmapTransparent(offset + 128, 160, road4, 127, 159);
  // this displays the road moving
  if (Switch_In()!= 17) {
  offset -= speed;  
  if (offset <= -128) {
    offset = 0;
  }
  }
  if (offset <= -128) {
     offset = 0;
  }

  carY = 0;
  ST7735_FillRect(OldCarX, OldCarY, 47, 10, 0xFFFF);

  uint32_t adc = ADCin(); // this reads the slide pot
  // based on the slide pot this determines the 3 lanes
    if (adc <= 1365){
    carY = 140; 
  }
    else if (adc <= 2730) {
    carY = 88;
  }
    else {
    carY = 36;
  }

  // this makes it look like the car is moving
  ST7735_DrawBitmapTransparent(0, carY, type2, 47, 21);     
  // this only happens if the character moves his car
  if (OldCarY != carY){
    ST7735_FillRect(OldCarX, (OldCarY-20), 47, 20, 0xFFFF);
    OldCarY = carY;
    OldCarX = carX;
  }
    drawFlag = 0;
  }


  spawnFlag = 0;
  enemyFrameCnt++;


  if (Switch_In() != 17){
    if (enemyFrameCnt >= 20 ) {
    // this makes it look like enemy 1 car is moving
    ST7735_FillRect(oldenemyX, (oldenemyY - 35), 50, 21, 0xFFFF);
    enemyX -= speed;
    ST7735_DrawBitmapTransparent(enemyX, enemyY, Enemy1, 50, 50);
    oldenemyX = enemyX;
    oldenemyY = enemyY;
    enemyFrameCnt = 0;
   
    // this makes it look like enemy 2 car is moving
    ST7735_FillRect(oldenemy2X, (oldenemy2Y - 35), 50, 21, 0xFFFF);
    enemy2X -= speed;
    ST7735_DrawBitmapTransparent(enemy2X, enemy2Y, porche, 50, 50);
    oldenemy2X = enemy2X;
    oldenemy2Y = enemy2Y;
    }
  }

 // this is for the collisions
 if (((enemyY < (carY + 18)) && ((enemyY + 34) > carY) && (enemyX < (carX + 41)) && (enemyX +50 > carX)) || ((enemy2Y < (carY + 18)) && ((enemy2Y + 34) > carY) && (enemy2X < (carX + 41)) && (enemy2X +50 > carX))){
    Sound_Crash(); // sound of crash
    ST7735_FillRect(0, 0, 128, 160, 0x0000);
    ST7735_SetRotation(1);
    // this displays the score and text in English
    if (english == 1){
    ST7735_SetCursor(9,5);
    ST7735_OutString("Game Over!");
    ST7735_SetCursor(9,6);
    ST7735_OutString("Score:");
    ST7735_SetCursor(16, 6);
    ST7735_OutUDec(((survivalTicks)/30));
    break;
    }
    else{
    // this displays the score and text in spanish
    ST7735_SetCursor(6,5);  
    ST7735_OutString("Fin del juego");
    ST7735_SetCursor(6,6);  
    ST7735_OutString("Puntuacion:");
    ST7735_SetCursor(18,6);  
    ST7735_OutUDec(((survivalTicks)/30));
    break;
    }
    }
}
}





