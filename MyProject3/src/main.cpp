/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// pn                   digital_out   H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
 motor lf = motor(PORT13, ratio6_1, true);
motor lb = motor(PORT10, ratio6_1, true);
motor lt = motor(PORT8, ratio6_1, false);
motor_group leftmtrs(lf,lb);
motor rb = motor(PORT18, ratio6_1, false);
motor rf = motor(PORT17, ratio6_1, false);
motor rt = motor(PORT16, ratio6_1, true);
motor_group rightmtrs(rf,rb);
drivetrain Drivetrain = drivetrain(leftmtrs, rightmtrs, 299.24, 295, 40, mm, 0.6);
motor_group r = motor_group(lt, lb,lf);
motor_group l = motor_group(rt, rb,rf);
motor hook = motor(PORT9, ratio6_1);
motor intake = motor(PORT19, ratio18_1);
controller Controller1 = controller();

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void BX(){
  pn.set(false);
}
void BB(){
  pn.set(true);
}
void R1(){
  hook.spin(forward);
}
void R2(){
  hook.spin(reverse);
}
void L1(){
  intake.spin(forward);
}
void L2(){
  intake.spin(reverse);
}
void stopintake(){
  intake.stop();
}
void stophook(){
  hook.stop();
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Drivetrain.setDriveVelocity(80,percent);
  Drivetrain.setTurnVelocity(100,percent);
  hook.setVelocity(70, percent);
  hook.setMaxTorque(100,percent);
  intake.setVelocity(100, percent);
  pn.set(false);
  Controller1.ButtonX.pressed(BX);
  Controller1.ButtonB.pressed(BB);
    Controller1.ButtonR1.pressed(R1);
  Controller1.ButtonR2.pressed(R2);
    Controller1.ButtonL1.pressed(L1);
  Controller1.ButtonL2.pressed(L2);
 Controller1.ButtonL1.released(stophook);
 Controller1.ButtonL2.released(stophook);
 Controller1.ButtonR1.released(stopintake);
 Controller1.ButtonR2.released(stopintake);
 while(1){
l.spin(forward,(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent))*12/100, volt);
r.spin(forward,(Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent))*12/100, volt);

wait(20, msec);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  Drivetrain.setDriveVelocity(20, percent);
  Drivetrain.setTurnVelocity(50,percent);
  hook.setVelocity(55,percent);
  pn.set(true);

  intake.spin(reverse);
  //Going for MoGO
  Drivetrain.drive(reverse);
  wait(1.1,seconds);
  pn.set(false);
  //Clamps
  wait(0.30,seconds);
  Drivetrain.stop();
  //Stops with the MoGo
  //Turns
  Drivetrain.turn(right);
  wait(0.65,seconds);
  Drivetrain.stop();
  //Goes for 1st donut
  hook.spin(forward);
  intake.spin(reverse);
  Drivetrain.drive(forward);
  wait(1.5,seconds);
  Drivetrain.stop();
  //Goes to ladder
  Drivetrain.turn(right);
  wait(1.6,seconds);
  Drivetrain.stop();
  
  Drivetrain.driveFor(forward,55,inches);
  hook.stop();
  intake.stop();
  //Done

  //////////////////////////////////////////////*/
  
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
