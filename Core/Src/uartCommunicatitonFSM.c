/*
 * uartCommunicatitonFSM.c
 *
 *  Created on: Nov 24, 2024
 *      Author: pham1
 */
#include "uartCommunicationFSM.h"

uint32_t ADCvalue = 0;
char str[20];
uint8_t resendFlag = 0;

void uartCommunicationFSM(void){
    switch(protocolState){
    case Idle:
        if(commandFlag == 1){
            protocolState = Send;
            commandFlag = 0;
        }
        break;
    case Send:
        ADCvalue = HAL_ADC_GetValue(&hadc1);
        sprintf(str, "!ADC=%lu#\n", ADCvalue);
        sendData(str);
        protocolState = Wait;
        setTimer(0, 3000);
        break;
    case Wait:
        // 3seconds
        if(isFlagOnTimer(0)){
            if(resendFlag){
                protocolState = Failure;
            }else{
                protocolState = Resend;
            }
        }
        if(receiveFlag == 1){
            protocolState = Received;
        }
        break;
    case Received:
        receiveFlag = 0;
        resendFlag = 0;
        protocolState = Idle;
        sendData("..OK..\n");
        break;
    case Resend:
        sprintf(str, "!ADC=%lu#\n", ADCvalue);
        sendData(str);
        resendFlag = 1;
        setTimer(0, 3000);
        protocolState = Wait;
        break;
    case Failure:
        protocolState = Idle;
        resendFlag = 0;
        sendData("..FAIL..\n");
        break;
    default:
        break;
    }
}

