#include "osKernel.h"
#include "STM32F4_RTOS_BSP.h"
#include "stm32f4xx.h"                  // Device header

#define LED_green       (1u << 5)
#define LED_BIT_green   (1u << 10)
#define LED_clock_green (1u << 2)
#define LED_red         (1u << 3)
#define LED_BIT_red     (1u << 6)
#define LED_clock_red   (1u << 4)

#define QUANTA 1

int32_t semp1, semp2, count0, count1;

void Task0(void){
	
	while(1){
		 osSignalSet(&semp1);
		osSignalWait(&semp2);
		count0++;
	}
}

void Task1(void){
	
	while(1){
		 osSignalSet(&semp2);
		osSignalWait(&semp1);
		count1++;
	}
}

void Task2(void){
	
	while(1){
		/*
		osSignalWait(&semp1);
		GPIOE->ODR ^= LED_red;  //Toggle LED bit state
    for(int i = 0; i < 300000; i++){}
		osSignalSet(&semp2);
		*/
	}
}

int main(void){
	
	RCC->AHB1ENR |= LED_clock_green | LED_clock_red; // Assigning system clock to GPIO
	GPIOC->MODER |= LED_BIT_green;                   // Mode setup output for GPIO LED green
	GPIOE->MODER |= LED_BIT_red;                     // Ditto as above, but for GPIO LED Red
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100u);
	__enable_irq();
	osSemaphoreInit(&semp1,0);
	osSemaphoreInit(&semp2,0);
	HAL_Init();
	Probe_Init();
	osKernelInit();
	osKernelAddThreads(&Task0, &Task1, &Task2);
	osKernelLaunch(QUANTA);
	
}


