#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (int argc,char* argv[]) {
	printf("-- RWE --\nstarting watch:");
	char* filepath;
	if (argc >= 2) {
	   filepath = argv[1];
	}
	printf("%s\n",filepath);
	long len;
	char* ofile = 0;
	FILE * f = fopen (filepath, "rb");
	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  len = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  ofile = malloc(len);
	  if (ofile)
	  {
	    fread (ofile, 1, len, f);
	  }
	  fclose (f);
	}
	else {
		printf("\x1B[31mCould not find file specified\x1b[0m");
		return -1;
	}
	char* efile = ofile;
	// main progam loop
	while (true) {
	  fseek (f, 0, SEEK_END);
	  len = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  efile = malloc(len);
	  if (efile)
	  {
	    fread (efile, 1, len, f);
	  }
	  if (strcmp(efile,ofile) == 0) {
		system(filepath);		  
		char* stder;
		char* stdo;
		if (stderr) {
		long stdelen;
		stdelen = ftell(stderr);
		fread(stder, 1, stdelen,stderr);
		}
		if (stderr) {
		long stdolen;
		stdolen = ftell(stderr);
		fread(stdo, 1, stdolen,stderr);
		}
		printf("stderr: %s",stder);
		printf("stdout: %s",stdo);
	  }
	}
	fclose (f);
	return 0;
}
