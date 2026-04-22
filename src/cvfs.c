#include "../include/cvfs.h"

//////////////////////////////////////////////////////////
//
//  Global variables or objects used in the project
//
//////////////////////////////////////////////////////////

struct BootBlock bootobj;
struct SuperBlock superobj;
struct UAREA uareaobj;
PINODE head = NULL;


//////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseUAREA
//  Description :       It is used to initialise UAREA members
//  Author :            Sanket Sadashiv Hajare
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////

void InitialiseUAREA()
{
   strcpy(uareaobj.ProcessName,"Myexe");
   
   int i = 0;

   for(i = 0; i < MAXOPENFILES; i++)
   {
        uareaobj.UFDT[i] = NULL;
   }
    printf("Marvellous CVFS : UAREA gets initialised succesfully\n");
}

//////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseSuperBlock
//  Description :       It is used to initialise Super block members
//  Author :            Sanket Sadashiv Hajare
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super block gets initialised succesfully\n");
}

//////////////////////////////////////////////////////////
//
//  Function Name :     CreateDILB
//  Description :       It is used to create Linkedlist of inodes
//  Author :            Sanket Sadashiv Hajare
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)    // LL is empty
        {
            head = newn;
            temp = head;
        }
        else                // LL contains atleast 1 node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }

    printf("Marvellous CVFS : DILB created succesfully\n");
}

//////////////////////////////////////////////////////////
//
//  Function Name :     StartAuxillaryDataInitilisation
//  Description :       It is used to call all such functions which are
//                      used to initialise auxillary data
//  Author :            Sanket Sadashiv Hajare
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////

void StartAuxillaryDataInitilisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");

    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary data initialised succesfully\n");
}

//////////////////////////////////////////////////////////
//
//  Function Name :     DisplayHelp
//  Description :       It is used to display the help page
//  Author :            Sanket Sadashiv Hajare
//  Date :              14/01/2026
//
//////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-----------------------------------------------\n");
    printf("---------- Marvellous CVFS Help Page ----------\n");
    printf("-----------------------------------------------\n");

    printf("man    : It is used to display manual page\n");
    printf("clear  : It is used to clear the terminal\n");
    printf("creat  : It is used to create new file\n");
    printf("write  : It is used to write the data into file\n");
    printf("read   : It is used to read the data from the file\n");
    printf("stat   : It is used to display statistical information\n");
    printf("unlink : It is used to delete the file\n");
    printf("exit   : It is used to terminate Marvellous CVFS\n");

    printf("-----------------------------------------------\n");

}

//////////////////////////////////////////////////////////
//
//  Function Name :     ManPageDisplay
//  Description :       It is used to display man page
//  Author :            Sanket Sadashiv Hajare
//  Date :              14/01/2026
//
//////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name) == 0)
    {
        printf("About : It is used to list the names of all files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp("man",Name) == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");        
    }
    else if(strcmp("exit",Name) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");        
    }
    else if(strcmp("clear",Name) == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");        
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }
}

//////////////////////////////////////////////////////////
//
//  Function Name :     IsFileExist
//  Description :       It is used to check whether file is already exist or not
//  Input :             It accept file name
//  Output :            It returns the true and false
//  Author :            Sanket Sadashiv Hajare
//  Date :              16/01/2026
//
//////////////////////////////////////////////////////////

bool IsFileExist(
                    char *name          // File name
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }

        temp = temp->next;
    }

    return bFlag;
}

//////////////////////////////////////////////////////////
//
//  Function Name :     CreatFile
//  Description :       It is used to create new regular file
//  Input :             It accept file name and permissions
//  Output :            It returns the file descriptor
//  Author :            Sanket Sadashiv Hajare
//  Date :              16/01/2026
//
//////////////////////////////////////////////////////////

int CreatFile(
                char *name,         // Name os new file 
                int permissions     // Permission for that file
             )
{
    PINODE temp = head;
    int i = 0;

    printf("Total number of inodes remaining : %d\n", superobj.FreeInodes);

    // If name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if(permissions < 1 || permissions > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If inodes are full 
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // If file is already present
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search empty Inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)                    // singly linear linked list is used that's why the last node points to the NULL
    {
        printf("There is no Inode\n");
        return ERR_NO_INODES;
    }

    // Search for empty UFDT entry
    // Note : 0,1,2 are reserved
    for(i = 3; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is full
    if(i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialize file table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permissions;

    // Connect File Table with Inode
    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permissions;

    // Allocate memory for files data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char * )malloc(MAXFILESIZE);

    superobj.FreeInodes--;

    return i;       // File Descriptor (fd)
}

//////////////////////////////////////////////////////////
//
//  Function Name :     LsFile
//  Description :       It is used to list all files
//  Input :             Nothing
//  Output :            Nothing
//  Author :            Sanket Sadashiv Hajare
//  Date :              16/01/2026
//
//////////////////////////////////////////////////////////

// ls -l
void LsFile()
{
    PINODE temp = head;

    printf("-----------------------------------------------\n");
    printf("------Marvellous CVFS Files Information--------\n");
    printf("-----------------------------------------------\n");

    while(temp != NULL)
    {   
        if(temp->FileType != 0)
        {
            printf("%d\t%s\t%d\t\n", temp->InodeNumber, temp->FileName, temp->ActualFileSize);
        }
        
        temp = temp->next;
    }

    printf("-----------------------------------------------\n");

}

//////////////////////////////////////////////////////////
//
//  Function Name :     UnlinkFile
//  Description :       It is used to delete the File
//  Input :             File Name
//  Output :            Nothing
//  Author :            Sanket Sadashiv Hajare
//  Date :              22/01/2026
//
//////////////////////////////////////////////////////////

int UnlinkFile(
                char *name
              )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExist(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Travel the UFDT
    for(i = 0; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName, name) == 0)
            {
                // Deallocate memory of Buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);
                uareaobj.UFDT[i]->ptrinode->Buffer = NULL;

                // Reset All values of inode
                // Dont deallocate memory of inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;

                memset(uareaobj.UFDT[i]->ptrinode->FileName, '\0', sizeof(uareaobj.UFDT[i]->ptrinode->FileName));

                // Deallocate memory of FileTable
                free(uareaobj.UFDT[i]);

                // Set NULL to UFDT
                uareaobj.UFDT[i] = NULL;

                // Increment free inode count
                superobj.FreeInodes++;

                break;                              // IMP


            }// End of if
        }// End of if
    }// End for loop

    return EXECUTE_SUCCESS;

}// End of UnlinkFile

//////////////////////////////////////////////////////////
//
//  Function Name :     WriteFile()
//  Description :       It is used to write  the data into the file
//  Input :             File descriptor
//                      Address of buffer which contains data
//                      Size of data that we want to write
//  Output :            Number of bytes succesfully writened
//  Author :            Sanket Sadashiv Hajare
//  Date :              22/01/2026
//
//////////////////////////////////////////////////////////

int WriteFile(
                int fd,
                char *data,
                int size
             )
{
    printf("File descriptor : %d\n",fd);
    printf("Data that we want to write : %s\n",data);
    printf("Number of bytes that we want to write : %d\n",size);

    // Invalid fd
    if(fd < 0 || fd >= MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // fd points to NULL
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // There is no permission to write
    if(!(uareaobj.UFDT[fd]->ptrinode->Permission & WRITE))
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficent space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    // Write the data into file
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]-> WriteOffset, data, size);

    // Update the write offset
    uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size;

    // Update the actual file size
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}

//////////////////////////////////////////////////////////
//
//  Function Name :     ReadFile()
//  Description :       It is used to read  the data from the file
//  Input :             File descriptor
//                      Address of empty buffer 
//                      Size of data that we want to read
//  Output :            Number of bytes succesfully read
//  Author :            Sanket Sadashiv Hajare
//  Date :              22/01/2026
//
//////////////////////////////////////////////////////////

int ReadFile(
                int fd,
                char *data,
                int size
)
{
    // Invalid fd
    if(fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(data == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(size < 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    //  Filter for permission
    if(!(uareaobj.UFDT[fd]->ptrinode->Permission & READ))
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficeint data
    if((uareaobj.UFDT[fd]->ptrinode->ActualFileSize - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    // Read the data
    strncpy(data,uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset, size);

    // Update the read offset
    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;

    return size;

}