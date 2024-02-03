#ifndef MSP430_I2C_HAL_H_
#define MSP430_I2C_HAL_H_
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
/******************* Defining Enums and Structs *******************************/


typedef enum
{
    Enable_Interrupt = 1, Disable_Interrupt = 0,
} I2C_Interrupt_Typedef;

typedef enum
{
    Pending = 1,
    No_Pending = 0,
} I2C_Message_Check_Typedef;

typedef enum
{
    New_Message = 3,
    Register_Message = 2,
    Ongoing_Message = 1,
    No_Message = 0,
} I2C_Message_Status_Typedef;


/********************** Defining Function Protypes ****************************/
void I2C_Slave_Init(uint16_t Own_Adress);
void I2C_Slave_Interrupt(I2C_Interrupt_Typedef I2C_Interrupt);
I2C_Message_Check_Typedef I2C_Slave_Message_Checker(void);
uint8_t I2C_Message_Size_Selection(uint8_t Register_Command_Data);
void I2C_Message_Wait(void);

#endif /* MSP430_I2C_HAL_H_ */
/***************************** End of File ************************************/
