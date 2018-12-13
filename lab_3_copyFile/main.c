#include "ccfile.h"

int main(){
creatFile(FILE_1);
if(copyFile(FILE_1,FILE_2)==-1)
	printf("error -1 \n");
else printf("done! \n");
return 0;
}
