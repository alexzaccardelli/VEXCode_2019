#include "main.h"
#include <thread>

vex::brain Brain;
vex::controller Controller;

int main() {
  //Reset all motors and sensors
  drive::reset();
  roller::reset();
  arm::reset(); 

  auton::small(auton::blue);
  //macro::stack();
  //drive::turn(180);
  
  //Driver Control Tasks
  /*vex::task driveTask(drive::op);
  vex::task armTask(arm::op);
  vex::task rollerTask(roller::op);
  while(true) {
    if(Controller.ButtonUp.pressing())
      macro::cubeIntakeMacro(&armTask, &rollerTask);
    if(Controller.ButtonRight.pressing())
      macro::stack(&armTask, &rollerTask, &driveTask);
    vex::task::sleep(5);
  }*/
}