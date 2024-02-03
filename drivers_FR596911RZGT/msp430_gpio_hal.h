/*******************************************************************************
 * @Header_Name : msp430_gpio_hal.h
 * @Created_on  : 24 Mar 2023
 * @Author      : Gokhan PACAL
 * @Email       : gokhan.pacal
 * @Company     : Asisguard
 * @Copyright   : All @Asisguard
 ******************************************************************************/

#ifndef MSP430_GPIO_HAL_H_
#define MSP430_GPIO_HAL_H_
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
/******************* Defining Enums and Structs *******************************/
typedef enum
{
    Input = 0, Output = 1,
} IO_Status_Typedef;

typedef enum
{
    Pull_Down = 0, Pull_Up = 1, No_Pull_Up_No_Pull_Down = 2,
} Pull_Status_Typedef;

typedef enum
{
    Pin_0 = 0,
    Pin_1 = 1,
    Pin_2 = 2,
    Pin_3 = 3,
    Pin_4 = 4,
    Pin_5 = 5,
    Pin_6 = 6,
    Pin_7 = 7,
} PinNum_Typedef;

typedef enum
{
    Port_1 = 1,
    Port_2 = 2,
    Port_3 = 3,
    Port_4 = 4,
    Port_5 = 5,
    Port_6 = 6,
    Port_7 = 7,
} PortNum_Typedef;

typedef enum
{
    Output_Low = 0, Output_High = 1,
} Output_Status_Typedef;

typedef enum
{
    Input_Low = 0, Input_High = 1, Input_Error = 2,
} GPIO_Input_Status_typedef;

/********************** Defining Function Protypes ****************************/

void MSP_HAL_GPIO_Set(PortNum_Typedef GPIO_Port, PinNum_Typedef GPIO_Pin,
                      IO_Status_Typedef GPIO_IO_Status);
void MSP_HAL_GPIO_Pull_Up_Down_Set(
        PortNum_Typedef GPIO_Port, PinNum_Typedef GPIO_Pin,
        Pull_Status_Typedef GPIO_Pull_Up_Down_Status);
void MSP_HAL_GPIO_Output_Set(PortNum_Typedef GPIO_Port, PinNum_Typedef GPIO_Pin,
                             Output_Status_Typedef GPIO_Output_Status);
GPIO_Input_Status_typedef MSP_HAL_GPIO_Read(PortNum_Typedef GPIO_Port,
                                            PinNum_Typedef GPIO_Pin);
#endif /* MSP430_GPIO_HAL_H_ */
/***************************** End of File ************************************/
