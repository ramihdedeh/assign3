#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include<time.h>

// to compile: gcc -g -pthread count_mutex.c -o count_mutex
// .\count_mutex.exe

#define ThreadCount 4//change the number of threads 
long*array; //creating a global array
long size;
long iterations=0;
long count=0;
pthread_mutex_t mutex;

void* ThreadsExecution(void* rank){
   long my_rank = (long) rank;
   long perthread = size/ThreadCount;
   long start = my_rank*perthread;
   long end = start+perthread;
   pthread_mutex_lock(&mutex);

   for(long x = start ; x < end; ++x ){
      if( array[x] == 1 ){
         ++count;
      }
      ++iterations;
   }
   pthread_mutex_unlock(&mutex);
}

void main (){

   size=100000000; // set size of array 
   srand(time(0));
   array = (long *)malloc(sizeof(long)*size);

   for(long x = 0 ; x < size ; ++x ){
      
      array[x] = rand()%6;
      
      }
   printf("\n");
   clock_t timetaken;
   pthread_mutex_init(&mutex,NULL);
   pthread_t T[ThreadCount];
   
   for(int x = 0; x < ThreadCount ; ++x ){
      pthread_create(&T[x],NULL,&ThreadsExecution,(void*)x);
   }


   for(int x = 0 ; x < ThreadCount ;++x){
      pthread_join(T[x],NULL);
   }
   timetaken=clock(); 
   
   printf("The following count of 1's are correct, since we used mutex\n");
   printf("Number of Threads: %d\n",ThreadCount);
   printf("Time Taken: %f\n",(((double)timetaken/CLOCKS_PER_SEC*1.0)));
   printf("count of 1's= %d\n", count);
   printf("Iterations = %d\n",iterations);
}