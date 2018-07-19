/*
 * rx.h
 *
 *  Created on: 1 Mar 2016
 *      Author: Kristjan
 */

#ifndef RX_H_
#define RX_H_


typedef enum {
    RX_ROLL = 0,
    RX_PITCH,
    RX_THROTTLE,
    RX_YAW,
    RX_AUX1,
    RX_AUX2,
    RX_NUM_CHANNELS,
} rxChannel_e;

void initRX();

float getRXchannel(rxChannel_e channel);

int isArmed();


#endif /* RX_H_ */
