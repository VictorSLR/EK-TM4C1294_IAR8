#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 2 estados e 1 evento temporal que alterna entre eles
// Seleção por evento

typedef enum {s000, s001, s011, s010, s110, s111, s101, s100} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = s000; // estado inicial da MEF
  
  LEDInit(LED1|LED2|LED3);
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      Evento = 0;
      switch(Estado){
        case s000:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado ++;
          break;
        case s001:
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado ++;
          break;
        case s011:
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado ++;
          break;
         case s010:
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado ++;
          break;
         case s110:
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado ++;
          break;
         case s111:
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado ++;
          break;
         case s101:
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado ++;
          break;
         case s100:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = s000;
          break;
      } // switch
    } // if
  } // while
} // main
