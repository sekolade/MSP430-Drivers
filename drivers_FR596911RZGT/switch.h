/*******************************************************************************
 * @File        : switch.h
 * @Created_on  : 06 Mar 2023
 * @Author      : Gokhan PACAL
 * @Email       : gokhan.pacal@asisguard.com.tr
 * @About       : Embedded Software Engineer
 * @Company     : Asisguard
 * @Copyright   : All rights @Asisguard
 ******************************************************************************/
#ifndef SWITCH_H_
#define SWITCH_H_
/******************* Defining Enums and Structs *******************************/
typedef enum
{
    Day_TV_Camera_Switch = 0,
    Thermal_Camera_Switch = 1,
    Laser_Pointer_Switch = 2,
    Laser_Range_Pointer_Switch = 3,
    Video_Processing_Board_Switch = 4,
    Heater_1_Switch = 5,
    Heater_2_Switch = 6,
    Heater_3_Switch = 7,
} Switch_Typedef;
typedef enum
{
    Switch_Disable = 0, Switch_Enable = 1,
} Switch_Status_Typedef;
/********************** Defining Function Protypes ****************************/
void Switch_Init(void);
void Switch_Set(Switch_Typedef Switch_Name,
                Switch_Status_Typedef Switch_Status);
#endif /* SWITCH_H_ */
/***************************** End of File ************************************/
