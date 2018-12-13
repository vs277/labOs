#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(){
        //int status;
	pid_t k;
	time_t It;
	if((k=fork())==0){
		It=time(NULL);
		printf("i am born %s \n",asctime(localtime(&It)));
		sleep(5);
		return 0;
	}
	else {
		waitpid(k,0,0);
		It=time(NULL);
		printf("process %d died %s\n",k,asctime(localtime(&It)));
	}
	return 0;
}
