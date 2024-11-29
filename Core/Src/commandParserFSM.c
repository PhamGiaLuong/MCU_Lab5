/*
 * commandParserFSM.c
 *
 *  Created on: Nov 24, 2024
 *      Author: pham1
 */

#include "commandParserFSM.h"
//char str1[5];

void commandParserFSM(void){
	uint8_t id = bufferID - 1;
	if(bufferID == 0) id = MaxBufferSize - 1;
//	clearString(str1);
	switch(parseState){
	case Idel:
		if(buffer[id] == '!'){
			parseState = Bang;
			clearString(commandData);
		}
		break;
	case Bang:
		if(buffer[id]=='!'){
			clearString(commandData);
		}else if(buffer[id] == '#'){
			if(stringCompare(commandData, "RST") == 0){
				commandFlag = 1;
			}else if(stringCompare(commandData, "OK") == 0){
				if(protocolState == Wait)receiveFlag = 1;
			}
			parseState = Idel;
		}else if(stringLength(commandData) < 10){
			commandData[stringLength(commandData)] = buffer[id];
		}else{
			clearString(commandData);
		}
		break;
	case Hash:
		break;
	default:

		break;
	}
}
