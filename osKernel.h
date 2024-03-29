#ifndef __OS_KERNEL_H
#define __OS_KERNEL_H
#include "stm32f4xx.h"                  // Device header
#include <stdint.h>

void osKernelLaunch(uint32_t quanta);

void osKernelInit(void);

void osSignalSet(int32_t *semaphore);
void osSignalWait(int32_t *semaphore);

uint8_t osKernelAddThreads(void(*task0)(void),
													 void(*task1)(void),
													 void(*task2)(void));

void osThreadYield(void);
void osSemaphoreInit(int32_t *semaphore, int32_t value);
													 
											
#define PERIOD		100
void Task3(void);
void Task4(void);												 
#endif
													 
											 