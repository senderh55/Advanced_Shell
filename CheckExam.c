#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024
#define LINE_LEN 50

void Error(char* msg){
    printf(msg);
    exit(EXIT_FAILURE);
}

void main(int argc, char* argv[]){
    int fd1, fd2, fd3, rbytes1, rbytes2, i, miss = 0, num_of_questions = 0, wbytes, outputLen;
    char buff1[BUFF_SIZE], buff2[BUFF_SIZE], solTestFile[LINE_LEN], studentTestFile[LINE_LEN], outputFileName[LINE_LEN];
    
    if(argc != 3){
       Error("Must have only two parameters\n");
    }

    // open and read solution file
    strcpy(solTestFile, "Sol_");
    strcat(solTestFile, argv[1]);;
    strcat(solTestFile, ".txt");

    if((fd1 = open(solTestFile, O_RDONLY)) == -1){
        printf("%s Not Found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

     if((rbytes1 = read(fd1, buff1, BUFF_SIZE)) == -1){
        Error("Failed to read first file\n");
    }

    // open and read student answers file
    strcpy(studentTestFile, argv[2]);
    strcat(studentTestFile, "_");
    strcat(studentTestFile, argv[1]);
    strcat(studentTestFile, ".txt");

    if((fd2 = open(studentTestFile, O_RDONLY)) == -1){
          printf("%s Not Found!\n", studentTestFile);
          exit(EXIT_FAILURE);
    }

    if((rbytes2 = read(fd2, buff2, BUFF_SIZE)) == -1){
        Error("Failed to read student test file\n");
    }

    // calculate questions and misses
    while(rbytes1 > 0 && rbytes2 > 0){
        if(rbytes1 != rbytes2){
            Error("Files are not the one that requested\n");
        }
        for(i = 0; i < rbytes1; i++){
            if(buff1[i] != '\n' && buff2[i] != '\n'){
                num_of_questions++;
            }
            
            if (buff1[i] != buff2[i]){
                miss++;
            }
        }
        if((rbytes1 = read(fd1, buff1, BUFF_SIZE)) == -1){
            Error("Failed to read solution file\n");
        }
        if((rbytes2 = read(fd2, buff2, BUFF_SIZE)) == -1){
            Error("Failed to read student answers file\n");
        }
    }

        sprintf(buff1, "%d/%d",miss ,num_of_questions); 

        // create output file
        strcpy(outputFileName, "Grade_");
        strcat(outputFileName, studentTestFile);;
        
        if((fd3 = open(outputFileName, O_WRONLY | O_CREAT, 0664)) == -1){
            Error("Failed to create output file\n");
        }
        int outputlen = strlen(buff1);

        if((wbytes = write(fd3, buff1, outputlen)) == -1){
            Error("Writing error\n");
        }
        if(wbytes != outputlen){
                Error("Bad writing\n");
        } 

        close(fd1);
        close(fd2);
        close(fd3);

 }

        