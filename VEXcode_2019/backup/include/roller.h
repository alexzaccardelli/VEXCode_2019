#ifndef _ROLLER_H_
#define _ROLLER_H_

namespace roller {
  extern vex::motor left, right;
  void reset();
  int getLeftTorque();
  int getRightTorque();
  void intake(int speed=100);
  void outake(int speed=-50);
  int op();
}

#endif