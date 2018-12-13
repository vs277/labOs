#include "head.h"


int main(){
	key_t key;
	int shmid;
	char* times;
	if((key=ftok(NAME_FILE,ID_FILE))<0) printf("error ftok\n");
	if((shmid=shmget(key,SIZE_MAS, 0666 | IPC_CREAT))<0) printf("error shmget\n");
	if ((times = (char*)shmat(shmid, 0, 0)) < 0) printf("shmat error\n");
	memset(times,'0',25);
	while(times[0]!='2'){
		if(times[0]=='1'& times[1]!='0'){
			printf("times is 2 program %s",&times[1]);
			memset(times,'0',25);
			//sleep(1);
		}//else sleep(1);
	}
	shmdt(times);
	
	return 0;
}
