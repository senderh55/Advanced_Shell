#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
#define LINE_LEN 50

void Error(char* msg){
    printf(msg);
    exit(EXIT_FAILURE);
}

// checks if the input is in the range of the question and answer numbers 
int checkInput(int qnum, int question, int answer){
    if(question < 1 ||question > qnum || answer < 1 || answer > 4){
        printf("Wrong input - please enter question and answer in the range\n");
        return -1;
    }
    return 1;
}

void main(int argc, char* argv[]){
    int fd1, fd2, rbytes, i = 0,j = 0, wbytes, len, question, answer;
    char test[BUFF_SIZE] = "",student_answers[BUFF_SIZE], fileName[LINE_LEN] = "", num_of_questions[LINE_LEN] = "";
    int *answers_arr;

    if(argc != 3){
        Error("Must have only two parameter - the name of the test and the name of the student\n");
    }

    // open the read the input file
    strcat(fileName,argv[1]);
    strcat(fileName,".txt");
    if((fd1 = open(fileName, O_RDONLY)) == -1){
        printf("%s Not Found!\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    if((rbytes = read(fd1, test, 1024)) == -1){
        Error("Failed to read input file\n");
    }
    

    // create output file
    strcpy(fileName,argv[2]);
    strcat(fileName,"_");
    strcat(fileName,argv[1]);
    strcat(fileName,".txt");
    
     if((fd2 = open(fileName, O_WRONLY | O_CREAT, 0664)) == -1){
        Error("Failed to create the output file\n");
    }

    // get to the number of questions in to variable

    while(i < rbytes && test[i] != '\n'){ 
        i++;
    }
    i++; // skip on the \n in the exam file
     while(i < rbytes && test[i] != '\n'){ 
        num_of_questions[j++] = test[i++];
    }

    // print the test to the screen
    printf(test);
    
    // array for the order of the questions
    answers_arr = (int*) malloc(atoi(num_of_questions) * sizeof(int));
    i = 0;
    if(answers_arr == NULL){
        Error("Allocation of memory failed (answers)\n");
    }
    // enter answers to the arr (for the question order)
    printf("Insert number of question and sol:\n");
    while(i < atoi(num_of_questions)){
        scanf("%d%d", &question, &answer);
        if(checkInput(atoi(num_of_questions), question, answer) != -1){
            answers_arr[question - 1] = answer;
            i++;
        }
    }
    // collect the data for output fike
    for(i = 0;i < atoi(num_of_questions); i++){
        char question_answer[LINE_LEN];
        sprintf(question_answer,"%d\n", answers_arr[i]);
        strcat(student_answers, question_answer);
    }

    len = strlen(student_answers);
    if((wbytes = write(fd2, student_answers, len)) == -1){
        Error("Failed write to output file\n");
    }
    
    free(answers_arr);
    close(fd1);
    close(fd2);
}