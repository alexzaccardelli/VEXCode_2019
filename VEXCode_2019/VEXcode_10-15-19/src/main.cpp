
#include "main.h"
#include <thread>

vex::brain Brain;
vex::controller Controller;

int main() {
  //Reset all motors and sensors
  drive::reset();
  roller::reset();
  arm::reset(); 
  //drive::forward(-61);
  /*vex::limit blah(Brain.ThreeWirePort.H);
  arm::run(-100);
  while(blah.value() == 0) {}
  arm::reset();
  arm::move(500);
  arm::hold();*/
  //drive::turn(108);
  //auton::skills();c
  vex::task temp (drive::gyroValue);
  drive::gyro.calibrate();
  vex::task::sleep(1500);
  drive::turn1(90, 100);
  
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