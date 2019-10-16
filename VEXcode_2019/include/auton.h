#ifndef _AUTON_H_
#define _AUTON_H_

namespace auton {
  void blueBig();
  void blueSmall();
  void redBig();

  /*
    _smallLift();
    Forward 14 inches
    intake 1 cube
    _smallLift();
    Forward 5.5 inches
    intake 1 cube
    _smallLift();
    Forward 5.5 inches
    intake 1 cube
    Turn 125 degrees right
    Forward at 100% for 1 second
    Stack 4 cubes
  */
  void redSmall();

  /*
    Arm to 200 degrees
    Forward 9.5 inches
    Intake cube
    Arm to 500 degrees
    Forward 22 inches
    Intake 2 cubes
  */
  void blueBigNew();
}

#endif