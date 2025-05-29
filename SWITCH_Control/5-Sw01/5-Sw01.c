#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lgpio.h>

#define GPIOCHIPNUM	4
#define LED0 23
#define SW0 4

int main(void){
	int hnd;
	int lFlgOut = 0;
	int lFlgIn = 0;
	
	hnd = lgGpiochipOpen(GPIOCHIPNUM);
	lgGpioClaimOutput(hnd, lFlgOut, LED0, LG_LOW);
	lgGpioClaimInput(hnd, lFlgIn, SW0);
	
	while(1){
		if(lgGpioRead(hnd, SW0) == LG_HIGH){
			lgGpioWrite(hnd, LED0, LG_HIGH);
		} else {
			lgGpioWrite(hnd, LED0, LG_LOW);
		}
		
		usleep(1000);
	}
	
	lgGpiochipClose(hnd);
	return EXIT_SUCCESS;
}
