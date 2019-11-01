#include "main.h"
  
namespace arm {
  vex::motor left (vex::PORT9, vex::gearSetting::ratio36_1, false);
  vex::motor right (vex::PORT6, vex::gearSetting::ratio36_1, true);
  vex::limit botLimit (Brain.ThreeWirePort.H);
  double const maxDef=100, kPDef=0.6, cerDef=10, cedDef=200;
  double degreesLeft = 0, degreesRight = 0;
  
  void reset() {
    left.stop();
    right.stop();
    left.resetRotation();
    right.resetRotation();
    left.setBrake(vex::brakeType::coast);
    right.setBrake(vex::brakeType::coast);
  }

  void setEncoder(double val) {
    left.setRotation(val, vex::rotationUnits::deg);
    right.setRotation(val, vex::rotationUnits::deg);
  }
  void run(int pow) {
    left.spin(vex::directionType::fwd, pow, vex::velocityUnits::pct);
    right.spin(vex::directionType::fwd, pow, vex::velocityUnits::pct);
  }
  void stop() {
    left.stop();
    right.stop();
  }

  int op() {
    int upSpeed = 100, downSpeed = -50, delay = 10;
    double leftSpeed = 0, rightSpeed = 0, max = 100, kP = 0.04, kTorque = 0, leftError = 0, rightError = 0, leftKp = 0, rightKp = 0; //Change kTorque
    while(true) {
      while(Controller.ButtonR1.pressing()) {
        left.spin(vex::directionType::fwd, upSpeed, vex::velocityUnits::pct);
        right.spin(vex::directionType::fwd, upSpeed, vex::velocityUnits::pct);
        degreesLeft = left.rotation(vex::rotationUnits::deg);
        degreesRight = right.rotation(vex::rotationUnits::deg);
        
      }
      while(Controller.ButtonR2.pressing()) {
        left.spin(vex::directionType::fwd, downSpeed, vex::velocityUnits::pct);
        right.spin(vex::directionType::fwd, downSpeed, vex::velocityUnits::pct);
        degreesLeft = left.rotation(vex::rotationUnits::deg);
        degreesRight = right.rotation(vex::rotationUnits::deg);
      }
      if(!Controller.ButtonR2.pressing() && !Controller.ButtonR1.pressing()) {
        while(!Controller.ButtonR2.pressing() && !Controller.ButtonR1.pressing()) {
          //Error
          leftError = degreesLeft - left.rotation(vex::rotationUnits::deg);
          rightError = degreesRight - right.rotation(vex::rotationUnits::deg);
          leftKp = kTorque * left.torque();
          rightKp = kTorque * right.torque();

          //Speed
          leftSpeed = leftError * leftKp;
          rightSpeed = rightError * rightKp;

          //Max speed
          if(leftSpeed > max)   leftSpeed = max;
          if(rightSpeed > max)  rightSpeed = max;
          if(leftSpeed < -max)  leftSpeed = -max;
          if(rightSpeed < -max) rightSpeed = -max;
      
          //Motor power
          left.setVelocity(leftSpeed, vex::velocityUnits::pct);
          right.setVelocity(rightSpeed, vex::velocityUnits::pct);

          //Delay
          vex::task::sleep(delay);
        }
      }
    }
    return 1;
  }

  int hold() {
    arm::degreesLeft = arm::left.rotation(vex::rotationUnits::deg);
    arm::degreesRight = arm::right.rotation(vex::rotationUnits::deg);
    stop();
    double leftError = 0, rightError = 0, kP = 0.5, max = 100, leftSpeed = 0, rightSpeed = 0;
    double leftKp = 0, rightKp = 0, kTorque = 0; //values
    int delay = 10;
    double degrees = left.rotation(vex::rotationUnits::deg);
    vex::timer timer, closeEnoughTimer;
    closeEnoughTimer.clear(); timer.clear();
    while(true) {
      leftKp = kTorque * left.torque();
      rightKp = kTorque * right.torque();

      //Error
      leftError = degrees - left.rotation(vex::rotationUnits::deg);
      rightError = degrees - right.rotation(vex::rotationUnits::deg);

      //Speed
      leftSpeed = leftError * leftKp;
      rightSpeed = rightError * rightKp;
  
      //Max speed
      if(leftSpeed > max)   leftSpeed = max;
      if(rightSpeed > max)  rightSpeed = max;
      if(leftSpeed < -max)  leftSpeed = -max;
      if(rightSpeed < -max) rightSpeed = -max;
  
      //Motor power
      left.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
      right.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);

      //Delay
      vex::task::sleep(delay);
    }
    stop();
    return 1;
  }

  int move(double degrees, double max, double kP, double closeEnoughRange, double closeEnoughDelay) {
    stop();
    double leftError = 0, rightError = 0, leftSpeed = 0, rightSpeed = 0;
    int delay = 10;
    vex::timer closeEnoughTimer;
    closeEnoughTimer.clear();
    while(true) {
      //Error
      leftError = degrees - left.rotation(vex::rotationUnits::deg);
      rightError = degrees - right.rotation(vex::rotationUnits::deg);

      //Speed
      leftSpeed = leftError * kP;
      rightSpeed = rightError * kP;
  
      //Max speed
      if(leftSpeed > max)   leftSpeed = max;
      if(rightSpeed > max)  rightSpeed = max;
      if(leftSpeed < -max)  leftSpeed = -max;
      if(rightSpeed < -max) rightSpeed = -max;

      //End condition
      if(abs((int)leftError) > closeEnoughRange && abs((int)rightError) > closeEnoughRange) closeEnoughTimer.clear();
      if(closeEnoughTimer.time() > closeEnoughDelay) break;
  
      //Motor power
      left.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
      right.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);

      //Delay
      vex::task::sleep(delay);
    }
    stop();
    return 1;
  }
}