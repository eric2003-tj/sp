# Homework 1

## Q1

```
  Assume there are m files
  for (i = 1 to m){
    if(mode == "--append"){
        fd_i = open(args[i],O_APPEND) // fd_i means the ith file descriptor
    }else{
        fd_i = open(args[i],O_RDWR)
    }
  }
  while((n=read(STDIN_FILENO,buffer,buffer_size)>0)){
    for(i = 1 to m){
        if (mode == "--append"){
            lseek(fd_i,0,SEEK_END)
        }
        write(fd_i,buffer,buffer_size);
    }
    write(1,buffer,buffer_size) //write to stdout
  }
  for (i = 1 to m){
    close(fd_i)
  }

```