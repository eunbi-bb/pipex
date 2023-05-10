# pipex

## Intorduction
Pipex is a project that focuses on understanding how UNIX mechanisms work.\
The project involves handling pipes in a manner that mimics the behavior of a shell.\
The mandatory part of the project requires handling one pipe.\
The program should behave in the same way as the shell command shown below:
```
$> < file1 cmd1 | cmd2 > file2
```
## Example
```
$> ./pipex infile "ls -l" "wc -l" outfile
```
should behave like:
```
< infile ls -l | wc -l > outfile
```
```
$> ./pipex infile "grep a1" "wc -w" outfile
```
should behave like:
```
< infile grep a1 | wc -w > outfile
```
## Functions
**pipex.c** : Generating child processes and creates files with error handling.\
**single_quotations.c** :  Combining strings into a string surrounded by single quotation marks.\
For example, it can handle the following command:
```
$> ./pipex infile "grep 'Have a nice day.'" "cat" outfile
```
**command.c** : Getting default shell commands directories through an environment pointer(char *envp[]) and check if a command is executable or not.\
**children.c** : Redirecting STDIN and STDOUT to infile and outfile. It also executes commands if they are executable.

## Usage
```
make
```
```
$> ./pipex infile 'cmd1' 'cmd2' outfile
```

