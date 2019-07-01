#include "peripherals/timer.h"

.global _generic_timer_init
_generic_timer_init:
    mov x0,#1
    msr cntp_ctl_el0,x0
    ret

.global _generic_timer_reset
_generic_timer_reset:
    orr x0, xzr, #COUNTDOWN_TIMER_VALUE  
    msr cntp_tval_el0,x0
    ret