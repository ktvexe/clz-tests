#ifndef CLZ_H
#define	CLZ_H

#include <stdint.h>

#if defined(recursive) 
unsigned clz2(uint32_t x,int c);
#else 
unsigned clz(uint32_t x);
#endif

#endif
