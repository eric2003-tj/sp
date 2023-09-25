# System programming File_io

## Categories

1. unbuffered IO  functions invokes stsyem calls to the kernel each time.
2. buffered IO  functions accumulate results in intermediate buffers,not making system calls each time.

Note: There are still buffers in unbuffered IO, but they are managed by kernel.

## About file

1. File contents are stored in the disk.
2. The metadeta that contains file information such as file permission and where file content is stored on the disk.

## File Descriptors

The Unix Kernel refers to an open file using file descriptor:

1. A non-negative integer ranges from 0 to OPEN_MAX-1;OPEN_MAX specifies the maximum number of files that one process can open at a time.
2. The kernel manages a file descriptor table for each process and allocates file descriptor.
3. The file descriptors are per-process; different processes may have the same file descriptor.
4. The numbers 0,1,and 2, also maps to constants: STDIN_FILENO,STDOUT_FILENO,and STDERR_FILENO.(The constants are defined in <unistd.h>).

<img src = "https://github.com/eric2003-tj/sp/blob/main/file%20descriptor.png" />

## open and openat

```
#include <fcntl.h>
// For both functions, the file descriptor is returned on a successful call; and -1 is returned on an error
int open(const char* path,int oflag,...../*mode_t mode*/);
int openat(int fd,const char* path,int oflag,...../*mode_t mode*/);
```
On a successful call, the returned file descriptor will be the lowest-numbered file descriptor not currently opened by the process.

**open**

1. path is the path of the file to open or create.
2. oflag is to specify the "access modes".
3. mode specifies the file mode bits(What permission does the user get) to be applied only when a new file is created; it is otherwise omitted.
<img src = "https://github.com/eric2003-tj/sp/blob/main/mode.png" />

**openat**

openat() operates exactly the same way as open() except that the fd parameter is used in conjunction with the path argument.  
1. If path is absolute, fd can be ignored.
2. If path is relative:need to assign a fd. (AT_FDCWD is current working directory)

## close

```
#include <fcntl.h>
int close(int fd);
```
## creat

```
#include <fcntl.h>
int creat(const char*path,mode_t mode);
```
A file is created and opened write-only by creat function. It is obsolete now.

## Unix kernel support for File_io
<img src = "https://github.com/eric2003-tj/sp/blob/main/kernel_support.png" />

The Unix OS kernel uses three data structures to represent an open file. The relationships among them determine the effect one process has on the another.

**open file descriptor table(per_process)**

one entry per each file descriptor, each entry contains:

1. The file descriptor flag
2. A pointer to a system open file table entry

**open file table**

each entry contains:

1. The file status flag for the file (read/write/append/sync/nonblocking)
2. current file offset
3. A pointer to the v-node table entry for the file

**V-node table**

each entry contains a V-node data structure that contains:

1. The pointer to the i-node structure of the file in memory (read from disk when the file is opened)
2. V-node information

**I-node**

I-node is both stored physically on the storage device and in-memory:

1. Contains the metadata about the file: file owner, file size, residing device, protection information,locations of the data blocks comprising a file
2. The OS kernel reads the I-node from the disk to memory when the associated file is opened

<img src = "https://github.com/eric2003-tj/sp/blob/main/node.png" />

## offset

An integer that counts the number of bytes from the start of the file. The value of the offset must be positive,however,some devices allow negative bytes.  By default,the offset is initiallized as 0 when the file is opened unless using append mode.  Read and write will increment the offset of the file.

## lseek

```
#include <unistd.h>
off_t lseek(int fd,off_t offset,int whence);
```

An open file's current offset can be set via lseek function.

**lseek_parameters**

1. fd is the file descriptor of the target file.
2. whence determines the interpretation of the offset parameter, can be set to three values:

$\qquad$ 1. SEEK_SET: the file’s offset is set to offset bytes from the beginning of the file  
$\qquad$ 2. SEEK_CUR: the file’s offset is set to its current value plus the offset (offset can be positive or negative)  
$\qquad$ 3. SEEK_END: the file’s offset is set to the size of the file plus the offset (offset can be positive or negative)

**Whether stdandard input is capable of seeking**

For a program like this: 

```
#include <unistd.h>
int main(){
  if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
    printf("fail\n");
  }else{
    printf("success\n");
  }
}
```

Below command will work:

```
./a.out < test.txt
```

Below cannot:

```
cat test.txt | ./a.out
```

pipe, FIFO, and socket can not work!


## read

```
#include <unistd.h>
ssize_t read(int fd,void *buf,size_t buffersize);
```

Data is read via fd into buf.The read operation starts at the current offset,and it will be increased by the number of bytes actually read.

## write

```
#include <unistd.h>
ssize_t write(int fd,void *buf,size_t buffersize);
```

Buf is written to the file via fd. And it will return the number of bytes that are actually written. It still starts at the current offset, and it will be increased by the number of bytes written in the file.  If the O_APPEND option was specified when the file was opened, the file’s offset is set to the current end of file before each write operation.

## Atomic operation

Since different processes may access the same file, it will intefere the change of the file. For example, assume below code is executed by two processes:

```
if (lseek(fd, 0, SEEK_END) < 0) err_sys(“lseek error”);
if (write(fd, buf, 100) != 100) err_sys(“write error”);
```

If below situation happens,
<img src = "https://github.com/eric2003-tj/sp/blob/main/process.png" />

Then the what we wrote in process B will be overwritten.  AAtomic operations are the operations that execute as a single unified operation. In simple terms, when an atomic operation is being executed, no other process can read through or modify the data that is currently used by atomic operation.

