#define MAXBUF 256  // max number of characteres allowed on command line

// TODO: Any global variables go below

// TODO: Function declarations go below
/**
 * @param line a string to be processed
 * @param lineSize the size of line (number of characters)
 * @returns a pointer to an array of strings, with each string being a single word from line 
 * Will stop processing after lineSize-1 characters have been processed (since we assume the last char is "\0"), or a "\0" is read)
*/
char** getEachWord(char* line, int lineSize);
