/*
 * global.c
 *
 *  Created on: Nov 24, 2024
 *      Author: pham1
 */

#include "global.h"


uint8_t temp = 0;
uint8_t buffer[MaxBufferSize];
uint8_t bufferID = 0;
uint8_t bufferFlag = 0;

enum systemState parseState= Idel;
enum systemState protocolState = Idel;

char commandData[10] = "Ok";
uint8_t commandFlag = 0;
uint8_t receiveFlag = 0;

// Compare 2 strings, return 0 if equal
int stringCompare(const char *str1, const char *str2){
	while(*str1 && (*str1 == *str2)){
		str1++;
		str2++;
	}
	return *(unsigned char *)str1 - *(unsigned char *)str2;
}
// Clear string
void clearString(char* str){
	for(uint8_t i = 0; i < 10; i++)
		str[i] = '\0';
}
// String's length
uint8_t stringLength(const char *str){
	uint8_t i = 0;
	for(; i < 10; i++)
		if(str[i] == '\0') break;
	return i;
}
