#ifndef MSP430_ADC_HAL_H_
#define MSP430_ADC_HAL_H_
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
/******************* Defining Enums and Structs *******************************/

typedef enum
{
    Activate = 1,
    Deactivate = 0,
}ADC_Activation_Typedef;

typedef enum
{
    Op_Amp_Port_1_0 = 4,
    Op_Amp_Port_1_1 = 3,
    Op_Amp_Port_1_2 = 2,
    Op_Amp_Port_3_1 = 1,
}ADC_Op_Amp_Typedef;

typedef enum
{
    Op_Amp_Port_1_0_Register = 0x0B,
    Op_Amp_Port_1_1_Register = 0x07,
    Op_Amp_Port_1_2_Register = 0x0D,
    Op_Amp_Port_3_1_Register = 0x09,
}ADC_Op_Amp_Register_Typedef;

/********************** Defining Function Protypes ****************************/
void ADC_Init(void);
void ADC_Activation(ADC_Op_Amp_Typedef op_amp, ADC_Activation_Typedef status);
void ADC_Read_Value(ADC_Op_Amp_Register_Typedef register_adress);
#endif /* MSP430_I2C_HAL_H_ */
/***************************** End of File ************************************/
