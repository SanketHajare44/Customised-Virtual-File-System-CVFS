# Customised Virtual File System (CVFS)

A virtual file system built in C that emulates the internal working of the UNIX File System.
All data structures are maintained in RAM — no actual disk I/O involved.

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
git clone https://github.com/your-username/CustomisedVirtualFileSystem.git
cd CustomisedVirtualFileSystem
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
Marvellous CVFS :> creat Demo.txt 3
File 'Demo.txt' created successfully — File Descriptor : 3

Marvellous CVFS :> write 3
Enter data to write :
Jay Ganesh
10 bytes written successfully

Marvellous CVFS :> read 3 10
Data : Jay Ganesh

Marvellous CVFS :> stat Demo.txt
 File Name      : Demo.txt
 Inode Number   : 1
 Actual Size    : 10 Bytes
 Permission     : Read Write

Marvellous CVFS :> unlink Demo.txt
File 'Demo.txt' deleted successfully

Marvellous CVFS :> exit
Thank you for using Marvellous CVFS. Goodbye!
```

---

## Project Structure

```
CustomisedVirtualFileSystem/
├── src/
│   ├── cvfs.h       Macros, structs, function prototypes
│   ├── cvfs.c       System call implementations
│   └── main.c       Shell loop and command dispatcher
├── docs/
│   └── architecture.md
├── Makefile
└── README.md
```

---

## Author

**Sanket Sadashiv Hajare**  
GitHub : [@your-username](https://github.com/your-username)  
LinkedIn : [your-linkedin](https://linkedin.com/in/your-linkedin)