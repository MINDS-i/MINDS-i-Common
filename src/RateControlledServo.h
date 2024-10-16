#include <Servo.h>

class RateControlledServo : public Servo
{
public:
  RateControlledServo();
  void attachInitAngle(int pin, int initAngle);  // attach to pin and set initial servo angle
  void writeRateControlled(int setAngle, int dps);  // angle (degrees) and degree per second limit (dps should be >= 0 && <= 4294)
  // todo write a method for specifying pulse width instead of angle
private:
  unsigned long lastUpdate_;
  unsigned long residual_;
  bool initialized_;
};