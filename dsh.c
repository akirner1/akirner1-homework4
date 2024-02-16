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
    int numChars = 0;
    line[lineSize-1] = "\0";
    //loop through once for char** memory allocation
    int i;
    for(i = 0; line[i]!="\0"; i++){
        if(line[i] == ' '){
            numWords++;
            //set the space to a string end character, allowing the use of strcpy later to properly transfer data
            line[i] = "\0";
        }
    }
    if(i != lineSize -1){
        lineSize = i+1;
    }
    //words holds numWords pointers, each pointing to a char* representing 1 word.
    char** words = (char**) malloc(8 * numWords);
    char* wordStart = line; //points to the start of the word to be copied.
    int wordNum = 0;
    int wordSize = 0;
    for(int i = 0; i < lineSize; i++){
        wordSize++;
        if(line[i] == "\0"){
            words[wordNum] = (char*) malloc(wordSize);
            strcpy(words[wordNum], wordStart);
            wordStart = &line[i+1];
        }
    }

}
