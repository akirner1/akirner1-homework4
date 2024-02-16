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
