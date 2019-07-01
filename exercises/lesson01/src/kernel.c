#include "mini_uart.h"
#include "utils.h"

static unsigned long curr_processor_id = 0;
void kernel_main(unsigned long processor_id)
{
	//run processor, one by one
	while (curr_processor_id!=processor_id);

	if(processor_id==0)
	{
		uart_init();
	}

	if (processor_id==0)
	{	

		uart_send_string("Hello, world 0 !\r\n");
		curr_processor_id++;

		//wait all processor done
		while (curr_processor_id!=3);

		while (1) {
			uart_send(uart_recv());
		}
	}
	else{
		uart_send_string("Hello, world n!\r\n");
		curr_processor_id++;
		while(1);
	}	
}
