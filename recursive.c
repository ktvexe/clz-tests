#include "clz.hpp"

static inline __attribute((always_inline))
unsigned clz2(uint32_t x,int c)
{
	const int magic[]={0,8,12,14,15};
	
	if(!x && !c)	return 32;

	uint32_t upper = (x >> (16>>c)); 
	if(c>=4) return ~upper&0x1;
//	if(upper ==1)	return (16>>c)-1;
	else if(upper)	return (upper >>(16 >>(c+1)))?clz2(upper>>(16 >>(c+1)),c+2):clz2(upper,c+1);
	uint32_t lower = (x & (0xFFFF>>magic[c]));
	if(lower>= (2<<((16>>c)-1)))	return 16>>c;
	return (16>>(c)) + clz2(lower,c+1);
}
