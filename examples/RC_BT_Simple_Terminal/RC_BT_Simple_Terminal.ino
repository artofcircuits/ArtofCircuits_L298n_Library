/**************************************************************************/
/*!
    @file     dual_motor_test.c
    @author   A. Khan
    @section LICENSE
    Copyright (c) 2015, Art of Circuits (artofcircuits.com)
    All rights reserved.

      Description:
      This is an application code for control of 2WD or 4WD robots using
      Bluetooth Application on Android Mobile. The commands received to this Arduino 
      Application have following format:
      <Letter-for-command> <optional argument><CR><LF>
      Following Commands are supportted:
      f<CR><LF>           Forward motion
      b<CR><LF>           Bacward motion
      l<CR><LF>           Left turn
      r<CR><LF>           right turn
      p<CR><LF>           stop motion
      s <0-255><CR><LF>   speed command give an argument in ascii decimal value from 0 - 255
        Example: 
        s 255 <CR><LF>    sets speed to maximum 

      [!] Notes: 
      1. Speed values Below 127 do not generate enough troque that can run robot
      2. Debugging messages from L298N module can be turned off by commenting out _DEBUG_ 
      statement in artofcrcuits_l298n.cpp module
      
       
      Major Components:      
      Motor Driver: L298N http://artofcircuits.com/product/l298n-motor-driver-board
      Bluetooth Module: HC-06
      Bluetooth App Name: BT Simple Terminal (https://play.google.com/store/apps/details?id=wingood.bluetooth.btsimpleterminal)
      

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
#include <SerialCommand.h>   /* SerialCommand module */

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
unsigned char speed = 127;

SerialCommand sCmd;     // The SerialCommand object

void setup()
{
  Serial.begin(9600);
  Serial.println ("Art of Circuits - L298n - dual motor test example");
  
  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("f", cmd_forward);  // forward command
  sCmd.addCommand("b", cmd_backward); // backward command
  sCmd.addCommand("l", cmd_left);     // left motion command
  sCmd.addCommand("r", cmd_right);    // left motion command  
  sCmd.addCommand("p", cmd_stop);     // stop command
  sCmd.addCommand("s", cmd_speed);     // stop command
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  
}

void loop ()
{
   sCmd.readSerial();     // process serial commands
}


///////////////////////////////////////////////////////////////////////////////
// function name: cmd_forward()
// inputs: none
// outputs: none
// Description: move forward
///////////////////////////////////////////////////////////////////////////////
void cmd_forward() {
  dcm1.forward(speed);    // cc/forward motion possible value of pwm can be 0 - 255
  dcm2.forward(speed);    // cc/forward motion possible value of pwm can be 0 - 255  
}


///////////////////////////////////////////////////////////////////////////////
// function name: cmd_backward()
// inputs: none
// outputs: none
// Description: move backward
///////////////////////////////////////////////////////////////////////////////
void cmd_backward() {
  dcm1.backward(speed);    // cc/forward motion possible value of pwm can be 0 - 255
  dcm2.backward(speed);    // cc/forward motion possible value of pwm can be 0 - 255  
}

///////////////////////////////////////////////////////////////////////////////
// function name: cmd_left()
// inputs: none
// outputs: none
// Description: turn left
///////////////////////////////////////////////////////////////////////////////
void cmd_left() {
  dcm1.backward(speed);    // cc/forward motion possible value of pwm can be 0 - 255
  dcm2.forward(speed);    // cc/forward motion possible value of pwm can be 0 - 255  
}


///////////////////////////////////////////////////////////////////////////////
// function name: cmd_right()
// inputs: none
// outputs: none
// Description: turn right
///////////////////////////////////////////////////////////////////////////////
void cmd_right() {
  dcm1.forward(speed);    // cc/forward motion possible value of pwm can be 0 - 255
  dcm2.backward(speed);    // cc/forward motion possible value of pwm can be 0 - 255  
}


///////////////////////////////////////////////////////////////////////////////
// function name: cmd_stop()
// inputs: none
// outputs: none
// Description: Stops motion
///////////////////////////////////////////////////////////////////////////////
void cmd_stop() {
  dcm1.disable();
  dcm2.disable();
}


///////////////////////////////////////////////////////////////////////////////
// function name: cmd_speed()
// inputs: none
// outputs: none
// Description: Implements set speed command.
///////////////////////////////////////////////////////////////////////////////
void cmd_speed() {
  char *arg;
  speed;  // global speed register

  arg = sCmd.next();
  if (arg != NULL) {
    speed = atoi(arg);    // Converts a char string to int
  }
  else {
    pSerial.println("NO SPEED?");  // no arguments received
  }

}


///////////////////////////////////////////////////////////////////////////////
// function name: unrecognized()
// inputs: char command string
// outputs: none
// Description: This gets set as the default handler, and gets called when 
// no other command matches.
///////////////////////////////////////////////////////////////////////////////

void unrecognized(const char *command) {
  pSerial.println("?");
}


