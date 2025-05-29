#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>

#define GPIOCHIPNUM	4
#define LED0 23

int main(void){
	int hnd;
	int lFlgOut = 0;
	
	hnd = lgGpiochipOpen(GPIOCHIPNUM);
	lgGpioClaimOutput(hnd, lFlgOut, LED0, LG_LOW);
	
	for(;;){
		lgGpioWrite(hnd, LED0, LG_HIGH);
		lguSleep(0.5);
		lgGpioWrite(hnd, LED0, LG_LOW);
		lguSleep(0.5);
	}
	
	lgGpiochipClose(hnd);
	return EXIT_SUCCESS;
}
