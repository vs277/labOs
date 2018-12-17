
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>



int main(){
	struct sembuf write_it = { 0, 1 , 0 };
	struct sembuf read_it = { 0, -1 , 0 };
	struct sembuf wait_it ={ 0 , 0 , 0 };
	key_t key;
	if((key=ftok("./file",'B'))<0){
		printf("error ftok\n");
		exit(0);
	}
	pid_t k;
	time_t It;
	int file_pipes[2];
	It=time(NULL);
	int semid;
	if ((semid = semget(key, 1,0666 | IPC_CREAT)) < 0) {
		printf("error sem \n");
		exit(0);
	}else	printf("semafor created %d \n",semid);

	if (pipe(file_pipes) == 0){
		if((k=fork())==0){
			int i=0;
			while(i<10){
				semop(semid,&wait_it,1);
				It=time(NULL);
				char* thattime=asctime(localtime(&It));
				write(file_pipes[1],thattime ,strlen(thattime));
				printf("sem is my and i write my time for pr1\n");
				i++;
				semop(semid,&write_it,1);
				sleep(1);
			}
			semctl(semid,IPC_RMID,0);
			exit(EXIT_SUCCESS);
		}
		else {
                 
			char times[25];
			while(1){

				if(k==(waitpid(k,0,WNOHANG))){
					printf("process %d died,i exit\n",k);
					exit(EXIT_SUCCESS);
				}
				if((waitpid(k,0,WNOHANG))<0){
                                        printf("process %d died,i exit\n",k);
                                        exit(EXIT_SUCCESS);
                                }

				if((semop(semid,&read_it,1))<0) {
				printf("semofor denied,proces 2 died,i am go to\n");
				exit(EXIT_SUCCESS);
				}
				read(file_pipes[0],times,sizeof(times));
				printf("time is 2 process %s",times);
				//sleep(1);

			}

			exit(EXIT_SUCCESS);


		}
	}
	printf("fiasko\n");
	return 0;

}


