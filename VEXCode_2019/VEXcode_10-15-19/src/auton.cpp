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
  int asdf() {
    arm::move(600, 100, 0.6, 20, 150);
    arm::hold();
    return 1;
  }
  //32 point skills
  void skills() {
    vex::timer t;
    
    vex::task jf(asdf);
    drive::forward(14.5, 25);
    
    //jf.stop();
    //vex::task temp5(arm::hold);
    roller::outake();
    vex::task::sleep(800);
    roller::reset();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(t.time());

    drive::forward(-8);
    drive::turn(80);
    drive::forward(34, 60);
    jf.stop();
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    roller::reset();
    drive::turn(120);
    drive::forward(33, 70);//32
    drive::forward(-1,70);//-2
    drive::turn(-60);
    drive::forward(18,100);
    drive::reset();
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, 30, vex:: velocityUnits::pct);
    drive::right1.spin(vex::directionType::fwd, 30, vex:: velocityUnits::pct);
    vex::task::sleep(1100);//1800
    drive::reset();
    drive::forward(-.5);
    macro::stack();
    vex::task temp5(arm::hold);

    drive::runRight(-100);
    vex::task::sleep(550);
    drive::reset();
    vex::task::sleep(300);
    drive::right1.spin(vex::directionType::fwd, 50, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -50, vex:: velocityUnits::pct);
    vex::task::sleep(1600);
    drive::reset();
    vex::task::sleep(500);
    drive::run(10);
    while(drive::left1.torque() < .4) {}
    drive::reset();
    vex::task::sleep(200);
    temp5.stop();
    
    drive::turn(-8, 100, 0.3, 4, 250); //Changed (-15)

    vex::task temp(delayedRunToBot);
    drive::forward(-69);//-70.5
    temp.stop();

    drive::turn(95);
    temp = vex::task(_bigLift);
    vex::task::sleep(800);
    drive::forward(21.5,60);
    
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    roller::reset();
    drive::turn(90);
    drive::forward(34, 70);
    //drive::forward(-2,70);
    drive::turn(64);
    drive::forward(13,100);//15
    drive::reset();
    drive::left2.spin(vex::directionType::fwd, 20, vex:: velocityUnits::pct);//0
    drive::left1.spin(vex::directionType::fwd, 20, vex:: velocityUnits::pct);//0
    drive::right2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right1.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    vex::task::sleep(1200);//2100
    drive::reset();
    drive::forward(-.5);

    roller::outake();
    vex::task::sleep(800);
    roller::reset();
    arm::run(55);
    roller::outake(-60);
    vex::task::sleep(700);
    arm::stop();
    roller::reset();
    _bigLift();
    vex::task temp6(arm::hold);

    drive::runRight(-100);
    vex::task::sleep(550);
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
    while(drive::left1.torque() < .42) {}
    drive::reset();
    vex::task::sleep(200);
    temp6.stop();
    drive::turn(-5);
    drive::forward(-45, 70);
    drive::turn(123);
    drive::forward(9.5);
    roller::outake();
    vex::task::sleep(700);
    roller::reset();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(t.time());
  }
}