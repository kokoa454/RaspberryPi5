#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define GPIOCHIP 0
#define TRIG 23
#define ECHO 24
#define LED 25

struct timeval start, end;

int main(void){
	int hndl;
	int lFlgOut = 0;
	int lFlgIn = 0;
	
	hndl = lgGpiochipOpen(GPIOCHIP);
	lgGpioClaimOutput(hndl, lFlgOut, TRIG, LG_LOW);
	lgGpioClaimInput(hndl, lFlgIn, ECHO);
	
	lgGpioClaimOutput(hndl, lFlgOut, LED, LG_LOW);
	
	while(1){
		lgGpioWrite(hndl, TRIG, LG_HIGH);
		usleep(10);
		lgGpioWrite(hndl, TRIG, LG_LOW);
		
		int timeout = 0;
		while(lgGpioRead(hndl, ECHO) == LG_LOW){
			usleep(1);
			timeout++;
			
			if(timeout > 100000){
				goto wait_next;
			}
		}
		
		gettimeofday(&start, NULL);
		while(lgGpioRead(hndl, ECHO) == LG_HIGH){
			lgGpioWrite(hndl, LED, LG_HIGH);
		}
		gettimeofday(&end, NULL);
			
		long usec = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);;
		float result = (usec * 0.034) /2;
		if(result <= 400){
			printf("測定距離: %.2f cm\n", (usec * 0.034) / 2);
		}		
		wait_next:
			lgGpioWrite(hndl, LED, LG_LOW);
			usleep(60000);
	}
	
	lgGpiochipClose(hndl);
	return EXIT_SUCCESS;
}
