/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>


// TODO: Your function definitions below (declarations in dsh.h)

/**
 * This is just an example. Delete this before 
 * submission.
 */

/**
 * @param line a string to be processed
 * @param lineSize the size of line (number of characters)
 * @returns a pointer to an array of strings, with each string being a single word from line 
 * Will stop processing after lineSize-1 characters have been processed (since we assume the last char is "\0"), or a "\0" is read)
*/
char** getEachWord(char* line, int lineSize){
    int numWords = 1;
    line[lineSize-1] = '\0';
    //loop through once for char** memory allocation
    
    int i;
    for(i = 0; line[i]!='\0'; i++){
        if(line[i] == ' ' || line[i] == '\t'){
            numWords++;
        }
    }
    //words holds numWords pointers, each pointing to a char* representing 1 word.
    char** words = (char**) malloc(sizeof(char*) * numWords + 1);
    char delim[3] = " \n\t";
    words[0] = strtok(line, delim);
    for(int i = 1; i <= numWords; i++){
        words[i] = strtok(NULL, delim);
    }
    return words;
    

}

int isCommand(char* cmd, char* expected){
    return !strcmp(cmd, expected);
}


/**
 * @param path the path to validate
 * @returns path if path is valid
 * @returns NULL if path is invalid
*/
char* validatePath(char* path){
    if (access(path, F_OK | X_OK) == 0) {
            return path;
        }else{
            return NULL;
        }
}



char* constructPath(char* rawPath, char* workingDir){
    if(rawPath[0] == '/'){
        //path is already constructed. Check if valid and then return
        char* goodPath = (char*) malloc(strlen(rawPath) + 1);
        strcpy(goodPath, rawPath);
        return validatePath(goodPath);
    }
    char* wdCatPath = (char*) malloc(strlen(workingDir) + 1 + strlen(rawPath) + 1);
    sprintf(wdCatPath, "%s/%s", workingDir, rawPath);
    if (validatePath(wdCatPath) != NULL){
        //the raw path exists in the current working directory
        return wdCatPath;
    }
    free(wdCatPath);
    char* envPath = (char*) malloc(strlen(getenv("PATH")) + 1);
    strcpy(envPath, getenv("PATH"));
    char* constructedPath = strtok(envPath, ":");
    char* testPath;
    
    while(constructedPath != NULL){
        testPath = (char*) malloc(strlen(constructedPath) + 1 + strlen(rawPath) + 1);
        sprintf(testPath, "%s/%s", constructedPath, rawPath);
        if(validatePath(testPath) != NULL){
            free(envPath);
            return testPath;
        }
        free(testPath);
        constructedPath = strtok(NULL, ":");
        
    }
    //all paths are invalid
    free(envPath);
    return NULL;
    

}

void decodeEnviromentVars(char** args){
    for(int i = 0; args[i] != NULL; i++){
        if(args[i][0] == '$'){
            args[i] = getenv(&args[i][1]);
        }

    }
}

int checkForeground(char** args){
    //TODO: due to confusion on where exactly the & can and can't be place in order to be detected, this function may be incorrect
    int i = 0;
    //we know args[0] is the path name, because if not this wouldn't be executed
    //since args's final index is a null pointer, args[i+1] won't skip the null pointer.
    while(args[i+1] != NULL){
        i++;
    }
    if(!strcmp("&", args[i])){
        args[i] = NULL;
        return 0;
    }
    return 1;
}