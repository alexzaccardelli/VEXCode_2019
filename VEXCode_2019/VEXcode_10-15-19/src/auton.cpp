#include "main.h"

namespace auton {

  /*
    Private functions:
      _bigLift(): Move to 550 degrees
      _medLift(): move to 0 degrees
      _smallLift(): move to 170 degrees
  */
  int _bigLift() {
    arm::move(670, 100, 0.6, 20, 150);
    return 1;
  }
  int _smallLift() {
    arm::move(230, 100, 0.6, 20, 200);
    return 1;
  }
  int _medLift() {
    arm::move(0, 100, 0.6, 20, 300);
    return 1;
  }
  int _reallySmallLift() {
    arm::move(180, 100, 0.6, 20, 200);
    return 1;
  }

  //idk how this works lol its fine
  void redSmall() {
    
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_smallLift); //Maybe change
    
    //vex::task temp1(arm::hold);
    drive::forward(18.5, 100, 0.12, 25, 100); //Needs changing
    
    temp.stop();
    //temp1.stop();
    roller::intake();
    //arm::resetBotLimit();
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    vex::task::sleep(700);
    roller::reset();
    

    for(int i = 0; i < 2; i++) {
      temp = vex::task(_smallLift);
      //temp1 = vex::task(arm::hold);
      drive::forward(5.5, 100, 0.12, 25, 100);
      
      temp.stop();
      //temp1.stop();
      roller::intake();
      vex::limit blah1(Brain.ThreeWirePort.H);
      arm::run(-100);
      while(blah1.value() == 0) {}
      arm::reset();
      vex::task::sleep(700);
      roller::reset();
    }

    drive::turn(125);
    drive::run(100);
    vex::task::sleep(1600); //Needs changing
    drive::reset();
    macro::stack();
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(8, 5);
    Brain.Screen.print(timer.time());
  }

  void blueSmall() {
    
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_smallLift); //Maybe change
    
    //vex::task temp1(arm::hold);
    drive::forward(18.5, 100, 0.12, 25, 100); //Needs changing
    
    temp.stop();
    //temp1.stop();
    roller::intake();
    //arm::resetBotLimit();
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    vex::task::sleep(700);
    roller::reset();
    

    for(int i = 0; i < 2; i++) {
      temp = vex::task(_smallLift);
      //temp1 = vex::task(arm::hold);
      drive::forward(5.5, 100, 0.12, 25, 100);
      
      temp.stop();
      //temp1.stop();
      roller::intake();
      vex::limit blah1(Brain.ThreeWirePort.H);
      arm::run(-100);
      while(blah1.value() == 0) {}
      arm::reset();
      vex::task::sleep(700);
      roller::reset();
    }

    drive::turn(-125);
    drive::run(100);
    vex::task::sleep(1600); //Needs changing
    drive::reset();
    macro::stack();
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(8, 5);
    Brain.Screen.print(timer.time());
  }

  void blueBigNew() {
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_reallySmallLift);
    //vex::task::sleep(300);
    drive::forward(13); //Needs tuning
    temp.stop();
    vex::limit blah(Brain.ThreeWirePort.H);
    roller::intake();
    while(arm::botLimit.value() == 0)
      arm::run(-100);
    arm::reset();
    vex::task::sleep(400);
    roller::reset();

    vex::task temp1(_bigLift);
    vex::task::sleep(350);
    drive::forward(22.5);
    temp1.stop();
    roller::intake();
    _medLift();
    //vex::task::sleep(500);
    roller::reset();

    drive::forward(-10);
    drive::turn(117);
    drive::runRight(100);
    drive::runLeft(70);
    vex::task::sleep(850);
    drive::runRight(50);
    drive::runLeft(100);
    vex::task::sleep(900);
    drive::reset();
    /*drive::forward(17.5, 100, 0.12, 30, 150);
    drive::turn(-30);
    drive::runRight(50);
    drive::runLeft(100);
    vex::task::sleep(800);
    drive::reset();*/
    macro::stack();

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