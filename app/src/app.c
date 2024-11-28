#include "main.h"
#include "app.h"
#include "mpu6050.h"
#include "stdio.h"
#include "string.h"
#include "servo.h"
#include "helpers.h"
#include "pid.h"

#define ERROR_SUM_MAX 100.0
#define ERROR_SUM_MIN -100.0

MPU6050_data_t mpuData;
volatile bool mpuDataUpdated = false;
float pitchAngle = 0, rollAngle = 0;

// float P = 0.05, I = 0.002, D = 0.3;
PID_t pitch;
PID_t roll;

void updatePitch()
{
    pitchAngle += pitch.output;
    pitchAngle = min(pitchAngle, SERVO_ANGLE_MAX);
    pitchAngle = max(pitchAngle, SERVO_ANGLE_MIN);

    setPitch(pitchAngle);
}

void updateRoll()
{
    rollAngle += roll.output;
    rollAngle = min(rollAngle, SERVO_ANGLE_MAX);
    rollAngle = max(rollAngle, SERVO_ANGLE_MIN);

    setRoll(rollAngle);
}

void APP_main()
{
    // init vars
    PID_init(&pitch);
    PID_init(&roll);

    // set pid
    pitch.P = 0.15;
    pitch.I = 0.00;
    pitch.D = 0.00;
    roll.P = 0.15;
    roll.I = 0.00;
    roll.D = 0.00;

    // enable servo
    serialPrint("enabling servo\n\r");
    enableServos();
    setPitch(pitchAngle);
    setRoll(rollAngle);

    // delay 5 seconds to start calibration
    delay(1000);

    // init accelerometer/gyro
    if (MPU6050_init(&mpuData) == MPU6050_ok)
        serialPrint("MPU initialized successfully.\n\r");
    else
    {
        serialPrint("MPU failed to initialize.\n\r");
    }

    // wait until mpu is calibrated
    serialPrint("Waiting for MPU calibration... ");
    while (!mpuData.calibration.calibrated)
        ;
    serialPrint("complete.\n\r");

    while (1)
    {
        if (mpuDataUpdated)
        {
            char buffer[64];
            memset(buffer, '\0', sizeof(buffer));

            // tuning prints
            // snprintf(buffer, sizeof(buffer), "pitch: %7.02f\tpitch.output: %7.02f\terrSum: %7.02f\n\r", mpuData.pitch, pitch.output, pitch.errorSum);
            snprintf(buffer, sizeof(buffer), "roll: %7.02f\troll.output: %7.02f\terrSum: %7.02f\n\r", mpuData.roll, roll.output, roll.errorSum);

            // data logging prints
            // snprintf(buffer, sizeof(buffer), "%06ld,%7.02f\n\r", millis(), mpuData.pitch);

            serialPrint(buffer);

            updatePitch();
            updateRoll();
        }
    }
}

void APP_mpuIntReqHandler()
{
    MPU6050_status_t status = MPU6050_getData(&mpuData);
    mpuDataUpdated = status == MPU6050_ok;
    setLed(mpuDataUpdated);

    if (mpuDataUpdated)
    {
        PID_update(&pitch, -mpuData.pitch);
        PID_update(&roll, -mpuData.roll);
    }
}