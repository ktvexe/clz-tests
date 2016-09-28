#include "clz.hpp"

unsigned clz2(uint32_t x,int c)
{
	const int mask[]={0,8,12,14};
	const int magic[]={2,1,0,0};
	
	if(!x && !c)	return 32;

	uint32_t upper = (x >> (16>>c)); 
	uint32_t lower = (x & (0xFFFF>>mask[c]));
	if(c==3) return upper?magic[upper]:2+magic[lower];
	return 	upper?clz2(upper,c+1):(16>>(c)) + clz2(lower,c+1);
}
