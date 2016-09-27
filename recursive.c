#include "clz.hpp"

unsigned clz2(uint32_t x,int c)
{
	const int magic[]={0,8,12,14,15};
	if(!x && !c)	return 32;
	else if(!x) return 0;
	uint32_t upper = (x >> (16>>c)); 
	if (c ==5) return 0;
	if(upper ==1)	return (16>>c)-1;
	uint32_t lower = (x & (0xFFFF>>magic[c]));
	c++;
	return upper ? clz2(upper,c) : (16>>(c-1)) + clz2(lower,c);
}
