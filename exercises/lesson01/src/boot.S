#include "mm.h"

.section ".text.boot"

.globl _start
	nop
	b   _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, master_cpu		    // Hang for all non-primary CPU
	b	slave_cpu

master_cpu:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov sp, #LOW_MEMORY
	mov x0, xzr	
    bl  kernel_main
	b   proc_hang

slave_cpu:
	//stack pointer per cpu = #LOW_MEMORY - kernel_stack_size * processor_id
    mov  x10, #LOW_MEMORY
	mov  x9,  #KERNEL_STACK_SIZE	 
	mul  x9, x9, x0 
	sub  sp, x10, x9

	bl	kernel_main         //x0 = processor id
	b 	proc_hang		    // should never come here

proc_hang:
	b 	proc_hang
