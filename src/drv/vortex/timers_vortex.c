#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>
// #include <pthread.h>
#include <signal.h>
#include <time.h>

#include <applicfg.h>
#include <timers.h>
#include "timers_driver.h"

#include "vortex/mcm/mcm_timer.h"

#include "io.h"

// static struct timeval last_sig;
unsigned long long last_sig;
void getSystemTime(unsigned long long* usec){
	*usec = timer_GetClocks64()/(unsigned long long)vx86_CpuCLK();
}

int cb_cnt = 0;
void timer_notify()
{
	cb_cnt++;
	getSystemTime(&last_sig);	
	TimeDispatch();	
}

//cearte a timer for canfestival	
void TimerInit(void)
{
	getSystemTime(&last_sig);
	initMCMTimer();
    attachTimerCb(&timer_notify);
}

void StopTimerLoop(TimerCallback_t exitfunction)
{

}

void StartTimerLoop(TimerCallback_t init_callback)
{
	// EnterMutex();
	// // At first, TimeDispatch will call init_callback.
	SetAlarm(NULL, 0, init_callback, 0, 0);
	// LeaveMutex();
}


#define maxval(a,b) ((a>b)?a:b)
void setTimer(TIMEVAL value)
{
	startTimer(value);
}

TIMEVAL getElapsedTime(void)
{
	unsigned long long n;
	getSystemTime(&n);
	return n - last_sig;
}

