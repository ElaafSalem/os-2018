/* 
Question: Use MUTEXT to increment the global variable once, then pass it to the next thread and so on, 
the output should be something as the following:
tidA 1
tidB 2
tidA 3
tidB 4 …

One possible solution using two functions: 
*/

#include <iostream>
#include "pthread.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using std::cout;
using std::dec;
using std::endl;
int counter = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
#define NLOOP 10
void * doit1(void *);
void * doit2(void *);
int main(){
	pthread_t tidA, tidB;
	pthread_create(&tidA, NULL, doit1, NULL);
	pthread_create(&tidB, NULL, doit2, NULL);
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	pthread_cond_destroy(&condition_var);
	pthread_mutex_destroy(&count_mutex);
	exit(0);
}
void * doit1(void *vprt){
	int i, val;
	for (i=0; i<NLOOP; i++) {
		pthread_mutex_lock(&count_mutex);
		cout<<"Thread 1 locked\n";
		val = counter;
		cout<<pthread_self()<<" "<<dec<<val<<endl;
		counter = val+1;
		pthread_cond_signal(&condition_var);
		pthread_mutex_unlock(&count_mutex);
		cout<<"Thread 1 unlocked\n";
		pthread_yield();
	}
	return (NULL);
}
void * doit2(void *vprt){
	int i, val;
	for (i=0; i<NLOOP; i++) {
		pthread_mutex_lock(&count_mutex);
		cout<<"Thread 2 locked\n";
		val = counter;
		cout<<pthread_self()<<" "<<dec<<val<<endl;
		counter = val+1;
		pthread_cond_wait(&condition_var, &count_mutex);
		pthread_mutex_unlock(&count_mutex);
		cout<<"Thread 2 unlocked\n";
	}
	return (NULL);
}
