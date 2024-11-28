#ifndef HELPERS
#define HELPERS

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define max(a, b) \
  ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
  ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

  void delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* HELPERS */