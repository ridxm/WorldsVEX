#include "autons.hpp"
#include "constants.hpp"
#include "main.h"

void red_red() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();


}