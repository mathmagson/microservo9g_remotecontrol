#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"

#include "rx.h"
#include "pwm.h"
#include "time.h"

float Throttle;

int main(void) {

    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // CLOCK 80 MHZ

    initTime();
    initPWM();
    initRX();
    IntMasterEnable();
    SysCtlDelay(3);

    while(!isArmed())   // Wait untill pilot arms quadcopter with remote
    {

    }

    while(1)
    {
        Throttle = getRXchannel(RX_THROTTLE);

        writeMotor(Throttle);

    }

}
