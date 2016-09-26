#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

#if defined(recursive)
#include "clz.hpp"
#else
#include "clz.h"
#endif

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}


int main(int argc,char *argv[]){
	FILE *output;
	struct timespec start,end;
	double time1;
	clock_gettime(CLOCK_REALTIME,&start);
	for(uint32_t i=0;i<UINT_MAX;i++){
//	for(uint32_t i=0;i<=10000;i++){
		clz(i);
	}
	clock_gettime(CLOCK_REALTIME,&end);
	time1 = diff_in_second(start,end);

#if defined(recursive)
	output =fopen("recursive.txt","a");
#elif defined(iteration)
	output =fopen("interation.txt","a");
#elif defined(byte)
	output =fopen("byte.txt","a");
#elif defined(binary)
	output =fopen("binary.txt","a");
#endif	

	fprintf(output,"time %lf sec\n",time1);
	fclose(output);

	printf("executiom time : %lf sec\n",time1);
	
	
	return 0;
}
