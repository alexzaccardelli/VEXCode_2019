#ifndef _ARM_H_
#define _ARM_H_

namespace arm {
  extern vex::motor left, right;
  void reset();
  void run(int pow);
  void stop();
  int move(double degrees, int max, double kP, double closeEnoughRange, double closeEnoughDelay);
  int moveIntakeMacro();
  int moveIntakeMacro4();
  int op();
  int currentVal();
  void setEncoder(double val);
  int hold();
}

#endif