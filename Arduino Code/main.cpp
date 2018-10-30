/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	Title:		AICHE Chem-E-Car Brainbox code
 *	Revision:		v0.0
 *	Author(s):	Rus Hoffman
 *	Date:		October 8, 2018
 *
 * * * * * * * * * * * * * * * * * * * * * * * */

#define DEBUG_FULL

#include <Arduino.h>
#include "LedControlShrink.h"
#include "settings.hpp"
#include "variables.hpp"
#include "functions.hpp"

void setup () {
	//Priority 0 setup, essentially just debug and testing
	pinMode(13, OUTPUT);
#if defined(DEBUG_SERIAL)

	if( !Serial) {
		Serial.begin(9600);
	}
	miniTimer = 0;
	while ( !Serial) {
		if(millis >= miniTimer + 100) {
			miniTimer = millis();
			flashKeepAlive();
#if defined(DEBUG_LEDS_MAX7219)
			postCode(0x03, debugFlasherUniversal);
			debugFlasherUniversal = !debugFlasherUniversal;
		}
		if(debugFlasherUniversal == true) {
			postCode(0x03, false);

#endif
		}
	}

#endif

//PRIORITY 1 SETUP:
//	pinMode(timingAgitator, OUTPUT);
//	analogWrite(agitatorAmount, timingAgitator);

//standard setup:
	pinMode(input_TimingSensor, INPUT);
	pinMode(input_StartCarButtonPin, INPUT);
//	pinMode(mainDriveMotorController, OUTPUT);
//	pinMode(powerAgitator, OUTPUT);
//	pinMode(timingAgitator, OUTPUT);

//Wait for start button to be pressed and released
	{
		miniTimer = 0;
		do {
			if(millis() >= miniTimer + startButtonWaitingFlashDelayA) {
				postCode(0x0E, debugFlasherUniversal);
				debugFlasherUniversal = !debugFlasherUniversal;
				miniTimer = millis();
			}
		} while (digitalRead(input_StartCarButtonPin) != HIGH);
		miniTimer = 0;
		do {
			if(millis() >= miniTimer + startButtonWaitingFlashDelayB) {
				postCode(0x0F, debugFlasherUniversal);
				debugFlasherUniversal = !debugFlasherUniversal;
				miniTimer = millis();
			}
		} while (digitalRead(input_StartCarButtonPin) != LOW);
	}
	mainLoopStateTimer = millis();
	postCode(0x11);
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
	benchmark_timer_mainLoop = millis();
#endif
#if !defined(COMPILE_FOR_SPEED)
	flashKeepAlive();
#endif
	switch (currentCarState) {
		case accelerating:
			//Accelerating
			if(mainLoopStateTimer + DRIVEMOTOR_PWM_TIME_DELAY >= millis()) {
				mainLoopStateTimer = millis();
				motorPWMLevel_current += motorPWMLevel_current > 255 ? 255 : DRIVEMOTOR_PWM_VALUE_INCRAMENT;
				analogWrite(OUTPUT_ANALOG_DRIVEMOTORCONTROLER, motorPWMLevel_current);
				if(motorPWMLevel_current >= DRIVEMOTOR_PWM_VALUE_TARGET) {
					currentCarState = holding;
				}
			}
			break;

		case holding:
			//Hold speed
			if(digitalRead(input_TimingSensor) == HIGH) {
				currentCarState = stopping;
#if defined(DEBUG_SERIAL)
				Serial.println("starting car stop function");
#endif

#if defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE)
				postCode(0x04);

			}
			else {
				postCode(0x05);
#endif
			}
			break;
		case stopping:
			//stopping the car

#if defined(DEBUG_SERIAL)
			Serial.println("starting car stop function");
#endif

#if defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE)
			postCode(0x00);
#endif
			const unsigned long delayInDecell = 50;
			unsigned long lastDecrement = millis();
			//do {
			if(lastDecrement + delayInDecell >= millis()) {
				//analogWrite(mainDriveMotorController, pwmSignalCurrent--);
#if defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE)
				postCode(0xFD);
#endif
			}
			//} while (motorPWMLevel > 0);

			break;

		case done:
			#if defined(DEBUG_SERIAL)
			if(Serial) {
				Serial.println("CAR HAS FINISHED");
				Serial.print("Took: ");
				Serial.print(millis());
				Serial.print("ms\n");

			}
			Serial.end();
#endif
#if defined(DEBUG_LEDS_MAX7219)
			if(millis() >= mainLoopStateTimer + generalFlashDelay) {
				mainLoopStateTimer = millis();
				postCode(0xFF, debugFlasherUniversal);
				debugFlasherUniversal = !debugFlasherUniversal;
			}
#endif
			break;
		default:
			#if defined(COMPETITION_MODE)
			currentCarState = holding;
#endif
#if defined(DEBUG_SERIAL)
			Serial.println("CAR IS FUCKED IN INVALID STATE");
#endif
#if defined(DEBUG_LEDS_MAX7219)

#endif
	}

#if defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_SERIAL)
	benchmark_timer_mainLoop = millis() - benchmark_timer_mainLoop;
#endif
#if defined(DEBUG_SERIAL) && defined(DEBUG_BENCHMARK)
	Serial.print("loop took: ");
	Serial.print((unsigned long)benchmark_timer_mainLoop);
	Serial.println("ms");
	numberOfLoops++;
	runningAverage = ( (runningAverage * (numberOfLoops - 1)) + benchmark_timer_mainLoop) / numberOfLoops;

#endif
#if defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE)
#if defined(DEBUG_LEDS_MAX7219_DOUBLE)

#define digitID_offset 0
#define digitID_timeLatest1 0
#define digitID_timeLatest2 1
#define digitID_timeLatest3 2
#define digitID_timeLatest4 3
#define chipID_timeLatest 1
#define startingChipID_timeAverage
#endif
#if defined(DEBUG_LEDS_MAX7219_SINGLE)
#define digitID_offset 0
#define digitID_timeLatest1 4
#define digitID_timeLatest2 5
#define digitID_timeLatest3 6
#define digitID_timeLatest4 7
#define chipID_timeLatest 0
#endif
	if(benchmark_timer_mainLoop == 0) {
		debugOutputLEDs.setRow(chipID_timeLatest, digitID_timeLatest4 + digitID_offset, B0000000);
		debugOutputLEDs.setRow(chipID_timeLatest, digitID_timeLatest3 + digitID_offset, B0000000);
		debugOutputLEDs.setRow(chipID_timeLatest, digitID_timeLatest2 + digitID_offset, B0000000);
		debugOutputLEDs.setChar(chipID_timeLatest, digitID_timeLatest1 + digitID_offset, '-', debugFlasherUniversal);
		debugFlasherUniversal = !debugFlasherUniversal;
	}
	else {
		digitsToDisplay[0] = (int) (benchmark_timer_mainLoop % 10);
		benchmark_timer_mainLoop = benchmark_timer_mainLoop / 10;
		digitsToDisplay[1] = (int) (benchmark_timer_mainLoop % 10);
		benchmark_timer_mainLoop = benchmark_timer_mainLoop / 10;
		digitsToDisplay[2] = (int) (benchmark_timer_mainLoop % 10);
		benchmark_timer_mainLoop = benchmark_timer_mainLoop / 10;
		digitsToDisplay[3] = (int) (benchmark_timer_mainLoop % 10);
		continueBlanking = true;
		for (int digitNumber = 3; digitNumber >= 0; digitNumber--) {
			if(continueBlanking == false) {
				debugOutputLEDs.setDigit(chipID_timeLatest, digitNumber + digitID_offset, digitsToDisplay[digitNumber], false);
			}
			else {
				if(digitsToDisplay[digitNumber] == 0) {
					debugOutputLEDs.setRow(chipID_timeLatest, digitNumber + digitID_offset, B0000000);
				}
				else {
					continueBlanking = false;
					debugOutputLEDs.setDigit(chipID_timeLatest, digitNumber + digitID_offset, digitsToDisplay[digitNumber], false);
				}
			}
		}

	}
#if defined(DEBUG_LEDS_MAX7219_DOUBLE)
	averageConvert = round(runningAverage);
	digitsToDisplay[0] = (int) (averageConvert % 10);
	averageConvert = averageConvert / 10;
	digitsToDisplay[1] = (int) (averageConvert % 10);
	averageConvert = averageConvert / 10;
	digitsToDisplay[2] = (int) (averageConvert % 10);
	averageConvert = averageConvert / 10;
	digitsToDisplay[3] = (int) (averageConvert % 10);

	for (int digitNumber = 4; digitNumber >= 3; digitNumber--) {
		if(continueBlanking == false) {
			debugOutputLEDs.setDigit(1, digitNumber, digitsToDisplay[digitNumber], false);
		}
		else {
			if(digitsToDisplay[digitNumber] == 0) {
				debugOutputLEDs.setRow(1, digitNumber, B0000000);
			}
			else {
				continueBlanking = false;
				debugOutputLEDs.setDigit(1, digitNumber, digitsToDisplay[digitNumber], false);
			}
		}
	}
#endif

#endif
}
