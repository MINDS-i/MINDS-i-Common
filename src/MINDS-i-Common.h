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

#ifndef MINDS_I_COMMON_H
#define MINDS_I_COMMON_H

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

#include "comms/Radio.h"
// TODO: control/RateControlledServo commonly conflicts with other libraries that use the same Timer
// TODO: sensors/Encoder include is statically defined as a header only file. Including this here will cause linking errors
// Consider removing this include or making it a normal .cpp file (and consider any perfomrance improvements/degradations)
#include "sensors/Ping.h"
#include "utils/io.h"

//#pragma GCC optimize ("Os")

//these macros can be turned off to save space
#define DEBUG 1
#if DEBUG
    #define TEST(a) Serial.print(#a);Serial.print(": ");Serial.print(a);Serial.print("\t");
    #define FAIL(a) {Serial.print("\nERROR:>"); Serial.println(a); return false; }
#else
    #define TEST(a) ;
    #define FAIL(a) return false;
#endif

#endif // MINDS_I_COMMON_H
