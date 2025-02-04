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

#include <MINDS-i-Common.h>

namespace minds_i_control = minds_i_common::control;

#define MAX_SERVO_DEGREES_PER_SECOND 500

minds_i_control::RateControlledServo servo;

unsigned long ticks;

void setup() {
    ticks = 0;
    servo.attachInitAngle(1, 0); // pin 1, initial angle 0
}

void loop() {
    if (ticks++ % 10000 < 5000) {
        servo.writeRateControlled(45, MAX_SERVO_DEGREES_PER_SECOND);
    } else {
        servo.writeRateControlled(135, MAX_SERVO_DEGREES_PER_SECOND);
    }
}
