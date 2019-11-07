
#include "main.h"
#include <thread>

vex::brain Brain;
vex::controller Controller;

int display() {
  while(true) {
    printf("%f   %f\n", arm::left.torque(), arm::right.torque());
    vex::task::sleep(10);
  }
  return 1;
}

int main() {
  //Reset all motors and sensors
  drive::reset();
  roller::reset();
  arm::reset(); 
  
  //auton::skills();
  vex::timer t;
  drive::runRight(-100);
    vex::task::sleep(550);
    drive::reset();
    vex::task::sleep(150);
    drive::right1.spin(vex::directionType::fwd, 50, vex:: velocityUnits::pct);
    drive::left2.spin(vex::directionType::fwd, 100, vex:: velocityUnits::pct);
    drive::right2.spin(vex::directionType::fwd, -100, vex:: velocityUnits::pct);
    drive::left1.spin(vex::directionType::fwd, -50, vex:: velocityUnits::pct);
    vex::task::sleep(1600);
    drive::reset();
    vex::task::sleep(100);
    drive::run(20);
    while(drive::left1.torque() < .4) {}
    drive::reset();
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.print(t.time());
  /*vex::task driveTask(drive::op);
  vex::task armTask(arm::op);
  vex::task rollerTask(roller::op);
  vex::task displayTask(display);
  while(true) {
    if(Controller.ButtonUp.pressing())
      macro::down(&armTask, &rollerTask);
    if(Controller.ButtonRight.pressing())
      macro::stack(&armTask, &rollerTask, &driveTask);
    if(Controller.ButtonDown.pressing())
      macro::armReset(&armTask);
    vex::task::sleep(5);
  }*/
}