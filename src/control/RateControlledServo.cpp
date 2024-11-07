/*
Copyright 2024 MINDS-i Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "RateControlledServo.h"

#include "wiring_private.h"


RateControlledServo::RateControlledServo() :
  Servo(), lastUpdate_(0), residual_(0), initialized_(false)
{}

void RateControlledServo::attachInitAngle(int pin, int initAngle)
{
  write(initAngle);
  attach(pin);
}

void RateControlledServo::writeRateControlled(int setAngle, int dps)
{
  int curAngle = read();
  unsigned long updateTime = micros();
  unsigned long elapsed_time = updateTime - lastUpdate_;
  
  if(!initialized_)
  {
    lastUpdate_ = updateTime;
    initialized_ = true;
    return;
  }
  
  if (elapsed_time == 0)
  {
    // no time has passed (skip this update)
    return;
  }
  else if (elapsed_time < 0)
  {
    // micros rolled over (happens about every 70 minutes)
    elapsed_time = 4294967295 - lastUpdate_;
    elapsed_time += updateTime;
  }

  // max angle the servo can achieve without violating the degree per second constraint before the next update
  residual_ += (dps * 1000000) / (updateTime - lastUpdate_);
  int maxAngleDelta = residual_ / 1000000;
  residual_ = residual_ % 1000000;

  if (abs(setAngle - curAngle) > maxAngleDelta)
  {
    if (setAngle > curAngle)
    {
      write(curAngle + maxAngleDelta);
    }
    else
    {
      write(curAngle - maxAngleDelta);
    }
  }
  else
  {
    // this move doesn't violate the rate limit
    write(setAngle);
  }

  lastUpdate_ = updateTime;
}
