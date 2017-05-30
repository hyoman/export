#define APP_VER "0.0.1"
#define TITLE_PARAM 10
//////////////////////
// struct define 
////////////////////////
struct sw_data{
	int line;
	char atomic_type;
	char data[32];

};

int argments_check(int argc);
void appinfo_print(int argc, char **argv);
int argv_parser(int argc, char **argv);
////////////////////////////////////////////
/* function define */
int find_space(char *buffer[], char *data);
int find_lf(char c);
int s_parser(struct sw_data* data, char *filename);
int show_all_data(struct sw_data* data);
/////////////////////////////////////////

