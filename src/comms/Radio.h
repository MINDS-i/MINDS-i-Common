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

#ifndef MINDS_I_COMMON_COMMS_RADIO_H
#define MINDS_I_COMMON_COMMS_RADIO_H

#include "Arduino.h"
#include "wiring_private.h"
#include <util/atomic.h>

namespace minds_i_common::comms {

/** maximum microseconds without a pulse before considering the signal off*/
constexpr uint32_t RADIO_PULSE_TIMEOUT = 80000;
/** high time in microseconds of a radio signal at 0 degrees */
constexpr uint16_t RADIO_MIN_US = 600;
/** high time in microseconds of a radio signal at 180 degrees */
constexpr uint16_t RADIO_MAX_US = 2400;
/** if a signal's high interval exceeds RADIO_INVALID_US, it is not
 * considered a radio signal by getRadioPulse
 */
constexpr uint16_t RADIO_INVALID_US = 3000;
/** signal to return from getRadio when nothing is received */
constexpr uint16_t DEFAULT_RADIO_SIGNAL = 90;
/** returned by getRadioPulse when no radio pulse is active */
constexpr uint16_t NO_PULSE = 0xffff;

/** Return the radio signal present on `pin`
 * The signal is scaled as if it were a servo signal into the range 0-180
 * If no signal is present, DEFAULT_RADIO_SIGNAL is returned
 * If `interrupt`, this will enable an interrupt based signal receiver
 *     and the call will immediatly return stored values from then on.
 * If `interrupt` is false or the pin does not support interrupt input,
 *     The call will wait until a new pulse arrives and time it.
 **/
uint16_t getRadio(int pin, bool interrupt = true);
/** Determines if a radio signal is present on the given pin */
bool isRadioOn(int pin, bool interrupt = true);
/** Return the raw radio pulse length on a given pin, or NO_PULSE */
uint16_t getRadioPulse(int pin, bool interrupt);

} // namespace minds_i_common::comms

#endif // MINDS_I_COMMON_COMMS_RADIO_H