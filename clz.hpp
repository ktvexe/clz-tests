#ifndef CLZ_H
#define	CLZ_H
#define clz(x) clz2(x,0)
//#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
//#define clz(...) GET_MACRO(__VA_ARGS__, FOO4, FOO3, FOO2)(__VA_ARGS__)
//#include <cstdint>
#include <stdint.h>

unsigned clz2(uint32_t x,int c);
//unsigned clz(uint16_t x,int c);
//unsigned clz(uint8_t x,int c);

#endif
