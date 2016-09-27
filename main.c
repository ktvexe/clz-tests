#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include "clz.h"

#if defined(recursive)
#define clz(x) clz2(x,0)
//#include "clz.hpp"
//#else
//#include "clz.h"
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
	double time1,time_all=0;
	assert(argv[1]&&argv[2]&&"insert argument");
	unsigned int min=atoi(argv[1]);
	unsigned int max=atoi(argv[2]);
#if defined(correct)
		for(uint32_t i=0;i<32;i++){
			const int num =clz(1<<i);
			printf("%ud:%d \n",1<<i,num);
			for(uint32_t j=(1<<i);j<(1<<(i+1));j++){
				assert( num == clz(j));
			}
		}	
#else
#if defined(recursive)
	output =fopen("recursive.txt","a");
#elif defined(iteration)
	output =fopen("iteration.txt","a");
#elif defined(byte)
	output =fopen("byte.txt","a");
#elif defined(binary)
	output =fopen("binary.txt","a");
#elif defined(harley)
	output =fopen("harley.txt","a");
#endif	

	
//	clock_gettime(CLOCK_REALTIME,&start);
	for(uint32_t i=min;i<max;i++){
//	for(uint32_t i=0;i<=10000;i++){
		clock_gettime(CLOCK_REALTIME,&start);
		clz(i);
		clock_gettime(CLOCK_REALTIME,&end);
		time1 = diff_in_second(start,end);
//		printf("time: %.10lf\n",time1);
		time_all+=time1;
		fprintf(output,"time: %.10lf sec\n",time1);
	}

//	clock_gettime(CLOCK_REALTIME,&end);
//	time1 = diff_in_second(start,end);

	fclose(output);

	printf("executiom time : %.10lf sec\n",time_all);
	
#endif		
	return 0;
}
