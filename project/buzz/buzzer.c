#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
char switch_state_down, switch_state_changed;

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6; /* enable output to speaker (P2.6) */
    switch_state_changed = 1;
    buzzer_update_period(1000);
}

void buzzer_update_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  if (switch_state_changed){
    //char flag =  switch_state_down ? BIT6 : 0;
    P2DIR ^= BIT6;
    // P2DIR |= flag;
    CCR0 = cycles;

    CCR1 = cycles >> 1;

  }
  
  switch_state_changed = 0;/* one half cycle */
}


    
    
  

