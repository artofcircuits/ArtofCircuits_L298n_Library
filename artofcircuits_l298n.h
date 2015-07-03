/*--------------------------------------------------------------------
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

  L298N library is free software: you can redistribute it and/or 
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
  --------------------------------------------------------------------*/

#ifndef ARTOFCIRCUITS_L298N_H
#define ARTOFCIRCUITS_L298N_H

// Compatibility for Arduino 1.0
#if ARDUINO >= 100
    #include "Arduino.h"
#else    
    #include "WProgram.h"
#endif

#ifdef _DEBUG_
 #define DEBUG_PRINT(x)  Serial.println (x)
 #define DEBUG_PRINTDEC(t,v)  Serial.print (t); Serial.println (v)
 #define DEBUG_PRINTHEX(t,v)  Serial.print (t); Serial.println (v,HEX)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTDEC(t,v)
 #define DEBUG_PRINTHEX(t,v)
#endif

// contant for _speed variable
#define L298N_DEFAULT_SPEED			127	// default speed
#define L298N_MAX_SPEED				255	// max speed
#define L298N_MIN_SPEED				63	// min speed that still rotates wheel

// constants for reporting status
#define L298N_DISABLED		0	// stopped or disabled state
#define L298N_BREAK			1	// stopped but l298n is enabled and break is applied
#define L298N_FORWARD		2	// forward motion state
#define L298N_BACKWARD		3	// backward motion state

class L298n {

 public:

  // Constructor: enable input , in1 and in2 direction control inputs
  L298n(uint8_t enable, uint8_t in1, uint8_t in2);
  ~L298n();
  void breaking();
  void disable();
  void forward(uint8_t speed);
  void backward(uint8_t speed);
  void setSpeed(uint8_t speed);
  uint8_t getSpeed(void);

 private:
 uint8_t _enable;
 uint8_t _in1;
 uint8_t _in2;
 uint8_t _status;		// holds l298n module status
 uint8_t _speed;		// holds pwm value / speed value
 
};

#endif // ARTOFCIRCUITS_DCMOTOR_H