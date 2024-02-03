/*******************************************************************************
 * @File        : GKK.c
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
#define master 1

#ifdef slave

#endif

#ifdef master

#endif

/*******************************************************************************
 * Initialization of Message Buffer.
 * buffer : Stores all data from sensors.
 * buffer size : Predetermined as "16" by Gimbal Communication Interface data.
******************************************************************************/
uint8_t buffer[16] = {0};



/************************ Defining Private Externs ****************************/

/*******************************************************************************
 * @Function_Name   : GGK_FSM_Init
 * @Function_Input  : None.
 * @Function_Output : None.
 * @Function_Brief  : This function is used for one time run configurations.
 ******************************************************************************/
void GGK_FSM_Init(void){
    /********************************Watchdog**********************************/
    Stop_Watchdog();
    /********************************Clock*************************************/
    // TODO : Clock_Config();
    Clock_Config();
    /********************************I2C***************************************/
    uint16_t Own_Adress = 0x10;
    I2C_Slave_Init((uint16_t) Own_Adress);
    I2C_Slave_Interrupt(Disable_Interrupt);
    /********************************ADC***************************************/
    ADC_Init();
    /**************************************************************************/
    // TODO : GPIO_Inýt();
    // TODO : I2C_Init();
    // TODO : Temperature_Init();
    // TODO : ADC_Init;

}
/*******************************************************************************
 * @Function_Name   : GGK_FSM
 * @Function_Input  : Temp_FMS_Status
 * @Function_Output : None.
 * @Function_Brief  : This function used to run FSM loop or test mode depending
 *                    on Temp_FMS_Status value.
 ******************************************************************************/
void GGK_FSM(FSM_Status_Typedef Temp_FMS_Status){
    FSM_Idle_Typedef FSM_State =  FSM_I2C;
    while(Temp_FMS_Status == FSM_Active)
    {
        if(FSM_State ==  FSM_I2C)
        {
            if(I2C_Slave_Message_Checker() == Pending)
            {
                I2C_Slave_Interrupt(Enable_Interrupt);
                I2C_Message_Wait();
                I2C_Slave_Interrupt(Disable_Interrupt);
            }
            FSM_State = FSM_Read_Temperature;
        }
        if(FSM_State == FSM_Read_Temperature)
        {



            FSM_State = FSM_Read_Op_Amp_Port_1_0;
        }
        if(FSM_State == FSM_Read_Op_Amp_Port_1_0)
        {
            ADC_Activation(Op_Amp_Port_1_0, Activate);
            ADC_Read_Value(Op_Amp_Port_1_0_Register);
            ADC_Activation(Op_Amp_Port_1_0, Deactivate);
            FSM_State = FSM_Read_Op_Amp_Port_1_1;
        }
        if(FSM_State == FSM_Read_Op_Amp_Port_1_1)
        {
            ADC_Activation(Op_Amp_Port_1_1, Activate);
            ADC_Read_Value(Op_Amp_Port_1_1_Register);
            ADC_Activation(Op_Amp_Port_1_1, Deactivate);
            FSM_State = FSM_Read_Op_Amp_Port_1_2;
        }
        if(FSM_State == FSM_Read_Op_Amp_Port_1_2)
        {
            ADC_Activation(Op_Amp_Port_1_2, Activate);
            ADC_Read_Value(Op_Amp_Port_1_2_Register);
            ADC_Activation(Op_Amp_Port_1_2, Deactivate);
            FSM_State = FSM_Read_Op_Amp_Port_3_1;
        }
        if(FSM_State == FSM_Read_Op_Amp_Port_3_1)
        {
            ADC_Activation(Op_Amp_Port_3_1, Activate);
            ADC_Read_Value(Op_Amp_Port_3_1_Register);
            ADC_Activation(Op_Amp_Port_3_1, Deactivate);
            FSM_State = FSM_I2C;
        }
    }
    //******************** TEST MODE ******************************************/
    while(Temp_FMS_Status == FSM_Deactive)
    {

    }
}





/***************************** End of File ************************************/
