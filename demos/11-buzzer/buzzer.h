#ifndef buzzer_included 
#define buzzer_included 

#define switches_included

#define SW1 BIT3/* switch1 is p1.3 */
#define SWITCHES SW1
void buzzer_init();
void buzzer_update_period(short cycles);

extern char switch_state_down, switch_state_changed; 
#endif // included
