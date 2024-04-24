#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"


char switch_state_down, switch_state_changed, state;
char
switch_update_interrupt_sense()

{

  char p2val = P2IN;

  /* update switch interrupt to detect changes from current buttons */

  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}
void
switch_init()/* setup switch */

{

  P2REN |= SWITCHES;/* enables resistors for switches */

  P2IE |= SWITCHES;/* enable interrupts from switches */

  P2OUT |= SWITCHES;/* pull-ups for switches */

  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  buzzer_update_period(1000);

}
void update_state();
void
switch_interrupt_handler()

{
  
  char p2val = switch_update_interrupt_sense();
  int switches = ~p2val & SWITCHES;
  if (switches & SWITCHES){
    switch_state_changed = 1;
    for (char sw=0; sw < 4; sw ++){
      int flag = 1 << sw;
      if (flag & switches){
	state = sw;
	break;
      }
    }
  }
  update_state();
  
}

void update_state(){
  switch(state){
  case 0:
    buzzer_update_period(500);
    break;
  case 1:
    buzzer_update_period(1000);
    break;
  case 2:
    buzzer_update_period(5000);
    break;
  case 3:
    buzzer_update_period(10000);
    break;
  }
}

int main() {
    configureClocks();    
    buzzer_init();
    switch_init();	/* start buzzing!!! 2MHz/1000 = 2kHz*/

    or_sr(0x18);          // CPU off, GIE on
}
void

__interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */

    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */

    switch_interrupt_handler();/* single handler for all switches */

  }

}
