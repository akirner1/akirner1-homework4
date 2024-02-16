#define MAXBUF 256  // max number of characteres allowed on command line

// TODO: Any global variables go below

// TODO: Function declarations go below
/**
 * @param line a string to be processed. This string will be destroyed, and the memory will be freed upon execution.
 * @param lineSize the size of line (number of characters)
 * @returns a pointer to an array of strings, with each string being a single word from line. It will contain a null pointer in the element after, representing the end of the array
 * Will overrite the final element of line with '\0', and will also only process up to the first '\0'
*/
char** getEachWord(char* line, int lineSize);


/**
 * @param cmd the string of the command attempted to be run
 * @param expected the string of the command we are expecting to run
 * @returns true if cmd is as expected, false if it's not
*/
int isCommand(char* cmd, char* expected);

/**
 * @param rawPath either an full path beginning with '/', or unconstructed path, not beginning with '/'. rawPath will be destroyed and freed during execution
 * @param workingDir the path of the current working directory
 * @returns a pointer to a string containing the exact path, ready to be executed.
 * @returns NULL if the path is invalid
*/
char* constructPath(char* rawPath, char* workingDir);


/**
 * @param args the array of arguments given by the user, terminating with a null pointer
 * replaces each string beginning in a "$" with the environment variable of the corresponding name
*/
void decodeEnviromentVars(char** args);

/**
 * @param args the list of arguments provided to the code
 * @return 1 if operation should be done in the foreground, and 0 if it should be done in the background
 * will also remove the & character from the end of the args if it is there
*/
int checkForeground(char** args);