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

#ifndef MINDS_I_COMMON_CONTROL_RATECONTOLLEDSERVO_H
#define MINDS_I_COMMON_CONTROL_RATECONTOLLEDSERVO_H

#include <Servo.h>

namespace minds_i_common::control {

class RateControlledServo : public Servo {
  public:
    RateControlledServo();
    void attachInitAngle(int pin, int initAngle); // attach to pin and set initial servo angle
    void writeRateControlled(int setAngle,
                             int dps); // angle (degrees) and degree per second limit (dps should be >= 0 && <= 4294)
                                       // todo write a method for specifying pulse width instead of angle
  private:
    unsigned long lastUpdate_;
    unsigned long residual_;
    bool initialized_;
};

} // namespace minds_i_common::control

#endif // MINDS_I_COMMON_CONTROL_RATECONTOLLEDSERVO_H