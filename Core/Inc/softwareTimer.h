/*
 * softwareTimer.h
 *
 *  Created on: Oct 27, 2024
 *      Author: phamgialuong
 *      Manual: call initSoftwareTimer function before using
 */

#ifndef INC_SOFTWARETIMER_H_
#define INC_SOFTWARETIMER_H_

#include "global.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void initSoftwareTimer(uint16_t systemTick);
uint16_t tickDuration(void);
int isFlagOnTimer(int index);
void setTimer(int index, int duration);
void timerRun(void);

#endif /* INC_SOFTWARETIMER_H_ */
