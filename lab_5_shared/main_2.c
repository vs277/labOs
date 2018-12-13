#include "head.h"


int main(){
	key_t key;
	int shmid;
	char* times;
	if((key=ftok(NAME_FILE,ID_FILE))<0) printf("error ftok\n");
	if((shmid=shmget(key,SIZE_MAS,0))<0) printf("error shmget\n");
	if ((times = (char*)shmat(shmid, 0, 0)) < 0) printf("shmat error\n");
	int i=0;
	//printf("key %d \n",key);
	time_t It;
	while(i<30){
		//if(times[0]=='0'){
			times[0]='1';
		It=time(NULL);
 		sprintf(&times[1],"%s",asctime(localtime(&It)));
		//}else
		 sleep(1);
		i++;
	}
	times[0]='2';
	sleep(3);
	printf("i'll be back\n");
	shmdt(times);
	return 0;
}

