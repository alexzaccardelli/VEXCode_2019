#include "main.h"

namespace roller {
  vex::motor left (vex::PORT20, vex::gearSetting::ratio18_1, false);
  vex::motor right (vex::PORT13, vex::gearSetting::ratio18_1, true);
  const int outSpeed = -50, inSpeed = 100, delay = 5;

  void reset() {
    left.stop();
    right.stop();
    left.resetRotation();
    right.resetRotation();
    left.setBrake(vex::brakeType::hold);
    right.setBrake(vex::brakeType::hold);
  }
  
  int getLeftTorque() {
    return left.torque(vex::torqueUnits::InLb);
  }
  int getRightTorque() {
    return right.torque(vex::torqueUnits::InLb);
  }

  void intake(int speed) {
    left.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    right.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }

  void outake(int speed) {
    left.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    right.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  }

  int op() {
    while(true) {
      while(Controller.ButtonX.pressing()) {
        left.spin(vex::directionType::fwd, inSpeed, vex::velocityUnits::pct);
        right.spin(vex::directionType::fwd, inSpeed, vex::velocityUnits::pct);
      }
      while (Controller.ButtonB.pressing()) {
        left.spin(vex::directionType::fwd, outSpeed, vex::velocityUnits::pct);
        right.spin(vex::directionType::fwd, outSpeed, vex::velocityUnits::pct);
      }
      left.stop();
      right.stop();
      vex::task::sleep(delay);
    }
    return 1;
  }
}