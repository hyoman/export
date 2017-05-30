#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include "include/util.h"
extern char filename[32];
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
 
int argv_parser(int argc, char **argv)
{
	int c;
	int digit_optind = 0;
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"add",     required_argument, 0,  'a' },
			{"sum", 	required_argument, 0,  's' },
			{"end ",  required_argument, 0,  'e' },
			{"verbose", no_argument,       0, 'v' },
			{"create",  no_argument,	 0, 'c'},
			{"file",    required_argument, 0, 'f' },
			{0,         0,                 0,  0 }
		};

		c = getopt_long(argc, argv, "abc:d:A:v:f:012",
				long_options, &option_index);
		if (c == -1)
			break;
		switch (c) {
			case 0:
				printf("option %s", long_options[option_index].name);
				if (optarg)
					printf(" with arg %s", optarg);
				printf("\n");
				break;

			case '0':
			case '1':
			case '2':
				if (digit_optind != 0 && digit_optind != this_option_optind)
					printf("digits occur in two different argv-elements.\n");
				digit_optind = this_option_optind;
				printf("option %c\n", c);
				break;

			case 'c':
				printf("c input\n");
				break;
			case 's':
				printf("c input\n");
				break;
			case 'e':
				printf("c input\n");
				break;
			case 'a':
			//	printf("add %s" , argv[optind-1]);
				break;
			case 'f':
			//	printf("flle %s" , argv[optind-1]);
				strcpy(filename, argv[optind-1]);
				break;
			case '?':
				printf("???\n");
				break;
			default:
				printf("?? getopt returned character code 0%o ??\n", c);
		}
	}

	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("[optid:%d]%s ",optind ,argv[optind++]);
		printf("\n");
	}

	//exit(EXIT_SUCCESS);
}
