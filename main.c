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
	int run = 1;
	while(run){
		printf("dsh> ");
		fgets(cmdline, MAXBUF, stdin);
		char** allWords = getEachWord(cmdline, MAXBUF);
		/*for(int i = 0; allWords[i] != NULL; i++){
			printf("%s\n", allWords[i]);
		}*/
		char* cmd = allWords[0]; //the command should always be the first input. 
		//explicit functions
		
		if(cmd == NULL){
			//do nothing
		}else if(isCommand(cmd, "exit")){
			run = 0;
		}else if(isCommand(cmd, "pwd")){
			char* workingDir = (char*) malloc(MAXBUF);
			getcwd(workingDir, MAXBUF);
			printf("%s\n", workingDir);
		}else if(isCommand(cmd, "cd")){
			char* targetDir = allWords[1]; 
			if(targetDir == NULL){
				printf("Insufficient arguments for command: cd");
			}else{
				if(chdir(targetDir) != 0){
					perror("");
				}
			}

		}else{
			//TODO user is attempting to run an external program
			//handle filepath, handle any invalid path errors that may occur, fork, run program
		}
		

		
	}
	free(cmdline);
	return 0;
}
