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
    while(blah.value() == 0)
      if(t > 1000) {
        flag = true;
        break;
      }
    arm::reset();
    if(flag == false)
      vex::task::sleep(700);
    roller::reset();
    arm::move(300);

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
    while(arm::left.rotation(vex::rotationUnits::deg) < 860 && timer.time() < 2000) {}
    arm::stop();
    roller::reset();

    if(a != NULL && b != NULL && c != NULL) {
      a->resume();
      b->resume();
      c->resume();
    }
    return 1;
  }
}