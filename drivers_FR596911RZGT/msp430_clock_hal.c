/*
 * msp430_clock_hal.c
 *
 *  Created on: 29 Mar 2023
 *      Author: gokhan.pacal
 */
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
#include "main.h"

//#include <msp430g2553.h>

/*******************************************************************************
 * @Function_Name   : Clock_Config
 * @Function_Input  : None.
 * @Function_Output : None.
 * @Function_Brief  : This function is used for configuration of clocks.
 ******************************************************************************/
void Clock_Config(void){

    /***************************************************************************
     * ACLK Clock Configuration to select ACLK source as VLOCLK
     * ACLK: Auxiliary clock.
     * ACLK can be divided by 1, 2, 4, 8, 16, or 32 by DIVA__x bit in CSCTL3
     * fVLO VLO frequency Measured at ACLK ~= 9.4 kHz
    ***************************************************************************/
    //CSCTL2 |= SELA__VLOCLK; //  ACLK source = VLOCLK
    //CSCTL3 |= DIVA__1; /* ACLK Source Divider f(ACLK)/1 */
    //CSCTL4 &= ~VLOOFF; /* VLO Off disable */








    /* -> DCOCTL Register
     * Bit 7-5 : DCOx = DCO Select Bit 0,
     *                  DC1 Select Bit 1,
     *                  DC2 Select Bit 2
     * Bit 4-0 : MODx = Modulation Bit 0,
     *                  Modulation Bit 1,
     *                  Modulation Bit 2,
     *                  Modulation Bit 3,
     *                  Modulation Bit 4,
     * -> BCSCTL1 Register
     * Bit 7 : XT2OFF = 0b = XT2 is on
     *                  1b = XT2 is off if it is not used for MCLK or SMCLK.
     * Bit 6 : XTS = LFXT1 mode select 0b = Low-frequency mode
     *                                 1b = High-frequency mode
     * Bit 5-4 : DIVAx = Divider for ACLK 00b = /1
     *                                    01b = /2
     *                                    10b = /4
     *                                    11b = /8
     * Bit 3-0 : RSELx = Range select. The lowest RSELx = 0.
     *                               RSEL3 is ignored when DCOR = 1.
     * -> BCSCTL2 Register
     * Bit 7-6 : SELMx = Select MCLK. 00b = DCOCLK
     *                                01b = DCOCLK
     *                                10b = XT2CLK when XT2 oscillator present.
     *                       LFXT1CLK or VLOCLK when XT2 oscillator not present
     *                                11b = LFXT1CLK or VLOCLK
     * Bit 5-4 : DIVMx = Divider for MCLK. 00b = /1
     *                                     01b = /2
     *                                     10b = /4
     *                                     11b = /8
     * Bit 3 : SELS = Select SMCLK. 0b = DCOCLK
     *                              1b = XT2CLK when XT2 oscillator present.
     *                        LFXT1CLK or VLOCLK when XT2 oscillator not present
     * Bit 2-1 : DIVSx = Divider for SMCLK 00b = /1
     *                                     01b = /2
     *                                     10b = /4
     *                                     11b = /8
     * Bit 0 : DCOR = DCO resistor select. 0b = Internal resistor
     *                                     1b = External resistor
     * -> BCSCTL3 Register
     * Bit 7-6 : XT2Sx = XT2 range select. 00b = 0.4- to 1-MHz clock source
     *                                     01b = 1- to 3-MHz
     *                                     10b = 3- to 16-MHz
     *                                     11b = Digital external 0.4- to 16-MHz
     * Bit 5-4 : LFXT1Sx :Low-frequency clock select and LFXT1 range select
     * -When XTS = 0:
     *  00b = 32768-Hz crystal on LFXT1
     *  01b = Reserved
     *  10b = VLOCLK (Reserved in MSP430F21x1 devices)
     *  11b = Digital external clock source
     *  00b = 0.4- to 1-MHz crystal or resonator
     * -When XTS = 1
     * (Not applicable for MSP430F20xx, MSP430G2xx1,MSP430G2xx2, MSP430G2xx3):
     *  00b = 0.4- to 1-MHz crystal or resonator
     *  01b = 1- to 3-MHz crystal or resonator
     *  10b = 3- to 16-MHz crystal or resonator
     *  11b = Digital external 0.4- to 16-MHz clock source
     *  LFXT1Sx definition for MSP430AFE2xx devices:
     *  00b = Reserved
     *  01b = Reserved
     *  10b = VLOCLK
     *  11b = Reserved
     * Bit 3-2 : XCAPx Oscillator capacitor selection.
     *           These bits select the effective capacitance seen by the
     *           LFXT1 crystal when XTS = 0.
     *           If XTS = 1 or if LFXT1Sx = 11 XCAPx should be 00.
     *           00b = Approximately 1 pF
     *           01b = Approximately 6 pF
     *           10b = Approximately 10 pF
     *           11b = Approximately 12.5 pF
     * Bit 1 : XT2OF : XT2 Just ->READ<- XT2 oscillator fault.
     *         Does not apply to MSP430x2xx, MSP430x21xx, or MSP430x22xx
     *         devices.
     *         0b = No fault condition present
     *         1b = Fault condition present
     * Bit 0 : LFXT1OF : LFXT1 Just ->READ<- oscillator fault.
     *         This bit is reserved in the MSP430AFE2xx devices.
     *         0b = No fault condition present
     *         1b = Fault condition present
     *
     * ************************************************************************/
    // TODO: Clock konfigürasyonlarý yapýlmalý
    //DCOCTL |= DCO0 + DCO1 + DCO2 + MOD0 + MOD1 + MOD2 + MOD3 + MOD4 ;
    //BCSCTL1 |= XT2OFF + LFXT1S1 + DIVA_0 + RSEL0;
    //BCSCTL2 |= SELM_3 + DIVM_0 + SELS + DIVS_0;
    //BCSCTL3 |= XT2S0 + LFXT1S_0 + XCAP_3 ;
    // TODO : void Main_Clock_Select(Main_Clock_Typedef Clock_Type);
    // TODO : void Sub_Clock_Select(Sub_Clock_Typedef Clock_Type);
    // TODO : void Aux_Clock_Select(Aux_Clock_Typedef Clock_Type);
    // Resource : slau144k.pdf page 277
}
