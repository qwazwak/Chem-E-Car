/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	Title:		AICHE Chem-E-Car Brainbox code
 *	Revision:		v0.0
 *	Author(s):	Rus Hoffman
 *	Start Date:		October 8, 2018
 *
 * * * * * * * * * * * * * * * * * * * * * * * */
#if !defined(AICHE_VARIABLES_HPP)
#define AICHE_VARIABLES_HPP


enum carStates {
	accelerating, holding, stopping, done
};

//Variables
unsigned long miniTimer;
unsigned long mainLoopStateTimer;

//Power Agitation:
int agitationAmount_Power_Current = 255;

//Timing Agitation:
int agitationAmount_Current_Timer = 255;

//Motor Control
int motorPWMLevel_current = DRIVEMOTOR_PWM_VALUE_START;

//State control
carStates currentCarState = accelerating;

//Debug

#if defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_LEDS_MAX7219_SINGLE)
bool debugFlasherUniversal = true;
bool continueBlanking;

int digitsToDisplay[4];
#endif
#if defined(DEBUG_LEDS_MAX7219_DOUBLE)
LedControl debugOutputLEDs(DIN_pin, CLK_pin, MAX7219_PIN_CHIPSELECT, 2);
#elif defined(DEBUG_LEDS_MAX7219_SINGLE)
LedControl debugOutputLEDs(DIN_pin, CLK_pin, MAX7219_PIN_CHIPSELECT, 1);
#endif
#if defined(DEBUG_SERIAL) || defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE)
unsigned long benchmark_timer_mainLoop;
double runningAverage;
unsigned long numberOfLoops = 0;
//unsigned long benchmark_timer_loopNOT;
#if defined(DEBUG_LEDS_MAX7219_SINGLE) || defined(DEBUG_LEDS_MAX7219_DOUBLE)
unsigned int averageConvert;
#endif
#endif

//#define startingChipID 1
//#define numberOfChipsAfterTheFirst 0
//#define maxBrightness 9
//double runningAverage = -1;
//unsigned long long numberOfCycles = 0;
//bool continueBlanking;
//int digitToDisplay[startingChipID + numberOfChipsAfterTheFirst][8];
//int oldDisplayedDigits[startingChipID + numberOfChipsAfterTheFirst][8];




#endif /* AICHE_VARIABLES_HPP */
