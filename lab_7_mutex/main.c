#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>


#define NAME_FILE "./file"
#define ID_FILE 'B'
#define SIZE_MAS 25


int i;
pthread_mutex_t mut;

void * thread_func_1(void *arg)
{
	 key_t key;
        int shmid;
        char* times;
	time_t It;
        if((key=ftok(NAME_FILE,ID_FILE))<0) printf("error ftok\n");
        if((shmid=shmget(key,SIZE_MAS, 0666 | IPC_CREAT))<0) printf("error shmget\n");
        if ((times = (char*)shmat(shmid, 0, 0)) < 0) printf("shmat error\n");

	while(1){
		//int b=a;
		pthread_mutex_lock(&mut);
		printf("Mutex is my %s threads,wrire data\n",(char*)arg);
		It=time(NULL);
                sprintf(times,"%s",asctime(localtime(&It)));
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	return 0;
}

void * thread_func_2(void *arg)
{

	key_t key;
        int shmid;
        char* times;
        if((key=ftok(NAME_FILE,ID_FILE))<0) printf("error ftok\n");
        if((shmid=shmget(key,SIZE_MAS, 0666 | IPC_CREAT))<0) printf("error shmget\n");
        if ((times = (char*)shmat(shmid, 0, 0)) < 0) printf("shmat error\n");

	while(1){

		pthread_mutex_lock(&mut);
		printf("Mutex is my %s threads,read data %s\n",(char*)arg,times);
		i++;
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
}

int main(){
	i=0;
	char a[]="1",b[]="2";

	pthread_mutex_init(&mut,NULL);
	pthread_mutex_lock(&mut);
	pthread_t  threads_1,threads_2;
	pthread_create(&threads_1, NULL, thread_func_1, (void *)a);
	sleep(1);
	pthread_create(&threads_2, NULL, thread_func_2, (void*)b);
	pthread_mutex_unlock(&mut);
	while(i<17);

	pthread_mutex_lock(&mut);
	printf("main kill pthreads \n");
	pthread_cancel(threads_2);
	pthread_cancel(threads_1);
	pthread_mutex_destroy(&mut);
	return 0;
}

