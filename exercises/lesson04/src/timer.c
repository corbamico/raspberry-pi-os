#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "timer.h"
#include "sched.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void timer_init ( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) 
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	printf("Timer interrupt received\n\r");
}

void enable_generic_timer()
{
	put32(TIMER_INT_CTRL_CORE_0,TIMER_INT_CTRL_CNTPNSIRQ);
}

unsigned int get_interrupt_source()
{
	return get32(IRQ_SOURCE_CORE_0);
}

void generic_timer_init(void)
{
	_generic_timer_init();
	_generic_timer_reset();
}
void handle_generic_timer(void)
{
	_generic_timer_reset();
	printf("Timer interrupt received\n\r");
	timer_tick();
}

