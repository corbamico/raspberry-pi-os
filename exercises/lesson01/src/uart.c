#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"


#define FR_BUSY (1<<3)
#define FR_RXFE (1<<4)
#define FR_TXFF (1<<5)

#define CR_RXE  (1<<9)
#define CR_TXE  (1<<8)
#define CR_UARTEN  (1)

#define LCRH_WLEN_8BITS (3<<5)
#define LCRH_WLEN_7BITS (2<<5)
#define LCRH_WLEN_6BITS (1<<5)
#define LCRH_WLEN_5BITS (0<<5)
#define LCRH_FEN        (1<<4)

void uart_send ( char c )
{
	while(get32(UART_FR) & FR_TXFF);
	put32(UART_DR,c);
}

char uart_recv ( void )
{
    while(get32(UART_FR) & FR_RXFE);
	return(get32(UART_DR) & 0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init(void)
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

    put32(UART_CR,0);                      //disable uart

    put32(UART_IBRD,26);                   //baud_rate=115200
    put32(UART_FBRD,3);

    put32(UART_LCRH, LCRH_WLEN_8BITS | LCRH_FEN); //enable 8 bits and FIFO
    put32(UART_IMSC,0);                    //mask interrupt
    put32(UART_CR,CR_RXE | CR_TXE);        

    put32(UART_CR,CR_RXE | CR_TXE | CR_UARTEN); //enable uart       

}