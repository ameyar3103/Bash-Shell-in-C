[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description
The C shell has been implemented as per the instructions given. For each specification, appropriate .c files(for most specifications) have been made and functions have been defined wherever necessary.

Apt text color have been used for directories and files in functions like peek and seek. The prompt text color is changed to magenta. 

Error handling is done as well.

The shell handles random spaces and tabs in the input. For compiling just run the makefile. For running, put "./a.out" on the terminal.

(1) For warp,the necessary code is present in warp.c. Note that the input is modified and checked for the command in main.c itself.

(2) For peek, all flags have been implemented and code for the same is in peek.c

(3) For pastevents, a text file pastevents.txt is created in the /home/${username}/Documents and is constantly updated and read for the pastevents command. Pastevents purge and pastevents execute have been implemented as well. Upto 15 commands are stored then the older ones are removed and newer ones are added.

(4) System commands have been implemented using execvp. Code for the same is in sys.c

(5) All background processes(upto 100) are stored in a 2-D array and their pids are checked to know if the process is completed or not and apt message is printed about the same.

(6) Proclore has been implemented as well which fetches information from the /proc folder and prints on the terminal.

(7) Seek has been implemented using a recursive algorithm that goes through the entire directory tree of the target directory and searches for the given file/directory.

(8) Prompt.c has the code that prints the apt prompt.

(9) In case a process, like sleep, takes more than 2s to complete on the foreground, the prompt does tell about the same. 

# Assumptions
(1) It has been assumed for the path to not be more than 256 bytes at some places (it can be changed to account for longer paths).

(2) There is atleast one space between command and & for background processes.

(3) The echo command prints everything ahead of it until it encounters a ';' or a newline.

(4) The seek command prints the path wrt to cwd/home directory if it finds the given file/directory.

(5) For pastevents, commands with random spaces and tabs and that without unnecessary spaces are considered the same. So they are not added again.

(6) Since the pastevents.txt is stored in /home/${username}/Documents, it is necessary that such a path does exist. So the OS has to have that.
