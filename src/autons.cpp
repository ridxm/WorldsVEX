#include "main.h"
#include "subsystems.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 100;
const int TURN_SPEED = 55;
const int SWING_SPEED = 110;

static int target = 0;


///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(15.0, 0.0, 150.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 40.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
  chassis.drive_imu_scaler_set(1.001);
}

void liftControlAuto() {
  double kp = 0.2;
  double error = target - lb_rotation.get_position();
  double velocity = kp * error;
  pros::lcd::set_text(1, std::to_string(velocity));
  pros::lcd::set_text(2, std::to_string(lb_rotation.get_position()));
  pros::lcd::set_text(3, std::to_string(target));
  ladyBrown.move(velocity);
}



void safe_autos_blue() {

  chassis.drive_angle_set(27_deg);

//   pros::delay(1000);
  
// chassis.pid_turn_set(-90_deg, TURN_SPEED);
// chassis.pid_wait();

// pros::delay(5000);

  ez::Piston leftDoinker('A', false);
ez::Piston doinkerClaw('B', false);

  // leftDoinker.set(true);
  // pros::delay(1000);
  // leftDoinker.set(false);
  // pros::delay(1000);
  chassis.pid_drive_set(21_in, 127);
  chassis.pid_wait_until(4_in);
  leftDoinker.set(true);
  doinkerClaw.set(true);
  pros::delay(350);
  doinkerClaw.set(false);
  pros::delay(50);
  leftDoinker.set(false);
  chassis.pid_wait();
  

  chassis.pid_drive_set(-15_in, 127, true);
  chassis.pid_wait();

  leftDoinker.set(true);
  pros::delay(100);
  doinkerClaw.set(true);


  chassis.pid_drive_set(-8_in, 80, true);
  chassis.pid_wait();

  leftDoinker.set(false);

  chassis.pid_turn_set(185_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, 40, true);
  chassis.pid_wait();

  clampPiston.set(true);




}

void safe_autos_red() {
  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  chassis.drive_angle_set(145_deg);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-30_in, 50, true);
  chassis.pid_wait();

  clampPiston.set(true);
  pros::delay(500);

  chassis.pid_turn_set(-85_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait();

  intake.move(127);
  pros::delay(1000);

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(1500);

  intake.brake();
  pros::delay(100);
  intake.move(-127);

  chassis.pid_drive_set(32_in, 55, true);
  chassis.pid_wait();

  pros::delay(500);

  intake.move(127);

  pros::delay(1500);

  chassis.pid_drive_set(-8_in, 30);
  chassis.pid_wait();

  pros::delay(3000);

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(110_in, 60, true);
  chassis.pid_wait();

  pros::delay(1500);

  intake.brake();
  pros::delay(100);

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  clampPiston.set(false);
  pros::delay(500);

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}