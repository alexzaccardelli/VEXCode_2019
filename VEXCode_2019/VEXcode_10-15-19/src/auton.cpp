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
  
  int runToBot() {
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    return 1;
  }
  int specialRunToBot() {
    vex::task::sleep(700);
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    return 1;
  }

  void small(int side) {
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_reallySmallLift); //Maybe change

    drive::forward(18.5, 100, 0.12, 25, 100);
    
    temp.stop();
    roller::intake();
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    vex::task::sleep(700);
    roller::reset();

    for(int i = 0; i < 2; i++) {
      temp = vex::task(_smallLift);
      drive::forward(5.5, 100, 0.12, 25, 100);
      temp.stop();
      roller::intake();
      vex::limit blah1(Brain.ThreeWirePort.H);
      arm::run(-100);
      while(blah1.value() == 0) {}
      arm::reset();
      vex::task::sleep(700);
      roller::reset();
    }
    if(side == 1) drive::turn(-120, 100, 0.3, 6, 300);
    else drive::turn(-120, 100, 0.3, 6, 300);
    vex::task::sleep(200);
    drive::run(100);
    vex::task::sleep(1600);
    drive::reset();
    macro::stackAuton();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(8, 5);
    Brain.Screen.print(timer.time());
  }
  void newBig() {
    vex::timer timer;
    arm::setEncoder(0);
    vex::task temp(_bigLift);
    drive::forward(38, 80);
    temp.stop();
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    roller::reset();
    drive::forward1(-31, 70);
    drive::turn(105);
    drive::runLeft(100);
    drive::runRight(50);
    vex::task::sleep(1800);
    drive::reset();
    macro::stackAuton();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
    
    /*drive::forward(0);
    drive::run(100);
    vex::task::sleep(500);
    macro::stack();*/
  }

  void big(int side) {
    vex::timer timer;
    timer.clear();
    arm::resetBotLimit();
    arm::setEncoder(0);

    vex::task temp(_reallySmallLift);
    drive::forward(13, 100, 0.12, 25, 100);
    temp.stop();
    vex::limit blah(Brain.ThreeWirePort.H);
    roller::intake();
    arm::run(-100);
    while(arm::botLimit.value() == 0) {}
    arm::reset();
    vex::task::sleep(400);
    roller::reset();

    vex::task temp1(_bigLift);
    vex::task::sleep(350);
    drive::forward(22.5, 60, 0.12, 25, 100);
    temp1.stop();
    roller::intake();
    arm::move(260, 100, 0.6, 20, 150); //changing
    roller::reset();
    arm::move(280, 100, 0.6, 20, 150);//changing

    drive::forward(-5);
    vex::task::sleep(200);
    temp = vex::task(_reallySmallLift);
    vex::task::sleep(200);
    if(side == 1) drive::turn(-108, 60);//changing
    else drive::turn(108, 60); //changing
    
    
    drive::forward(21.5, 50);
    roller::intake();
    arm::run(-100);
    while(arm::botLimit.value() == 0) {}
    arm::reset();
    vex::task::sleep(400);
    roller::reset();

    drive::runRight(50);
    drive::runLeft(100);
    
    vex::task::sleep(800);
    drive::reset();

    //Change this to not use timing
    /*drive::forward(-10);
    drive::turn(117);
    drive::runRight(100);
    drive::runLeft(70);
    vex::task::sleep(850);
    drive::runRight(50);
    drive::runLeft(100);
    vex::task::sleep(900);
    drive::reset();*/

    macro::stack();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }


  //32 point skills

  int luca() {
    arm::move(250, 100, 0.6, 20, 300);
    return 1;
  }
  void skills() {
    vex::timer t;
    newBig();
    vex::task::sleep(200);
    
    drive::runRight(-100);
    drive::left2.spin(vex::directionType::fwd, 70, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -10, vex:: velocityUnits::pct);
    vex::task::sleep(400);
    drive::reset();
    vex::task::sleep(200);
    //drive::forward(-5);
    drive::right1.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    vex::task::sleep(1200);
    drive::reset();

    //dont know if this works !
    drive::run(25);
    vex::task::sleep(800);
    drive::runRight(10);
    drive::runLeft(30);
    vex::task::sleep(800);
    drive::reset();
    drive::right1.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    vex::task::sleep(400);
    drive::reset();
    
    drive::turn(-5, 100, 0.3, 4, 250); //Changed (-15)

    /*vex::task temp(specialRunToBot);
    drive::forward(-65);
    temp.stop();

    drive::turn(91);
    temp = vex::task(_bigLift);
    vex::task::sleep(800);
    drive::forward(25.5);
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    drive::turn(-75);
    drive::forward(-36);*/

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(t.time());
  }
}