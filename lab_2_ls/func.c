#include "func.h"

void printFileInfo(struct stat * buff,char * name){
        char * time = ctime(&buff->st_mtime);
        time[strlen(time) - 1] = 0;
        struct passwd* user;
        user=getpwuid(buff->st_uid);
        struct group* grup;
        grup=getgrgid(buff->st_gid);
        char mode[11];
        get_state(buff->st_mode,mode);
        printf("%s %4hd %-8s %-8s %8lld %s %s \n",mode,buff->st_nlink,user->pw_name,grup->gr_name,buff->st_size,time,name);
}

void get_state( int mode, char str[] )
{
        strcpy( str, "----------" );           

        if ( S_ISDIR(mode) )  str[0] = 'd';    
        if ( S_ISCHR(mode) )  str[0] = 'c';    
        if ( S_ISBLK(mode) )  str[0] = 'b';    
        if ( mode & S_IRUSR ) str[1] = 'r';    
        if ( mode & S_IWUSR ) str[2] = 'w';
        if ( mode & S_IXUSR ) str[3] = 'x';
        if ( mode & S_IRGRP ) str[4] = 'r';    
        if ( mode & S_IWGRP ) str[5] = 'w';
        if ( mode & S_IXGRP ) str[6] = 'x';
        if ( mode & S_IROTH ) str[7] = 'r';    
        if ( mode & S_IWOTH ) str[8] = 'w';
        if ( mode & S_IXOTH ) str[9] = 'x';
}


