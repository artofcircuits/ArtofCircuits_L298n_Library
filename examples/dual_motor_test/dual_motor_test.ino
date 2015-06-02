/**************************************************************************/
/*!
    @file     dual_motor_test.c
    @author   A. Khan
    @section LICENSE
    Copyright (c) 2015, Art of Circuits (artofcircuits.com)
    All rights reserved.

      This is an example code for motor driver using L298N Module
      http://artofcircuits.com/product/l298n-motor-driver-board

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
/**************************************************************************/

#include <artofcircuits_l298n.h>

// one L298N module can drive 2x left side motors in 4WD robot
#define    DCM1_ENABLE    13    // enable input of motor driver 
#define    DCM1_IN1       11     // input-1 of motor driver
#define    DCM1_IN2       10     // input-2 of motor driver

// one L298N module can drive 2x right side motors in 4WD robot
#define    DCM2_ENABLE    12    // enable input of motor driver 
#define    DCM2_IN1       9     // input-1 of motor driver
#define    DCM2_IN2       8     // input-2 of motor driver

// initialize L298n motor driver instances
L298n dcm1 (DCM1_ENABLE, DCM1_IN1, DCM1_IN2);    // L298n (enable,in1,in2) - left side motors
L298n dcm2 (DCM2_ENABLE, DCM2_IN1, DCM2_IN2);    // L298n (enable,in1,in2) - right side motors


void setup()
{
  Serial.begin(9600);
  Serial.println ("Art of Circuits - L298n - dual motor test example");
}

void loop ()
{
  dcm1.forward(255);    // cc/forward motion possible value of pwm can be 0 - 255
  dcm2.forward(255);    // cc/forward motion possible value of pwm can be 0 - 255
  delay (2000);
  dcm1.breaking();
  dcm2.breaking();
  delay (100);
  //dcm1.disable();
  dcm1.backward(170);    // ccw/backward motion possible value of pwm can be 0 - 255
  dcm2.backward(170);    // ccw/backward motion possible value of pwm can be 0 - 255
  delay (2000);
  dcm1.breaking();
  dcm2.breaking();
  delay (100);  
}



