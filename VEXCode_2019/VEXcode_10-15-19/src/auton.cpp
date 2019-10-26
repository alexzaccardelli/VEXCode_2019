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
    if(side == 1) drive::turn(130);
    else drive::turn(-124);
    drive::run(100);
    vex::task::sleep(1600);
    drive::reset();
    macro::stackAuton();

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(8, 5);
    Brain.Screen.print(timer.time());
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
    temp = vex::task(_smallLift);
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
    vex::task::sleep(1000);
    drive::reset();
    vex::task::sleep(200);

    drive::turn(-15);
    //drive::forward(-10);
    //vex::task::sleep(300);
    //drive::turn(-146, 60);

    vex::task temp(specialRunToBot);
    drive::forward(-68);
    temp.stop();

    drive::turn(98);
    temp = vex::task(_bigLift);
    vex::task::sleep(800);
    drive::forward(15);
    roller::intake();
    arm::move(100, 100, 0.6, 20, 300);
    roller::reset();
    drive::forward(-5, 50);
    drive::turn(102, 70);
    vex::task dumb(luca);
    drive::forward(24, 55);
    dumb.stop();
    roller::intake();
    runToBot();
    vex::task::sleep(700);
    drive::runLeft(100);
    drive::runRight(55);
    vex::task::sleep(800);
    roller::reset();
    drive::reset();
    macro::stack();
    /*drive::run(-100);
    vex::task::sleep(500);
    drive::reset();
    temp = vex::task(_bigLift);
    drive::forward(29.5);
    temp.stop();

    roller::intake();
    _medLift();
    vex::task::sleep(300);

    /*vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    vex::task::sleep(700);
    roller::reset();

    // ** Drive to goal zone idk how rn **

    macro::stack();
    drive::forward(-5);
    drive::turn(-135);
    drive::forward(2);
    vex::limit blah1(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah1.value() == 0) {}
    arm::reset();
    vex::task::sleep(700);
    roller::reset();
    
    drive::turn(-100);
    //Task to lift to small tower
    drive::forward(50);
    roller::outake();
    vex::task::sleep(400);
    roller::reset();
    drive::forward(-24);
    //Task to lift to 3 cube stack
    drive::turn(100);
    drive::forward(12);
    vex::limit blah2(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah2.value() == 0) {}
    arm::reset();
    vex::task::sleep(700);
    roller::reset();
    drive::turn(90);
    //Task to lift to big tower
    drive::forward(24);
    roller::outake();
    vex::task::sleep(400);
    roller::reset();
    //Task to lift to small tower
    drive::turn(75);
    drive::forward(26);
    roller::outake();
    vex::task::sleep(400);
    roller::reset();
    drive::turn(100);
    drive::forward(52);
    roller::outake();
    vex::task::sleep(400);
    roller::reset();
    //Lift arm to prevent descoring tower cubes*/

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(t.time());
  }
}