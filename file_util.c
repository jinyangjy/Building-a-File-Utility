/*
This block includes the libraries that we'll be using throughout our program  
*/
#include <fcntl.h>  //needed for open()
#include <unistd.h> //needed for read() and close()
#include <stdlib.h>  //used in main function for library functions such as atoi etc...
#include <string.h>  //used in main function for strings
#include <ctype.h>   //used in is_digit function 
#include <stdbool.h> //needed library for the is_digit function


/**
 * It checks if the string is a digit.
 * 
 * @param digit the string to be checked
 * 
 * @return The function is_digit is returning a boolean value.
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

    
    /* This block of code is checking if the first argument is not null and the first character of the
    argument is a slash. If it is, then it will open the file and read it. If it is not, then it
    will display an error message. */
    if (argv[1] != NULL && argv[1][0] == '/'){
        file_descriptor_1 = open(argv[1], O_RDONLY, 0664);
        i = 2;  
        if (file_descriptor_1 < 0){
            write(1, "There is an error opening the absolute path\n", 45);
            exit(1);
        }
    }

    
    /* This block of code is checking if the path is only ./a.out or ./a.out with a path file argument,
    if it consists either one of the command lines, then it would display the first 10 words of the default
    file or the file that user wants. */
    else{
        file_descriptor_1 = open("sample.txt", O_RDONLY, 0664);
        i = 1;  
        if (file_descriptor_1 < 0){
            write(1, "There is an error opening the file\n", 36);
            exit(1);
        }
    }

    
    /* This block of code is checking if the user has not specified any arguments after the command
    line. If the user has not specified any arguments, then it will display the first 10 words of
    the default file or the file that user wants. */
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
        if (0 == strcmp(argv[i], "-a")){   
            /* This block of code is checking if the argument after -a is a path file or not. If it is
            a path file, then it will open the file and append the file. If it is not a path file, then it will display an
            error message. */
            if (argv[i+1] != NULL && argv[i+1][0] == '/'){
                file_descriptor_2 = open(argv[i+1], O_WRONLY | O_APPEND | O_CREAT, 0664);
                if (file_descriptor_2 == -1){
                    write(1, "There is an error opening the second file\n", 43);
                    exit(1);
                }
                consists_a = 1;
                i = i + 1;
            }
            /* This is an error message that will be displayed if the user has not specified a path
            file after the -a argument. */
            else{
                write(1, "Whoopsie it is an invalid argument for -a\n", 43);
                exit(1);
            }
        }

        /**
         * If the argument is -n, then the next argument should be a number, and if it is, then the
         * integer_nth is set to that number, and consists_n is set to 1
         * 
         * @param i the index of the argument
         */
        else if (0 == strcmp(argv[i], "-n")){
            if (argv[i+1] != NULL && is_digit(argv[i+1])){
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

    
    /* This block of code is checking if the user has specified the -n argument and the -a argument. If
    the user has specified the -n argument, then it will display the first n words of the default
    file or the file that user wants. */
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

        
    /* This block of code is checking if the user has specified the -a argument and the -n argument. If
    the user has specified the -a argument, then it will display the first 10 words of the default
    file or the file that user wants. */
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
        
    /* This block of code is checking if the user has specified the -a argument and the -n argument. If
        the user has specified the -a argument, then it will display the first n words of the default
        file or the file that user wants. */
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
