#include "autons.hpp"
#include "constants.hpp"
#include "main.h"

void red_blue() {
  chassis.pid_drive_set(24_in, 100, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, 100, true);
  chassis.pid_wait();
}