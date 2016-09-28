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
static inline void get_cycles(unsigned *high,unsigned *low)
{
		asm volatile ("CPUID\n\t" 
					"RDTSC\n\t"
 					"mov %%edx, %0\n\t"
 					"movl %%eax, %1\n\t": "=r" (*high), "=r" (*low)::"%rax","%rbx","%rcx","%rdx"
		);	
}

static inline void get_cycles_end(unsigned *high,unsigned *low){

		asm volatile("RDTSCP\n\t"
					 "mov %%edx, %0\n\t"
					 "mov %%eax, %1\n\t"
					 "CPUID\n\t": "=r" (*high), "=r" (*low)::"%rax","%rbx","%rcx","%rdx"
		);
}

static inline uint64_t diff_in_cycles(unsigned high1,unsigned low1,unsigned high2,unsigned low2){
		uint64_t start,end;
		start = ( ((uint64_t)high1 << 32) | low1 );
		end = ( ((uint64_t)high2 << 32) | low2 );
		return end-start;
}


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
	//struct timespec start,end;
	double time1;
	uint64_t time_all=0;
	//int time_all=0;
#if defined(correct)
	for(int try=0;try<20;try++){
		time1=0;
		clock_gettime(CLOCK_REALTIME,&start);
		for(uint32_t i=0;i<32;i++){
			const int num =clz(1<<i);
			printf("%ud:%d \n",1<<i,num);
			for(uint32_t j=(1<<i);j<(1<<(i+1));j++){
				assert( num == clz(j));
			}
		}	
		clock_gettime(CLOCK_REALTIME,&end);
		time1 += diff_in_second(start,end);
		printf("executiom time : %.10lf sec\n",time1);
	}
#else
	assert(argv[1]&&argv[2]&&"insert argument");
	unsigned int min=atoi(argv[1]);
	unsigned int max=atoi(argv[2]);
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
	uint64_t timec,timecall;
	unsigned timec_high1,timec_low1,timec_high2,timec_low2;
//	fprintf(output,"min:%d \n",min);
//	fprintf(output,"max:%d \n",max);
//	clock_gettime(CLOCK_REALTIME,&start);
	for(uint32_t i=min;i<max;i++){
//	for(uint32_t i=0;i<=10000;i++){
		time1 =0;
		timecall=0;
		for(int j=0;j<100;j++){
//			clock_gettime(CLOCK_REALTIME,&start);
			get_cycles(&timec_high1,&timec_low1);
			clz(i);
			get_cycles_end(&timec_high2,&timec_low2);
			timec=diff_in_cycles(timec_high1,timec_low1,timec_high2,timec_low2);	

//			clock_gettime(CLOCK_REALTIME,&end);
			timecall+=timec;
//			time1 += diff_in_second(start,end);
//			printf("time: %lu\n",timec);
		}
		time_all+=(timecall/100);
		//time_all+=(time1/100);
		fprintf(output,"%d %lu cycles\n",i,timecall/100);
		//fprintf(output,"%d %.10lf sec\n",i,time1/100);
	}

//	clock_gettime(CLOCK_REALTIME,&end);
//	time1 = diff_in_second(start,end);

	fclose(output);

	printf("took %lf million cycles\n",time_all/1000000.0);
	//printf("executiom time : %.10lf sec\n",time_all);
	
#endif		
	return 0;
}
