#ifndef SERVO
#define SERVO

#ifdef __cplusplus
extern "C"
{
#endif

#define SERVO_ANGLE_MAX 90.0
#define SERVO_ANGLE_MIN -90.0

    void enableServos();
    void disableServos();
    void setPitch(float angle);
    void setRoll(float angle);

#ifdef __cplusplus
}
#endif

#endif /* SERVO */