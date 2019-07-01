#include "arm/sysregs.h"

#include "mm.h"

.section ".text.boot"

.globl _start
_start:
    b   __boot_entry

// it works for
// qemu-system-aarch64 -m 128 -M raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.elf
// Exception level: 2
el2_entry:	
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #LOW_MEMORY
	bl	kernel_main



__boot_entry:

	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	ldr	x0, =SCTLR2_VALUE_MMU_DISABLED
	msr	sctlr_el2, x0		

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0

	ldr	x0, =SCR_VALUE
	msr	scr_el3, x0

	ldr	x0, =SPSR_VALUE_EL2
	msr	spsr_el3, x0

	adr	x0, el2_entry		
	msr	elr_el3, x0

	eret				
