#include "ccfile.h"

int creatFile(char * name){
	FILE * fp;
	if((fp=fopen(name,"w"))==NULL) return -1;
	else {
		int i;
		for(i=0;i<10000000;i++)
			fprintf(fp,"this line is nomber %d \n",i);
		fclose(fp);
	}
	return 0;
}

int copyFile(char * name1,char * name2){


	int n_read = open(name1,O_RDONLY,0);
	int n_copy = creat(name2,PERMS);
	if(n_read==-1 || n_copy==-1) return -1;
	int n;
	char buf[BUFSIZE];
	printf("started copy file \n");
	while((n=read(n_read,buf,BUFSIZE))>0){
		//printf("copy %d byte \n",n);
		if(write(n_copy,buf,n)!=n) return -1;
		printf("copy %d byte \n",n);

	}
	return 0;
}

