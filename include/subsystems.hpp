#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;


inline pros::MotorGroup rollers({2, -9});
inline pros::MotorGroup ladyBrown({1, -10});

inline pros::Rotation lb_rotation(8);
inline pros::Optical color(7);


inline ez::Piston clampPiston('A', false);
inline ez::Piston flipperPiston('G', false);
inline ez::Piston rightDoinker('H', false);
inline ez::Piston leftDoinker('D', false);