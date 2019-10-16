#include "main.h"
#include <thread>

vex::brain Brain;
vex::controller Controller;

int main() {
  //Reset all motors and sensors
  drive::reset();
  roller::reset();
  arm::reset(); 

  //Auton or Driver control select
  while(true) {
    if(Controller.ButtonA.pressing())
      auton::redSmall();
    else if(Controller.ButtonB.pressing())
      break;
     else if(Controller.ButtonY.pressing())
      arm::move(130, 100, 1, 20, 200);
    vex::task::sleep(5);
  }
  
  //Driver Control Tasks
  vex::task driveTask(drive::op);
  vex::task armTask(arm::op);
  vex::task rollerTask(roller::op);
  while(true) {
    if(Controller.ButtonUp.pressing())
      macro::cubeIntakeMacro(&armTask, &rollerTask);
    if(Controller.ButtonRight.pressing())
      macro::stack(&armTask, &rollerTask, &driveTask);
    vex::task::sleep(5);
  }
}