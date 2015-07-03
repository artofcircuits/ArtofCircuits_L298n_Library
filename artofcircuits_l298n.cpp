/*-------------------------------------------------------------------------
  Arduino library for L298N module
  
  Written by Asim Khan / Art of Circuits
  
  Art of Circuits is Pakistan’s popular online store that sells electronics 
  components, boards and tools to make your electronics projects possible. 
  Art of Circuits is located in Islamabad, and sells products across all 
  cities of Pakistan.

  Contact Info:
  Email: asim@artofcircuits.com
  Web:  http://artofcircuits.com

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
#define _DEBUG_		/* Comment if you want to disable debug serial prints */
#include "artofcircuits_l298n.h"

/**
 * Default Constructor
 */
 
L298n::L298n(uint8_t enable, uint8_t in1, uint8_t in2) {
	// assign to private variables
	_enable = enable;	
	_in1 = in1;
	_in2 = in2;
	_status = L298N_DISABLED;
	_speed = L298N_DEFAULT_SPEED;	// default speed
	
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
	_status = L298N_BREAK;
	
	DEBUG_PRINT("breaking()");
	DEBUG_PRINTDEC("enable: ", _enable);
	DEBUG_PRINTDEC("in1: ", _in1);
	DEBUG_PRINTDEC("in2: ", _in2);
	DEBUG_PRINTDEC("status: ", _status);
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
	_status = L298N_DISABLED;
}

/**
 * forward motion
 */
void L298n::forward(uint8_t speed)
{
	analogWrite(_enable, speed);
	digitalWrite(_in1, HIGH);
	digitalWrite(_in2, LOW);
	_status = L298N_FORWARD;
	
	DEBUG_PRINT("forward()");
	DEBUG_PRINTDEC("speed: ", speed);
	DEBUG_PRINTDEC("enable: ", _enable);
	DEBUG_PRINTDEC("in1: ", _in1);
	DEBUG_PRINTDEC("in2: ", _in2);
	DEBUG_PRINTDEC("status: ", _status);	
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
	_status = L298N_BACKWARD;
	
	DEBUG_PRINT("backward()");
	DEBUG_PRINTDEC("speed: ", speed);
	DEBUG_PRINTDEC("enable: ", _enable);
	DEBUG_PRINTDEC("in1: ", _in1);
	DEBUG_PRINTDEC("in2: ", _in2);
	DEBUG_PRINTDEC("status: ", _status);
	DEBUG_PRINT("");
}

/**
 * set speed
 */
void L298n::setSpeed(uint8_t speed)
{
	DEBUG_PRINT("setSpeed()");
	_speed = speed;
	switch (_status)
	{
		case L298N_DISABLED:
		
		break;

		case L298N_BREAK:
		
		break;
		
		case L298N_FORWARD:
		forward(_speed);
		break;
		
		case L298N_BACKWARD:
		backward(_speed);
		break;
		
		default: 
		break;		
	}
}

/**
 * get speed
 */
uint8_t L298n::getSpeed(void)
{
	return _speed;
}
