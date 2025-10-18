#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/display/lv_display.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/misc/lv_types.h"
#include "liblvgl/widgets/image/lv_image.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "autons.h"    // IWYU pragma: keep
#include "globals.hpp"
#include "pros/screen.h"


using namespace std;
// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({1, -2, -3}, pros::MotorGearset::blue); // left motor group - ports 1, 2 (reversed), 3
pros::MotorGroup rightMotors({-4, 5, 6}, pros::MotorGearset::blue); // right motor group - ports 4 (reversed), 5, 6 (reversed)


// motors
pros::Motor intake(8);
pros::Motor fly(-7);

// pneumatics
pros::adi::Pneumatics lowFunnel('A', false);
pros::adi::Pneumatics drop('B', true, true);
<<<<<<< HEAD
pros::adi::Pneumatics odomLift('C', true, true);
pros::adi::Pneumatics descorer('G', false); 
pros::adi::Pneumatics matchloader('H', false);
=======
pros::adi::Pneumatics lowFunnel('A', true, true);
pros::adi::Pneumatics matchloader('H', false);
pros::adi::Pneumatics descorer('G', false);
pros::adi::Pneumatics odomLift('C', false);
>>>>>>> ac8f3ef216e0347375ed8690e360614cd6706f53


// Inertial Sensor on port 10
pros::Imu imu(12);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 8, not reversed
pros::Rotation horizontalEnc(10);
// vertical tracking wheel encoder. Rotation sensor, port 7, not reversed
pros::Rotation verticalEnc(-11);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, 2, -5.1);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, 2, 0.25);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.75, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(5.15, // proportional gain (kP)
                                            0.3, // integral gain (kI)
                                            15.5, // derivative gain (kD)
                                            2, // anti windup
                                            0.5, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            2, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            15 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(1.67, // proportional gain (kP)
                                             0.18, // integral gain (kI)
                                             11.5, // derivative gain (kD)
                                             5, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(13, // joystick deadband out of 127
                                     13, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(13, // joystick deadband out of 127
                                  13, // minimum output where drivetrain will move out of 127
                                  1 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);


// auton num
int autonIndex;


//using modulo (math)
void leftScreenButton() {
    autonIndex = (autonIndex - 1 + autons.size()) % (autons.size());
}

void rightScreenButton() {
    autonIndex = (autonIndex + 1) % (autons.size());
}

lv_obj_t *img = nullptr;

// Aura.
bool touchEnabled = false;
inline void black_background() { lv_obj_set_style_bg_color( lv_screen_active(), lv_color_hex(0x000000), 0); }
void displayImage() {
    pros::lcd::shutdown();
    black_background();
    // var for c array
    LV_IMAGE_DECLARE(speedzappers_logo_rotated);
    //declare and define the image object
    img = lv_image_create(lv_screen_active());

    // set the source data for the image
    lv_image_set_src(img, &speedzappers_logo_rotated);

    // alignment
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    touchEnabled = true;
    
}
void invisibleImage() {
    lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
}


void lcdSetup() {
    pros::lcd::initialize(); // initialize brain screen
    pros::lcd::register_btn0_cb(leftScreenButton);
    pros::lcd::register_btn1_cb(displayImage);
    pros::lcd::register_btn2_cb(rightScreenButton);
    pros::lcd::print(2, "test");
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 
void initialize() {
    autonIndex = 4;

    pros::lcd::initialize(); // initialize brain screen
    pros::lcd::register_btn0_cb(leftScreenButton);
    pros::lcd::register_btn1_cb(displayImage);
    pros::lcd::register_btn2_cb(rightScreenButton);
    
    chassis.calibrate(); // calibrate sensors


    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging


    //pros::Task pidTuner()

    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %.4f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %.4f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %.3f", chassis.getPose().theta); // heading
            // printf("\n Theta: %f", chassis.getPose().theta);
            // printf("\n X: %f, Y: %f", chassis.getPose().x, chassis.getPose().y);
            pros::lcd::print(3, "auton index: %d", autonIndex);
            pros::lcd::print(4, "%s", std::get<0>(autons[autonIndex]));

            pros::lcd::print(5, "Left: %f    Right: %f", leftMotors.get_temperature(), rightMotors.get_temperature());
            pros::lcd::print(6, "Intake: %f", intake.get_temperature());
            pros::lcd::print(7, "Fly: %f", fly.get_temperature());

            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
    
}
void touchHandler() {
    if (!touchEnabled) return;
    touchEnabled = false;

    pros::lcd::initialize(); // initialize brain screen
    pros::lcd::register_btn0_cb(leftScreenButton);
    pros::lcd::register_btn1_cb(displayImage);
    pros::lcd::register_btn2_cb(rightScreenButton);
    invisibleImage();

}


/**
 * Runs while the robot is disabled
 */
void disabled() {

    
}

/**
 * runs after initialize if the robot is connected to field control
 */



void competition_initialize() {
}

// get a path used for pure pursuit
// this needs to be put outside a function
//ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    //autonIndex = 0; // Change this to whichever auton you want to run
    std::get<1>(autons[autonIndex])();
    
}

/**
 * Runs in driver control
 */
void opcontrol() {
    
<<<<<<< HEAD
    displayImage();
    pros::screen::touch_callback(touchHandler, TOUCH_PRESSED);
=======
    // displayImage();
>>>>>>> ac8f3ef216e0347375ed8690e360614cd6706f53
    // controller
    // loop to continuously update motors

    while (true) {
        // get joystick positions
        int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
        //rajeev drive
        chassis.arcade(rightY, leftX);

        //shuhul drive
        //chassis.arcade(leftY, rightX);



        // intake
        if (controller.get_digital(DIGITAL_R1)) {
            intake.move(128);
        }

        // outtake
        else if (controller.get_digital(DIGITAL_L1)) {
            if(lowFunnel.is_extended()) {
                intake.move(-128);
            }
            else {
                intake.move(-100);
            }
        }
        
        // stop take
        else {
            intake.move(0);
        }


        //
        if (controller.get_digital(DIGITAL_R2)) {
            fly.move(128);
        }
        else if (controller.get_digital(DIGITAL_L2)) {
            fly.move(-128);
        }
        else if (controller.get_digital(DIGITAL_R1)) {
            fly.move(-32);
        }
        else {
            fly.move(0);
        }



        // drop DOWN
        if (controller.get_digital_new_press(DIGITAL_DOWN)) {
            drop.toggle();
        }

        // matchloader B
        if (controller.get_digital_new_press(DIGITAL_B)) {
            matchloader.toggle();
        }

        // descorer A
        if (controller.get_digital_new_press(DIGITAL_A)) {
            descorer.toggle();
        }

        // odomlift UP
        if (controller.get_digital_new_press(DIGITAL_UP)) {
            odomLift.toggle();
        }

        // bottom funnel RIGHT
        if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
            lowFunnel.toggle();
        }

        pros::delay(10);
    }
}