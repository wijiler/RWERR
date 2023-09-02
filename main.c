#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// https://stackoverflow.com/questions/22973670/creating-my-own-strcmp-function-in-c
int bstrcmp(const char *a, const char *b)
{
    while (*a && *a == *b) { ++a; ++b; }
    return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}
char* readfile(char* path) {
    FILE    *textfile;
    char    *text;
    long    numbytes;
     
    textfile = fopen(path, "r");
    if(textfile == NULL) {
	printf("\x1B[31mCannot Open file\x1B[0m\n");
        exit(1);
    } 
    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);  
 
    text = (char*)calloc(numbytes, sizeof(char));   
    if(text == NULL)
	exit(1);
 
    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);
    return text;
}
char* readfile_f(FILE* f) {
    FILE    *textfile;
    char    *text;
    long    numbytes;
     
    textfile = f;
    if(textfile == NULL) {
	printf("\x1B[31mCannot Open file\x1B[0m\n");
        exit(1);
    } 
    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);  
 
    text = (char*)calloc(numbytes, sizeof(char));   
    if(text == NULL)
	exit(1);
 
    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);
    return text;
}

int main (int argc,char* argv[]) {
	char* filepath;
	if (argc >= 2) {
	   filepath = argv[1];
	}
	printf("-- RWE --\nstarting watch on %s:\n",filepath);
	char* ofile = readfile(filepath);
	char* efile = ofile;
    	// main progam loop
	while (true) {
	    efile = readfile(filepath);  
	    if (bstrcmp(ofile,efile) != 0) {
		system(filepath);
		char* stde = readfile_f(stderr);	
		char* stdo = readfile_f(stdout);
		printf("stderr: %s\n",stde);
		printf("stdout: %s\n",stdo);
	    }
	}
	free(efile);
	free(ofile);
	return 0;
}
