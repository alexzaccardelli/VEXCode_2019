#include "main.h"
  
  namespace arm {
  vex::motor left (vex::PORT9, vex::gearSetting::ratio36_1, false);
  vex::motor right (vex::PORT6, vex::gearSetting::ratio36_1, true);
  std::vector<double> armTime, armError, armSpeed, armRotation;
  
  void reset() {
    left.stop();
    right.stop();
    left.resetRotation();
    right.resetRotation();
    left.setBrake(vex::brakeType::coast);
    right.setBrake(vex::brakeType::coast);
  }
  int currentVal() {
    return left.rotation(vex::rotationUnits::deg);
  }
  void setEncoder(double val) {
    left.setRotation(val, vex::rotationUnits::deg);
    left.setRotation(val, vex::rotationUnits::deg);
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
    double max = 100, kP = 0.5;
    double leftSpeed = 0, rightSpeed = 0;
    double leftError = 0, rightError = 0;
    int degreesLeft = 0, degreesRight = 0;
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
      while(!Controller.ButtonR2.pressing() && !Controller.ButtonR1.pressing()) {
        leftError = degreesLeft - left.rotation(vex::rotationUnits::deg);
        rightError = degreesRight - right.rotation(vex::rotationUnits::deg);

        leftSpeed = leftError * kP;
        rightSpeed = rightError * kP;
    
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
    }
    return 1;
  }

  int hold() {
    stop();
    double leftSpeed = 0, rightSpeed = 0;
    double leftError = 0, rightError = 0, accel = 1, kP = 0.5, max = 100;
    int degrees = arm::currentVal();
    int delay = 10;
    vex::timer timer, closeEnoughTimer;
    closeEnoughTimer.clear(); timer.clear();
    while(true) {
      //Error
      leftError = degrees - left.rotation(vex::rotationUnits::deg);
      rightError = degrees - right.rotation(vex::rotationUnits::deg);
      
      //Slew rate
      if(leftError * kP > leftSpeed)
        leftSpeed += accel;
      else
        leftSpeed = leftError * kP;
      if(rightError * kP > rightSpeed)
        rightSpeed += accel;
      else
        rightSpeed = rightError * kP;
      /*leftSpeed = leftError * kP;
      rightSpeed = rightError * kP;*/
  
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

  int move(double degrees, int max, double kP, double closeEnoughRange, double closeEnoughDelay) {
    stop();
    double leftSpeed = 0, rightSpeed = 0;
    double leftError = 0, rightError = 0, accel = 1;
    int delay = 10;
    vex::timer timer, closeEnoughTimer;
    closeEnoughTimer.clear(); timer.clear();
    while(true) {
      //Error
      leftError = degrees - left.rotation(vex::rotationUnits::deg);
      rightError = degrees - right.rotation(vex::rotationUnits::deg);
      
      //Slew rate
      if(leftError * kP > leftSpeed)
        leftSpeed += accel;
      else
        leftSpeed = leftError * kP;
      if(rightError * kP > rightSpeed)
        rightSpeed += accel;
      else
        rightSpeed = rightError * kP;
      //leftSpeed = leftError * kP;
      //rightSpeed = rightError * kP;
  
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