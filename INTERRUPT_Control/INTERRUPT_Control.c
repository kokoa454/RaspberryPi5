#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>

#define GPIOCHIP 4
#define LED0 23
#define LED1 22
#define SW0 4

void CbfSw0(int e, lgGpioAlert_p evt, void *userdata);

int g_hnd;

int main(void){
	int lFlgOut = 0;
	int lFlgIn = LG_SET_PULL_DOWN;
	int userdata;
	
	g_hnd = lgGpiochipOpen(GPIOCHIP);
	lgGpioClaimOutput(g_hnd, lFlgOut, LED0, LG_LOW);
	lgGpioClaimOutput(g_hnd, lFlgOut, LED1, LG_LOW);
	lgGpioSetAlertsFunc(g_hnd, SW0, CbfSw0, &userdata);
	lgGpioClaimAlert(g_hnd, lFlgIn, LG_RISING_EDGE, SW0, -1);
	
	for(;;){
		lgGpioWrite(g_hnd, LED0, LG_HIGH);
		lguSleep(0.5);
		lgGpioWrite(g_hnd, LED0, LG_LOW);
		lguSleep(0.5);
	}
	
	lgGpiochipClose(g_hnd);
	return EXIT_SUCCESS;
}

void CbfSw0(int e, lgGpioAlert_p evt, void *userdata){
	lgGpioWrite(g_hnd, LED1, LG_HIGH);
}
