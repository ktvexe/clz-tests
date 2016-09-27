#ifndef CLZ_H
#define	CLZ_H
#define clz(x) clz2(x,0)
#include <stdint.h>

unsigned clz2(uint32_t x,int c);

#endif
