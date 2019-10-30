
#include "main.h"
#include <thread>

vex::brain Brain;
vex::controller Controller;

int display() {
  while(true) {
    printf("%f  %f\n", arm::left.rotation(vex::rotationUnits::deg), arm::right.rotation(vex::rotationUnits::deg));
    vex::task::sleep(10);
  }
  return 1;
}

int main() {
  //Reset all motors and sensors
  drive::reset();
  roller::reset();
  arm::reset(); 
  //auton::big(auton::blue);
  //auton::newBig();
  auton::skills();

  //arm::setEncoder(900);
  //Driver Control Tasks
  //auton::runToBot();
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