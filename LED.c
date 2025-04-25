/*
 * LED.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table

// initialize your LEDs
void LED_Init(void){
    IOMUX -> SECCFG.PINCM[PA26INDEX] = 0x81; // red
    IOMUX -> SECCFG.PINCM[PA27INDEX] = 0x81; // green
    IOMUX -> SECCFG.PINCM[PA28INDEX] = 0x81; // yellow
    GPIOA -> DOE31_0 |= 0x1C000000;
}
// data specifies which LED to turn on
void LED_On(uint32_t data){
    // write this
    // use DOUTSET31_0 register so it does not interfere with other GPIO
    GPIOA -> DOUTSET31_0 = (1 << data);
}

// data specifies which LED to turn off
void LED_Off(uint32_t data){
    // write this
    // use DOUTCLR31_0 register so it does not interfere with other GPIO
    GPIOA->DOUTCLR31_0 = (1 << data);
}

// data specifies which LED to toggle
void LED_Toggle(uint32_t data){
    // write this
    // use DOUTTGL31_0 register so it does not interfere with other GPIO
     GPIOA->DOUTTGL31_0 = (1 << data);
}
