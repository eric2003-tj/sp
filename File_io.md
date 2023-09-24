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


