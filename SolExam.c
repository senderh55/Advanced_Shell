#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF_SIZE 256
#define LINE_LEN 50

void Error(char* msg){
    printf(msg);
    exit(EXIT_FAILURE);
}


void main(int argc, char* argv[]){
    int fd1, fd2, rbytes, i = 0,j = 0, wbytes, len;
    char buff1[BUFF_SIZE] = "",buff2[BUFF_SIZE], fileName[LINE_LEN] = "", num_of_questions[LINE_LEN] = "", answer[LINE_LEN];
    if(argc != 2){
        Error("Must have only one parameter - the name of the file\n");
    }
    // input file
    strcat(fileName,argv[1]);
    strcat(fileName,".txt");
    if((fd1 = open(fileName, O_RDONLY)) == -1){
        printf("%s Not Found!\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    // output file
    strcpy(fileName,"Sol_");
    strcat(fileName,argv[1]);
    strcat(fileName,".txt");
    
    if((rbytes = read(fd1, buff1, 256)) == -1){
        Error("Failed to read input file\n");
    }

     if((fd2 = open(fileName, O_WRONLY | O_CREAT, 0664)) == -1){
        Error("Failed to create the output file\n");
    }
    while(i < rbytes && buff1[i] != '\n'){ // get to the number of questions
        i++;
    }
    i++; // skip on the \n in the exam file
     while(i < rbytes && buff1[i] != '\n'){ // get to the number of questions
        num_of_questions[j++] = buff1[i++];
    }

    printf("Number of questions: %d\n",atoi(num_of_questions));
    for(i = 1; i <= atoi(num_of_questions); i++){
        printf("Insert True Sol for Question %d:\n", i);
        scanf("%s", answer);
        strcat(buff2,answer);
        strcat(buff2,"\n");

    }
    len = strlen(buff2);
    if((wbytes = write(fd2, buff2, len)) == -1){
        Error("Failed write to output file\n");
    }
    
    close(fd1);
    close(fd2);

}