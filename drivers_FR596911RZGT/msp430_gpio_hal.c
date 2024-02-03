/*******************************************************************************
 * @File        : msp430_gpio_hal.c
 * @Created_on  : 24 Mar 2023
 * @Author      : Gokhan PACAL
 * @Email       : gokhan.pacal@asisguard.com.tr
 * @About       : Embedded Software Engineer
 * @Company     : Asisguard
 * @Copyright   : All rights @Asisguard
 ******************************************************************************/
/************************ Defining Header *************************************/
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
#include "main.h"
/************************ Defining Private Variables **************************/

/************************ Defining Private Externs ****************************/

/*******************************************************************************
 * @Function_Name   : MSP_HAL_GPIO_Set
 * @Function_Input  : Port Number, Pin Number and IO Status
 * @Function_Output : None.
 * @Function_Brief  : This function using for set IO Status
 ******************************************************************************/
void MSP_HAL_GPIO_Set(PortNum_Typedef GPIO_Port, PinNum_Typedef GPIO_Pin,
                      IO_Status_Typedef GPIO_IO_Status)
{
    volatile uint8_t Temp_GPIO_Pin = 0x01;
    volatile uint8_t Shift_Number = 0;
    if(GPIO_Pin == Pin_0)
        Shift_Number = 0;
    if(GPIO_Pin == Pin_1)
        Shift_Number = 1;
    if(GPIO_Pin == Pin_2)
        Shift_Number = 2;
    if(GPIO_Pin == Pin_3)
        Shift_Number = 3;
    if(GPIO_Pin == Pin_4)
        Shift_Number = 4;
    if(GPIO_Pin == Pin_5)
        Shift_Number = 5;
    if(GPIO_Pin == Pin_6)
        Shift_Number = 6;
    if(GPIO_Pin == Pin_7)
        Shift_Number = 7;
    Temp_GPIO_Pin = Temp_GPIO_Pin << Shift_Number;
    switch (GPIO_Port)
    {
    case Port_1:
#ifdef __MSP430_HAS_PORT1_R__
        if (GPIO_IO_Status == Output)
        {
            P1SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P1SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P1DIR |= Temp_GPIO_Pin;   // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P1SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P1SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P1DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_2:
#ifdef __MSP430_HAS_PORT2_R__
        if (GPIO_IO_Status == Output)
        {
            P2SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P2SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P2DIR |= Temp_GPIO_Pin;  // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P2SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P2SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P2DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_3:
#ifdef __MSP430_HAS_PORT3_R__
        if (GPIO_IO_Status == Output)
        {
            P3SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P3SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P3DIR |= Temp_GPIO_Pin;  // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P3SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P3SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P3DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            // Do nothing.
        }
#endif
        break;

    case Port_4:
#ifdef __MSP430_HAS_PORT4_R__
        if (GPIO_IO_Status == Output)
        {
            P4SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P4SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P4DIR |= Temp_GPIO_Pin;  // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P4SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P4SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P4DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_5:
#ifdef __MSP430_HAS_PORT5_R__
        if (GPIO_IO_Status == Output)
        {
            P5SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P5SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P5DIR |= Temp_GPIO_Pin;  // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P5SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P5SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P5DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_6:
#ifdef __MSP430_HAS_PORT6_R__
        if (GPIO_IO_Status == Output)
        {
            P6SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P6SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P6DIR |= Temp_GPIO_Pin;  // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P6SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P6SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P6DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            //Do nothing.
        }
#endif
        break;
    case Port_7:
#ifdef __MSP430_HAS_PORT7_R__
        if (GPIO_IO_Status == Output)
        {
            P7SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P7SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P7DIR |= Temp_GPIO_Pin;  // Set output
        }
        else if (GPIO_IO_Status == Input)
        {
            P7SEL0 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P7SEL1 &= ~Temp_GPIO_Pin; // Set General Purpose I-O
            P7DIR &= ~Temp_GPIO_Pin;  // Set input
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    default:
        break;
    }

}
/*******************************************************************************
 * @Function_Name   : MSP_HAL_GPIO_Pull_Up_Down_Set
 * @Function_Input  : Port Number, Pin Number and GPIO Pull Up - Pull Down Status
 * @Function_Output : None.
 * @Function_Brief  : This function using for set Pull up - Pull Down Status
 ******************************************************************************/
void MSP_HAL_GPIO_Pull_Up_Down_Set(PortNum_Typedef GPIO_Port,
                                   PinNum_Typedef GPIO_Pin,
                                   Pull_Status_Typedef GPIO_Pull_Up_Down_Status)
{
    volatile uint8_t Temp_GPIO_Pin = 1;
    volatile uint8_t Shift_Number = (uint8_t)GPIO_Pin;
    Temp_GPIO_Pin = Temp_GPIO_Pin << Shift_Number;
    switch (GPIO_Port)
    {
    case Port_1:
#ifdef __MSP430_HAS_PORT1_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P1REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P1REN |= Temp_GPIO_Pin;

        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P1REN &= Temp_GPIO_Pin;

        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_2:
#ifdef __MSP430_HAS_PORT2_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P2REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P2REN |= Temp_GPIO_Pin;

        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P2REN &= Temp_GPIO_Pin;

        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_3:
#ifdef __MSP430_HAS_PORT3_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P3REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P3REN |= Temp_GPIO_Pin;

        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P3REN &= Temp_GPIO_Pin;
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_4:
#ifdef __MSP430_HAS_PORT4_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P4REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P4REN |= Temp_GPIO_Pin;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P4REN &= Temp_GPIO_Pin;
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_5:
#ifdef __MSP430_HAS_PORT5_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P5REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P5REN |= Temp_GPIO_Pin;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P5REN &= Temp_GPIO_Pin;
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_6:
#ifdef __MSP430_HAS_PORT6_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P6REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P6REN |= Temp_GPIO_Pin;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P6REN &= Temp_GPIO_Pin;
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_7:
#ifdef __MSP430_HAS_PORT7_R__
        if (GPIO_Pull_Up_Down_Status == No_Pull_Up_No_Pull_Down)
        {
            P7REN = 0;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Up)
        {
            P7REN |= Temp_GPIO_Pin;
        }
        else if (GPIO_Pull_Up_Down_Status == Pull_Down)
        {
            Temp_GPIO_Pin = ~Temp_GPIO_Pin;
            P7REN &= Temp_GPIO_Pin;
        }
        else
        {
            // Do nothing.
        }
        break;
#endif
    default:
        break;
    }
}
/*******************************************************************************
 * @Function_Name   : MSP_HAL_GPIO_Output_Set
 * @Function_Input  : Port Number, Pin Number and GPIO Output Status
 * @Function_Output : None.
 * @Function_Brief  : This function using for set Output Status
 ******************************************************************************/
void MSP_HAL_GPIO_Output_Set(PortNum_Typedef GPIO_Port, PinNum_Typedef GPIO_Pin,
                             Output_Status_Typedef GPIO_Output_Status)
{
    volatile uint8_t Temp_GPIO_Dir;
    volatile uint8_t Temp_GPIO_Ren;
    volatile uint8_t Temp_GPIO_Pin = 1;
    volatile uint8_t Shift_Number = (uint8_t)GPIO_Pin;
    Temp_GPIO_Pin = Temp_GPIO_Pin << GPIO_Pin;

    switch (GPIO_Port)
    {
    case Port_1:
#ifdef __MSP430_HAS_PORT1_R__
        Temp_GPIO_Dir = P1DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
        if (Temp_GPIO_Dir == 1)
        {
            Temp_GPIO_Ren = P1REN;
            Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Ren == 0)
            {
                if (GPIO_Output_Status == Output_High)
                {
                    P1OUT |= Temp_GPIO_Pin;

                }
                else if (GPIO_Output_Status == Output_Low)
                {
                    Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                    P1OUT &= Temp_GPIO_Pin;
                }
                else
                {
                    // Do nothing.
                }
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_2:
#ifdef __MSP430_HAS_PORT2_R__
        Temp_GPIO_Dir = P2DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
        if (Temp_GPIO_Dir == 1)
        {
            Temp_GPIO_Ren = P2REN;
            Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Ren == 0)
            {
                if (GPIO_Output_Status == Output_High)
                {
                    P2OUT |= Temp_GPIO_Pin;

                }
                else if (GPIO_Output_Status == Output_Low)
                {
                    Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                    P2OUT &= Temp_GPIO_Pin;
                }
                else
                {
                    // Do nothing.
                }
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_3:
#ifdef __MSP430_HAS_PORT3_R__
        Temp_GPIO_Dir = P3DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
        if (Temp_GPIO_Dir == 1)
        {
            Temp_GPIO_Ren = P3REN;
            Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Ren == 0)
            {
                if (GPIO_Output_Status == Output_High)
                {
                    P3OUT |= Temp_GPIO_Pin;

                }
                else if (GPIO_Output_Status == Output_Low)
                {
                    Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                    P3OUT &= Temp_GPIO_Pin;
                }
                else
                {
                    // Do nothing.
                }
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_4:
#ifdef __MSP430_HAS_PORT4_R__
            Temp_GPIO_Dir = P4DIR;
            Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Dir == 1)
            {
                Temp_GPIO_Ren = P4REN;
                Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
                if (Temp_GPIO_Ren == 0)
                {
                    if (GPIO_Output_Status == Output_High)
                    {
                        P4OUT |= Temp_GPIO_Pin;

                    }
                    else if (GPIO_Output_Status == Output_Low)
                    {
                        Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                        P4OUT &= Temp_GPIO_Pin;
                    }
                    else{
                        // Do nothing.
                    }
                }
                else{
                    // Do nothing.
                }
            }
            else{
                // Do nothing.
            }
#endif
        break;
    case Port_5:
#ifdef __MSP430_HAS_PORT5_R__
            Temp_GPIO_Dir = P5DIR;
            Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Dir == 1)
            {
                Temp_GPIO_Ren = P5REN;
                Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
                if (Temp_GPIO_Ren == 0)
                {
                    if (GPIO_Output_Status == Output_High)
                    {
                        P5OUT |= Temp_GPIO_Pin;

                    }
                    else if (GPIO_Output_Status == Output_Low)
                    {
                        Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                        P5OUT &= Temp_GPIO_Pin;
                    }
                    else{
                        // Do nothing.
                    }
                }
                else{
                    // Do nothing.
                }
            }
            else{
                // Do nothing.
            }
#endif
        break;
    case Port_6:
#ifdef __MSP430_HAS_PORT6_R__
            Temp_GPIO_Dir = P6DIR;
            Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Dir == 1)
            {
                Temp_GPIO_Ren = P6REN;
                Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
                if (Temp_GPIO_Ren == 0)
                {
                    if (GPIO_Output_Status == Output_High)
                    {
                        P6OUT |= Temp_GPIO_Pin;

                    }
                    else if (GPIO_Output_Status == Output_Low)
                    {
                        Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                        P6OUT &= Temp_GPIO_Pin;
                    }
                    else{
                        // Do nothing.
                    }
                }
                else{
                    // Do nothing.
                }
            }
            else{
                // Do nothing.
            }
#endif
        break;
    case Port_7:
#ifdef __MSP430_HAS_PORT7_R__
            Temp_GPIO_Dir = P7DIR;
            Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - Shift_Number)) >> 7;
            if (Temp_GPIO_Dir == 1)
            {
                Temp_GPIO_Ren = P7REN;
                Temp_GPIO_Ren = (Temp_GPIO_Ren << (7 - Shift_Number)) >> 7;
                if (Temp_GPIO_Ren == 0)
                {
                    if (GPIO_Output_Status == Output_High)
                    {
                        P7OUT |= Temp_GPIO_Pin;

                    }
                    else if (GPIO_Output_Status == Output_Low)
                    {
                        Temp_GPIO_Pin = ~Temp_GPIO_Pin;
                        P7OUT &= Temp_GPIO_Pin;
                    }
                    else{
                        // Do nothing.
                    }
                }
                else{
                    // Do nothing.
                }
            }
            else{
                // Do nothing.
            }
#endif
        break;

    default:
        break;
    }
}
/*******************************************************************************
 * @Function_Name   : MSP_HAL_GPIO_Read
 * @Function_Input  : Port Number, Pin Number
 * @Function_Output : GPIO_Input_Status
 * @Function_Brief  : This function using for reading port value
 ******************************************************************************/
GPIO_Input_Status_typedef MSP_HAL_GPIO_Read(PortNum_Typedef GPIO_Port,
                                            PinNum_Typedef GPIO_Pin)
{
    uint8_t Temp_GPIO_Dir;
    uint8_t Temp_GPIO_Pin = 1;
    uint8_t Temp_GPIO_In;
    Temp_GPIO_Pin = Temp_GPIO_Pin << GPIO_Pin;

    switch (GPIO_Port)
    {
    case Port_1:
#ifdef __MSP430_HAS_PORT1_R__
        Temp_GPIO_Dir = P1DIR; // Port_1 Input Deðerlerini Oku.
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0) // GPIO Input Ýse.
        {
            Temp_GPIO_In = P1IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == 0)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == 1)
            {
                return Input_High;
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_2:
#ifdef __MSP430_HAS_PORT2_R__
        Temp_GPIO_Dir = P2DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0)
        {
            Temp_GPIO_In = P2IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == 0)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == 1)
            {
                return Input_High;
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_3:
#ifdef __MSP430_HAS_PORT3_R__
        Temp_GPIO_Dir = P3DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0)
        {
            Temp_GPIO_In = P3IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == Output_Low)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == Output_High)
            {
                return Input_High;
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_4:
#ifdef __MSP430_HAS_PORT4_R__
        Temp_GPIO_Dir = P4DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0)
        {
            Temp_GPIO_In = P4IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == Output_Low)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == Output_High)
            {
                return Input_High;
            }
            else{
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_5:
#ifdef __MSP430_HAS_PORT5_R__
        Temp_GPIO_Dir = P5DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0)
        {
            Temp_GPIO_In = P5IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == Output_Low)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == Output_High)
            {
                return Input_High;
            }
            else{
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_6:
#ifdef __MSP430_HAS_PORT6_R__
        Temp_GPIO_Dir = P6DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0)
        {
            Temp_GPIO_In = P6IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == Output_Low)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == Output_High)
            {
                return Input_High;
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    case Port_7:
#ifdef __MSP430_HAS_PORT7_R__
        Temp_GPIO_Dir = P7DIR;
        Temp_GPIO_Dir = (Temp_GPIO_Dir << (7 - GPIO_Pin)) >> 7;
        if (Temp_GPIO_Dir == 0)
        {
            Temp_GPIO_In = P7IN;
            Temp_GPIO_In = (Temp_GPIO_In << (7 - GPIO_Pin)) >> 7;
            if (Temp_GPIO_In == Output_Low)
            {
                return Input_Low;
            }
            else if (Temp_GPIO_In == Output_High)
            {
                return Input_High;
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
#endif
        break;
    default:
        break;
    }
    return Input_Error;
}
/***************************** End of File ************************************/
