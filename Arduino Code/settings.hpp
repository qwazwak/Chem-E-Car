/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	Title:		AICHE Chem-E-Car Brainbox code
 *	Revision:		v0.0
 *	Author(s):	Rus Hoffman
 *	Date:		October 8, 2018
 *
 * * * * * * * * * * * * * * * * * * * * * * * */
#if !defined(AICHE_SETTINGS_HPP)
#define AICHE_SETTINGS_HPP

#define LEDCONTROL_NOSAFETYCHECKS


#if defined(DEBUG_FULL)
#define DEBUG_SERIAL
#define DEBUG_LEDS_MAX7219_DOUBLE
#undef DEBUG_LEDS_MAX7219_SINGLE
#define DEBUG_LEDS_MINIMAL
#endif

//Adjustable settings
#define agitationAmount_Power_Max 255
#define agitationAmount_Timer_Max 255
#define DRIVEMOTOR_PWM_TARGET 255

//Other adjustables
#define startButtonWaitingFlashDelayA 180
#define startButtonWaitingFlashDelayB 75

//Input pins
#define input_TimingShadeSensor 12
#define input_StartCarButtonPin 10

//Output Pins
#define CLK_pin 7
#define DIN_pin 9

#define mainDriveMotorController
#define powerAgitator
#define timingAgitator

#if defined(DEBUG_MINIMAL)
#define keepAliveLED 13
#define minimalStateLEDA
#define minimalStateLEDB
#endif

#if defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_LEDS_MAX7219_SINGLE)
#define MAX7219_PIN_CHIPSELECT 8
#endif

#endif /* AICHE_SETTINGS_HPP */

