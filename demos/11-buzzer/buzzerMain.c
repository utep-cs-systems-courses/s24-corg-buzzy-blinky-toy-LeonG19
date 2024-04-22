#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"


char switch_state_down, switch_state_changed;

switch_update_interrupt_sense()

{

  char p1val = P1IN;

  /* update switch interrupt to detect changes from current buttons */

  P1IES |= (p1val & SWITCHES);/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);/* if switch down, sense up */

  return p1val;

}

switch_init()/* setup switch */

{

  P1REN |= SWITCHES;/* enables resistors for switches */

  P1IE |= SWITCHES;/* enable interrupts from switches */

  P1OUT |= SWITCHES;/* pull-ups for switches */

  P1DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  buzzer_update_period(1000);

}

switch_interrupt_handler()

{

  char p1val = switch_update_interrupt_sense();

  switch_state_down = (p1val & SW1) ? 0 : 1;
  switch_state_changed = 1;
  buzzer_update_period(1000);

}

int main() {
    configureClocks();    
    buzzer_init();
    switch_init();	/* start buzzing!!! 2MHz/1000 = 2kHz*/

    or_sr(0x18);          // CPU off, GIE on
}
void

__interrupt_vec(PORT1_VECTOR) Port_1(){

  if (P1IFG & SWITCHES) {      /* did a button cause this interrupt? */

    P1IFG &= ~SWITCHES;      /* clear pending sw interrupts */

    switch_interrupt_handler();/* single handler for all switches */

  }

}
