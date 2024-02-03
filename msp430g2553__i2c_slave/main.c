#include <msp430.h> 
#include <stdint.h>
//g2553
//slave




/**
 * main.c
 */

//port1
uint8_t *P1IN_ = (uint8_t *) 0x0020;
uint8_t *P1OUT_ = (uint8_t *) 0x0021;
uint8_t *P1DIR_ = (uint8_t *) 0x0022;
uint8_t *P1IFG_ = (uint8_t *) 0x0023;
uint8_t *P1IES_ = (uint8_t *) 0x0024;
uint8_t *P1IE_ = (uint8_t *) 0x0025;
uint8_t *P1SEL_ = (uint8_t *) 0x0026;
uint8_t *P1REN_ = (uint8_t *) 0x0027;
uint8_t *P1SEL2_ = (uint8_t *) 0x0041;

//i2c
uint16_t *UCB0OA_ = (uint16_t *) 0x0118; //own adress
uint16_t *UCB0SA_ = (uint16_t *) 0x011A; //slave adress
uint8_t *UCB0CTL0_ = (uint8_t *) 0x0068;
uint8_t *UCB0CTL1_ = (uint8_t *) 0x0069;
uint8_t *UCB0BR0_ = (uint8_t *) 0x006A;
uint8_t *UCB0BR1_ = (uint8_t *) 0x006B;
uint8_t *UCB0RXBUF_ = (uint8_t *) 0x006E;
uint8_t *UCB0TXBUF_ = (uint8_t *) 0x006F;
uint8_t *IE2_ = (uint8_t *) 0x0001;
uint8_t *IFG2_ = (uint8_t *) 0x0003;
uint8_t *UCB0CIE_ = (uint8_t *) 0x006C;

uint8_t message[5] = {0};
uint8_t index = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //setup i2c
    *UCB0CTL1_ |= 1; //reset

    *UCB0CTL0_ |= 0<<3; //slave mode
    *UCB0CTL0_ |= (uint8_t) 0b11 <<1; //i2c mode
    *UCB0CTL0_ |= 1; //synchronous

    //UCB0CTL1_ |= 0b11<<6; //smclk
    //*UCB0BR0_ = 10; //prescalar = 10, actual = 5
    *UCB0CTL1_ |= 0<<4; //recieve

    *UCB0OA_ |= (uint16_t) 0b1000001; //7-bit own adress = 0x0012

    *P1SEL_ |= 1<<6; //set p1.6 as scl
    *P1SEL2_ |= 1<<6;

    *P1SEL_ |= 1<<7; //set p1.7 as sda
    *P1SEL2_ |= 1<<7;

    *UCB0CTL1_ &= ~1; //disable reset

    //*IE2_ |= 1<<3; //enable tx interrupt
    *IE2_ |= 1<<2; //enable rx interrupt
    //*UCB0CIE_ |= 1<<1; //enable start condition interrupt


    //*UCB0CTL1_ |= 1<<2; // set stop condition



    //setup button
    *P1DIR_ &= (uint8_t)~1<<3;
    *P1REN_ |= (uint8_t)1<<3;
    *P1OUT_ |= (uint8_t)1<<3;
    *P1IES_ |= (uint8_t)1<<3;
    *P1IE_ |= (uint8_t)1<<3;
    *P1IFG_ &= (uint8_t)~1<<3;

    //setup led
    *P1DIR_ |= (uint8_t)1<<0;
    *P1OUT_ &= (uint8_t)~(1<<0);



    __enable_interrupt(); //global interrupt enable
    while(1){}

	return 0;
}



#pragma vector = USCIAB0TX_VECTOR

__interrupt void ISR_rx_tx(void)
{
    if(index == sizeof(message)){
        index = 0;
    }
    if((*IFG2_ & 1<<3)!= 0){ //tx
        *UCB0TXBUF_ = message[index];
        index++;
    }
    else if((*IFG2_ & 1<<2)!= 0){ //rx
        message[index] = *UCB0RXBUF_;
        index++;
    }

}

#pragma vector = PORT1_VECTOR

__interrupt void ISR_button(void)
{
    *P1IFG_ &= (uint8_t)~1<<3;
    *P1OUT_ ^= (uint8_t)1<<0;

}
