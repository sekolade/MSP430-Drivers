/*
 * main.h
 *
 *  Created on: May 18, 2023
 *      Author: HP
 */
#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
#include <msp430fr59691.h>
#include <intrinsics.h>
#include <in430.h>
#include <msp430.h>
#include <msp430_gpio_hal.h>
//#include <msp430g2553.h>
#include <GGK.h>
#include <msp430_watchdog_hal.h>
#include <msp430_clock_hal.h>
#include <msp430_watchdog_hal.h>
#include <msp430_i2c_hal.h>
#include <switch.h>
#include <temperature.h>
#include <GGK.h>
#include <msp430_adc_hal.h>




#define LRF_Port Port_3
#define LRF_Pin Pin_4
#define LASER_Port Port_3
#define LASER_Pin Pin_5
#define FLIR_Port Port_3
#define FLIR_Pin Pin_6
#define GNDZ_Port Port_3
#define GNDZ_Pin Pin_7

#define IN1_Port Port_4
#define IN1_Pin Pin_2
#define IN2_Port Port_4
#define IN2_Pin Pin_3
#define IN3_Port Port_4
#define IN3_Pin Pin_4
#define IN4_Port Port_4
#define IN4_Pin Pin_5



#endif /* MAIN_H_ */
