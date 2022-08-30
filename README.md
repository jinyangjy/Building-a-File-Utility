# Building a File Utility
Building a file utility without any functions available in <stdio.h>. This means, the use of printf() to produce output will be restricted. For example, to print output in the terminal,  I've wrote to standard output directly, by using appropriate file system calls. 

In order to increase the difficulty of the task, the system() library function, and any library functions which spawns new process(s) from the program. This allows us to interact with services of the operating system directly. 


Example Commands

$ ./fileutil
Displays the first 10 words of the sample.txt file from the current directory /n

$ ./fileutil -n 20
Displays the first 20 words of the sample.txt file from the current directory

$ ./fileutil /home/student/dir1/a.txt
Displays the first 10 words of the a.txt file

$ ./fileutil /home/student/dir1/a.txt -n 20
Displays the first 20 words of the a.txt file

$ ./fileutil /home/student/dir1/a.txt -a /home/student/dir2/b.txt
append first 10 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 10 words of the a.txt should be copied to it. 

$ ./fileutil /home/student/dir1/a.txt -a /home/student/dir2/b.txt -n 15
append first 15 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 15 words of the a.txt should be copied to it. 

$ ./fileutil -a /home/student/dir2/b.txt
Append the first 10 lines of sample.txt from the current directory to b.txt
 
$ ./fileutil /home/student/dir1/a.txt -n
Invalid argument, no line numbers specified after the -n argument!

$ ./fileutil /home/student/dir1/a.txt -n 15 -a /home/student/dir2/b.txt
append first 15 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 15 words of the a.txt should be copied to it.

$ ./fileutil /home/student/dir1/a.txt -a /home/student/dir2/b.txt -n 15
append first 15 words in a.txt to the end of b.txt. If b.txt does not exist, a new b.txt should be created and first 15 words of the a.txt should be copied to it.


