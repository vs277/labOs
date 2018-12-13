#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

int i;
pthread_mutex_t mut;
pthread_cond_t cond;
void * thread_func_1()
{
        while(1){
		pthread_mutex_lock(&mut);
                pthread_cond_wait(&cond,&mut);
                if(i%3==1) printf("threads 1 activated\n");
               // i++;
                pthread_mutex_unlock(&mut);
                //sleep(1);
        }
        return 0;
}

void * thread_func_2()
{
        while(1){
		pthread_mutex_lock(&mut);
                pthread_cond_wait(&cond,&mut);
                if(i%2==0) printf("threads 2 acivated\n");
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
        while(i<17){
	pthread_mutex_lock(&mut);
	i++;
	pthread_cond_broadcast(&cond);
	//pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mut);
	sleep(1);
	
	}

        pthread_mutex_lock(&mut);
        printf("main kill pthreads \n");
        pthread_cancel(threads_2);
        pthread_cancel(threads_1);
        pthread_mutex_destroy(&mut);
        return 0;
}

