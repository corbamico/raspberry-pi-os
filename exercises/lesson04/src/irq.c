#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "entry.h"
#include "peripherals/irq.h"

#include "mini_uart.h"

#define IRQ_SOURCE_CNTPNSIRQ      (1<<1)

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

#define INTERRUPT_AUX_INT     (1<<29)

void enable_interrupt_controller()
{
	put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1 | INTERRUPT_AUX_INT);
}

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}

void handle_irq_core0(void)
{
	unsigned int irq = get_interrupt_source();
	//no irq_core0, ignore.
	if (irq==0) return;	

	switch (irq) {
		case (IRQ_SOURCE_CNTPNSIRQ):
			handle_generic_timer();
			break;
		default:
			printf("Unknown core 0 pending irq: 0x%x\r\n", irq);
	}
	
}

void handle_irq_peripheral(void)
{
	unsigned int irq = get32(IRQ_PENDING_1);

	while(irq!=0){
		if (irq & SYSTEM_TIMER_IRQ_1){
			handle_timer_irq();
			irq &= ~SYSTEM_TIMER_IRQ_1;				
		}else if (irq & INTERRUPT_AUX_INT){
			handle_aux_interrupt();
			irq &= ~INTERRUPT_AUX_INT;				
		}else{
			printf("Unknown peripheral pending irq: 0x%x\r\n", irq);
			irq = 0;			
		}
	}
}
