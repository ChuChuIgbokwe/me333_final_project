#include "utilities.h"
#include "NU32.h"

static volatile state_t state = IDLE;


state_t util_state_get()                // get the current state
{
	return state;
}

void util_state_set(state_t s)         // atomically set the current state. 
{
	__builtin_disable_interrupts();
	state = s;
  	__builtin_enable_interrupts();
}