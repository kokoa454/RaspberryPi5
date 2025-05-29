#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>

#define GPIOCHIPNUM	4
#define LED0 23
#define SW0 4

int main(void){
	int i = 0;
	int hnd;
	int lFlgOut = 0;
	int lFlgIn =LG_SET_PULL_DOWN;
	int s0Now = 0;
	int s0Pre = 0;
	int alt0 = 0;
	
	
	hnd = lgGpiochipOpen(GPIOCHIPNUM);
	lgGpioClaimOutput(hnd, lFlgOut, LED0, LG_LOW);
	lgGpioClaimInput(hnd, lFlgIn, SW0);
	
	while(1){
		s0Pre = s0Now;
		s0Now = lgGpioRead(hnd, SW0);
		
		if((s0Pre == LG_LOW) && (s0Now == LG_HIGH)){
			alt0 = !alt0;
			lgGpioWrite(hnd, LED0, alt0);
			printf("%d alt0 = %d\n", ++i, alt0);
		}
	}
	
	lgGpiochipClose(hnd);
	return EXIT_SUCCESS;
}


