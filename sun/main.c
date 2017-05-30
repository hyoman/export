#include<stdio.h>
#include "include/util.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <getopt.h>

/* preprocess */
//#define DEBUG 


///////////////
/* return */
////////////////////////
#define LINEFEED 16
#define SPACE	32

////////////////////
/* buffer len */
///////////////////////
#define DATA_FILE "deca"
#define TEMP_LEN 10240*11
#define LINE_BUF_LEN 128 
#define DATA_SIZE 4096

int calc_sum(struct sw_data *data,int startl,int endl);

int get_data(struct sw_data *data,int startl,int endl);
	
	
int main(int argc, char** argv){
	char filename[32];

	int start_line, end_line = 0;
	memset(filename, 0x00, 32);
//	appinfo_print(argc,argv);
	struct sw_data parsing_data[DATA_SIZE];
	memset(parsing_data, 0x00, sizeof(struct sw_data)*DATA_SIZE);
	int c;
	int digit_optind = 0;
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"add",     required_argument, 0,  'a' },
			{"start", 	required_argument, 0,  's' },
			{"end ",  required_argument, 0,  'e' },
			{"verbose", no_argument,       0, 'v' },
			{"create",  no_argument,	 0, 'c'},
			{"open",    required_argument, 0, 'o' },
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
			case 'o':
		//		printf("open [flle] %s" , argv[optind-1]);
				strcpy(filename, argv[optind-1]);
				s_parser(parsing_data,filename);
				break;
			case 'c':
				break;
			case 's':
			start_line =	atoi(argv[optind-1]) ;
			printf("start_line : %d  \n",start_line);
				break;
			case 'e':
				end_line =	atoi(argv[optind-1]) ;
				printf("end_ine : %d  \n",end_line);
				if(end_line<=start_line){
					printf(" line error .. \n");
					return 0;
				}
				if(start_line>0){
					//find & getdata
					get_data(parsing_data,start_line,end_line);
					//calc sum
				}
				break;
			case 'a':
			//	printf("add %s" , argv[optind-1]);
				break;
			case '?':
				printf("???\n");
				break;
			case 'v':
				show_all_data(parsing_data);
				break;
			default:
				printf("?? getopt returned character code 0%o ??\n", c);
		}
	}
	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ",optind ,argv[optind++]);
		printf("\n");
	}
	
}


int s_parser(struct sw_data *parsing_data, char *filename){

	int fd;
	int line_count=0;
	int ret=1;
	char line_buffer[LINE_BUF_LEN]={0,};

	int st_index=0;
	if((strlen(filename)>2)){
		//printf("open 1\n");
		fd = open(filename, O_RDONLY);
	}else{
	//	printf("open 2\n");
		fd = open(DATA_FILE, O_RDONLY);
	}
	if (!fd)
		printf( "Can't open proc file 'version'");
	
	char c='a';
	int offset=0;
	while(  read(fd,&c, 1) > 0){
		ret=find_lf(c);
		if(ret == LINEFEED){
			line_count++;
			offset=0;
			//여기서 데이터 수정
#if 0
			if( (line_count % 9) == 5 ){
				parsing_data[st_index].line = line_count;
				parsing_data[st_index].atomic_type = line_buffer[0];
#ifdef DEBUG
				printf("[%d,%c]",parsing_data[st_index].line, parsing_data[st_index].atomic_type);
#endif
				st_index++;
			}else if ( (line_count % 9) ==6){
				strcpy(parsing_data[st_index].data, line_buffer);
				parsing_data[st_index].line = line_count;
#ifdef DEBUG
				printf("[%d,%s]",parsing_data[st_index].line, parsing_data[st_index].data);
#endif
				st_index++;
			}
#else 
			if( (line_count % 9) == 5 ){
				parsing_data[st_index].line = line_count;
				parsing_data[st_index].atomic_type = line_buffer[0];
			}else if ( (line_count % 9) ==6){
				strcpy(parsing_data[st_index].data, line_buffer);
				st_index++;
			}
			
#endif

#ifdef DEBUG
			printf("%s [LINE:%d] \n", line_buffer, line_count);
#endif
			memset(line_buffer, 0x00, LINE_BUF_LEN);

		}else{
			line_buffer[offset]=c;
			offset++;
		}
	}	
	close(fd);
}


int find_lf(char c)
{
	if(c ==0xa){ 
		return LINEFEED;
	}
	return 0;			
}



int show_all_data(struct sw_data* data)
{
	int i=0;
	int temp_double;

	char *stop;
	while(i<DATA_SIZE){
		if(data[i].line>0){
			//stdout
			printf("[line:%d, type:%c data:%s]\n",data[i].line, data[i].atomic_type, data[i].data);
			//TO DO : need to convert data TO number from string 
		}
		i++;
	}

}

int get_data(struct sw_data *data,int startl,int endl){
	
	int i=0;
	while(i<DATA_SIZE)
	{
		if(startl >= data[i].line){
			printf("start line choose :%d\n", data[i].line);
			break;
		}else {
			
		}
		i++;
	}

}
#if 0
int calc_sum(struct sw_data *data,int startl,int endl){



}
#endif
