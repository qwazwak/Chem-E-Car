/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	Title:		AICHE Chem-E-Car Brainbox code
 *	Revision:		v0.0
 *	Author(s):	Rus Hoffman
 *	Date:		October 8, 2018
 *
 * * * * * * * * * * * * * * * * * * * * * * * */

#define DEBUG_FULL
/*
 * Debugging guide:
 *
 *	First pair of display is motor controller PWM level
 *	00-FF (000-255)
 *
 *
 *
 *	Final pair of display is Error description
 *	00 - LED board booting, no info here
 *	01 - Cannot establish serial connection
 *	02 - waiting for serial connection
 *	03 - serial connection is good
 *	04 - Timer has been read to be high, moving to stopping state
 *	05 - Timer has been read to be low, continueing to hold speed
 *	06 -
 *	07 -
 *	08 -
 *	09 -
 *	0A -
 *	0b -
 *	0C -
 *	0d -
 *	0E - waiting for button to be depressed
 *	0F - button pressed, car will start when released
 *	11 - CAR STARTING
 *	12 -
 *	13 -
 *	14 -
 *	15 -
 *	16 -
 *	17 -
 *	18 -
 *	19 -
 *	1A -
 *	1b -
 *	1C -
 *	1d -
 *	1E -
 *	1F -
 *	...
 *	F1 - starting stopping the car
 *	F2 -
 *	F3 -
 *	F4 -
 *	F5 -
 *	F6 -
 *	F7 -
 *	F8 -
 *	F9 -
 *	FA -
 *	Fb -
 *	FC -
 *	Fd -
 *	FE -
 *	FF - car has finished all code and car has stopped
 *
 *
 */

#include <Arduino.h>
#include "LedControlShrink.h"
#include "settings.hpp"
#include "variables.hpp"
#include "functions.hpp"

void setup () {
	//Priority 0 setup, essentially just debug and testing
	pinMode(13, OUTPUT);

#if defined(DEBUG_HARDWARE)
	debug = new debuggerTool(true);
#endif
#if defined(DEBUG_SERIAL)
	{
		if( !Serial) {
			Serial.begin(9600);
		}
		miniTimer = 0;
		bool flasherState = true;
		while ( !Serial) {
			if(millis >= miniTimer + 100) {
				miniTimer = millis();
				flashKeepAlive();
#if defined(DEBUG_HARDWARE)
				debug->postCode(0x03, flasherState);
				flasherState = !flasherState;

#endif
			}
#if defined(DEBUG_HARDWARE)
			if(flasherState == true) {
				debug->postCode(0x03, false);
			}
#endif
		}
	}
#endif

//PRIORITY 1 SETUP:
//	pinMode(timingAgitator, OUTPUT);
//	analogWrite(agitatorAmount, timingAgitator);

//standard setup:
	pinMode(input_TimingShadeSensor, INPUT);
	pinMode(input_StartCarButtonPin, INPUT);
//	pinMode(mainDriveMotorController, OUTPUT);
//	pinMode(powerAgitator, OUTPUT);
//	pinMode(timingAgitator, OUTPUT);

//Wait for start button to be pressed and released
	{
		bool buttonWaitingFlasher = true;
		unsigned long tempTimerStart = 0;
		do {
			if(millis() >= tempTimerStart + startButtonWaitingFlashDelayA) {
				postCode(0x0E, buttonWaitingFlasher);
				buttonWaitingFlasher = !buttonWaitingFlasher;
				tempTimerStart = millis();
			}
		} while (digitalRead(input_StartCarButtonPin) != HIGH);
		tempTimerStart = 0;
		do {
			if(millis() >= tempTimerStart + startButtonWaitingFlashDelayB) {
				postCode(0x0F, buttonWaitingFlasher);
				buttonWaitingFlasher = !buttonWaitingFlasher;
				tempTimerStart = millis();
			}
		} while (digitalRead(input_StartCarButtonPin) != LOW);
		postCode(0x11);
	}
}
/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
void loop () {
#if defined(DEBUG_SERIAL)
	Serial.println("start of loop");
#endif
#if defined(DEBUG_BENCHMARK)
	test_timer_mainloop = millis();
#endif
#if !defined(COMPILE_FOR_SPEED)
	flashKeepAlive();
#endif
	switch (currentCarState) {
		case accelerating:
			//Accelerating

			if(motorPWMLevel_current >= DRIVEMOTOR_PWM_TARGET) {
				currentCarState = holding;
			}
			break;
		case holding:
			//Hold speed
			if(digitalRead(input_TimingShadeSensor) == HIGH) {
				currentCarState = stopping;
#if defined(DEBUG_LEDS)
//				postWrap(0x04);

			}
			else {
//				postWrap(0x05);
#endif
			}

			break;
		case stopping:
			//stopping the car

#if defined(DEBUG_SERIAL)
			Serial.println("starting car stop function");
#endif

#if defined(DEBUG_LEDS)
			//postWrap();
#endif
			const unsigned long delayInDecell = 50;
			unsigned long lastDecrement = millis();
			//do {
			if(lastDecrement + delayInDecell >= millis()) {
				//					analogWrite(mainDriveMotorController, pwmSignalCurrent--);
			}
			//} while (motorPWMLevel > 0);
#if defined(DEBUG_LEDS)
//			postWrap(0xFE);
#endif
			break;
		case done:
			#if defined(DEBUG_SERIAL)
			Serial.println("FINISHED");
			Serial.end();
#endif
#if defined(DEBUG_LEDS)
			unsigned long tempMiniBuffer;
			delete debug;
			while (true) {
				tempMiniBuffer = millis();
				while (millis() <= tempMiniBuffer + 75) {
//					postWrap(0xFF, true);
				}
				tempMiniBuffer = millis();
				while (millis() <= tempMiniBuffer + 75) {
//					postWrap(0xFF, false);
				}
			}
#endif
			break;
		default:
			break;
	}
#if defined(DEBUG_BENCHMARK)
	test_timer_mainloop = millis() - test_timer_mainloop;

#endif
#if defined(DEBUG_SERIAL) && defined(DEBUG_BENCHMARK)
	Serial.print("loop took: ");
	Serial.print((unsigned long)test_timer_mainloop);
	Serial.println("ms");
#endif
#if defined(DEBUG_LEDS) && defined(DEBUG_BENCHMARK)
	debug->updateOnLoopEnd();
#endif
}
