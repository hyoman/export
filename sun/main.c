#include<stdio.h>
#include "util.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


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


//////////////////////
// struct define 
////////////////////////
struct sw_data{
	int line;
	char atomic_type;
	char data[32];

};
////////////////////////////////////////////
/* function define */
int find_space(char *buffer[], char *data);
int find_lf(char c);
int s_parser(struct sw_data*);
int show_all_data(struct sw_data* data);
/////////////////////////////////////////


int main(int argc, char** argv){
//	appinfo_print(argc,argv);
	struct sw_data parsing_data[DATA_SIZE];
	memset(parsing_data, 0x00, sizeof(struct sw_data)*DATA_SIZE);
	s_parser(parsing_data);
	show_all_data(parsing_data);
	return 0;

}


int s_parser(struct sw_data *parsing_data){

	int fd;
	int line_count=0;
	int ret=1;
	char line_buffer[LINE_BUF_LEN]={0,};

	int st_index=0;


	fd = open(DATA_FILE, O_RDONLY);
	if (!fd)
		printf( "Can't open proc file 'version'");
	
	char c='a';
	int offset=0;
	while(  read(fd,&c, 1) > 0){
		ret=find_lf(c);
#if 1
		if(ret == LINEFEED){
			line_count++;
			offset=0;
			//여기서 데이터 수정
			if( (line_count % 9) == 5 ){
				parsing_data[st_index].line = line_count;
				parsing_data[st_index].atomic_type = line_buffer[0];
#ifdef DEBUG
				printf("[%d,%c]",parsing_data[st_index].line, parsing_data[st_index].atomic_type);
#endif
				st_index++;
			}else if ( (line_count % 9) ==6){
				find_space(&line_buffer, parsing_data[st_index].data);
				strcpy(parsing_data[st_index].data, line_buffer);
				parsing_data[st_index].line = line_count;
#ifdef DEBUG
				printf("[%d,%s]",parsing_data[st_index].line, parsing_data[st_index].data);
#endif
				st_index++;
			}
#ifdef DEBUG
			printf("%s [LINE:%d] \n", line_buffer, line_count);
#endif
			memset(line_buffer, 0x00, LINE_BUF_LEN);

		}else{
			line_buffer[offset]=c;
			offset++;
		}
#endif
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


/// is deprecated
int find_space(char *buffer[], char *data)
{
	int i=0;
#ifdef DEBUG	
		printf("%s\n",buffer);
#endif
		i++;

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
