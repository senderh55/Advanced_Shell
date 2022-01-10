#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define LINE_LEN 100
#define ARGUMENTS 5 
#define SPEICIAL_COMMANDS 5

void Error(char* msg){
    printf(msg);
    exit(EXIT_FAILURE);
}

int isSpecialCommand(char* filename){
    int i;
    char* commands[SPEICIAL_COMMANDS] = {"CreateExam", "SolExam", "StartExam", "CheckExam", "CalcGrade"};
    for(i = 0; i < SPEICIAL_COMMANDS; i++){
        if(strcmp(filename, commands[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void main(){
    int id, i;
    char *arguments_arr[ARGUMENTS], path[LINE_LEN] , user_input[LINE_LEN];
    while(1){
        printf("AdvShell>");
        for(i = 0; i < ARGUMENTS; i++){
            arguments_arr[i] = NULL;
        }
        // scan and split the user input to the arguments array 
        scanf(" %[^\n]", user_input);
        arguments_arr[0] = strtok(user_input, " ");

        for(i = 1; i < ARGUMENTS; i++){
            arguments_arr[i] = strtok(NULL, " ");
        }

        // user input - "GoodBye" - exit the advanced shell
        if(strcmp(arguments_arr[0], "GoodBye") == 0){
            return;
        }
        // create child process
        if((id = fork()) == -1){
            Error("fork error\n"); 
        }       
        if(id == 0){
            //check if special command the define path according to the checking result
            if(isSpecialCommand(arguments_arr[0]) == 1){
                strcpy(path, "./");
            }
            else{
                strcpy(path, "/bin/");
            }
            //execute the child process
            strcat(path, arguments_arr[0]);
            execv(path, arguments_arr);
            printf("Not Supported\n"); // the message will be printed only in case the son process was not executed
            break;
        }
        // holds the while loop until the child process ends
        wait();
      }
   
}


       
     
     
