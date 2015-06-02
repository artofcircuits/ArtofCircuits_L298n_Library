/*-------------------------------------------------------------------------
  Arduino library for L298N module
  
  Written by Asim Khan 
  
  Art of Circuits is Pakistan’s popular online store that sells electronics 
  components, boards and tools to make your electronics projects possible. 
  Art of Circuits is located in Islamabad, and sells products across all 
  cities of Pakistan.

  -------------------------------------------------------------------------
  This file is part of the Art of Circuits L298N library.

  DC Motor library is free software: you can redistribute it and/or 
  modify it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  DC Motor Library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with dcmotor library.  If not, see
  <http://www.gnu.org/licenses/>.
  -------------------------------------------------------------------------*/

#include "artofcircuits_l298n.h"

/**
 * Default Constructor
 */
 
L298n::L298n(uint8_t enable, uint8_t in1, uint8_t in2) {
	// assign to private variables
	_enable = enable;	
	_in1 = in1;
	_in2 = in2;
	
	// set pin modes for L298N inputs
    pinMode(enable, OUTPUT);
    pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	disable();	// call disable to disable l298n driver
}

/**
 * Default Destructor
 */
L298n::~L298n() {
 	disable();		// disable driver
	
	// configure all pins used by the module as input before exit
	pinMode(_enable, INPUT);
	pinMode(_in1, INPUT);	
	pinMode(_in2, INPUT);
	
}

/**
 * Apply break to motor
 */
void L298n::breaking(void)
{
	digitalWrite(_enable, HIGH);
	digitalWrite(_in1, LOW);
	digitalWrite(_in2, LOW);
	
	DEBUG_PRINT("breaking()");
	DEBUG_PRINTDEC("enable: ", _enable);
	DEBUG_PRINTDEC("in1: ", _in1);
	DEBUG_PRINTDEC("in2: ", _in2);
	DEBUG_PRINT("");
	
}

/**
 * disable l298n driver
 */
void L298n::disable(void)
{
	digitalWrite(_enable, LOW);
	digitalWrite(_in1, LOW);
	digitalWrite(_in2, LOW);
}

/**
 * forward motion
 */
void L298n::forward(uint8_t speed)
{
	analogWrite(_enable, speed);
	digitalWrite(_in1, HIGH);
	digitalWrite(_in2, LOW);
	
	DEBUG_PRINT("forward()");
	DEBUG_PRINTDEC("speed: ", speed);
	DEBUG_PRINTDEC("enable: ", _enable);
	DEBUG_PRINTDEC("in1: ", _in1);
	DEBUG_PRINTDEC("in2: ", _in2);
	DEBUG_PRINT("");
}

/**
 * backward motion
 */
void L298n::backward(uint8_t speed)
{
	analogWrite(_enable, speed);
	digitalWrite(_in1, LOW);
	digitalWrite(_in2, HIGH);
	
	DEBUG_PRINT("backward()");
	DEBUG_PRINTDEC("speed: ", speed);
	DEBUG_PRINTDEC("enable: ", _enable);
	DEBUG_PRINTDEC("in1: ", _in1);
	DEBUG_PRINTDEC("in2: ", _in2);
	DEBUG_PRINT("");
}
