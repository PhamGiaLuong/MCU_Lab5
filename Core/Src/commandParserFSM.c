/*
 * commandParserFSM.c
 *
 *  Created on: Nov 24, 2024
 *      Author: pham1
 */

#include "commandParserFSM.h"

void commandParserFSM(void){
    uint8_t id = bufferID - 1;
    if(bufferID == 0) id = MaxBufferSize - 1;
    switch(parseState){
    case Idle:
        if(buffer[id] == '!'){
            parseState = Parse;
            clearString(commandData);
        }
        break;
    case Parse:
        if(buffer[id]=='!'){
            clearString(commandData);
        }else if(buffer[id] == '#'){
            parseState = Check;
            bufferFlag = 1;
        }else if(stringLength(commandData) < 10){
            commandData[stringLength(commandData)] = buffer[id];
        }else{
            clearString(commandData);
        }
        break;
    case Check:
        if(stringCompare(commandData, "RST") == 0){
            commandFlag = 1;
        }else if(stringCompare(commandData, "OK") == 0){
            if(protocolState == Wait)receiveFlag = 1;
        }
        parseState = Idle;
        break;
    default:
        break;
    }
}
