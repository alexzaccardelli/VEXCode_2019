#ifndef _MACRO_H_
#define _MACRO_H_FILE

namespace macro {

  /*
  Start roller intake
  Lower arm to minimum position
  wait 700 mS
  Stop rollers
  Raise to (above the height of a cube)
  */
  int down(vex::task* a=NULL, vex::task* b=NULL);
  
  int stack(vex::task* a=NULL, vex::task* b=NULL, vex::task* c=NULL);

  int armReset(vex::task* a=NULL);
}

#endif