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

