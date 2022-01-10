#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
#define LINE_LEN 50
#define ANSWERS 4

void Error(char* msg){
    printf(msg);
    exit(EXIT_FAILURE);
}

void main(int argc, char* argv[]){
    char buff[BUFF_SIZE] = "", fileName[LINE_LEN] = "", num[LINE_LEN];
    int i,j, num_of_questions, file_to, wbytes, rbytes;

    if(argc != 4){
        Error("Must have three parameters\n");
    }

    // subject of the test
    strcat(buff, argv[2]);
    strcat(buff, "\n");

    // number of questions
    printf("Insert number of questions:\n");
    scanf("%d", &num_of_questions);
    sprintf(num, "%d\n", num_of_questions); // integer to string
    strcat(buff, num);

    // print questions and answers creating menu to the screen and the inputs to the file
    for(i = 1; i <= num_of_questions; i++){
        // Question number i:
        printf("Insert Question %d:\n",i);
        char question_number[LINE_LEN];
        sprintf(question_number, " \nQuestion %d:\n   ", i);
        strcat(buff, question_number);
        char question[LINE_LEN] = "";
        getchar();
        scanf("%[^\n]", question);
        strcat(question, "\n   ");
        strcat(buff, question);
        // answers
        printf("Insert 4 answers \n");
        for(j = 1 ; j <= ANSWERS ; j++){
            char answer_number[LINE_LEN];
            printf("  %d. ", j);
            sprintf(answer_number, "  %d. ", j);
            strcat(buff, answer_number);
            char answer[LINE_LEN] = "";
            getchar();
            scanf("%[^\n]", answer);
            if(j != ANSWERS){
                strcat(answer, "\n   ");
            }
            strcat(buff, answer);
        } 
    }
    // name of the test author
    strcat(buff, "\n\nSuccessfuly\n");
    strcat(buff, argv[3]);
    strcat(buff, "\n");

    // create the output file
    int len = strlen(buff);
    strcat(fileName, argv[1]);
    strcat(fileName, ".txt");
    
    if((file_to = open(fileName, O_WRONLY | O_CREAT, 0664)) == -1){
            Error("Failed to create output file\n");
    }

     if((wbytes = write(file_to, buff, len)) == -1){
            Error("Writing error\n");
     }
    if(wbytes != len){
            Error("Bad writing\n");
    }   
    close(file_to);

}