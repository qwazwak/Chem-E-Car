/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	Title:		AICHE Chem-E-Car Brainbox code
 *	Revision:		v0.0
 *	Author(s):	Rus Hoffman
 *	Date:		October 8, 2018
 *
 * * * * * * * * * * * * * * * * * * * * * * * */


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
 *	12 - the code is fucked, something caused the state to be invalid
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
 *	E1 -
 *	E2 -
 *	E3 -
 *	E4 -
 *	E5 -
 *	E6 -
 *	E7 -
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







#if !defined(AICHE_SETTINGS_HPP)
#define AICHE_SETTINGS_HPP

#define LEDCONTROL_NOSAFETYCHECKS
#define DEBUG_FULL

#if defined(DEBUG_FULL)
#define DEBUG_SERIAL
#define DEBUG_LEDS_MAX7219_DOUBLE
#undef DEBUG_LEDS_MAX7219_SINGLE
#define DEBUG_LEDS_MINIMAL
#endif

#if defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_LEDS_MAX7219_SINGLE)
#define DEBUG_LEDS_MAX7219
#endif


#if defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_SERIAL)
#define DEBUG_BENCHMARK
#endif

//Adjustable settings
#define agitationAmount_Power_Max 255
#define agitationAmount_Timer_Max 255
#define DRIVEMOTOR_PWM_TIME_DELAY 5
#define DRIVEMOTOR_PWM_VALUE_INCRAMENT 5
#define DRIVEMOTOR_PWM_VALUE_START 10
#define DRIVEMOTOR_PWM_VALUE_TARGET 255


//Other adjustables
#define startButtonWaitingFlashDelayA 150
#define startButtonWaitingFlashDelayB 75
#define generalFlashDelay 60

//Input pins
#define input_TimingSensor 12
#define input_StartCarButtonPin 10

//Output Pins
#define CLK_pin 7
#define DIN_pin 9

#define OUTPUT_ANALOG_DRIVEMOTORCONTROLER 6
#define powerAgitator 5
#define timingAgitator 4

#define DEBUG_MINIMAL
#if defined(DEBUG_MINIMAL)
#define keepAliveLED 13
#define minimalStateLEDA 2
#define minimalStateLEDB 3
#endif

#if defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_LEDS_MAX7219_SINGLE)
#define MAX7219_PIN_CHIPSELECT 8
#endif

#endif /* AICHE_SETTINGS_HPP */

