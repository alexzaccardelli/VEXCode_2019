#include "main.h"

namespace auton {

  /*
    Private functions:
      _bigLift(): Move to 550 degrees
      _medLift(): move to 0 degrees
      _smallLift(): move to 170 degrees
  */
  int _bigLift() {
    arm::move(550, 100, 0.6, 20, 150);
    return 1;
  }
  int _smallLift() {
    arm::move(170, 100, 0.6, 20, 200);
    return 1;
  }
  int _medLift() {
    arm::move(0, 100, 0.6, 20, 300);
    return 1;
  }

  //idk how this works lol its fine
  void redSmall() {
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_smallLift); //Maybe change
    drive::forward(23); //Needs changing
    temp.stop();
    roller::intake();
    arm::resetBotLimit();
    while(arm::botLimit.value() == 0)
        arm::run(-100);
    vex::task::sleep(700);
    roller::reset();
    arm::reset();

    for(int i = 0; i < 2; i++) {
      arm::resetBotLimit();
      temp = vex::task(_smallLift);
      drive::forward(5.5);
      temp.stop();
      roller::intake();
      while(arm::botLimit.value() == 0)
        arm::run(-100);
      vex::task::sleep(700);
      arm::reset();
      roller::reset();
    }

    drive::turn(125);
    drive::run(100);
    vex::task::sleep(1000); //Needs changing
    drive::reset();
    macro::stack();

    Brain.Screen.printAt(5, 5, "%d", timer.time());
  }

  void blueBigNew() {
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_smallLift);
    //vex::task::sleep(300);
    drive::forward(8, 100, 0.14, 10, 150); //Needs tuning
    temp.stop();
    roller::intake();
    while(arm::botLimit.value() == 0)
      arm::run(-100);
    vex::task::sleep(400);
    arm::reset();
    roller::reset();

    vex::task temp1(_bigLift);
    vex::task::sleep(350);
    drive::forward(24.5);
    temp1.stop();
    roller::intake();
    _medLift();
    vex::task::sleep(500);
    roller::reset();

    drive::forward(-10);
    drive::turn(117);
    drive::forward(13.5, 60, 0.14, 30, 150);
    drive::turn(-21);
    drive::runRight(80);
    drive::runLeft(100);
    vex::task::sleep(500);
    drive::reset();
    //macro::stack();*/

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }

  /*void blueBig() {
    vex::timer timer;
    timer.clear();
    vex::limit botLimit(Brain.ThreeWirePort.H);
    arm::setEncoder(0);

    vex::task temp(_bigLift);
    drive::forward(31.5);
    temp.stop();
    roller::intake();
    while(arm::left.rotation(vex::rotationUnits::deg) > 100)
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
    stack();

    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }*/
}