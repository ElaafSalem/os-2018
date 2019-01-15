/* 
Question: Use MUTEXT to increment the global variable once, then pass it to the next thread and so on, 
the output should be something as the following:
tidA 1
tidB 2
tidA 3
tidB 4 …

One possible solution is by locking and unlocking the thread on each loop and then delying the current 
thread to allow the second to acquire the lock.
*/

#include <iostream>
#include <unistd.h>
#include "pthread.h"

using std::cout;
using std::endl;

#define n 10

int counter = 0;
pthread_mutex_t mutex_count = PTHREAD_MUTEX_INITIALIZER;
void * doit(void *);
int main() {
	pthread_t tidA, tidB;
	pthread_create(&tidA, NULL, doit, NULL);
	pthread_create(&tidB, NULL, doit, NULL);
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	pthread_mutex_destroy(&mutex_count);
	return 0;
}
void * doit(void *){
	int i, val;
	
	for (i = 0; i < n; i++) {
		pthread_mutex_lock(&mutex_count);
		val = counter;
		cout << pthread_self() << " " << val+1 << endl;
		sleep(1);
		counter = val + 1;
		pthread_mutex_unlock(&mutex_count);
		sleep(2);
	}

}
