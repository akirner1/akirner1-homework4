/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"

#define MAX_PROC 250

int main(int argc, char *argv[]) {

	// DO NOT REMOVE THE BLOCK BELOW (FORK BOMB PREVENTION) //
	struct rlimit limit;
	limit.rlim_cur = MAX_PROC;
	limit.rlim_max = MAX_PROC;
	setrlimit(RLIMIT_NPROC, &limit);
	// DO NOT REMOVE THE BLOCK ABOVE THIS LINE //

	char *cmdline = (char*) malloc(MAXBUF); // stores user input from commmand line
	//while(1){
		printf("dsh> ");
		fgets(cmdline, MAXBUF, stdin);
		getEachWord("hello world", MAXBUF);
		//for(int i = 0; i < sizeof(*allWords); i++){
		//	printf("%s", allWords[i]);
		//}
		
		
		
		
	//}

	return 0;
}
