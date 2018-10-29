/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	Title:		AICHE Chem-E-Car Brainbox code
 *	Revision:		v0.0
 *	Author(s):	Rus Hoffman
 *	Start Date:		October 8, 2018
 *
 * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(FUNCTIONS_HPP)
#define FUNCTIONS_HPP

#if !defined(Arduino_h)
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#endif

#if defined(DEBUG_LEDS_MAX7219_DOUBLE) || defined(DEBUG_LEDS_MAX7219_SINGLE)
void postCode(int code, bool DecimalPoint_First = false, bool DecimalPoint_Second = false) {
	debugOutputLEDs.setDigit(0, 1, (code & 0xF0) >> 4, DecimalPoint_First);
	debugOutputLEDs.setDigit(0, 0, (code & 0xF) >> 0, DecimalPoint_Second);
}

void postWrapA(int code, bool DPF = false, bool DPS = false) {
	postCode(code, DPF, DPS);
}

void postCodeB(int code, bool DecimalPoint_First = false, bool DecimalPoint_Second = false) {
	debugOutputLEDs.setDigit(0, 1, (code & 0xF0) >> 4, DecimalPoint_First);
	debugOutputLEDs.setDigit(0, 0, (code & 0xF) >> 0, DecimalPoint_Second);
}
#endif

#if defined(DEBUG_LEDS_MINIMAL)
bool ledState = true;
inline void flashKeepAlive () {
	digitalWrite(13, ledState);
	ledState = !ledState;
}
#endif

#endif
