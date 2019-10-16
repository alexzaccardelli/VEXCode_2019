#include "main.h"
#include <thread>

vex::brain Brain;
vex::controller Controller;
vex::limit botLimit (Brain.ThreeWirePort.H);

int encoderTest() {
  while(true) {
    Brain.Screen.printAt(5, 5, "Arm: %d", arm::currentVal());
    Brain.Screen.printAt(6, 5, "DriveLeft: %d", drive::getLeftEnc());
    Brain.Screen.printAt(7, 5, "DriveRight: %d", drive::getRightEnc());
    Brain.Screen.printAt(8, 5, "DriveTracker: %d", drive::getTrackEnc());
    Brain.Screen.printAt(9, 5, "leftRollerTorque: %d", roller::getLeftTorque());
    Brain.Screen.printAt(10, 5, "rightRollerTorque: %d", roller::getRightTorque());
    printf("Arm: %d\n", arm::currentVal());
    printf("DriveLeft: %d\n", drive::getLeftEnc());
    printf("DriveRight: %d\n", drive::getRightEnc());
    printf("DriveTracker: %d\n", drive::getTrackEnc());
    vex::task::sleep(5);
  }
  return 1;
}

int main() {
  printf("hello\n");
  drive::reset();
  roller::reset();
  arm::reset();
  while(true) {
    if(Controller.ButtonA.pressing())
      auton::blueBigNew();
    else if(Controller.ButtonB.pressing())
      break;
    vex::task::sleep(5);
  }

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