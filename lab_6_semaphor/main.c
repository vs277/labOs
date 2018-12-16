
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

//union semun {
//  int              val;    /* Value for SETVAL */
//  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
//  unsigned short  *array;  /* Array for GETALL, SETALL */
//  struct seminfo  *__buf;  /* Buffer for IPC_INFO
//                              (Linux specific) */
//};


int main(){
	struct sembuf do_it = { 0, 1, 0 };
	struct sembuf wait_w = { 0, -1, 0 };
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
	}else	printf("semafor created \n");
	union semun sem_union;
	sem_union.val = 1;
	if (semctl(semid, 0, SETVAL, sem_union)==-1) printf("error value sem \n");

	if (pipe(file_pipes) == 0){
		if((k=fork())==0){
			int i=0;
			while(i<10){
				if (semop(semid, &wait_w, 1) < 0) {
					printf("Невозможно выполнить операциюn");
					exit(1);
				}

				It=time(NULL);
				char* thattime=asctime(localtime(&It));
				write(file_pipes[1],thattime ,strlen(thattime));
				printf("sem is my and i write my time for pr1\n");
				i++;
				if (semop(semid, &do_it, 1) < 0) {
					printf("Невозможно выполнить операциюn");
					exit(1);
				}	
				sleep(1);
			}
			semctl(semid, 0, IPC_RMID);
			exit(EXIT_SUCCESS);
		}
		else {
			sleep(1);
			char times[25];
			while(1){
				if(k==(waitpid(k,0,WNOHANG))){
					printf("process %d died,i exit\n",k);
					exit(EXIT_SUCCESS);
				}

				if (semop(semid, &wait_w, 1) < 0) {
					printf("erorror \n");
					if(k==(waitpid(k,0,WNOHANG))){
						printf("process %d died,i exit\n",k);
						exit(EXIT_SUCCESS);
					}

					exit(1);;
				}
				read(file_pipes[0],times,sizeof(times));
				printf("time is 2 process %s",times);
				sleep(1);
				if (semop(semid, &do_it, 1) < 0) {
					printf("eroro wait m.b. semafor was deleted pr2\n");
					if(k==(waitpid(k,0,WNOHANG))){
						printf("process %d died,i exit\n",k);
						exit(EXIT_SUCCESS);
					}

					exit(0);
				}

			}

			exit(EXIT_SUCCESS);


		}
	}
	printf("fiasko\n");
	return 0;

}


