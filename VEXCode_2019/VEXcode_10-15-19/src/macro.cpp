#include "main.h"

namespace macro {
  int down(vex::task* a, vex::task* b) {
    bool flag = false;
    if(a != NULL and b != NULL) {
      a->suspend();
      b->suspend();
    }

    roller::intake();
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    vex::timer t;
    while(blah.value() == 0) {
    }
    arm::reset();
    if(flag == false)
      vex::task::sleep(700);
    roller::reset();
    arm::move(250);
    arm::degreesLeft = arm::left.rotation(vex::rotationUnits::deg);
    arm::degreesRight = arm::right.rotation(vex::rotationUnits::deg);
    if(a != NULL and b != NULL) {
      a->resume();
      b->resume();
    }
    return 1;
  }

  int stack(vex::task* a, vex::task* b, vex::task* c) {
    if(a != NULL && b != NULL && c != NULL) {
      a->suspend();
      b->suspend();
      c->suspend();
    }

    roller::outake();
    vex::task::sleep(800);
    roller::reset();
    arm::run(55);
    roller::outake(-60);
    vex::timer timer;
    while(arm::left.rotation(vex::rotationUnits::deg) < 900 && timer.time() < 1950) {}
    arm::stop();
    roller::reset();
    arm::degreesLeft = arm::left.rotation(vex::rotationUnits::deg);
    arm::degreesRight = arm::right.rotation(vex::rotationUnits::deg);
    if(a != NULL && b != NULL && c != NULL) {
      a->resume();
      b->resume();
      c->resume();
    }
    return 1;
  }

  int armReset(vex::task* a) {
    if(a != NULL)
      a->suspend();
    vex::limit blah(Brain.ThreeWirePort.H);
    arm::run(-100);
    while(blah.value() == 0) {}
    arm::reset();
    arm::degreesLeft = arm::left.rotation(vex::rotationUnits::deg);
    arm::degreesRight = arm::right.rotation(vex::rotationUnits::deg);
    if(a != NULL)
      a->resume();
    return 1;
  }
}