#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include<time.h>

// to compile: gcc -g -pthread count_private.c -o count_private
// .\count_private.exe

#define ThreadCount 4//change number of threads 
long*array; //creating a global array
long size;
long iterations=0;
long privatecount=0;
long privaterations=0;

void* ThreadsExecution(void* rank){ //each function in this method has it's own local variables
   
   long my_rank = (long) rank;
   long perthread = size/ThreadCount;
   long iterations=0;
   long count=0;
   long start = my_rank*perthread;
   long end = start+perthread;
   for(long i=start;i<end;++i){
      if(array[i]==1){
          ++count;
      }
      ++iterations;
   }
   privatecount+=count;
   privaterations+=iterations;
}

void main (){
   size=100000000; // set size of array here
   srand(time(0));
   array = (long *)malloc(sizeof(long)*size);
   for(long x = 0 ; x < size ; ++x ){
      array[x] = rand()%6;
      }
   printf("\n");
   clock_t timetaken;
   pthread_t T[ThreadCount];

   for(int x = 0 ; x < ThreadCount ; ++x ){
      pthread_create(&T[x],NULL,&ThreadsExecution,(void*)x );
   }

   for(int x = 0 ; x < ThreadCount ; ++x){
      pthread_join(T[x],NULL);
   }
   timetaken=clock();
   printf("now The results are with fixing the Race Condition which must be correct\n");
   printf("Number of Threads: %d\n",ThreadCount);
   printf("Time Taken: %f\n",(((double)timetaken/CLOCKS_PER_SEC*1.0)));
   printf("count of 1's= %d\n", privatecount);
   printf("Iterations = %d",privaterations);
}