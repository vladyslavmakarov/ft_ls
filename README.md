# ft_ls
Recreation of Unix command ls using C language.

### About
This is the first project from UNIX branch of School's 42 curriculum. The aim of this project
is to recreate the behaviour of UNIX command ls. The code is written in accordance
with the Norm.

### Requirements
* GNU make
* GCC

### Building the program
1. Clone the source code
2. From the root directory run `make`

### Supported flags
* G - Enable colorized output.
* R - Recursively list subdirectories encountered.
* S - Sort files by size.
* a - Include hidden directory entries (thoe which names begin with a dot (.)).
* i - For each file, print the file's file serial number (inode number).
* l - List in long format. A total sum for all the
      file sizes is output on a line before the long listing.
* o - List in long format, but omit the group id.
* r - Reverse the order of the sort to get reverse lexicographical order or
      the oldest entries first (or largest files last, if combined with sort by size
* s - Display the number of file system blocks actually used by each file.
* t - Sort by time modified (most recently modified first).

### TODO
* Fixing memory leaks
