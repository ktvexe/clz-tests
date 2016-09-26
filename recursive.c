#include "clz.hpp"
#include <iostream> 
using namespace std;

unsigned clz(uint32_t x)
{
	// shift upper half down, rest is filled up with 0s
	uint16_t upper = (uint16_t)(x >> 16); 
	// mask upper half away
	uint16_t lower = (uint16_t)(x & 0xFFFF);
	// their type is std::uint16_t so a smaller overload is chosen
	return upper ? clz(upper) : 16 + clz(lower);
}

unsigned clz(uint16_t x)
{
	// shift upper half down, rest is filled up with 0s
	uint8_t upper = (uint8_t)(x >> 8); 
	// mask upper half away
	uint8_t lower = (uint8_t)(x & 0xFF);
	// their type is std::uint16_t so a smaller overload is chosen
	return upper ? clz(upper) : 8 + clz(lower);
}


unsigned clz(uint8_t x)
{
	if(x == 0) return 8;
	int n =1;
	if ((x >> 4) == 0) { n += 4; x <<= 4; }
    if ((x >> 6) == 0) { n += 2; x <<= 2; }
    n = n - (x >> 31);
    return n;	
}
	

/*
unsigned clz(uint8_t x)
{
	// shift upper half down, rest is filled up with 0s
	uint8_t upper = (x >> 4); 
	// mask upper half away
	auto lower = (x & 0xF)<<4;
	// their type is std::uint16_t so a smaller overload is chosen
return 0;	
//	return upper ? clz(upper) : 4 + clz(lower);
}
*/
