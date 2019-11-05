#include "main.h"

namespace auton {

  int _bigLift() { arm::move(670, 100, 0.6, 20, 150); return 1; }
  int _otherLift() { arm::move(500, 100, 0.6, 20, 150); return 1; }
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
  int delayedRunToBot() {
    vex::task::sleep(1000);
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
      drive::forward(5.7, 100, 0.12, 25, 100);
      temp.stop();
      roller::intake();
      runToBot();
      vex::task::sleep(700);
      roller::reset();
    }
    if(side == red) drive::turn(128, 100, 0.3, 6, 150);
    else drive::turn(-120, 100, 0.3, 6, 300);
    drive::run(100);
    vex::task::sleep(1600);
    drive::reset();
    macro::stack();
    drive::run(-40);
    while(timer.time() < 15000) {}
    drive::reset();

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
    if(side == blue || side == auton) drive::turn(105);
    else drive::turn(-107);
    if(side == blue || side == auton) {
      drive::runLeft(100);
      drive::runRight(50);
    }
    else {
      drive::runRight(100);
      drive::runLeft(40);
    }
    
    vex::task::sleep(1800);
    drive::reset();
    macro::stack();
    if(side != auton) {
      drive::run(-40);
      while(timer.time() < 15000) {}
      drive::reset();
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(timer.time());
  }


  //32 point skills
  void skills() {
    vex::timer t;
    drive::forward(2);
    arm::move(600, 100, 0.6, 20, 150);
    vex::task temp5(arm::hold);
    drive::forward(12.5);
    roller::outake();
    vex::task::sleep(800);
    roller::reset();
    drive::forward(-8);

    drive::turn(80);
    drive::forward(34, 60);
    temp5.stop();
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    roller::reset();
    drive::turn(120);
    drive::forward(34, 70);
    drive::forward(-2,70);
    drive::turn(-60);
    drive::forward(17,100);
    drive::reset();
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, 30, vex:: velocityUnits::pct);
    drive::right1.spin(vex::directionType::fwd, 30, vex:: velocityUnits::pct);
    vex::task::sleep(1800);
    drive::reset();
    macro::stack();
    temp5 = vex::task(arm::hold);
    /*drive::turn(-68);
    drive::runLeft(100);
    drive::runRight(60);
    vex::task::sleep(1600);
    drive::reset();
    vex::task::sleep(300);*/
    /*
    drive::right1.spin(vex::directionType::fwd, 70, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -70, vex:: velocityUnits::pct);
    vex::task::sleep(1800);
    drive::reset();
    vex::task::sleep(300);
    drive::runLeft(80);
    drive::runRight(100);
    vex::task::sleep(1000);
    drive::reset();
    macro::stack();
    temp5 = vex::task(arm::hold);*/

    drive::runRight(-100);
    vex::task::sleep(400);
    drive::reset();
    vex::task::sleep(300);
    drive::right1.spin(vex::directionType::fwd, 50, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -50, vex:: velocityUnits::pct);
    vex::task::sleep(2300);
    drive::reset();
    vex::task::sleep(500);
    drive::run(10);
    while(drive::left1.torque() < .4) {}
    drive::reset();
    vex::task::sleep(200);
    temp5.stop();
    
    drive::turn(-5, 100, 0.3, 4, 250); //Changed (-15)

    vex::task temp(delayedRunToBot);
    drive::forward(-70.5);
    temp.stop();

    drive::turn(92);
    temp = vex::task(_bigLift);
    vex::task::sleep(800);
    drive::forward(20.5,60);
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    roller::reset();

    drive::turn(96);
    drive::forward(34, 70);
    vex::task::sleep(300);
    //drive::turn(13);
    drive::right1.spin(vex::directionType::fwd, -70, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, 70, vex:: velocityUnits::pct);
    vex::task::sleep(1000);
    drive::reset();
    drive::runLeft(65);
    drive::runRight(100);
    vex::task::sleep(1200);
    drive::reset();
    macro::stack();
    drive::reset();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(t.time());
  }
}