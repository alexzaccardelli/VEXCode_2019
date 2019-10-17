#ifndef _ARM_H_
#define _ARM_H_

namespace arm {
  
  //Global access
  extern vex::motor left, right;
  extern vex::limit botLimit;
  extern double degreesLeft, degreesRight;

  //Default parameters for move()
  extern const double maxDef, kPDef, cerDef, cedDef;
  

  /*
    stop left and right motor
    left and right brake coast
    reset left and right encoders
    resetBotLimit()
  */
  void reset();

  /*
    Redeclares botLimit (effectively sets it to 0)
  */
  void resetBotLimit();

  /*
    Set left and right encoder to val
      Defulat parameters:
        val = 0
  */
  void setEncoder(double val = 0);

  /*
    Sets arm motors to pow
  */
  void run(int pow);

  /*
    Stops left and right motors (Does not reset encoders or hold position)
  */
  void stop();

  /*
    Move arm to degrees using p-controller
      Default parameters:
        max = 100
        kP = 0.6
        closeEnoughRange = 20
        closeEnoughDelay = 200
  */
  int move(double degrees, double max=maxDef, double kP=kPDef, double closeEnoughRange=cerDef, double closeEnoughDelay=cedDef);

  /*
    Hold left and right at last recorded encoder position
  */
  int hold();

  /*
    Driver control of arm
      R1: up
      R2: down
      None: hold motors at last recorded encoder position
  */
  int op();
}

#endif