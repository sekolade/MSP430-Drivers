#include <msp430.h>
#include <stdint.h>


/**
 * main.c
 */

// port
uint8_t *P1OUT_ = (uint8_t *) 0x0021;
uint8_t *P1DIR_ = (uint8_t *) 0x0022;
uint8_t *P1IFG_ = (uint8_t *) 0x0023;
uint8_t *P1IES_ = (uint8_t *) 0x0024;
uint8_t *P1IE_ = (uint8_t *) 0x0025;
uint8_t *P1SEL_ = (uint8_t *) 0x0026;
uint8_t *P1SEL2_ = (uint8_t *) 0x0041;
uint8_t *P1REN_ = (uint8_t *) 0x0027;


//timer
uint16_t *TA0CTL_ = (uint16_t *) 0x0160;
uint16_t *TA0CCTL0_ = (uint16_t *) 0x0162;
uint16_t *TA0CCTL1_ = (uint16_t *) 0x0164;
uint16_t *TA0R_ = (uint16_t *) 0x0170;
uint16_t *TA0CCR0_ = (uint16_t *) 0x0172;
uint16_t *TA0CCR1_ = (uint16_t *) 0x0174;


//uart
uint8_t *UCA0CTL0_ = (uint8_t *) 0x0060;
uint8_t *UCA0CTL1_ = (uint8_t *) 0x0061;
uint8_t *UCA0BR0_ = (uint8_t *) 0x0062;
uint8_t *UCA0MCTL_ = (uint8_t *) 0x0064;
uint8_t *UCA0RXBUF_ = (uint8_t *) 0x0066;
uint8_t *UCA0TXBUF_ = (uint8_t *) 0x0067;
uint8_t *IE2_ = (uint8_t *) 0x0001;
uint8_t *IFG2_ = (uint8_t *) 0x0003;
uint8_t *UCA0ABCTL_ = (uint8_t *) 0x5D;



uint8_t message[5] = {'a','b','c','d',0};
uint8_t message_index = 0;

int main(void)
    {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
    {
      while(1);                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;
    //setup button
    *P1DIR_ &= (uint8_t)~1<<3;
    *P1REN_ |= (uint8_t)1<<3;
    *P1OUT_ |= (uint8_t)1<<3;
    *P1IES_ |= (uint8_t)1<<3;
    *P1IE_ |= (uint8_t)1<<3;
    *P1IFG_ &= (uint8_t)~1<<3;


    //setup timer
    *TA0CTL_ |= (uint16_t)1<<2; //reset timer
    *TA0CTL_ = (uint16_t)0b0000000111010010;
    *TA0CTL_ &= (uint16_t) ~1;
    *TA0CCR0_ = (uint16_t)30000;
    *TA0CCTL1_ |= (uint16_t) 0b1110000100000000;


    //setup uart
    *UCA0CTL1_ |= 1; //
    //*UCA0CTL0_ = (uint8_t)0b00000000;
    *UCA0CTL1_ = (uint8_t)0b11000001;
    *P1SEL_ |= 0b00000110;
    *P1SEL2_ |= 0b00000110;
    *UCA0BR0_ = (uint8_t)104;
    *UCA0MCTL_ = (uint8_t)0b00000010;
    //*UCA0ABCTL_ = (uint8_t) 0b00000001;
    *UCA0CTL1_ &=(uint8_t) ~1; //
    *IFG2_ &= (uint8_t) ~1;
    //*UCA0ABCTL_ = (uint8_t) 0b00000001;

    *IE2_ |= (uint8_t) 1; // enable rx interrupt



    __enable_interrupt();





    while(1){}


    return 0;
}

#pragma vector = PORT1_VECTOR

__interrupt void ISR_button(void)
{
    if((*P1IFG_ & (uint8_t)1<<3) != 0){
        *P1IFG_ &= (uint8_t)~1<<3;
        *TA0CCTL1_ ^= (uint16_t)0x1000;
        message[4] = *TA0CCR1_;
        message_index = 0;
        *IE2_ |= (uint8_t) 2; // enable tx interrupt

    }

}
#pragma vector = TIMER0_A1_VECTOR

__interrupt void ISR_ccr0(void)
{
    if((*TA0CTL_ & (uint16_t)1) != 0){
        *TA0CTL_ &= (uint16_t) ~1;

        // capture_time += 10;
    }
}


#pragma vector = USCIAB0RX_VECTOR

__interrupt void ISR_rx(void)
{
    if((*IFG2_ & (uint8_t)1) != 0){
        *IFG2_ &= (uint16_t) ~1;
        if (message_index == (sizeof(message) -1)) {
            message_index = 0;
        }
        message[message_index] = *UCA0RXBUF_;
        message_index++;


    }
}

#pragma vector = USCIAB0TX_VECTOR

__interrupt void ISR_tx(void)
{
    if((*IFG2_ & (uint8_t)2) != 0){
        if (message_index < sizeof(message)){
            *UCA0TXBUF_ = message[message_index];
            message_index++;
        }
        else{
            message_index = 0;

            *IE2_ &= (uint8_t) ~2; //disable tx interrupt
        }
    }
}


