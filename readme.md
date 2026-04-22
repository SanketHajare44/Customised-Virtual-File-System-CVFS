# Customised Virtual File System (CVFS)

This project is a custom implementation of a Virtual File System (VFS) that simulates
the core functionality of the Linux file system. It is built entirely in C, with its own custom
shell to interact with the virtual environment. The project provides a practical understanding
of system calls, file handling, memory management, and OS internals.

---

## Tech Stack

- Language : C
- Interface : Command Line (Custom Shell)
- Platform  : Linux / Windows

---

## What It Does

- Emulates core UNIX file system data structures in memory
- Provides a custom interactive shell with Linux-like commands
- Implements real OS system calls — `creat`, `read`, `write`, `unlink`, `stat`
- Runs on any platform without OS-level file APIs

---

## Data Structures Used

|     Structure     |                  Purpose                    |
|-------------------|---------------------------------------------|
| Inode             | Stores file metadata and data pointer       |
| Inode Table (DILB)| Linked list of all inode slots              |
| File Table        | Tracks read/write offsets for open files    |
| UAREA             | Per-process area holding the UFDT           |
| UFDT              | Maps file descriptors to File Table entries |
| Super Block       | Tracks total and free inode count           |

---

## System Calls Implemented

|   Call   |                Description                 |
|----------|--------------------------------------------|
| `creat`  | Create a new file, returns file descriptor |
| `write`  | Write N bytes into a file                  |
| `read`   | Read N bytes from a file                   |
| `unlink` | Delete a file and free its memory          |
| `stat`   | Display file metadata from inode           |
 
---

## Shell Commands

```
creat  <filename> <perm>   Create file  (perm: 1=Read  2=Write  3=Read+Write)
write  <fd>                Write data into file
read   <fd> <bytes>        Read N bytes from file
stat   <filename>          Show file information
unlink <filename>          Delete a file
ls                         List all files
man    <command>           Show usage of a command
clear                      Clear the screen
help                       List all commands
exit                       Exit the shell
```

---

## Getting Started

**Clone**
```bash
git clone https://github.com/SanketHajare44/Customised-Virtual-File-System-CVFS
cd Customised-Virtual-File-System-CVFS
```

**Build**
```bash
make
```
or manually:
```bash
gcc -Wall src/main.c src/cvfs.c -o Myexe
```

**Run**
```bash
./Myexe
```

---

## Example

```
CVFS :> creat Demo.txt 3
File 'Demo.txt' created successfully — File Descriptor : 3

CVFS :> write 3
Enter data to write :
Jay Ganesh
10 bytes written successfully

CVFS :> read 3 10
Data : Jay Ganesh

CVFS :> stat Demo.txt
 File Name      : Demo.txt
 Inode Number   : 1
 Actual Size    : 10 Bytes
 Permission     : Read Write

CVFS :> unlink Demo.txt
File 'Demo.txt' deleted successfully

CVFS :> exit
Thank you for using CVFS.
```

---

## Project Structure

```
Customised-Virtual-File-System-CVFS/
├── src/
│   ├── cvfs.c       System call implementations
│   └── main.c       Shell loop and command dispatcher
|
├── include/
│   ├── cvfs.h       Macros, structs, function prototypes
|
├── Makefile
└── README.md
```

---

## Author

**Sanket Sadashiv Hajare**  
GitHub : [Link](https://github.com/SanketHajare44)  
LinkedIn : [Link](www.linkedin.com/in/sankethajare)