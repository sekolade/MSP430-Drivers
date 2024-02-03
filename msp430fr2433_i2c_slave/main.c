#include <msp430.h> 
#include <stdint.h>
//fr2433 slave

//port1
uint8_t *P1IN_ = (uint8_t *) 0x0200;
uint8_t *P1OUT_ = (uint8_t *) 0x0202;
uint8_t *P1DIR_ = (uint8_t *) 0x0204;
uint8_t *P1REN_ = (uint8_t *) 0x0206;
uint8_t *P1SEL0_ = (uint8_t *) 0x020A;
uint8_t *P1SEL1_ = (uint8_t *) 0x020C;
uint8_t *P1IES_ = (uint8_t *) 0x0218;
uint8_t *P1IE_ = (uint8_t *) 0x021A;
uint8_t *P1IFG_ = (uint8_t *) 0x021C;
//port2
uint8_t *P2IN_ = (uint8_t *) 0x0201;
uint8_t *P2OUT_ = (uint8_t *) 0x0203;
uint8_t *P2DIR_ = (uint8_t *) 0x0205;
uint8_t *P2REN_ = (uint8_t *) 0x0207;
uint8_t *P2SEL0_ = (uint8_t *) 0x020B;
uint8_t *P2SEL1_ = (uint8_t *) 0x020D;
uint8_t *P2IES_ = (uint8_t *) 0x0219;
uint8_t *P2IE_ = (uint8_t *) 0x021B;
uint8_t *P2IFG_ = (uint8_t *) 0x021D;
//i2c
uint16_t *UCB0CTLW0_ = (uint16_t *) 0x00540;
uint16_t *UCB0CTLW1_ = (uint16_t *) 0x0542;
uint16_t *UCB0BR0_ = (uint16_t *) 0x0546;
uint16_t *UCB0TBCNT_ = (uint16_t *) 0x054A;
uint16_t *UCB0RXBUF_ = (uint16_t *) 0x054C;
uint16_t *UCB0TXBUF_ = (uint16_t *) 0x054E;
uint16_t *UCB0I2CSA_ = (uint16_t *) 0x0560;
uint16_t *UCB0I2COA0_ = (uint16_t *) 0x0554;
uint16_t *UCB0IE_ = (uint16_t *) 0x056A;
uint16_t *UCB0IFG_ = (uint16_t *) 0x0056C;

uint8_t message_write[5] = {1,2,3,4,5};
uint8_t index_write = 0;
uint8_t message_read[5] = {0};
uint8_t index_read = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    //setup button left
    *P2DIR_ |= 0<<3; //input
    *P2REN_ |= 1<<3; //resistor
    *P2OUT_ |= 1<<3; //pull up
    *P2IES_ |= 1<<3; //high to low
    *P2IE_ |= 1<<3; //interrupt enable
    *P2IFG_ &= ~1<<3; //clear flag
    //setup led1
    *P1DIR_ |= 1<<0;
    *P1OUT_ &= ~(1<<0);
    //setup led2
    *P1DIR_ |= 1<<1;
    *P1OUT_ &= ~(1<<1);
    //setup i2c
    *UCB0CTLW0_ |= 1; //reset
    *UCB0CTLW0_ |= 0<<15; // 7-bit adress own
    *UCB0CTLW0_ |= 0<<11; //slave mode
    *UCB0CTLW0_ |= 0b11<<9; //i2c mode
    *UCB0CTLW0_ |= 0<<4; //recieve

    *P1SEL1_ &= ~(1<<2); // p1.2 as sda
    *P1SEL0_ |= 1<<2;
    *P1SEL1_ &= ~(1<<3);// p1.3 as scl
    *P1SEL0_ |= 1<<3;

    *UCB0I2COA0_ |= 0<<15; //don't respond to general call
    *UCB0I2COA0_ |= (uint16_t) 0b0100001; //own adress0
    *UCB0I2COA0_ |= 1<<10; //enable slave adress0

    *UCB0CTLW1_ |= 0b01<<2; //UCBCNTIFG is set when byte counter reaches UCB0TBCNT
    *UCB0TBCNT_ =(uint16_t) 5;

    *UCB0CTLW0_ &= ~1; //disable reset

    *UCB0IE_ |= 1<<1; //tx0 interrupt enable
    *UCB0IE_ |= 1; //rx0 interrupt enable
    *UCB0IE_ |= 1<<6; //byte counter interrupt enable
    *UCB0IE_ |= 1<<2; //start condition interrupt enable

    PM5CTL0 &= ~LOCKLPM5; // enable i/o
    __enable_interrupt(); //enable global interrupt
    while(1){
    }
    return 0;
}
#pragma vector = PORT2_VECTOR
__interrupt void ISR_button(void)
{
    if((*P2IFG_ & 1<<3) !=0){
        *P2IFG_ &= ~(1<<3);
        *P1OUT_ ^= 1<<0;
    }
}
#pragma vector = USCI_B0_VECTOR
__interrupt void ISR_rx_tx(void)
{
    if((*UCB0IFG_ & 1) != 0){ //rx0
        if(index_read >= sizeof(message_read)){
            index_read = 0;
        }
        *UCB0IFG_ &= ~1; //clear rx0 flag
        message_read[index_read] = *UCB0RXBUF_; //recieve byte
        index_read++;
    }
    else if((*UCB0IFG_ & 1<<1) != 0){ //tx0
        if(index_write >= sizeof(message_write)){
            index_write = 0;
        }
        *UCB0IFG_ &= ~(1<<1); //clear tx0 flag
        *UCB0TXBUF_ = message_write[index_write]; //sent byte
        index_write++;
    }
    if((*UCB0IFG_ & 1<<6)!= 0){ // byte counter
        *UCB0IFG_ &= ~(1<<6); //clear flag
        *UCB0IE_ &= ~(1<<6); //byte counter interrupt disable
        if((*UCB0CTLW0_ & 1<<4)!= 0){ //slave transmits = writes
            *P1OUT_ |= (1<<0);
            int i;
            for(i=0;i<10000;i++){}
            *P1OUT_ &= ~(1<<0);
        }
        else{ //slave recieves = reads
            *P1OUT_ |= (1<<1);
            int i;
            for(i=0;i<10000;i++){}
            *P1OUT_ &= ~(1<<1);
        }
    }
    if((*UCB0IFG_ & 1<<2)!= 0){ // start condition
        *UCB0IFG_ &= ~(1<<2); //clear flag
        *UCB0IE_ |= 1<<6; //byte counter interrupt enable
    }
}
