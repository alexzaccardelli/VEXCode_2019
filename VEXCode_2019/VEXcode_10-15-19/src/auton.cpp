#include "main.h"

namespace auton {

  int _bigLift() { arm::move(670, 100, 0.6, 20, 150); return 1; }
  int _smallLift() { arm::move(230, 100, 0.6, 20, 200); return 1; }
  int _medLift() { arm::move(0, 100, 0.6, 20, 300); return 1; }
  int _reallySmallLift() { arm::move(180, 100, 0.6, 20, 200); return 1; }
  
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
      runToBot();
      vex::task::sleep(700);
      roller::reset();
    }
    if(side == red) drive::turn(120, 100, 0.3, 6, 300);
    else drive::turn(-120, 100, 0.3, 6, 300);
    vex::task::sleep(200);
    drive::run(100);
    vex::task::sleep(1600);
    drive::reset();
    macro::stack();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(8, 5);
    Brain.Screen.print(timer.time());
  }

  void big(int side) {
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
    if(side == blue) drive::turn(105);
    else drive::turn(-97);
    drive::runRight(100);
    drive::runLeft(50);
    vex::task::sleep(1800);
    drive::reset();
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
    big(blue);
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