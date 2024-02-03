#include <msp430.h> 
#include <stdint.h>
//fr2433 master

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
uint16_t *UCB0IE_ = (uint16_t *) 0x056A;
uint16_t *UCB0IFG_ = (uint16_t *) 0x0056C;

uint8_t message[5] = {1,2,3,4,5};
uint8_t index = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//setup button
	*P2DIR_ |= 0<<3; //input
	*P2REN_ |= 1<<3; //resistor
	*P2OUT_ |= 1<<3; //pull up
	*P2IES_ |= 1<<3; //high to low
	*P2IE_ |= 1<<3; //interrupt enable
	*P2IFG_ &= ~1<<3; //clear flag
	//setup i2c
	*UCB0CTLW0_ |= 1; //reset
	*UCB0CTLW0_ |= 0<<14; // 7-bit adress slave
	*UCB0CTLW0_ |= 1<<11; //master mode
	*UCB0CTLW0_ |= 0b11<<9; //i2c mode
	*UCB0CTLW0_ |= 0b11<<6; //smclk
	*UCB0CTLW0_ |= 1<<4; //transmit

	*UCB0CTLW1_ |= 0b10<<2; //auto stop after sent byte count reaches UCB0TBCNT
	*UCB0CTLW1_ |= 0b11<<6; //clock low time-out counter (count for 34ms)
	*UCB0BR0_ = (uint16_t) 0xFFFF;  //prescalar = 10
	//*UCB0TBCNT_ = sizeof(message); // sent 4 bytes than sent stop condition
	*UCB0TBCNT_ =(uint16_t) 5;
	*UCB0I2CSA_ = (uint16_t) 0b1000001; // slave adress = 0x0012

	*P1SEL1_ &= ~(1<<2); // p1.2 as sda
	*P1SEL0_ |= 1<<2;
    *P1SEL1_ &= ~(0<<3);// p1.3 as scl
    *P1SEL0_ |= 1<<3;

    *UCB0CTLW0_ &= ~1; //disable reset

    *UCB0IE_ |= 1<<1; //tx interrupt enable
    *UCB0IE_ |= 1; //rx interrupt enable
    *UCB0IE_ |= 1<<5; //no ack interrupt enable
    *UCB0IE_ |= 1<<7; //clock low time-out interrupt enable

	PM5CTL0 &= ~LOCKLPM5; // enable i/o
	__enable_interrupt(); //enable global interrupt
	//*UCB0CTLW0_ |= 1<<2; //stop bit
	while(1){
	}
	return 0;
}

#pragma vector = PORT2_VECTOR
__interrupt void ISR_button(void)
{
    if((*P2IFG_ & 1<<3) !=0){
        *P2IFG_ &= ~(1<<3);
        //*P2IFG_ &= ~(1<<3);
        index = 0;
        *UCB0CTLW0_ |= 1<<4; //transmit = write
        // *UCB0CTLW0_ &= ~(1<<4); //recieve = read
        //*UCB0IFG_ &= ~(1<<3); // clear stop condition detected flag
        //*UCB0CTLW0_ |= 1<<2; //set stop condition
        //for(i = 1; i<40000;i++){};
        *UCB0CTLW0_ |= 1<<1; //START
        //*UCB0TXBUF_ = message[index];
    }
}
#pragma vector = USCI_B0_VECTOR
__interrupt void ISR_rx_tx(void)
{
    if((*UCB0IFG_ & 1) != 0){ //rx
        *UCB0IFG_ &= ~1; //clear rx flag
        message[index] = *UCB0RXBUF_; //recieve byte
        index++;
    }
    else if((*UCB0IFG_ & 1<<1) != 0){ //tx
        *UCB0IFG_ &= ~(1<<1); //clear tx flag
        *UCB0TXBUF_ = message[index]; //sent byte
        index++;
    }
    else if((*UCB0IFG_ & 1<<5) != 0){ // no ack
        *UCB0CTLW0_ |= 1<<2; //set stop condition
        *UCB0IFG_ &= ~(1<<5); //clear no ack flag
    }
    else if((*UCB0IFG_ & 1<<7) != 0){ // clock low time-out
        *UCB0IFG_ &= ~(1<<7);
    }
}
