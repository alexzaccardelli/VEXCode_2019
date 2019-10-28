#include "main.h"

namespace drive {
  vex::motor left1 (vex::PORT1, vex::gearSetting::ratio18_1, false);
  vex::motor left2 (vex::PORT2, vex::gearSetting::ratio18_1, false);
  vex::motor right1 (vex::PORT3, vex::gearSetting::ratio18_1, true);
  vex::motor right2 (vex::PORT4, vex::gearSetting::ratio18_1, true);
  vex::encoder leftEnc (Brain.ThreeWirePort.A);
  vex::encoder rightEnc (Brain.ThreeWirePort.C);
  const double maxDef=100, kPDef=0.12, cerDef=20, cedDef=100;
  const double maxDef1=100, kPDef1=0.3, cerDef1=6, cedDef1=150;
  
  void reset() {
    left1.stop();
    left2.stop();
    right1.stop();
    right2.stop();
    left1.setBrake(vex::brakeType::coast);
    left2.setBrake(vex::brakeType::coast);
    right1.setBrake(vex::brakeType::coast);
    right2.setBrake(vex::brakeType::coast);
    left1.resetRotation();
    left2.resetRotation();
    right1.resetRotation();
    right2.resetRotation();
    leftEnc.setRotation(0, vex::rotationUnits::deg);
    rightEnc.setRotation(0, vex::rotationUnits::deg);
  }
  void run(int speed) {
    left1.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
    left2.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
    right1.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
    right2.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
  }
  void runLeft(int speed) {
    left1.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
    left2.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
  }
  void runRight(int speed) {
    right1.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
    right2.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
  }

  int turn(double degrees, double max, double kP, double closeEnoughRange, double closeEnoughDelay) {
    reset();
    vex::timer closeEnoughTimer, timer;
    double target = 5.46666667 * degrees, kp = 0.3, error = 0, speed = 0;
    int delay = 10;
    timer.clear();
    closeEnoughTimer.clear();
    while(true) {
      //Error
      error = target - left1.rotation(vex::rotationUnits::deg);

      speed = error * kp;

      //Max speed
      if(speed > max)       speed = max;
      else if(speed < -max) speed = -max;

      //End condition
      if(abs((int)error) > closeEnoughRange)          closeEnoughTimer.clear();
      if(closeEnoughTimer.time() > closeEnoughDelay)  break;

      //Motor power
      left1.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
      left2.spin(vex::directionType::fwd, speed, vex:: velocityUnits::pct);
      right1.spin(vex::directionType::fwd, -speed, vex:: velocityUnits::pct);
      right2.spin(vex::directionType::fwd, -speed, vex:: velocityUnits::pct);

      //Delay
      vex::task::sleep(delay);
    }
    reset();
    return 1;
  }
  int forward1(double inches, double max, double kP, double closeEnoughRange, double closeEnoughDelay) {
    reset();

    vex::timer closeEnoughTimer, timer;
    double leftSpeed = 0, rightSpeed = 0, delay = 10; //was 10 delay
    double target = 41.66966 * inches, leftKp = kP, rightKp = kP, leftError = 0.0, rightError = 0.0, accel = 0.5;
    //leftEnc.setRotation(0, vex::rotationUnits::deg);
    vex::task::sleep(300);
    closeEnoughTimer.clear(); timer.clear();
    while(true) {
      //Error
      leftError = target - leftEnc.rotation(vex::rotationUnits::deg);
      rightError = target - leftEnc.rotation(vex::rotationUnits::deg);

      //Slew rate
      if(inches > 0) {
        if(leftError * leftKp > leftSpeed) leftSpeed += accel;
        else leftSpeed = leftError * leftKp;
        if(rightError * rightKp > rightSpeed) rightSpeed += accel;
        else rightSpeed = rightError * rightKp;
      }
      else {
        if(leftError * leftKp < leftSpeed) leftSpeed -= accel;
        else leftSpeed = leftError * leftKp;
        if(rightError * rightKp < rightSpeed) rightSpeed -= accel;
        else rightSpeed = rightError * rightKp;
      }

      //Max speed
      if(leftSpeed > max) leftSpeed = max;
      else if(leftSpeed < -max) leftSpeed = -max;
      if(rightSpeed > max) rightSpeed = max;
      else if(rightSpeed < -max) rightSpeed = -max;

      //End condition
      if(abs((int)leftError) > closeEnoughRange)
        closeEnoughTimer.clear();
      if(closeEnoughTimer.time() > closeEnoughDelay)
        break;

      //Motor power
      left1.spin(vex::directionType::fwd, leftSpeed, vex:: velocityUnits::pct);
      left2.spin(vex::directionType::fwd, leftSpeed, vex:: velocityUnits::pct);
      right1.spin(vex::directionType::fwd, rightSpeed, vex:: velocityUnits::pct);
      right2.spin(vex::directionType::fwd, rightSpeed, vex:: velocityUnits::pct);

      //Delay
      vex::task::sleep(delay);
    }
    reset();
    return 1;
  }

  int forward(double inches, double max, double kP, double closeEnoughRange, double closeEnoughDelay) {
    reset();

    vex::timer closeEnoughTimer, timer;
    double leftSpeed = 0, rightSpeed = 0, delay = 10; //was 10 delay
    double target = 41.66966 * inches, leftKp = kP, rightKp = kP, leftError = 0.0, rightError = 0.0, accel = 0.8;
    //leftEnc.setRotation(0, vex::rotationUnits::deg);
    vex::task::sleep(300);
    closeEnoughTimer.clear(); timer.clear();
    while(true) {
      //Error
      leftError = target - leftEnc.rotation(vex::rotationUnits::deg);
      rightError = target - leftEnc.rotation(vex::rotationUnits::deg);

      //Slew rate
      if(inches > 0) {
        if(leftError * leftKp > leftSpeed) leftSpeed += accel;
        else leftSpeed = leftError * leftKp;
        if(rightError * rightKp > rightSpeed) rightSpeed += accel;
        else rightSpeed = rightError * rightKp;
      }
      else {
        if(leftError * leftKp < leftSpeed) leftSpeed -= accel;
        else leftSpeed = leftError * leftKp;
        if(rightError * rightKp < rightSpeed) rightSpeed -= accel;
        else rightSpeed = rightError * rightKp;
      }

      //Max speed
      if(leftSpeed > max) leftSpeed = max;
      else if(leftSpeed < -max) leftSpeed = -max;
      if(rightSpeed > max) rightSpeed = max;
      else if(rightSpeed < -max) rightSpeed = -max;

      //End condition
      if(abs((int)leftError) > closeEnoughRange)
        closeEnoughTimer.clear();
      if(closeEnoughTimer.time() > closeEnoughDelay)
        break;

      //Motor power
      left1.spin(vex::directionType::fwd, leftSpeed, vex:: velocityUnits::pct);
      left2.spin(vex::directionType::fwd, leftSpeed, vex:: velocityUnits::pct);
      right1.spin(vex::directionType::fwd, rightSpeed, vex:: velocityUnits::pct);
      right2.spin(vex::directionType::fwd, rightSpeed, vex:: velocityUnits::pct);

      //Delay
      vex::task::sleep(delay);
    }
    reset();
    return 1;
  }


  int op() {
    double left1Speed = 0, left2Speed = 0, right1Speed = 0, right2Speed = 0, delay = 0, otherDelay = 0;
    double extendedArmMaxSpeed = 40, extendedArmThresh = 600, blah = 0, last1 =0, last2=0;
    double accel = 0.6;
    while(true) {
      //Axis values
      double y1 = Controller.Axis3.position();
      double y2 = Controller.Axis2.position();
      double x1 = Controller.Axis4.position();
      double x2 = Controller.Axis1.position();
      //left1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      if(abs((int)x2) > 20) {
        blah = Controller.Axis1.position();
        while(abs((int)blah) > 1) {
          otherDelay = 8;
          blah = Controller.Axis1.position();
          if(blah > right1Speed) {
            right1Speed -= accel;
            right2Speed += accel;
            left1Speed += accel;
            left2Speed -= accel;
          }
          else if(blah < right1Speed) {
            right1Speed += accel;
            right2Speed -= accel;
            left1Speed -= accel;
            left2Speed += accel;
          }
          left1.spin(vex::directionType::fwd, blah, vex::velocityUnits::pct);
          left2.spin(vex::directionType::fwd, -blah, vex::velocityUnits::pct);
          right1.spin(vex::directionType::fwd, -blah, vex::velocityUnits::pct);
          right2.spin(vex::directionType::fwd, blah, vex::velocityUnits::pct);  
          vex::task::sleep(otherDelay);
        }
        right1Speed = 0;
        right2Speed = 0;
        left1Speed = 0;
        left2Speed = 0;
      }
      else {
        printf("%d   %d\n", y2, y1);
         delay = 5;
        if(abs((int)y2 - (int)y1) > 50) {
          while(abs((int)y2 - (int)y1) > 20) {
            printf("hello\n");
            y1 = Controller.Axis3.position();
            y2 = Controller.Axis2.position();
            left1Speed = y1;
            left2Speed = y1;
            right1Speed = y2;
            right2Speed = y2;
            left1.spin(vex::directionType::fwd, left1Speed, vex::velocityUnits::pct);
            left2.spin(vex::directionType::fwd, left2Speed, vex::velocityUnits::pct);
            right1.spin(vex::directionType::fwd, right1Speed, vex::velocityUnits::pct);
            right2.spin(vex::directionType::fwd, right2Speed, vex::velocityUnits::pct);
            vex::task::sleep(0);
          }
        }
          if(y1 > left1Speed || y1 > left2Speed) {
            left1Speed += accel;
            left2Speed += accel;
          }
          else if(y1 < left1Speed || y1 < left2Speed) {
            left1Speed -= accel;
            left2Speed -= accel;
          }
          if(y2 > right1Speed || y2 > right2Speed) {
            right1Speed += accel;
            right2Speed += accel;
          }
          else if(y2 < right1Speed || y2 > right2Speed) {
            right1Speed -= accel;
            right2Speed -= accel;
          }
      }
      
      /*if(arm::left.rotation(vex::rotationUnits::deg) > extendedArmThresh) {
        if(left1Speed > extendedArmMaxSpeed)        left1Speed = extendedArmMaxSpeed;
        else if(left1Speed < -extendedArmMaxSpeed)  left1Speed = -extendedArmMaxSpeed;
        if(left2Speed > extendedArmMaxSpeed)        left2Speed = extendedArmMaxSpeed;
        else if(left2Speed < -extendedArmMaxSpeed)  left2Speed = -extendedArmMaxSpeed;
        if(right1Speed > extendedArmMaxSpeed)       right1Speed = extendedArmMaxSpeed;
        else if(right1Speed < -extendedArmMaxSpeed) right1Speed = -extendedArmMaxSpeed;
        if(right2Speed > extendedArmMaxSpeed)       right2Speed = extendedArmMaxSpeed;
        else if(right2Speed < -extendedArmMaxSpeed) right2Speed = -extendedArmMaxSpeed;
      }*/
      /*else if() {

      }*/
      

      //Deadbands
      //if(abs(y1) > 0 && x1 > -10 && x1 < -10) x1 = 0;
      //if(abs(x1) > 0 && y1 > -10 && y1 < -10) y1 = 0;

      //Acceleration control
      /*if(y1 + x2 + x1 > left1Speed)       left1Speed += accel;
      else if(y1 + x2 + x1 < left1Speed)  left1Speed -= accel;
      if(y1 + x2 - x1 > left2Speed)       left2Speed += accel;
      else if(y1 + x2 - x1 < left2Speed)  left2Speed -= accel;
      if(y1 - x2 - x1 > right1Speed)      right1Speed += accel;
      else if(y1 - x2 - x1 < right1Speed) right1Speed -= accel;
      if(y1 - x2 + x1 > right2Speed)      right2Speed += accel;
      else if(y1 - x2 + x1 < right2Speed) right2Speed -= accel;

      //Max speed with extended arm
      if(arm::left.rotation(vex::rotationUnits::deg) > extendedArmThresh) {
        delay = extendedArmDelay;
        if(left1Speed > extendedArmMaxSpeed)        left1Speed = extendedArmMaxSpeed;
        else if(left1Speed < -extendedArmMaxSpeed)  left1Speed = -extendedArmMaxSpeed;
        if(left2Speed > extendedArmMaxSpeed)        left2Speed = extendedArmMaxSpeed;
        else if(left2Speed < -extendedArmMaxSpeed)  left2Speed = -extendedArmMaxSpeed;
        if(right1Speed > extendedArmMaxSpeed)       right1Speed = extendedArmMaxSpeed;
        else if(right1Speed < -extendedArmMaxSpeed) right1Speed = -extendedArmMaxSpeed;
        if(right2Speed > extendedArmMaxSpeed)       right2Speed = extendedArmMaxSpeed;
        else if(right2Speed < -extendedArmMaxSpeed) right2Speed = -extendedArmMaxSpeed;
      }
      else delay = normalDelay;*/
        
      //Motor power
      left1.spin(vex::directionType::fwd, left1Speed, vex::velocityUnits::pct);
      left2.spin(vex::directionType::fwd, left2Speed, vex::velocityUnits::pct);
      right1.spin(vex::directionType::fwd, right1Speed, vex::velocityUnits::pct);
      right2.spin(vex::directionType::fwd, right2Speed, vex::velocityUnits::pct);

      //delay
      vex::task::sleep(delay);
    }
    return 1;
  }
}