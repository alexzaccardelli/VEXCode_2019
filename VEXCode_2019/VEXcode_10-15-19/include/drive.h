#ifndef _DRIVE_H_
#define _DRIVE_H_

namespace drive {

  //Global access
  extern vex::motor left1, right1, left2, right2;
  extern vex::encoder leftEnc, rightEnc;

  //Default parameters for forward()
  extern const double maxDef, kPDef, cerDef, cedDef;
  extern const double maxDef1, kPDef1, cerDef1, cedDef1;
  
  /*
    Stops all motors
    Reset left and right tracking encoders
    Reset all motor encoders
  */
  void reset();

  /*
    Sets all motors to speed
  */
  void run(int speed);

  /*
    Sets left motors to speed
  */
  void runLeft(int speed);

  /*
  Sets right motors to speed
  */
  void runRight(int speed);

  /*
    Turn drivetrain degrees
      Constants:
        max = 100
        kP = 0.3
        closeEnoughRange = 3
        closeEnoughDelay = 300
    Includes acceleration cap
  */
  int turn(double degrees, double max=maxDef1, double kP=kPDef1, double closeEnoughRange=cerDef1, double closeEnoughDelay=cedDef1);
  /*
    Forward inches using p-controller
      Default parameters:
        max = 100
        kP = 0.14
        closeEnoughRange = 10
        closeEnoughDelay = 300
    Includes acceleration cap
  */
  int forward1(double inches, double max=maxDef, double kP=kPDef, double closeEnoughRange=cerDef, double closeEnoughDelay=cedDef);
  int forward(double inches, double max=maxDef, double kP=kPDef, double closeEnoughRange=cerDef, double closeEnoughDelay=cedDef);

  /*
    Driver control
      Left axes: Planar movement
      Right x-axis: Turning
    Includes acceleration cap
    Includes reduced speed dependent on arm height
  */
  
  int op();
}

#endif