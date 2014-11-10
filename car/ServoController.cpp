#include "ServoController.h"

//
void ServoController::set(float _target, float _vel)
{
  target = _target;
  vel = _vel;
}

//
void ServoController::update(float elapsed)
{
  if (vel == 0.0f)
  {
    pos = target;
  }
  else if (pos < target)
  {
    pos += vel * elapsed;
    if (pos > target)
      pos = target;
  }
  else if (pos > target)
  {
    pos -= vel * elapsed;
    if (pos < target)
      pos = target;
  }
  
  servo->writeMicroseconds((int)pos);
}

