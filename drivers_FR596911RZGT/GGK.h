/*******************************************************************************
 * @File        : GKK.h
 * @Created_on  : 24 Mar 2023
 * @Author      : Gokhan PACAL
 * @Email       : gokhan.pacal@asisguard.com.tr
 * @About       : Embedded Software Engineer
 * @Company     : Asisguard
 * @Copyright   : All rights @Asisguard
 ******************************************************************************/
#ifndef GGK_H_
#define GGK_H_
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>


/******************* Defining Enums *******************************************/
typedef enum{
    FSM_Deactive    = 0,
    FSM_Active      = 1
}FSM_Status_Typedef;

typedef enum {
    FSM_I2C = 0,
    FSM_Read_Temperature = 1,
    FSM_Read_Op_Amp_Port_1_0 = 2,
    FSM_Read_Op_Amp_Port_1_1 = 3,
    FSM_Read_Op_Amp_Port_1_2 = 4,
    FSM_Read_Op_Amp_Port_3_1 = 5,
}FSM_Idle_Typedef;
/******************* Defining Structs *****************************************/

/******************* Defining Function Protypes *******************************/
void GGK_FSM_Init(void);
void GGK_FSM(FSM_Status_Typedef Temp_FMS_Status);
#endif /* GGK_H_ */
/***************************** End of File ************************************/
