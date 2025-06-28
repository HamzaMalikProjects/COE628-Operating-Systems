#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 
#define TOO_MANY_ARGS 2
#define TOO_FEW_ARGS 1

int main(int argc, char* argv[]) {
    //Default values:
    int exit_code = EXIT_SUCCESS;
    char * greeting = "Hello";
    char * person = "UNKNOWN";
   
    if (argc == 1) {
        exit_code = 0;
    } 
    else if (argc > 2) {
        exit_code = 1;
         
    } 
    if (argc > 1) {
        person = argv[1];
    }


    int len = strlen(argv[0]);
    char * last3 = argv[0] + len - 3; 
    fprintf(stderr, "%s\n", argv[0]);
    fprintf(stderr, "%s\n", last3);

    //Add code to change 'greeting' if last 3 chars of command are 'bye'
    if (strcmp(last3, "bye") == 0) {
        greeting = "bye";
    }

    printf("%s %s\n", greeting, person);

    fprintf(stderr, "exit_code: %d\n", exit_code);

    return exit_code; //Could also say exit(exit_code)
}