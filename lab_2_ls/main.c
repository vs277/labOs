#include "func.h"
int main(){


	DIR * dfd;
	struct dirent * dp;
	char * name=".";
	struct stat stbuf;
	dfd=opendir(name);
	while((dp = readdir(dfd)) != NULL){
		if(stat(dp->d_name,&stbuf)!=-1)
			printFileInfo(&stbuf,dp->d_name);
	}
	return 0;
}

