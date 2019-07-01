#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "fork.h"
#include "sched.h"
#include "mini_uart.h"
#include "utils.h"

typedef  unsigned char BOOL;
#define FALSE 0
#define TRUE  1
static BOOL _b_uart_inited = FALSE;

void process(char *array)
{
	while (1){
		for (int i = 0; i < 5; i++){
			uart_send(array[i]);
			delay(100000);
		}
	}
}

void kernel_el3_init(void)
{
	uart_init();
	_b_uart_inited = TRUE;
	init_printf(0, putc);
	printf("[kernel main el3]init uart ok.\r\n");		
}

void kernel_el2_init(void)
{
	if(!_b_uart_inited)	uart_init();
	init_printf(0, putc);
	printf("[kernel main el2]init uart ok.\r\n");	
}

void kernel_el1_main(void)
{
	//uart_init();
	init_printf(0, putc);
	printf("[kernel main el1]init uart ok.\r\n");
	irq_vector_init();
	timer_init();
	generic_timer_init();
	
	enable_interrupt_controller();
	enable_generic_timer();	
	enable_irq();


	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		printf("error while starting process 1");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		printf("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}	
}
