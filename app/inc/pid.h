#ifndef PID
#define PID

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        float P;
        float I;
        float D;
        float error;
        float errorPrev;
        float errorSum;
        float output;
    } PID_t;

    void PID_init(PID_t *pid);
    void PID_update(PID_t *pid, float error);

#ifdef __cplusplus
}
#endif

#endif /* PID */