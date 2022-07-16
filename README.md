# Advanced_Shell

UNIX shell upgrade - An assignment in an operating systems course.

The goal of the program is to create 6 more commands beyond the existing shell,
the additional commands are for creating, answering and testing exams.
These commands use processes and system calls such as open, read, write and exec.
'Advanced_shell.c' is the main program that use exec system call accoring to the user input.

## Commands
* CreateExam - accepts three parameters: name, subject and the writer of the exam, the command will run `CreateExam.c`.
After getting the user input for the desired number of questions, the user writes the questions with 4 answers for every question.
All the questions and the answers will be written to a text file called `examName.txt` (according to the exam name input).

* SolExam - accepts one parameter: the name of the exam, the command will run `SolExam.c`.
The program asks the user to enter the correct answer number for each question in order.
All the correct answers by questions order will be written to a text file called `SOL_examName.txt`.

* StartExam - accepts two parameters: the name of the exam and the name of the student, the command will run `StartExam.c`.
The program prints the exam to the shell, and waits for user (student) input - the number of the question and the answer option.
After the student answering on all of the questions, the input will be written to a text file called `examName_StudentName.txt`.

* CheckExam - accepts two parameters: the name of the exam and the name of the student, the command will run `CheckExam.c`.
The program compares between the student answers with the correct answers according the solution file that were created at `SolExam` command.
After comparing, the number of the currect answers of the students and the number of questions will be written to a text file called `Grade_studentName_examName.txt`

* CalcGrade - accepts two parameters: the name of the exam and the name of the student, the command will run `CalcGrade.c`.
The program open the the file that were created in CheckExam command, calculate the final score and add it to the openned file.

* Goodbye - this command will exit the Advanced shell and will return to the original shell
