#ifndef _ROLLER_H_
#define _ROLLER_H_

namespace roller {
  
  //Global access
  extern vex::motor left, right;

  /*
    Stops left and right motor
    Reset left and right encoder
    Set brakemode to hold
  */
  void reset();

  /*
    Set left and right to speed
      Default parameter:
        speed = 100
  */
  void intake(int speed=100);

  /*
    Set left and right to speed
      Default parameter:
        speed = -50
  */
  void outake(int speed=-50);

  /*
    Driver Control
      X: intake
      B: outake
  */
  int op();
}

#endif