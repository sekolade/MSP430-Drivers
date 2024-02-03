/*******************************************************************************
 * @File        : msp430_watchdog_hal.c
 * @Created_on  : 29 Mar 2023
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
void Stop_Watchdog(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
}
// TODO : void Start_Watchdog(void) eklenmeli
/***************************** End of File ************************************/
