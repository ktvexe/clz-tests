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
	double time1,time_all=0;
	if(argc>1){
		printf("%d \n",atoi(argv[1]));
		printf("%d \n",clz((unsigned)atoi(argv[1])));
	}
	else{
#if defined(recursive)
	output =fopen("recursive.txt","a");
#elif defined(iteration)
	output =fopen("interation.txt","a");
#elif defined(byte)
	output =fopen("byte.txt","a");
#elif defined(binary)
	output =fopen("binary.txt","a");
#elif defined(harley)
	output =fopen("harley.txt","a");
#endif	

	
	clock_gettime(CLOCK_REALTIME,&start);
	for(uint32_t i=0;i<UINT_MAX;i++){
//	for(uint32_t i=0;i<=10000;i++){
	//	clock_gettime(CLOCK_REALTIME,&start);
		clz(i);
//		clock_gettime(CLOCK_REALTIME,&end);
	//	time1 = diff_in_second(start,end);
//		printf("time: %lf\n",time1);
		time_all+=time1;
//		fprintf(output,"time: %lf sec\n",time1);
	}

	clock_gettime(CLOCK_REALTIME,&end);
	time1 = diff_in_second(start,end);

	fclose(output);

	printf("executiom time : %lf sec\n",time1);
	
	}	
	return 0;
}
