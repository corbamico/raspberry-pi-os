#ifndef	_TIMER_H
#define	_TIMER_H

void timer_init ( void );
void handle_timer_irq ( void );

void generic_timer_init(void);
void handle_generic_timer(void);

extern void _generic_timer_init(void);
extern void _generic_timer_reset(void);

void enable_generic_timer();
unsigned int get_interrupt_source();

#endif  /*_TIMER_H */
