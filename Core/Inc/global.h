/*
 * global.h
 *
 *  Created on: Nov 24, 2024
 *      Author: pham1
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "softwareTimer.h"
#include <stdio.h>
#include <string.h>

#define MaxBufferSize 30
extern uint8_t temp;
extern uint8_t buffer[MaxBufferSize];
extern uint8_t bufferID;
extern uint8_t bufferFlag;

enum systemState {Idle, Parse, Check, Send, Wait,
                    Resend, Received, Failure};

extern enum systemState parseState;
extern enum systemState protocolState;

extern char commandData[10];
extern uint8_t commandFlag;
extern uint8_t receiveFlag;

int stringCompare(const char *str1, const char *str2);
void clearString(char *str);
uint8_t stringLength(const char *str);

#endif /* INC_GLOBAL_H_ */
