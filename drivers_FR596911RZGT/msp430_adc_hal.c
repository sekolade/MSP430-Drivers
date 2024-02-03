#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
#include <main.h>
/*******************************************************************************
 * @Function_Name   : ADC_Init
 * @Function_Input  : None.
 * @Function_Output : None.
 * @Function_Brief  : This function is used for initialization of ADC.
 *                    With configuration below,ADC read value stored as 0 to 255
 *                    or 0000h to 00FFh in ADC12MEM0 0 --> 0V , 255 --> 3.4V
 ******************************************************************************/
/******************************************************************************/
extern uint8_t buffer[];
/******************************************************************************/
void ADC_Init(void)
{
    P1SEL1 |= BIT0; // select port1.0 as ADC
    P1SEL0 |= BIT0;
    P1SEL1 |= BIT1; // select port1.1 as ADC
    P1SEL0 |= BIT1;
    P1SEL1 |= BIT2; // select port1.2 as ADC
    P1SEL0 |= BIT2;
    P3SEL1 |= BIT1; // select port3.1 as ADC
    P3SEL0 |= BIT1;
    ADC12CTL0 |= ADC12SHT01; // 16 ADC12CLK cycles
    ADC12CTL0 |= ADC12SHT11;
    ADC12CTL0 &= ~ADC12MSC; /*The sampling timer requires a rising edge of the
                            SHI signal to trigger each sample-and-convert.*/
    ADC12CTL1 |= ADC12SHP; // SAMPCON signal is sourced from the sampling timer.
    ADC12CTL1 |= ADC12SSEL0_L;//Chose SMCLK
    ADC12CTL1 |= ADC12SSEL1_L;
    ADC12CTL1 &= ~ADC12CONSEQ0;//Single-channel, single-conversion
    ADC12CTL1 &= ~ADC12CONSEQ0;
    ADC12CTL2 &= ~ADC12RES1_L; // 8 bit resolution
    ADC12CTL3 &= ~ADC12CSTARTADD0_L; //ADC12MEM0 is used for a single conversion
    ADC12CTL3 &= ~ADC12CSTARTADD1_L;
    ADC12CTL3 &= ~ADC12CSTARTADD2_L;
    ADC12CTL3 &= ~ADC12CSTARTADD3_L;
    ADC12CTL3 &= ~ADC12CSTARTADD4_L;

    /*  ADC read value stored as 0 to 255 or 0000h to 00FFh in ADC12MEM0
        0 --> 0V , 255 --> 3.4V
    */
}
/*******************************************************************************
 * @Function_Name   : ADC_Activation
 * @Function_Input  : Op_Amp, Activate/Deactivate.
 * @Function_Output : None.
 * @Function_Brief  : This function is used for activation/deactivation of ADC
 *                    for given Op_Amp.
 ******************************************************************************/
void ADC_Activation(ADC_Op_Amp_Typedef op_amp, ADC_Activation_Typedef status)
{
    if(status == Activate)
    {
        if(op_amp == Op_Amp_Port_1_0)
        {
            ADC12MCTL0 &= ~ADC12INCH0;//set Op_Amp_Port_1_0 to ADC12MEM0
            ADC12MCTL0 &= ~ADC12INCH1;
            ADC12MCTL0 &= ~ADC12INCH2;
            ADC12MCTL0 &= ~ADC12INCH3;
            ADC12MCTL0 &= ~ADC12INCH4;

        }
        else if(op_amp == Op_Amp_Port_1_1)//set Op_Amp_Port_1_1 to ADC12MEM0
        {
            ADC12MCTL0 |= ADC12INCH0;
            ADC12MCTL0 &= ~ADC12INCH1;
            ADC12MCTL0 &= ~ADC12INCH2;
            ADC12MCTL0 &= ~ADC12INCH3;
            ADC12MCTL0 &= ~ADC12INCH4;
        }
        else if(op_amp == Op_Amp_Port_1_2)//set Op_Amp_Port_1_2 to ADC12MEM0
        {
            ADC12MCTL0 &= ~ADC12INCH0;
            ADC12MCTL0 |= ADC12INCH1;
            ADC12MCTL0 &= ~ADC12INCH2;
            ADC12MCTL0 &= ~ADC12INCH3;
            ADC12MCTL0 &= ~ADC12INCH4;
        }
        else if(op_amp == Op_Amp_Port_3_1)//set Op_Amp_Port_3_1 to ADC12MEM0
        {
            ADC12MCTL0 |= ADC12INCH0;
            ADC12MCTL0 &= ~ADC12INCH1;
            ADC12MCTL0 |= ADC12INCH2;
            ADC12MCTL0 |= ADC12INCH3;
            ADC12MCTL0 &= ~ADC12INCH4;
        }
        ADC12CTL0 |= ADC12ON; //ADC12_B on
        ADC12CTL0 |= (ADC12SC | ADC12ENC);//enable conversion + start conversion

    }
    else if(status == Deactivate)
    {
        ADC12CTL0 &=~(ADC12SC | ADC12ENC);//disable + stop conversion
        ADC12CTL0 &= ~ADC12ON; //ADC12_B off
    }
}
/*******************************************************************************
 * @Function_Name   : ADC_Read_Value
 * @Function_Input  : register_adress.
 * @Function_Output : None.
 * @Function_Brief  : This function is used for storing ADC value.
 ******************************************************************************/
void ADC_Read_Value(ADC_Op_Amp_Register_Typedef register_adress)
{
    while((ADC12IFGR0 & ADC12IFG0) == 0); //wait till ADC peripheral reads value

    uint16_t value = (uint16_t) ((((uint8_t) ADC12MEM0) *(0.0039215686274509803921568627451))*(3.3)*1000);
    buffer[register_adress] = (uint8_t) (value & (0b0000000011111111));
    buffer[register_adress + 1] = (uint8_t) ((value >> 8) & (0b0000000011111111));
}


