#ifndef buzzer_included 
#define buzzer_included 

#define switches_included


#define SWITCHES 15
void buzzer_init();
void buzzer_update_period(short cycles);
extern char state;
extern char switch_state_down, switch_state_changed; 
#endif // included
