# Building a File Utility
Building a file utility without any functions available in <stdio.h>. This means, the use of printf() to produce output will be restricted. For example, to print output in the terminal,  I've wrote to standard output directly, by using appropriate file system calls. 

In order to increase the difficulty of the task, the system() library function is restricted, and any library functions which spawns new process(s) from the program is not allowed as well. This allows us to interact with services of the operating system directly. 

Summary of all command-line arguments and their functionalities: <br />
Sourcefile  <br />
Allows user to input a path for the sourcefilee to diplay/copy. Sourcefile must appear immediateely after the command (e.g. ./filetil sourcefile) <br />
-a destfile <br />
Allows the user to input a path for thee destination file for appending thee source file. (destfile must appear immediately after -a) <br />
-n numwords <br />
Allows the usere to input a number to specify how many words of text should be displayed/ appended. (numwords must appear immediately after -n) <br />

Example Commands <br />
$ ./file_util <br />
Displays the first 10 words of the sample.txt file from the current directory /n

$ ./file_util -n 20 <br />
Displays the first 20 words of the sample.txt file from the current directory

$ ./file_util /home/student/dir1/sample2.txt <br />
Displays the first 10 words of the a.txt file

$ ./file_util /home/student/dir1/sample2.txt -n 20 <br />
Displays the first 20 words of the a.txt file

$ ./file_util /home/student/dir1/sample2.txt -a /home/student/dir2/sample3.txt <br />
append first 10 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 10 words of the a.txt should be copied to it. 

$ ./file_util /home/student/dir1/sample2.txt -a /home/student/dir2/sample3.txt -n 15 <br />
append first 15 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 15 words of the a.txt should be copied to it. 

$ ./file_util -a /home/student/dir2/sample3.txt <br />
Append the first 10 lines of sample.txt from the current directory to b.txt
 
$ ./file_util /home/student/dir1/sample2.txt -n <br />
Invalid argument, no line numbers specified after the -n argument!

$ ./file_util /home/student/dir1/sample2.txt -n 15 -a /home/student/dir2/sample3.txt <br />
append first 15 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 15 words of the a.txt should be copied to it.

$ ./file_util /home/student/dir1/sample2.txt -a /home/student/dir2/sample3.txt -n 15 <br />
append first 15 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 15 words of the a.txt should be copied to it.

