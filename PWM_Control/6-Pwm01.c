#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>

#define CHIPNUM 4
#define LED0 23

int main(void){
	int hnd;
	int lFlgOut = 0;
	int duty;
	
	hnd = lgGpiochipOpen(CHIPNUM);
	lgGpioClaimOutput(hnd, lFlgOut, LED0, LG_LOW);
	
	while(1){
		for(duty = 0; duty < 100; duty++){
			lgTxPwm(hnd, LED0, 100.0, duty, 0, 0);
			lguSleep(0.05);
		}
	}
	
	lgGpiochipClose(hnd);
	return EXIT_SUCCESS;
}
