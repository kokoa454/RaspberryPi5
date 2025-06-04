#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define GPIOCHIP 0
#define TRIG 20
#define ECHO 21
#define LED 23
#define DISTANCE 10.0

void ECHO_DETECT(int e, lgGpioAlert_p prev, void *userdata);

struct timeval start, end;

int hndl;

int main(void){
	int lFlgOut = 0;
	int lFlgIn = 0;
	int userdata;

	hndl = lgGpiochipOpen(GPIOCHIP);
	lgGpioClaimOutput(hndl, lFlgOut, TRIG, LG_LOW);
	lgGpioClaimInput(hndl, lFlgIn, ECHO);
	lgGpioClaimOutput(hndl, lFlgOut, LED, LG_LOW);
	lgGpioSetAlertsFunc(hndl, ECHO, ECHO_DETECT, &userdata);
	lgGpioClaimAlert(hndl, LG_SET_PULL_DOWN, LG_RISING_EDGE, ECHO, -1);
	
	while(1){
		lgGpioWrite(hndl, TRIG, LG_HIGH);
		usleep(10);
		lgGpioWrite(hndl, TRIG, LG_LOW);
		usleep(500000);
		
		if(lgGpioRead(hndl, LED) == LG_HIGH){
			lgGpioWrite(hndl, LED, LG_LOW);
		}
	}
	
	lgGpiochipClose(hndl);
	return EXIT_SUCCESS;
}

void ECHO_DETECT(int e, lgGpioAlert_p prev, void *userdata){
	gettimeofday(&start, NULL);
	
	while(lgGpioRead(hndl, ECHO) == LG_HIGH){}
	
	gettimeofday(&end, NULL);
	
	lgGpioWrite(hndl, LED, LG_LOW);
	
	long usec = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);;
	float result = (usec * 0.034) /2;
	
	if(result <= DISTANCE){
		lgGpioWrite(hndl, LED, LG_HIGH);
	}
	
	printf("測定距離: %.2f cm\n", result);
	
	return;
}
