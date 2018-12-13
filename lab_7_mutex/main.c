#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
//#include <sys/wait.h>
//#include <time.h>
#include <unistd.h>
int i;
pthread_mutex_t mut;

void * thread_func(void *arg)
{
	while(1){
		//int b=a;
		pthread_mutex_lock(&mut);
		printf("Mutex is my %s threads\n",(char*)arg);
		i++;
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	return 0;
}

int main(){
	i=0;
	char a[]="1",b[]="2";

	pthread_mutex_init(&mut,NULL);
	pthread_mutex_lock(&mut);
	pthread_t  threads_1,threads_2;
	pthread_create(&threads_1, NULL, thread_func, (void *)a);
	pthread_create(&threads_2, NULL, thread_func, (void*)b);
	pthread_mutex_unlock(&mut);
	while(i<17);

	pthread_mutex_lock(&mut);
	printf("main kill pthreads \n");
	pthread_cancel(threads_2);
	pthread_cancel(threads_1);
	pthread_mutex_destroy(&mut);
	return 0;
}

