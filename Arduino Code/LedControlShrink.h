/* LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 * Copyright (c) 2007 Eberhard Fahle, modified by Rus Hoffman in 2018
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * This permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#if !defined(LedControlShrink_h)
#define LedControlShrink_h


/*
 * #define LEDCONTROL_NOSAFETYCHECKS
 * to disable bounds checking for more speed
 *
 *
 */

#include <avr/pgmspace.h>
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class LedControl {
	private:
		//The array for shifting the data to the devices
		byte spidata[16];
		//Send out a single command to the device
		void spiTransfer (unsigned int addr, byte opcode, byte data);

		//We keep track of the led-status for all 8 devices in this array
		byte status[64];
		//SPI data pin
		unsigned int SPI_MOSI;
		//SPI clock pin
		unsigned int SPI_CLK;
		//SPI chip select pin
		unsigned int SPI_CS;
		//Number of MAX chips
		unsigned int maxDevices;

	public:
		/*
		 * Create a new controler
		 * Params :
		 * dataPin		pin on the Arduino where data gets shifted out
		 * clockPin		pin for the clock
		 * csPin		pin for selecting the device
		 * numDevices	maximum number of devices that can be controled
		 */
		LedControl (unsigned int dataPin, unsigned int clkPin, unsigned int csPin, unsigned int numDevices = 1);

		/*
		 * Gets the number of devices attached to this LedControl.
		 * Returns :
		 * unsigned int	the number of devices on this LedControl
		 */
		unsigned int getDeviceCount ();

		/*
		 * Set the shutdown (power saving) mode for the device
		 * Params :
		 * addr	The address of the display to control
		 * status	If true the device goes into power-down mode. Set to false
		 *		for normal operation.
		 */
		void shutdown (unsigned int addr, bool status);

		/*
		 * Set the number of digits (or rows) to be displayed.
		 * See datasheet for sideeffects of the scanlimit on the brightness
		 * of the display.
		 * Params :
		 * addr	address of the display to control
		 * limit	number of digits to be displayed (1..8)
		 */
		void setScanLimit (unsigned int addr, unsigned int limit);

		/*
		 * Set the brightness of the display.
		 * Params:
		 * addr		the address of the display to control
		 * intensity	the brightness of the display. (0..15)
		 */
		void setIntensity (unsigned int addr, unsigned int intensity);

		/*
		 * Switch all Leds on the display off.
		 * Params:
		 * addr	address of the display to control
		 */
		void clearDisplay (unsigned int addr);

		/*
		 * Set the status of a single Led.
		 * Params :
		 * addr	address of the display
		 * row	the row of the Led (0..7)
		 * col	the column of the Led (0..7)
		 * state	If true the led is switched on,
		 *		if false it is switched off
		 */
		void setLed (unsigned int addr, unsigned int row, unsigned int col, boolean state);

		/*
		 * Set all 8 Led's in a row to a new state
		 * Params:
		 * addr	address of the display
		 * row	row which is to be set (0..7)
		 * value	each bit set to 1 will light up the
		 *		corresponding Led.
		 */
		void setRow (unsigned int addr, unsigned int row, byte value);

		/*
		 * Set all 8 Led's in a column to a new state
		 * Params:
		 * addr	address of the display
		 * col	column which is to be set (0..7)
		 * value	each bit set to 1 will light up the
		 *		corresponding Led.
		 */
		void setColumn (unsigned int addr, unsigned int col, byte value);

		/*
		 * Display a hexadecimal digit on a 7-Segment Display
		 * Params:
		 * addr	address of the display
		 * digit	the position of the digit on the display (0..7)
		 * value	the value to be displayed. (0x00..0x0F)
		 * dp	sets the decimal point.
		 */
		void setDigit (unsigned int addr, unsigned int digit, byte value, boolean dp);

		/*
		 * Display a character on a 7-Segment display.
		 * There are only a few characters that make sense here :
		 *	'0','1','2','3','4','5','6','7','8','9','0',
		 *  'A','b','c','d','E','F','H','L','P',
		 *  '.','-','_',' '
		 * Params:
		 * addr	address of the display
		 * digit	the position of the character on the display (0..7)
		 * value	the character to be displayed.
		 * dp	sets the decimal point.
		 */
		void setChar (unsigned int addr, unsigned int digit, char value, boolean dp);
};

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

/*
 * Segments to be switched on for characters and digits on
 * 7-Segment Displays
 */
const static byte charTable[] PROGMEM = {
B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000,
B01111111, B01111011, B01110111, B00011111, B00001101, B00111101, B01001111, B01000111,
B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000, B00000000, B00000000, B00000000, B10000000, B00000001, B10000000, B00000000,
B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000,
B01111111, B01111011, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000, B01110111, B00011111, B00001101, B00111101, B01001111, B01000111, B00000000,
B00110111, B00000000, B00000000, B00000000, B00001110, B00000000, B00000000, B00000000,
B01100111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001000,
B00000000, B01110111, B00011111, B00001101, B00111101, B01001111, B01000111, B00000000,
B00110111, B00000000, B00000000, B00000000, B00001110, B00000000, B00010101, B00011101,
B01100111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};

LedControl::LedControl (unsigned int dataPin, unsigned int clkPin, unsigned int csPin, unsigned int numDevices) {
	SPI_MOSI = dataPin;
	SPI_CLK = clkPin;
	SPI_CS = csPin;
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	maxDevices = numDevices <= 8 ? numDevices : 8;
#elif
	maxDevices = numDevices;
#endif
	pinMode(SPI_MOSI, OUTPUT);
	pinMode(SPI_CLK, OUTPUT);
	pinMode(SPI_CS, OUTPUT);
	digitalWrite(SPI_CS, HIGH);
	for (unsigned int i = 0; i < 64; i++)
		status[i] = 0x00;
	for (unsigned int i = 0; i < maxDevices; i++) {
		spiTransfer(i, OP_DISPLAYTEST, 0);
		//scanlimit is set to max on startup
		setScanLimit(i, 7);
		//decode is done in source
		spiTransfer(i, OP_DECODEMODE, 0);
		clearDisplay(i);
		//we go into shutdown-mode on startup
#if defined(LEDCONTROL_DEFAULT_POWER_ON)
		shutdown(i, true);
#else defined(LEDCONTROL_DEFAULT_POWER_OFF)
		shutdown(i, false);
#endif
	}
}

unsigned int LedControl::getDeviceCount () {
	return maxDevices;
}

void LedControl::shutdown (unsigned int addr, bool b) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(addr >= maxDevices)
		return;
#endif
	spiTransfer(addr, OP_SHUTDOWN, b);
}

void LedControl::setScanLimit (unsigned int addr, unsigned int limit) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(addr >= maxDevices || limit >= 8 || addr >= maxDevices)
		return;
#endif
	spiTransfer(addr, OP_SCANLIMIT, limit);
}

void LedControl::setIntensity (unsigned int addr, unsigned int intensity) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(addr >= maxDevices || intensity >= 16 || addr >= maxDevices)
		return;
#endif
	spiTransfer(addr, OP_INTENSITY, intensity);
}

void LedControl::clearDisplay (unsigned int addr) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(addr >= maxDevices || addr >= maxDevices)
		return;
#endif
	unsigned int offset = addr * 8;
	for (unsigned int i = 0; i < 8; i++) {
		status[offset + i] = 0;
		spiTransfer(addr, i + 1, status[offset + i]);
	}
}

void LedControl::setLed (unsigned int addr, unsigned int row, unsigned int column, boolean state) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(row > 7 || column > 7 || addr >= maxDevices)
		return;
#endif
	byte val = B10000000 >> column;
	if(state)
		status[ (addr * 8) + row] = status[ (addr * 8) + row] | val;
	else {
		val = ~val;
		status[ (addr * 8) + row] = status[ (addr * 8) + row] & val;
	}
	spiTransfer(addr, row + 1, status[ (addr * 8) + row]);
}

void LedControl::setRow (unsigned int addr, unsigned int row, byte value) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(row > 7 || addr >= maxDevices)
		return;
#endif
	status[ (addr * 8) + row] = value;
	spiTransfer(addr, row + 1, status[ (addr * 8) + row]);
}

void LedControl::setColumn (unsigned int addr, unsigned int col, byte value) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)

	if(col > 7 || addr >= maxDevices)
		return;
#endif
	byte val;
	for (unsigned int row = 0; row < 8; row++) {
		val = value >> (7 - row);
		val = val & 0x01;
		setLed(addr, row, col, val);
	}
}

void LedControl::setDigit (unsigned int addr, unsigned int digit, byte value, boolean dp) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(addr >= maxDevices || digit > 7 || value > 15)
		return;
#endif
	byte v = pgm_read_byte_near(charTable + value);
	if(dp)
		v |= B10000000;
	status[ (addr * 8) + digit] = v;
	spiTransfer(addr, digit + 1, v);
}

void LedControl::setChar (unsigned int addr, unsigned int digit, char value, boolean dp) {
#if !defined(LEDCONTROL_NOSAFETYCHECKS)
	if(addr >= maxDevices || digit > 7)
		return;
#endif
	byte index, v;
	//no defined beyond index 127, so we use the space char
	index = value > 127 ? 32 : (byte)value;
	v = pgm_read_byte_near(charTable + index);
	if(dp)
		v |= B10000000;
	status[ (addr * 8) + digit] = v;
	spiTransfer(addr, digit + 1, v);
}

void LedControl::spiTransfer (unsigned int addr, volatile byte opcode, volatile byte data) {
	//Create an array with the data to shift out
	unsigned int maxbytes = maxDevices * 2;

	for (unsigned int i = 0; i < maxbytes; i++)
		spidata[i] = (byte)0;
	//put our device data into the array
	spidata[ (addr * 2) + 1] = opcode;
	spidata[addr * 2] = data;
	//enable the line
	digitalWrite(SPI_CS, LOW);
	//Now shift out the data
	for (unsigned int i = maxbytes; i > 0; i--)
		shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, spidata[i - 1]);
	//latch the data onto the display
	digitalWrite(SPI_CS, HIGH);
}

#endif	//LedControl.h

