#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//#include <limits.h>

#define FILE_1 "origin.txt"
#define FILE_2 "clone.txt"
#define BUFSIZE 1024
#define PERMS 0666

int creatFile(char * name);
 
int copyFile(char * name1,char * name2);

