#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/logger/logger.hpp"
#include "lemlib/logger/telemetrySink.hpp" // IWYU pragma: keep
#include "RclTracking.hpp"

#include "liblvgl/llemu.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/optical.hpp" // IWYU pragma: keep
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include "autons.h"    // IWYU pragma: keep
#include "globals.hpp"
#include "pros/screen.h" // IWYU pragma: keep
#include <algorithm> // IWYU pragma: keep
#include <cstdio>

extern int auton;
extern bool ovrde;

// odom lift flag
//bool odomLiftRaise = false;

// screen task flag
bool screenTaskRunning = true;


//FILE* file = fopen("/usd/auto.txt", "w");


// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-13, 14, -15}, pros::MotorGearset::blue); // left motor group - ports 1, 2 (reversed), 3
pros::MotorGroup rightMotors({10, 6, -8}, pros::MotorGearset::blue); // right motor group - ports 4 (reversed), 5, 6 (reversed)

bool leverDown = true;
float leverTarget = 0;
int leverTime = 0;
float leverSpeed = 128;
// bool leverReset = true;
bool competitionInitialize = false;
bool opControl = false;

// motors
pros::Motor intakeRight(19);
pros::Motor intakeLeft(-21);
pros::MotorGroup intake({19, -21});
pros::Motor shotgun(3, pros::MotorGearset::red);
pros::Rotation shotgunRS(-1);

// optical disconnect on port 12
// pros::Optical opticalSensor(12);



// game color (0 for red, 1 for blue, -1 for none)
int gameColor = -1;

// pneumatics
pros::adi::Pneumatics drop('G', false, false);
pros::adi::Pneumatics odomLift('D', true, true);
pros::adi::Pneumatics descorer('E', false); 
pros::adi::Pneumatics matchloader('H', false);
pros::adi::Pneumatics passTheJuice('B', false, false);


// Inertial Sensor on port 10
pros::Imu imu(20);


// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 8, not reversed
pros::Rotation horizontalEnc(12);
// vertical tracking wheel encoder. Rotation sensor, port 7, not reversed
pros::Rotation verticalEnc(-2);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, 2, -3.7);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, 2, -0.4);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(5.5, // proportional gain (kP)
                                            0.24, // integral gain (kI)
                                            12, // derivative gain (kD)
                                            2, // anti windup
                                            0.5, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            2, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            15 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(angular_kp, // proportional gain (kP)
                                             angular_ki, // integral gain (kI)
                                             angular_kd, // derivative gain (kD)
                                             5, // anti windup
                                             1, // small error range, in degrees
                                             75, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             250, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularControllerU30(4.3, // proportional gain (kP)
                                             0.28, // integral gain (kI)
                                             20, // derivative gain (kD)
                                             4, // anti windup
                                             1, // small error range, in degrees
                                             75, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             250, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
/*lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);*/

//sensors for rcl
lemlib::OdomSensors sensors(nullptr,
                            nullptr,
                            nullptr,
                            nullptr,
                            &imu
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
lemlib::Chassis chassis(drivetrain, linearController, angularController, angularControllerU30, sensors, &throttleCurve, &steerCurve);


// distance sensors
pros::Distance leftDist(18);
pros::Distance rightDist(5);
pros::Distance backDist(17);

//rcl setup
inline RclSensor rightRcl(&rightDist, 3.1, 5.1, 90);
inline RclSensor leftRcl(&leftDist, -3.1, 5.1, 270);
inline RclSensor backRcl(&backDist, -3.25, -7, 180);
inline RclTracking RclMain(&chassis);

// loaders
inline Circle_Obstacle redUpLoader(-67.5, 46.5, 3);
inline Circle_Obstacle redDownLoader(-67.5, -46.5, 3);
inline Circle_Obstacle blueUpLoader(67.5, 46.5, 3);
inline Circle_Obstacle blueDownLoader(67.5, -46.5, 3);

// legs
inline Circle_Obstacle upLongGoalLeft(-21, 47.5, 4);
inline Circle_Obstacle upLongGoalRight(21, 47.5, 4);
inline Circle_Obstacle downLongGoalLeft(-21, -47.5, 4);
inline Circle_Obstacle downLongGoalRight(21, -47.5, 4);
inline Circle_Obstacle centerGoals(0, 0, 5);

// Disable Line for the autonomous period
inline Line_Obstacle disableLine(0, FIELD_NEG_HALF_LENGTH, 0, FIELD_HALF_LENGTH);


void updateAutoFile() {
    FILE* file = fopen("/usd/auto.txt", "r+");
    if (file != NULL) {
        fseek(file, 0, SEEK_SET); 
        fprintf(file, "%d", auton);
        fclose(file); 
    } else {
        // If file doesn't exist, create one
        file = fopen("/usd/auto.txt", "w");
        if (file != NULL) {
            fprintf(file, "%d", auton);
            fclose(file);
        }
    }
}

//using modulo (math)
void leftScreenButton() {
    auton = (auton - 1 + autons.size()) % (autons.size());
    updateAutoFile();
}

void rightScreenButton() {
    auton = (auton + 1) % (autons.size());
    updateAutoFile();
}


void displayImage();
void initialize() {
    shotgunRS.set_position(0);
    
    RclMain.startTracking();
    

    /*if(ovrde) {
        //sdcard index = get<0>(auton)
        FILE* file = fopen("/usd/auto.txt", "w");
        fputs(""+auton, file);
        fclose(file);
    }*/

    //get<0>(auton) = sdcard index
    FILE* file = fopen("/usd/auto.txt", "r");
    if (file != NULL) {
        char buf[3];        //two for digit, one for null terminator
        fread(buf, 1, 2, file);
        buf[2] = '\0';      // tells stoi where string ends
        
        auton = std::stoi(buf); 
        printf("Loaded Auton: %s\n", buf);
        fclose(file);
    } else {
        auton = 0; // default if no file is found
        printf("SD Card not found, defaulting to auton 0\n");
    }


    displayImage();
    
    
    chassis.calibrate(); // calibrate sensors


    chassis.setPose(-48, -48, 0); // or whatever your actual starting coords are
    RclMain.setRclPose(chassis.getPose());
    RclMain.updateBotPose(&backRcl);
    RclMain.updateBotPose(&leftRcl);


    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging


    //pros::Task pidTuner()

    pros::Task screenTask([&]() {
        while (screenTaskRunning) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %.4f", RclMain.getRclPose().x); // x
            pros::lcd::print(1, "Y: %.4f", RclMain.getRclPose().y); // y
            pros::lcd::print(2, "Theta: %.3f", chassis.getPose().theta); // heading
            
            pros::lcd::print(3, "auton index: %d", auton);
            pros::lcd::print(4, "%s", std::get<0>(autons[auton]));

            // auto leftResult = leftRcl.getBotCoord(chassis.getPose());
            // auto rightResult = backRcl.getBotCoord(chassis.getPose());
            //auto rightResult = rightRcl.getBotCoord(chassis.getPose());

            //pros::lcd::print(4, "R: type=%d val=%.2f", (int)rightResult.first, rightResult.second);

            
            pros::lcd::print(5, "Left: %f    Right: %f", leftMotors.get_temperature(), rightMotors.get_temperature());
            pros::lcd::print(6, "Intake: %f", intake.get_temperature());
            pros::lcd::print(7, "Shotgun: %f", shotgun.get_temperature());

            // pros::lcd::print(5, "L dist: %d  conf: %d", leftDist.get(), leftDist.get_confidence());
            // pros::lcd::print(6, "R dist: %d  conf: %d", rightDist.get(), rightDist.get_confidence());
            // pros::lcd::print(7, "B dist: %d  conf: %d", backDist.get(), backDist.get_confidence());
            // pros::lcd::print(3, "L: type=%d val=%.2f", (int)leftResult.first, leftResult.second);
            // pros::lcd::print(4, "B: type=%d val=%.2f", (int)rightResult.first, rightResult.second);
            // pros::lcd::print(5, "RCL: %.2f %.2f", RclMain.getRclPose().x, RclMain.getRclPose().y);
            // pros::lcd::print(6, "LEM: %.2f %.2f", chassis.getPose().x, chassis.getPose().y);
            // pros::lcd::print(7, "Ldiff: %.2f", std::abs(leftResult.second - RclMain.getRclPose().x));

            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // telemetry.log(Level level, fmt::format_string<T...> format, T &&args...)
            // delay to save resources
            pros::delay(50);
        }
    });
    
    
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
    competitionInitialize = true;
}

// get a path used for pure pursuit
// this needs to be put outside a function
//ASSET(example_txt); // '.' replaced with "_" to make c++ happy


void autonomous() {
    // screenTaskRunning = false; // stop the screen task during auton

    
    //autonIndex = 0; // Change this to whichever auton you want to run
    std::get<1>(autons[auton])();
    
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
    // loop to continuously update motors
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    printf("\nDriver Control Started\n");
    opControl = true;
    float error = lemlib::angleError(108, shotgunRS.get_position()/100.0, false);
    if(auton == 10 || auton == 11) {
        passTheJuice.extend();
    }

    while (true) {
        // get joystick positions
        int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
        //rajeev drive
        chassis.arcade(rightY, 0.95 * leftX);

        //shuhul drive
        //chassis.arcade(leftY, rightX);

        if (shotgunRS.get_position()/100 < 1 || shotgunRS.get_position()/100 > 355) {
            leverDown = true;
            shotgun.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        } else {
            leverDown = false;
            shotgun.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        }
        // printf("\n%d\n", shotgunRS.get_position());

        // intake
        if (controller.get_digital(DIGITAL_R1) && (shotgunRS.get_position()/100 > 355 || shotgunRS.get_position()/100 < 5)) {
            intake.move(128);
            odomLift.retract();
        }

        // outtake
        else if (controller.get_digital(DIGITAL_L1) || (shotgunRS.get_position()/100 > 30 && shotgunRS.get_position()/100 < 270)) {
            if (auton == 10 || auton == 11)
                intake.move(-30);
            else
                intake.move(-80);
        }
        
        // stop take
        else {
            intake.move(0);
        }

        if (controller.get_digital_new_press(DIGITAL_L2)) {
            drop.toggle();
        }

        //
        if (controller.get_digital(DIGITAL_R2)) {
            leverTarget = -1;
            if(!drop.is_extended()) {
                if ((auton == 10 || auton == 11)) {
                    passTheJuice.retract();
                    if(controller.get_digital(DIGITAL_Y))
                        shotgun.move_velocity(32);
                    else 
                        shotgun.move_velocity(17);
                }
                else if (!(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))) {
                    shotgun.move_velocity(30);
                }
                else {
                    shotgun.move_velocity(70);
                }

            
            }
            //else if (controller.get_digital(DIGITAL_Y) && !(auton == 10 || auton == 11)) {
            //    shotgun.move_velocity(100);
            //}
            else {
                if ((auton == 10 || auton == 11)){
                    error = lemlib::angleError(108, shotgunRS.get_position()/100.0, false);
                    shotgun.move(128 - (80/(1 + pow(2, 0.2*(error - 70) ) ) ) );
                    passTheJuice.retract();
                }
                else shotgun.move_velocity(70);
            }

        } else if(!leverDown) {
            leverTarget = 0;
            leverSpeed = 70;
            if(auton == 10 || auton == 11) {
                passTheJuice.extend();
            }
        }

        // matchloader B
        if (controller.get_digital_new_press(DIGITAL_B)) {
            matchloader.toggle();
        }

        // descorer RIGHT
     
        if (leverTarget != -1) {
            float error = leverTarget - shotgunRS.get_position()/100.0f;
            if ((fabs(error) < 3) || (leverTime > 1000)) {
                shotgun.brake();
                leverTarget = -1;
                leverTime = 0;
            } else {
                if (leverTarget == 0) {
                    shotgun.move(-leverSpeed);
                }
                leverTime+=10;
            }
        }

        if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
            /*if(!competitionInitialize) {
                rightScreenButton();
            }
            else */
            descorer.toggle();
            
        }

        if (controller.get_digital_new_press(DIGITAL_DOWN)) {
            passTheJuice.toggle();
        }

        if(controller.get_digital_new_press(DIGITAL_UP)) {
            odomLift.toggle();
            if(odomLift.is_extended()) {
                controller.rumble(".");
            }
        }

        if (controller.get_digital_new_press(DIGITAL_X)) {
            pidTest();
        }
        
        
        /*if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) && !competitionInitialize) {
            leftScreenButton();
        }*/

        pros::delay(10);
    }
}