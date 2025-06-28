/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: hemalik
 *
 * Created on February 2, 2024, 10:13 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

void executeCommand(char* command, int waitFlag);

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
     
        printf("Your command> ");

        
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        int waitFlag = 1; 


        char *ampersandPosition = strchr(command, '&');
        if (ampersandPosition != NULL && (ampersandPosition == command || ampersandPosition[-1] != ' ')) {
            waitFlag = 0; 
            *ampersandPosition = '\0'; 
        }

      
        if (strcmp(command, "exit") == 0) {
            printf("Exiting the shell. Goodbye!\n");
            break;
        }

    
        executeCommand(command, waitFlag);
    }

    return 0;
}

void executeCommand(char* command, int waitFlag) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        char* args[MAX_COMMAND_LENGTH];
        char* token = strtok(command, " ");

        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the arguments array

        execvp(args[0], args);
        
        
        perror("Exec failed");
        exit(1);
    } else {
        // Parent process
        if (waitFlag) {
         
            int status;
            waitpid(pid, &status, 0);
            
            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else {
                printf("Child process terminated abnormally\n");
            }
        }
    }
}

