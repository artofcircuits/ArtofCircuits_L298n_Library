/*--------------------------------------------------------------------
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

#ifndef ARTOFCIRCUITS_DCMOTOR_H
#define ARTOFCIRCUITS_DCMOTOR_H

#define _DEBUG_				/* Comment if you want to disable debug serial prints */

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

class L298n {

 public:

  // Constructor: enable input , in1 and in2 direction control inputs
  L298n(uint8_t enable, uint8_t in1, uint8_t in2);
  ~L298n();
  void breaking();
  void disable();
  void forward(uint8_t speed);
  void backward(uint8_t speed);

 private:
 uint8_t _enable;
 uint8_t _in1;
 uint8_t _in2;

};

#endif // ARTOFCIRCUITS_DCMOTOR_H