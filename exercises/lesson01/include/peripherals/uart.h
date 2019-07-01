#include "peripherals/base.h"

//Physical address range from 0x3F000000 to 0x3FFFFFFF
//the bus address for peripherals are set up to map onto
//the peripheral bus address rage starting at 0x7E000000
//Thus peripheral adverttised here at but 0x7Ennnnnn is 
//available at physical address 0x3Fnnnnnn

//included in peripherals/base.h
//#define PBASE         0x3F000000 

#define UART_REG_OFFSET (PBASE+0x00201000)
enum uart_regs {
    UART_DR = UART_REG_OFFSET + 0x00,
    UART_FR = UART_REG_OFFSET + 0x18,
    
    //baud_rate integer part, and fraction part
    UART_IBRD = UART_REG_OFFSET + 0x24,
    UART_FBRD = UART_REG_OFFSET + 0x28,

    UART_LCRH = UART_REG_OFFSET + 0x2c,
    UART_CR = UART_REG_OFFSET + 0x30,
    UART_IMSC = UART_REG_OFFSET + 0x38,
};