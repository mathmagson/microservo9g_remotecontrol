/*
 * pwm.c
 *
 *  Created on: 6 de jul de 2018
 *      Author: mathmagson
 */


#include <stdint.h>
#include <stdbool.h>

#include "pwm.h"
#include "mat.h"

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"

#define PWM_FREQUENCY 55

void initPWM() {

    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 83;

    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64); // SET PWM CLOCK BY: CLOCK_CPU/64

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // ENABLES PWM
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); // ENABLES PD

    ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0); // DEFINE PWM IN PIN PD0
    ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0); // CONFIGS PD0 AS M1PWM0

    ui32PWMClock = SysCtlClockGet() / 64; // PUT IN A VARIABLE THE PWM's CLOCK
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1; // TRANSFORMS THE CLOCK WHO WANTS TO WORK IN A COUNTER THAT INITIALIZE AT 0 (THIS IS WHY "-1")
    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN); // CONFIGS THE COUNTER AS DESCENT
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load); // SET THE COUNTER

    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000); // SPLIT THE COUNTER BY 1000 AND MULTIPLIES BY THE ADJUST FOR PUT THE SERVO IN THE MIDDLE POSITION: 1.51ms (1/55HZ * ADJUST /1000)
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true); // CONFIGS THE PWM MODULE 1 AS OUT
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0); // ENABLES THE PWM GENERATION
}

void writeMotor(float value){
    value = mapf(value, -1000., 1000., 1280, 2500);
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, value); // SET THE PWM's DUTY CYCLE
}

