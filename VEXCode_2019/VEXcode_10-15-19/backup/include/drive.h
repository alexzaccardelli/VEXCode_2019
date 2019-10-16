#ifndef _DRIVE_H_
#define _DRIVE_H_

namespace drive {
  extern const double maxDef, kPDef, cerDef, cedDef;
  extern vex::motor left1, right1, left2, right2;
  void reset();
  int run(int speed);
  int runLeft(int speed);
  int runRight(int speed);
  int getLeftEnc();
  int getRightEnc();
  int getTrackEnc();
  int turn(double degrees);
  int forward(double inches, double max=maxDef, double kP=kPDef, double closeEnoughRange=cerDef, double closeEnoughDelay=cedDef);
  int op();
}

#endif