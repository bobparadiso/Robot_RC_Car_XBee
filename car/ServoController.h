#include <Servo.h>

class ServoController
{
public:
  Servo *servo;
  float pos;
  float target;
  float vel;
    
public:
  void set(float _target, float _vel);
  void update(float elapsed);
};

