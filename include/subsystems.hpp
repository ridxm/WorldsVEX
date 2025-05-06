#pragma once

#include "EZ-Template/api.hpp"
#include "EZ-Template/piston.hpp"
#include "api.h"

extern Drive chassis;

inline pros::MotorGroup intake({2, -9});
inline pros::MotorGroup ladyBrown({1, -10});

inline pros::Optical color(3);


inline ez::Piston clampPiston ('A');
inline ez::Piston leftDoinker('D');
inline ez::Piston leftDoinkerClaw('C');
inline ez::Piston rightDoinker('B');
inline ez::Piston rightDoinkerClaw('E');
inline ez::Piston flipperPiston('F');
inline ez::Piston lbExpand('G');



