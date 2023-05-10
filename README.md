# pipex
Discover in detail a UNIX mechanism.

## Intorduction
Pipex project is about handling pipes as shell behaves.\
In the mandatory part of the project, Handling a pipe with 2 child processs.\
It must behave exactly the same as the shell command below :
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
**pipex.c** : Generating child processes and creating files with error handlings.\
**single_quotations.c** :  Combining strings to a string that are surronded by single quotation marks.
for example, to operate below case :
```
$> ./pipex infile "grep 'Have a nice day.'" "cat" outfile
```
**command.c** : Getting default shell commands directories through an environment pointer(char *envp[]) and check if a command is executable or not.\
**children.c** : Redirecting STDIN and STDOUT to infile and outfile. Executing commands if it is executable.

## Usage
```
make
```
```
$> ./pipex infile 'cmd1' 'cmd2' outfile
```

