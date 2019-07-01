#ifndef	_P_TIMER_H
#define	_P_TIMER_H

#include "peripherals/base.h"

#define TIMER_CS        (PBASE+0x00003000)
#define TIMER_CLO       (PBASE+0x00003004)
#define TIMER_CHI       (PBASE+0x00003008)
#define TIMER_C0        (PBASE+0x0000300C)
#define TIMER_C1        (PBASE+0x00003010)
#define TIMER_C2        (PBASE+0x00003014)
#define TIMER_C3        (PBASE+0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)



#define BCM2836_BASE              0x40000000 
#define TIMER_INT_CTRL_CORE_0     0x40000040
#define IRQ_SOURCE_CORE_0         0x40000060

#define COUNTDOWN_TIMER_VALUE (1<<24)


//CNTP Non-Secure IRQ
#define TIMER_INT_CTRL_CNTPNSIRQ  (1<<1)
#define IRQ_SOURCE_CNTPNSIRQ      (1<<1)


#endif  /*_P_TIMER_H */
