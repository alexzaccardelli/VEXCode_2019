#include "main.h"

namespace auton {

  int _bigLift() {
    arm::move(500, 100, 0.5, 20, 150);
    return 1;
  }
  int _smallLift() {
    arm::move(200, 100, 0.5, 20, 150);
    return 1;
  }

  void redSmall() {
    vex::timer timer;
    timer.clear();

    vex::task temp(_smallLift);
    drive::forward(15); //Temporary value
    temp.stop();
    macro::cubeIntakeMacro();

    for(int i = 0; i < 2; i++) { //Was 3
      temp = (arm::moveIntakeMacro);
      drive::forward(5.5);
      temp.stop();
      macro::cubeIntakeMacro();
    }

    drive::turn(130); //Was 135
    drive::forward(40, 100, 0.14, 30, 150);
    drive::run(100);
    vex::task::sleep(400);
    drive::reset();
    macro::stack();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }

/*
Arm to 200 degrees
Forward 9.5 inches
Intake cube
Arm to 500 degrees
Forward 22 inches
Intake 2 cubes
*/

  void blueBigNew() {
    vex::timer timer;
    timer.clear();
    vex::limit botLimit(Brain.ThreeWirePort.H);
    arm::setEncoder(0);

    vex::task temp(_smallLift);
    drive::forward(9.5);
    temp.stop();
    /*while(botLimit.value() == 0)
      arm::run(-100);
    vex::task::sleep(700);
    arm::stop();
    roller::reset();
    vex::task temp1(_bigLift);
    drive::forward(22);
    temp1.stop();
    roller::intake();
    while(arm::currentVal() > 300)
      arm::run(-100);
    vex::task temp2(arm::hold);
    vex::task::sleep(500);
    roller::reset();
    drive::turn(110);
    drive::forward(30, 100, 0.14, 30, 150);
    drive::turn(18);
    drive::runRight(100);
    drive::runLeft(80);
    temp1.stop();
    vex::task::sleep(300);
    drive::reset();
    macro::stack();*/

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }

  void blueBig() {
    vex::timer timer;
    timer.clear();
    vex::limit botLimit(Brain.ThreeWirePort.H);
    arm::setEncoder(0);

    vex::task temp(_bigLift);
    drive::forward(31.5);
    temp.stop();
    roller::intake();
    while(arm::currentVal() > 100)
      arm::run(-100);
    vex::task temp1(arm::hold);
    vex::task::sleep(200);
    roller::reset();
    drive::turn(128);
    drive::forward(30, 100, 0.14, 30, 150);
    drive::runRight(100);
    drive::runLeft(80);
    temp1.stop();
    vex::task::sleep(300);
    drive::reset();
    /*stack();*/

    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }
}