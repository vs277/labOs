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
pthread_cond_t cond;
void * thread_func_1()
{
	 key_t key;
        int shmid;
        char* times;
        time_t It;
        if((key=ftok(NAME_FILE,ID_FILE))<0) printf("error ftok\n");
        if((shmid=shmget(key,SIZE_MAS, 0666 | IPC_CREAT))<0) printf("error shmget\n");
        if ((times = (char*)shmat(shmid, 0, 0)) < 0) printf("shmat error\n");


        while(1){
		pthread_mutex_lock(&mut);
                //pthread_cond_wait(&cond,&mut);
                printf("threads 1 activated\n");
               // i++;
	        It=time(NULL);
                sprintf(times,"%s",asctime(localtime(&It)));
		pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&mut);
                sleep(1);
        }
        return 0;
}

void * thread_func_2()
{
	key_t key;
        int shmid;
        char* times;
        if((key=ftok(NAME_FILE,ID_FILE))<0) printf("error ftok\n");
        if((shmid=shmget(key,SIZE_MAS, 0666 | IPC_CREAT))<0) printf("error shmget\n");
        if ((times = (char*)shmat(shmid, 0, 0)) < 0) printf("shmat error\n");

        while(1){
		pthread_mutex_lock(&mut);
                pthread_cond_wait(&cond,&mut);
                printf("threads 2 acivated time 1 thread %s",times);
                //i++;
                pthread_mutex_unlock(&mut);
                //sleep(1);
        }
        return 0;
}


int main(){
        i=0;
        //char a[]="1",b[]="2";
	
        pthread_mutex_init(&mut,NULL);
        pthread_cond_init(&cond,NULL);
	pthread_mutex_lock(&mut);
        pthread_t  threads_1,threads_2;
        pthread_create(&threads_1, NULL, thread_func_1, NULL);
        pthread_create(&threads_2, NULL, thread_func_2, NULL);
        pthread_mutex_unlock(&mut);
        while(i<10){
	pthread_mutex_lock(&mut);
	i++;
	printf("main ++\n");
	//pthread_cond_broadcast(&cond);
	//pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mut);
	sleep(2);
	
	}

        pthread_mutex_lock(&mut);
        printf("main kill pthreads \n");
        pthread_cancel(threads_2);
        pthread_cancel(threads_1);
        pthread_mutex_destroy(&mut);
        return 0;
}

