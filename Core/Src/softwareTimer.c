/*
 * softwareTimer.c
 *
 *  Created on: Oct 27, 2024
 *      Author: phamgialuong
 *      Manual: call initSoftwareTimer function before using
 *      		call timerRun in interrupt call back function
 */

#include "softwareTimer.h"

// The number of timers
#define MAX_TIMERS 10

// System interrupt cycle (millisecond)
uint16_t Tick = 10; //time duration of timer interrupt

uint16_t tickDuration(void){
	return Tick;
}

// Flags for time expiration
int flag[MAX_TIMERS] = {0};
int timerCounter[MAX_TIMERS] = {0};

typedef struct timerStruct{
	uint16_t delay;
	uint8_t id;

	struct timerStruct* next;
	struct timerStruct* previous;
}Timer;

uint8_t timerCount; // The number of timer in the list
Timer* timerList;	// Head of the list

// Set 1 system Tick
void initSoftwareTimer(uint16_t tick){
	timerCount = 0;
	Tick = tick;
}

// Check for time expiration
int isFlagOnTimer(int index){
	return (flag[index] == 1) ? 1 : 0;
}

// delete the same existing timer in the list before set new one
void deleteExistedTimer(uint8_t id){
	Timer* node = timerList;
	while(node){
		if(node->id == id){
			if(timerCount == 1){ // One element list
				timerList = NULL;
			}else{
				if(node == timerList){ // Delete at head
					timerList = node->next;
					timerList->previous = NULL;
					node->next = NULL;
					timerList->delay += node->delay;
				}else if(node->next == NULL){ // Delete at tail
					node->previous->next = NULL;
					node->previous = NULL;
				}else{ // Delete at middle
					node->next->delay += node->delay;
					node->previous->next = node->next;
					node->next->previous = node->previous;
					node->next = NULL;
					node->previous = NULL;
				}
			}
			free(node);
			timerCount--;
			return;
		}
		node = node->next;
	}
}

// Set timer duration
void setTimer(int timer, int duration){
	Timer* tmp = (Timer*)malloc(sizeof(Timer));
	tmp->delay = duration / Tick;
	tmp->id = timer;
	tmp->previous = NULL;
	tmp->next = NULL;
	flag[timer] = 0;
	if(timerCount == 0){ // Add the first node of the list
		timerList = tmp;
		timerCount++;
	}else{
		Timer* node = timerList;
		deleteExistedTimer(tmp->id);
		if(timerCount == 0){ // Add the first node to the list
			timerList = tmp;
			timerCount++;
			return;
		}
		if(tmp->delay < timerList->delay){ // Add at the first node of the list
			tmp->next = timerList;
			timerList->previous = tmp;
			timerList = tmp;
		}else{
			node = timerList;
			uint32_t totalDelay = node->delay;
			while((totalDelay <= tmp->delay) && (node->next != NULL)){ // Find suitable place
				totalDelay += node->next->delay;
				node = node->next;
			}
			if(node->next == NULL && totalDelay <= tmp->delay){ // Add tail
				tmp->delay -= totalDelay;
				node->next = tmp;
				tmp->previous = node;
				timerCount++;
				return;
			}else{ // Add middle
				tmp->delay -= (totalDelay - node->delay);
				node->previous->next = tmp;
				tmp->previous = node->previous;
				tmp->next = node;
				node->previous = tmp;
			}
		}
		// If new node is not added at the end of linked list, update the delay for it's next task
		tmp->next->delay -= tmp->delay;
		timerCount++;
	}
}

// Run timers, call in interrupt function
void timerRun(void){
	if(timerList){
		if(timerList->delay > 0){
			timerList->delay--;
		}
		while(timerList->delay <= 0){
			flag[timerList->id] = 1;
			Timer* tmp = timerList;
			timerList = timerList->next;
			tmp->next = NULL;
			if(timerList){
				timerList->previous = NULL;
			}
			timerCount--;
			free(tmp);
			if(timerList == NULL) return;
		}
	}
}
