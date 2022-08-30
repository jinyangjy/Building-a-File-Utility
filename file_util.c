/*
This block includes the libraries that we'll be using throughout our program  
*/
#include <fcntl.h>  //needed for open()
#include <unistd.h> //needed for read() and close()
#include <stdlib.h>  //used in main function for library functions such as atoi etc...
#include <string.h>  //used in main function for strings
#include <ctype.h>   //used in is_digit function 
#include <stdbool.h> //needed library for the is_digit function


/*
This block of code helps us to identify within the command line with -n if it is an integer, because -n states
 the amount of words we should display, and it would be an integer (e.g. ./a.out -n 20) <- the integer 20 is an
 integer.

 We're utilising the library ctype.h within this block, which we're iterating through the array to identify if
 each character is a digit itself. Therefore, if there's an integer within the command line then it will be TRUE
 after each character in the array has been iterated. If there's no integer within the command line, then it will
 be FALSE, after each character in the array has been iterated. 
*/
bool is_digit(char digit[]){
    int i = 0;
    for (i; digit[i] != 0; i++){
        if(!isdigit(digit[i])){
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]){

    int file_descriptor_1;
    int file_descriptor_2;    //variables for file descriptors
    int i;
    int counter;
    int tracker_for_the_last_word;      /*Variables included within the loop to check every argument.
                                     Counter is for counting and also checking the number of words within the variable.
                                       tracker_for_the_last_word tracks the last word of the variable.*/
    int integer_nth;         //When -n is used we will display till the nth word
    int consists_a;
    int consists_n;     // We'll check if it consists of -a and -n within the command line

    char variable[1024];   //buffer for reading the entire file content, which has been set to 1024 based on lab 2

    //check first argument whether is a path or not //task2
    if (argv[1] != NULL && argv[1][0] == '/'){
        file_descriptor_1 = open(argv[1], O_RDONLY, 0664);
        i = 2;  //if the first position is a pathfile, i is equated to 2 because for the upcoming for loop, the program
        //does not need to care about the first argument anymore
        if (file_descriptor_1 < 0){
            write(1, "There is an error opening the absolute path\n", 45);
            exit(1);
        }
    }
    /*if the first argument is null or the first character of the argument is not a slash, then we'll open the
    default file */
    else{
        file_descriptor_1 = open("sample.txt", O_RDONLY, 0664);
        i = 1;  //if the first position is not a pathfile, for -a or -n as the starting positions, then we'll need to
        // loop through the entire argument.
        if (file_descriptor_1 < 0){
            write(1, "There is an error opening the file\n", 36);
            exit(1);
        }
    }

    /* This block of code, is checking if the path is only ./a.out or ./a.out with a path file argument, if it consists
     either one of the command lines, then it would display the first 10 words of the default file or the file that
     user wants. */
    if (argc < 3){
        read(file_descriptor_1, variable, sizeof(variable));
        counter = 0;
        for (int j = 0; j < sizeof(variable); j++){
            if (variable[j] == ' ' || variable[j] == '\n'){
                counter++;
                tracker_for_the_last_word = j;
            }
            if (counter == 10){
                variable[tracker_for_the_last_word] = '\n';
                write(1, variable, tracker_for_the_last_word+1);
                break;
            }
        }
        if (counter < 10){
            write(1, variable, strlen(variable));
        }
    }

    for (i; i < argc; i++){
        if (0 == strcmp(argv[i], "-a")){   //if it is 0 at return from the comparison, then argv[i] is = 0 because of -a
            /* i + 1 states the next argument after -a because it is a path file, and the next argument is '/', continuosly 
               written along with the path directory. */
            if (argv[i+1] != NULL && argv[i+1][0] == '/'){
                file_descriptor_2 = open(argv[i+1], O_WRONLY | O_APPEND | O_CREAT, 0664);
                if (file_descriptor_2 == -1){
                    write(1, "There is an error opening the second file\n", 43);
                    exit(1);
                }
                //if the above condition is met then consists_a is equals to 1, and we skip the argument for -a
                //and check for the next argument
                consists_a = 1;
                i = i + 1;
            }
                //so in this else condition if i + 1 is equals then we have a huge problem
            else{
                write(1, "Whoopsie it is an invalid argument for -a\n", 43);
                exit(1);
            }
        }
            //similar to the argument above, but this time round we're checking if argv[i] is = 0 because of "-n"
        else if (0 == strcmp(argv[i], "-n")){
            //i+1 states the next argument after -n because it is a path file, and it is a number after the number n
            if (argv[i+1] != NULL && is_digit(argv[i+1])){
                //changing string to integer
                integer_nth = atoi(argv[i+1]);
                i = i + 1;
                consists_n = 1;
            }
            else{
                write(1, "Whoopsie it is an invalid argument for, there's no line number specified after the -n argument\n", 97);
                exit(1);
            }
        }
    }

    /* condition to check if '-a' does not exist and '-n' exists within the command line given by the user. So the loop
     will be looping through the entire the given text file and it'll check how many words are within it, and it will
     be displaying the words by the integer stated after -n. */
    if (1 != consists_a && 1 == consists_n){
        read(file_descriptor_1, variable, sizeof(variable));
        counter = 0;
        for (int j = 0; j < sizeof(variable); j++){
            if (variable[j] == ' ' || variable[j] == '\n'){
                counter ++;
                tracker_for_the_last_word = j;
            }
            if (counter == integer_nth){
                variable[tracker_for_the_last_word] = '\n';
                write(1, variable, tracker_for_the_last_word+1);
                break;
            }

        }
        if (counter < integer_nth){
            write(1, variable, strlen(variable));
        }
    }

        /*condition to check if '-a' exists and '-n' does not exist, which meannnnsssss we'll have to append only, based
        on the user's command. So the loop will be looping through the entire the given text file and it'll check how
        many words are within it, and it will be appending words towards a text file and notifying user it has been
        appended. */
    else if(1 == consists_a && 1 != consists_n){
        read(file_descriptor_1, variable, sizeof(variable));
        counter = 0;
        for (int j = 0; j < sizeof(variable); j++){
            if(variable[j] == ' ' || variable[j] == '\n'){
                counter++;
                tracker_for_the_last_word = j;
            }
            if (counter == 10){
                variable[tracker_for_the_last_word] = '\n';
                write(file_descriptor_2, variable, tracker_for_the_last_word+1);
                write(1, "Yay it has been appended\n", 26);
                break;
            }
        }
        if (counter < 10){
            write(file_descriptor_2, variable, strlen(variable));
            write(1, "Yay it has been appended\n", 26);
        }
    }
        /*condition to check if both '-a' and '-n' exists within the command line. So the loop will be iterating through
         the entire given text file to the stated number of words state on the -n 'number', which then we'll append a
         given text onto it. */
    else if(1 == consists_a && 1 == consists_n){
        read(file_descriptor_1, variable, sizeof(variable));
        counter = 0;
        for (int j = 0; j < sizeof(variable); j++){
            if(variable[j] == ' ' || variable[j] == '\n'){
                counter++;
                tracker_for_the_last_word = j;
            }
            if (counter == integer_nth){
                variable[tracker_for_the_last_word] = '\n';
                write(file_descriptor_2, variable, tracker_for_the_last_word+1);
                write(1, "Yay it has been appended\n", 26);
                break;
            }
        }
        if (counter < integer_nth){
            write(file_descriptor_2, variable, strlen(variable));
            write(1, "Yay it has been appended\n", 26);
        }
    }

    close(file_descriptor_1); // closing the file_descriptor_1
    close(file_descriptor_2); // closing the file_descriptor_2
    return 0;
}
