# shell_pipes
Bash Pipe simulation using C
# Descreption
this is my 7th project at 1337, here we started the system calls in C, and simulate the bash pipes using those systemCalls.
this program execute commands in pipes : means it transfer the output to the next command and so on..
# usage
### 1-mandatory (one pipe)
```
$./pipex inputfile command1 command2 outputfile
```
#### ex:
```
$./pipex users.txt "cat" "wc -l" number-of-users.txt
```
### 2-bonus
#### 2.1 multiple pipes
```
$./pipex_bonus infile cmd1 cmd2 ..... cmdn outfile
```
##### ex.
```
$./pipex_bonus users.txt "cat" "awk '{print \$1}'" "uniq" "wc -l" users-names-no-duplications.txt
```
#### 2.2 heredoc
```
$./pipex here_doc LIMITER cmd1 cmd2 .......cmdn outfile
```

#####ex.
```
$./pipex_bonus here_doc END "cat" "wc -l" number-of-registred_users.txt
> Jhon Doe
> YaS Dale
> Jeany js
> Jupiter zelter
> END
$
```
