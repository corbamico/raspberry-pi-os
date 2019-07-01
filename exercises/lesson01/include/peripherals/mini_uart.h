#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

#define AUX_ENABLES     (PBASE+0x00215004)
#define AUX_MU_IO_REG   (PBASE+0x00215040)
#define AUX_MU_IER_REG  (PBASE+0x00215044)
#define AUX_MU_IIR_REG  (PBASE+0x00215048)
#define AUX_MU_LCR_REG  (PBASE+0x0021504C)
#define AUX_MU_MCR_REG  (PBASE+0x00215050)
#define AUX_MU_LSR_REG  (PBASE+0x00215054)
#define AUX_MU_MSR_REG  (PBASE+0x00215058)
#define AUX_MU_SCRATCH  (PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (PBASE+0x00215060)
#define AUX_MU_STAT_REG (PBASE+0x00215064)
#define AUX_MU_BAUD_REG (PBASE+0x00215068)

/**
 * baudrate = system_clock_freq/(8*(baudrate_reg+1))
 * 
 * system_clock_freq = 250 MHz
 * baudrate_reg = system_clock_freq/(baudrate * 8) - 1
 */
typedef enum {
    baud_rate_1200 = 1200,
    baud_rate_2400 = 2400,
    baud_rate_4800 = 4800,
    baud_rate_9600 = 9600,
    baud_rate_19200 = 19200,
    baud_rate_38400 = 38400,
    baud_rate_57600 = 57600,    
    baud_rate_115200 = 115200
} mini_baud_rate_t;

typedef enum {
    baud_rate_reg_1200 = (250000000>>3) / baud_rate_1200 - 1,
    baud_rate_reg_2400 = (250000000>>3) / baud_rate_2400 - 1,
    baud_rate_reg_4800 = (250000000>>3) / baud_rate_4800 - 1,
    baud_rate_reg_9600 = (250000000>>3) / baud_rate_9600 - 1,
    baud_rate_reg_19200 = (250000000>>3) / baud_rate_19200 - 1,
    baud_rate_reg_38400 = (250000000>>3) / baud_rate_38400 - 1,
    baud_rate_reg_57600 = (250000000>>3) / baud_rate_57600 - 1,    
    baud_rate_reg_115200 = (250000000>>3) / baud_rate_115200 - 1
} mini_baud_rate_reg_t;

#endif  /*_P_MINI_UART_H */
