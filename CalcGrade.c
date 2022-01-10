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
    int fd, rbytes, wbytes, len, i = 0, j = 0;
    char buff[BUFF_SIZE], fileName[LINE_LEN], output[LINE_LEN], correct_answers[LINE_LEN] = "", num_of_questions[LINE_LEN] = "";
    int grade;

    if(argc != 3){
       Error("Must have only two parameters\n");
    }

    // open input file
    strcpy(fileName, "Grade_");
    strcat(fileName, argv[2]);
    strcat(fileName, "_");
    strcat(fileName, argv[1]);
    strcat(fileName, ".txt");

    if((fd = open(fileName, O_RDONLY)) == -1){
         printf("%s Not Found!\n", argv[1]);
         exit(EXIT_FAILURE);
    }

    if((rbytes = read(fd, buff, BUFF_SIZE)) == -1){
        Error("Failed to read check file\n");
    }

    close(fd);

    // get the number of correct answers
    while(i < rbytes && buff[i] != '/'){ 
        correct_answers[j++] = buff[i++];
    }
    i++; // skip on '/'
    // get the number of questions
    j = 0;
    while(i < rbytes && buff[i] != '\n'){ 
        num_of_questions[j++] = buff[i++];
    }
    // calculate the grade 
    grade = 100.00 * (atof(correct_answers) / atof(num_of_questions));
    sprintf(output, "\nFinal Grade: %d/100",grade);
    printf("%s\n%s%s\n", argv[2], argv[1], output);
    len = strlen(output);
    
    // open and write the grade to output file
    if((fd = open(fileName, O_WRONLY | O_CREAT, 0664)) == -1){
            Error("Failed to open output file\n");
    }
     if((lseek(fd, 0, SEEK_END)) == -1){
            Error("lseek error\n");
    }
    
    if((wbytes = write(fd, output, len)) == -1){
            Error("Writing error\n");
    }

    close(fd);

}