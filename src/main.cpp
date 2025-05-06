#include "main.h"

#include "autons.hpp"
#include "constants.hpp"
#include "pros/motors.h"
#include "subsystems.hpp"

// // Chassis constructor
// ez::Drive chassis(
//     // These are your drive motors, the first motor is used for sensing!
//     {11, -12, -13, 14, -15},  // Left Chassis Ports (negative port will reverse it!)
//     {16, -17, 18, -19, 20},   // Right Chassis Ports (negative port will reverse it!)

//     10,    // IMU Port
//     2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
//     600);  // Wheel RPM = cartridge * (motor gear / wheel gear)

void initialize() {
  if (currentBot == BIG) {
    ez::Drive chassis(
        // These are your drive motors, the first motor is used for sensing!
        {11, -12, -13, 14, -15},  // Left Chassis Ports (negative port will reverse it!)
        {16, -17, 18, -19, 20},   // Right Chassis Ports (negative port will reverse it!)

        10,    // IMU Port
        2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
        600);  // Wheel RPM = cartridge * (motor gear / wheel gear)
  } else {
    ez::Drive chassis(
        // These are your drive motors, the first motor is used for sensing!
        {-11, 12, -13, 14, -15},  // Left Chassis Ports (negative port will reverse it!)
        {16, -17, 18, -19, 20},   // Right Chassis Ports (negative port will reverse it!)

        21,    // IMU Port
        2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
        600);  // Wheel RPM = cartridge * (motor gear / wheel gear)
  }
  // determines which bot the code is on
  pros::DeviceType dt = pros::Device::get_plugged_type(3);
  int dt_val = static_cast<int>(dt);

  if (dt_val == 2) {
    currentBot = SMALL;
  } else {
    currentBot = BIG;
  }
  // Line 5, formatted print of the enum’s underlying integer
  // pros::lcd::print(5, "Device type: %d", dt_val);

  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  chassis.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // // Set the drive to your own constants from autons.cpp!
  default_constants();

  // // Autonomous Selector using LLEMU
  if (currentBot) {
    ez::as::auton_selector.autons_add({
        {"black blue drive", black_blue},
        {"black red drive", black_red},
        {"red blue drive", red_blue},
        {"red red drive", red_red},
    });
  } else {
    ez::as::auton_selector.autons_add({
        {"black blue drive", black_blue},
        {"black red drive", black_red},
        {"red blue drive", red_blue},
        {"red red drive", red_red},
    });
  }

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  // default_constants();
  // drive_and_turn();

  // chassis.pid_targets_reset();                // Resets PID targets to 0
  // chassis.drive_imu_reset();                  // Reset gyro position to 0
  // chassis.drive_sensor_reset();               // Reset drive sensors to 0
  // chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  // chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  // ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector

  default_constants();

  if (currentBot == BIG) {
    if (fieldColor == RED) {
      black_red();
    } else {
      black_blue();
    }
  } else {
    if (fieldColor == RED) {
      red_red();
    } else {
      red_blue();
    }
  }
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_BRAKE);

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    // ez_template_extras();

    // chassis.opcontrol_tank();  // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT);  // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    if (master.get_digital(DIGITAL_R1)) {
      intake.move(127);
    } else if (master.get_digital(DIGITAL_R2)) {
      intake.move(-127);
    } else {
      intake.brake();
    }

    if (master.get_digital(DIGITAL_L1)) {
      ladyBrown.move(127);
    } else if (master.get_digital(DIGITAL_L2)) {
      ladyBrown.move(-127);
    } else {
      ladyBrown.brake();
    }

    clampPiston.button_toggle(master.get_digital(DIGITAL_B));
    rightDoinker.set(master.get_digital(DIGITAL_Y) && !flipperPiston.get());

    leftDoinker.set(master.get_digital(DIGITAL_RIGHT) && !flipperPiston.get());

    flipperPiston.set(master.get_digital(DIGITAL_DOWN) && !rightDoinker.get() && !leftDoinker.get());

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
