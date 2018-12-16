#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_rwlock_t war;
int i;
char* words;

void * thread_func(void *arg)
{
	while(1){
		pthread_rwlock_wrlock(&war);
		printf(" %s threads read is %s ",(char*)arg,words);
		pthread_rwlock_unlock(&war);
		printf(" %s threads lock out \n ",(char*)arg);
		i++;
		sleep(1);
		if(i>17)return 0;
	}
	return 0;
}

int main(){
	i=0;
	if(pthread_rwlock_init(&war,0)<0) printf("aaaaaaaaaaa eroror creat wrlock\n");
	//char* words_2;
	//char* words_3;
	//words=words_2;
	time_t It;
	char a[]="1",b[]="2";
	pthread_t  threads_1,threads_2;
	pthread_create(&threads_1, NULL, thread_func, (void *)a);
	pthread_create(&threads_2, NULL, thread_func, (void*)b);
	while(i<17){
		pthread_rwlock_rdlock(&war);
		It=time(NULL);
		words=asctime(localtime(&It));
	//	int j;
	//	for( j=0;j<24;j++)
	//		words[j]=words_2[j];

		printf("main is write %s",words);
		sleep(2);
		pthread_rwlock_unlock(&war);
		sleep(1);		
	}
	pthread_exit(&threads_1);
	pthread_exit(&threads_2);

	printf("main kill pthreads \n");
	return 0;
}

