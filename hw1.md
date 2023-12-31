# Homework 1

## Q1

```
  Assume there are m files
  for (i = 1 to m){
    if(OPTION == "--append" || OPTION == "-a"){
        fd_i = open(args[i],O_APPEND) // fd_i means the ith file descriptor
    }else{
        fd_i = open(args[i],O_RDWR)
    }
  }
  while((n=read(STDIN_FILENO,buffer,buffer_size)>0)){
    for(i = 1 to m){
        write(fd_i,buffer,buffer_size);
    }
        write(1,buffer,buffer_size) //write to stdout
  }
  for (i = 1 to m){
    close(fd_i)
  }

```

In this question, I opened every assigned files first using open function which taught in class and assigned every file to a fd_i. Here, I used an "if-statement" to check whether the file's mode was append or not.
Then, I used a read function to read input from stdin, and then use lseek function to make sure that the input will be written to correct position.Finally, I used close function to close the file.

## Q2

**2.1**

```
./a.out > outfile 2>&1
```

Initiallty, ">" means that we redirects stdout(1) to outfile(file descriptor 1 points to the entry that corresponds to outfile in open table). Then, "2>&1" means that we redirects stderr(2) to where stdout(1) directs to, thus, stderr will be redirected to outfile(file descriptor 2 points to the entry that corresponds to outfile in open table). outfile will have both stdout and stderr messages. 

```
./a.out 2>&1 > outfile
```

"2>&1" means that we redirects stderr(2) to where stdout(1) directs to, thus, stderr will be redirected to terminal(file descriptor 2 points to the entry that corresponds to stdout in open table). Then ">" means we redirect stdout(1) to outfile(file descriptor 1 points to the entry that corresponds to outfile in open table), thus, outfile will have stdout message.

**2.2**

If I want to compile a "main.c" file and I do not want to see error messages in terminal if they exist. Then I can use 2>&1 to redirect the message to other files.

Ex: gcc main.c > outfile 2>&1

## Q3

**3.1**
No  
If a file is opened with append mode, it can not change writing location even eith using lseek.

**3.2**
No  
It may lead to same directory.(/)

**3.3**
Yes

**3.4**
Yes

**3.5**
Yes

Reference

1. https://www.ibm.com/docs/en/aix/7.2?topic=f-fcntl-dup-dup2-subroutine
2. https://segmentfault.com/a/1190000040086046

