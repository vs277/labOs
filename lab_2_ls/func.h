#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

void printFileInfo(struct stat * buff,char * name);

void get_state( int mode, char str[] );

