#pragma once
#include "api.h"
#include "autons.hpp"
#include "subsystems.hpp"

bool intaking = false;

// intake helper methods
inline void intakeStart(int voltage) {
  intake.move(voltage);
}

inline void intakeStart(int voltage, int ms) {
  intake.move(voltage);
  pros::delay(ms);
  intake.brake();
}

inline void intakeStop() {
  intake.brake();
}


// piston helpers

inline void clampIn() {
  clampPiston.set(true);
}

inline void clampOut() {
  clampPiston.set(false);
}

inline void flipperIn() {
  flipperPiston.set(true);
}

inline void flipperOut() {
  flipperPiston.set(false);
}

inline void leftDoinkerIn() {
  leftDoinker.set(false);
}

inline void leftDoinkerOut() {
  leftDoinker.set(true);
}

inline void rightDoinkerIn() {
  rightDoinker.set(false);
}

inline void rightDoinkerOut() {
  rightDoinker.set(true);
}

inline void rushClawIn() {
    rightDoinker.set(true);
  }
  
inline void rushClawOut() {
    rightDoinker.set(false);
}

inline side getSideColor(){
    return fieldColor;
}

inline void setSideColor(side side){
    fieldColor = side;
}


// inline void lbMove(int target, int timeout) {
//   int target_position = target;
//   int pressTime = pros::millis();

//   while (abs(position) < target_position) {
//     pros::lcd::print(1, "Rotation: %i", position);

//     int curTime = pros::millis();
//     position = lb_rotation.get_position();
//     ladyBrown.move(40);  // 55
//     pros::delay(20);

//     if (curTime - pressTime > timeout) break;
//   }
// }

// inline void unJamFunction() {
//   pros::delay(4000);
//   while (true) {
//     int velocity = intake.get_actual_velocity();
//     if (pros::competition::is_autonomous() && isIntaking) {
//       if (velocity < 10 && velocity >= 0) {
//         groupStart(-127);
//         pros::delay(300);
//       }
//       groupStart(127);
//     }
//     pros::delay(10);
//   }
// }

// inline void colorSortingFunction() {
//   pros::delay(4000);

//   while (true) {
//     double hue = color.get_hue();
//     color.set_led_pwm(100);
//     if (pros::competition::is_autonomous()) {
//       if (red_side) {
//         if (hue > 100 && hue < 360) {
//           pros::delay(50);
//           conveyor.brake();
//           conveyor.move(-127);
//           pros::delay(200);
//         }
//       } else if (red_side == false) {
//         if (hue > 0 && hue < 20) {
//           pros::delay(80);
//           conveyor.brake();
//           conveyor.move(-127);
//           pros::delay(200);
//         }
//       }
//     }
//   }
// }