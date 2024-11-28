#include "pid.h"
#include "helpers.h"

void PID_init(PID_t *pid)
{
    pid->P = 0;
    pid->I = 0;
    pid->D = 0;
    pid->error = 0;
    pid->errorPrev = 0;
    pid->errorSum = 0;
    pid->output = 0;
}

void PID_update(PID_t *pid, float error)
{
    pid->errorPrev = pid->error;
    pid->error = error;
    pid->errorSum += error;

    // limit errorSum
    pid->errorSum = min(pid->errorSum, 100.0);
    pid->errorSum = max(pid->errorSum, -100.0);

    pid->output = (pid->P * pid->error) + (pid->I * pid->errorSum) + (pid->D * (pid->error - pid->errorPrev));
}