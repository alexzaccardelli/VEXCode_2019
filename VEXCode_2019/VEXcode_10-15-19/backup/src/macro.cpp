#include "main.h"

namespace macro {
  int cubeIntakeMacro(vex::task* a, vex::task* b) {
    vex::limit botLimit (Brain.ThreeWirePort.H);
    if(a != NULL and b != NULL) {
      a->suspend();
      b->suspend();
    }
    arm::move(200, 100, 0.5, 30, 150); //Was 20 error
    roller::intake();
    while(botLimit.value() == 0)
      arm::run(-100);
    vex::task::sleep(700);
    arm::stop();
    roller::reset();
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
    if(arm::currentVal() < 50)
      drive::forward(-1, 100, 0.14, 30, 150); //Was just -1
    arm::run(40);
    roller::outake();
    vex::timer timer;
    while(arm::currentVal() < 860 && timer.time() < 2700) {}
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