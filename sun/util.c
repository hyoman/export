#include<stdio.h>
#include "util.h"
static char app_info[][TITLE_PARAM] ={
	"APP NAME",
	"VERSION",
};
int argments_check(int argc){
	if(argc>1)
		return argc-1;
	else
		return 0;
}

void appinfo_print(int argc, char **argv){
	int i;
	
	printf("[INFO]\n====================================================\n");
	printf("%-10s\t%-10s\n",*app_info, *(argv)+2);
	printf("%-10s\t%-10s\n",*(app_info+1), APP_VER);

	printf("----------------------------------------------------\n");
	
	if(argments_check(argc)){
		printf("argc:%d \t argments ->", argc);
		for(i=0; i<argc ; i++){
			printf("[%d]:%s\t",i, *(argv+i));
		}
		printf("\n");
	}
	
	printf("====================================================\n");

}
