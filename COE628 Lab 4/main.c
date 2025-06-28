/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: hemalik
 *
 * Created on February 15, 2024, 10:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>



// Function to execute parent and child commands with a pipe
void executeCommands(char* parent_command, char* child_command);



int main(int argc, char** argv) {
    char *parent_command, *child_command;
    
    parent_command = (char *)malloc(100 * sizeof(char));
    child_command = (char *)malloc(100 * sizeof(char));

    
   
    printf("Your Command>");
    fgets(parent_command, 100, stdin);

    // Identify the pipe symbol and extract child command
    child_command = strchr(parent_command, '|') + 1;

    
    // Check for the presence of a pipe
    
    if (child_command - 1 == NULL) {
        fprintf(stderr, "No Pipe Found");
        exit(1);
    }

    // Remove leading spaces in child command
    for (; child_command[0] == ' '; child_command = child_command + 1);

    
    // Remove trailing spaces in parent command
    for (char *temp = strchr(parent_command, '|') - 1; temp[0] == ' '; temp[0] = '\0', temp--);

    // Execute commands with a pipe
    executeCommands(parent_command, child_command);

    return 0;
}

// Function to execute parent and child commands with a pipe

void executeCommands(char* parent_command, char* child_command) {
    int pd[2];

    // Create a pipe descriptor
    if (pipe(pd) < 0) {
        fprintf(stderr, "Error in creating pipe");
        exit(1);
    }

    // Fork to create a child process
    
    if (fork() == 0) {
        // Child process
        dup2(pd[0], 0); // Redirect stdin to the read end of the pipe
        close(pd[1]);   // Close the write end of the pipe
        system(child_command); // Execute the child command
        exit(0);
   
    } 
    
    else {
        // Parent process
        dup2(pd[1], 1); // Redirect stdout to the write end of the pipe
        close(pd[0]);   // Close the read end of the pipe
        system(parent_command); // Execute the parent command
    }
    
}










