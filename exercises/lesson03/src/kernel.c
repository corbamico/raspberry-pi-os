#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "mini_uart.h"

typedef  unsigned char BOOL;
#define FALSE 0
#define TRUE  1
static BOOL _b_uart_inited = FALSE;


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

	while (1){
		//uart_send(uart_recv());
	}	
}
