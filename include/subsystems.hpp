#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/adi.h"

extern Drive chassis;

inline pros::MotorGroup intake({2, -9});
inline pros::MotorGroup ladyBrown({1, -10});

inline pros::Rotation lb_rotation(-7);
inline pros::Optical color(6);

inline ez::Piston clampPiston('C', false);
// inline ez::Piston flipperPiston('E', false);
inline ez::Piston rightDoinker('D', false);
inline ez::Piston leftDoinker('A', false);
inline ez::Piston doinkerClaw('B', false);

// inline pros::Motor Doinker('A');
inline pros::Motor flipperPiston('E');

inline pros::adi::DigitalIn sensor ('H');
