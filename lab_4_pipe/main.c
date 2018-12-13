#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	pid_t k;
	time_t It;
	int file_pipes[2];
	It=time(NULL);
	if (pipe(file_pipes) == 0){
		if((k=fork())==0){
			int i=0;
			while(i<10){
				It=time(NULL);
				char* thattime=asctime(localtime(&It));
				write(file_pipes[1],thattime ,strlen(thattime));
				sleep(1);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		else { 
			char times[25];
			while(1){
			        sleep(1);
				if(k==(waitpid(k,0,WNOHANG))){printf("process %d died,i exit\n",k);  exit(EXIT_SUCCESS);}	
				read(file_pipes[0],times,sizeof(times));
				printf("time is 2 process %s",times);
				}


			exit(EXIT_SUCCESS);
		}
	}
	printf("fiasko\n");
	return 0;

}
