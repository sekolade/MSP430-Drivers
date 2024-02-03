#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
#include "main.h"

/*******************************************************************************
 * Initialization of Message Buffer.
 * local_buffer : Stores all data from sensors.
 * buffer size : Predetermined as "16" by Gimbal Communication Interface data.
 * Register_Command_Data : Starting index of message.
 * Message_Size : Size of corresponding message.
 * message_index : Current index of message in buffer.
******************************************************************************/
I2C_Message_Status_Typedef Message_Status = No_Message;
uint8_t Register_Command_Data;
extern uint8_t buffer[];
uint16_t Message_Size;
volatile uint16_t message_index;
/*******************************************************************************
 * @Function_Name   : I2C_Slave_Init
 * @Function_Input  : Own Adress.
 * @Function_Output : None.
 * @Function_Brief  : This function is used for initialization of Slave.
 ******************************************************************************/
void I2C_Slave_Init(uint16_t Own_Adress)
{
    /***************************************************************************
         * I2C, predetermined configurations
         * Own address is a 7-bit address.
         * Starting Mode: Slave and Receiver
    ***************************************************************************/
    /*
        Initializing or reconfiguring the eUSCI_B module
        The recommended eUSCI_B initialization/reconfiguration process is:
        1. Set UCSWRST (BIS.B
        #UCSWRST,&UCxCTL1).
        2. Initialize all eUSCI_B registers with UCSWRST = 1 (including UCxCTL1).
        3. Configure ports.
        4. Clear UCSWRST through software (BIC.B
        #UCSWRST,&UCxCTL1).
        5. Enable interrupts (optional).
     */
    UCB0CTLW0 |= UCSWRST; //eUSCI_B is inactive logic held in reset state.
    UCB0CTLW0 &= ~(UCA10); //Own address is a 7-bit address.
    UCB0CTLW0 &= ~(UCMST); // select Slave mode
    UCB0CTLW0 |= UCMODE_3; // select I2C mode for eUSCI_B
    UCB0CTLW0 &= ~(UCTR); // select Receiver mode
    P1SEL1 |= BIT6; // select port1.6 as SDA of I2C
    P1SEL0 &= ~BIT6;
    P1SEL1 |= BIT7;// select port1.7 as SCL of I2C
    P1SEL0 &= ~BIT7;

    /* . The address is right justified. In 7-bit addressing mode, bit 6 is the
    MSB and bits 9-7 are ignored. In 10-bit addressing mode, bit 9 is the MSB.*/
    UCB0I2COA0 |= (uint16_t) Own_Adress; // set own adress of slave
    UCB0I2COA0 &= ~(UCGCEN); //Do not respond to a general call
    UCB0I2COA0 |= (UCOAEN); //= The slave address defined in I2COA0 is enabled
    UCB0CTLW0 &= ~UCSWRST;
}
/*******************************************************************************
 * @Function_Name   : I2C_Slave_Interrupt
 * @Function_Input  : Enable/Disable
 * @Function_Output : None.
 * @Function_Brief  : This function is used for configuration of clocks.
 ******************************************************************************/
void I2C_Slave_Interrupt(I2C_Interrupt_Typedef I2C_Interrupt)
{
    if(I2C_Interrupt == Enable_Interrupt)
    {
        if(Message_Status == No_Message)
        {
            Message_Status = New_Message;
        }
        UCB0IE |= UCRXIE0;//I2C Receive Interrupt Enable 0
        UCB0IE |= UCTXIE0;//I2C Transmit Interrupt Enable 0
        UCB0IE |= UCSTTIE;//I2C START Condition interrupt enable
        UCB0IE |= UCSTPIE;//I2C STOP Condition interrupt enable
        __enable_interrupt();
    }
    else if(I2C_Interrupt == Disable_Interrupt)
    {
        UCB0IE &= ~UCRXIE0;//I2C Receive Interrupt disable 0
        UCB0IE &= ~UCTXIE0;//I2C Transmit Interrupt disable 0
        UCB0IE &= ~UCSTTIE;//I2C START Condition interrupt disable
        UCB0IE &= ~UCSTPIE;//I2C STOP Condition interrupt disable
        __disable_interrupt();
    }
}

/*******************************************************************************
 * @Function_Name   : I2C_Slave_Message_Checker
 * @Function_Input  : None.
 * @Function_Output : I2C_Message_Check
 * @Function_Brief  : This function is used for checking whether there is any
 *                    I2C message request.
 ******************************************************************************/
I2C_Message_Check_Typedef I2C_Slave_Message_Checker(void)
{
    if((UCB0IFG & UCSTTIFG) != 0)
    { // I2C START Condition interrupt Flag
        return Pending;
    }
    else
    {
        return No_Pending;
    }
}


/*******************************************************************************
 * @Function_Name   : I2C_Message_Size_Selection
 * @Function_Input  : Register_Command_Data
 * @Function_Output : None
 * @Function_Brief  : This function is used for setting message_size through
 *                    predetermined Gimbal Communication Interface data.
 ******************************************************************************/
uint8_t I2C_Message_Size_Selection(uint8_t Register_Command_Data)
{
    if(Register_Command_Data == 0x00)
    {
        return 1;
    }
    else if(Register_Command_Data == 0x01)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x03)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x05)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x07)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x09)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x0B)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x0D)
    {
        return 2;
    }
    else if(Register_Command_Data == 0x0F)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void I2C_Message_Wait(void)
{
    while(Message_Status != No_Message); // wait till transmission ends
}



#pragma vector = USCI_B0_VECTOR
__interrupt void ISR_i2c_rx_tx(void)
{
    if((UCB0IFG & UCSTTIFG) != 0) // I2C START Condition interrupt Flag
    {
        if(Message_Status == New_Message)
        {
            Message_Status = Register_Message;
        }
        UCB0IFG &= ~(UCSTTIFG); // clear I2C START Condition interrupt Flag
    }
    if((UCB0IFG & UCSTPIFG) != 0)//I2C STOP Condition interrupt Flag
    {
        if(Message_Status == Register_Message)
        {
            Message_Status = Ongoing_Message;
        }
        else if(Message_Status == Ongoing_Message)
        {
            Message_Status = No_Message;
        }
        UCB0IFG &= ~(UCSTPIFG); // clear I2C STOP Condition interrupt Flag
    }
    if((UCB0IFG & UCTXIFG0) != 0)//I2C Transmit Interrupt Flag 0
    {
        if(Message_Status == Ongoing_Message){
            UCB0TXBUF = buffer[message_index];
            message_index++;
        }
        UCB0IFG &= ~(UCTXIFG0); // clear I2C Transmit Interrupt Flag 0
    }
    else if((UCB0IFG & UCRXIFG0) != 0)//I2C Receive Interrupt Flag 0
    {
        if(Message_Status == Register_Message)
        {
            Register_Command_Data = (uint8_t) UCB0RXBUF;
            Message_Size = I2C_Message_Size_Selection(Register_Command_Data);
            message_index = Register_Command_Data;
        }
        else if(Message_Status == Ongoing_Message)
        {
            buffer[message_index] = UCB0RXBUF;
            message_index++;
        }
        UCB0IFG &= ~(UCRXIFG0); // clear I2C Receive Interrupt Flag 0
    }
}
