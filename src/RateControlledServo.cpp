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
  residual_ += (dps * 1e6) / (updateTime - lastUpdate_);
  int maxAngleDelta = residual_ / 1e6;
  residual_ = residual_ % 1e6;

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
