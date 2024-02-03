/*******************************************************************************
 * @File        : main.c
 * @Created_on  : 05 Mar 2023
 * @Author      : Gokhan PACAL
 * @Email       : gokhan.pacal@asisguard.com.tr
 * @About       : Embedded Software Engineer
 * @Company     : Asisguard
 * @Copyright   : All rights @Asisguard
 ******************************************************************************/
/***************************** Inculudes **************************************/

/***************************** Private Includes *******************************/
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
#include "main.h"
/***************************** Private Defines ********************************/

/***************************** Private Externs ********************************/

/***************************** Private Variables ******************************/

/***************************** Main Starting **********************************/

void main(void)
{
    GGK_FSM_Init();

    while(1){
        GGK_FSM(FSM_Active);
    }
}

/***************************** End of File ************************************/
