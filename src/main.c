#include "../include/cvfs.h"

//////////////////////////////////////////////////////////
//
//  Entry Point function of the project
//
//////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    char InputBuffer[MAXFILESIZE] = {'\0'};
    char *EmptyBuffer = NULL;

    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitilisation();

    printf("-----------------------------------------------\n");
    printf("----- Marvellous CVFS started succesfully -----\n");
    printf("-----------------------------------------------\n");
    
    // Infinite Listening Shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);
        
        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3], Command[4]);

        fflush(stdin);

        if(iCount == 1)
        {   
            // Marvellous CVFS : > exit
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            // Marvellous CVFS : > ls
            else if(strcmp("ls",Command[0]) == 0)
            {
                LsFile();
            }
            // Marvellous CVFS : > help
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }
            // Marvellous CVFS : > clear
            else if(strcmp("clear", Command[0]) == 0)
            {
                #ifdef _WIN32
                    system("cls");      // conditional preproccesing
                #else
                    system("clear");
                #endif
            }

        } // End of else if 1
        else if(iCount == 2)
        {   
            // Marvellous CVFS : > man ls
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }

            // Marvellous CVFS : > unlink Demo.txt
            if(strcmp("unlink",Command[0]) == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter\n");
                }

                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to delete as there is no such file\n");
                }

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("File gets succesfully deleted\n");
                }
            }
            // Marvellous CVFS : > write 2
            else if(strcmp("write",Command[0]) == 0)
            {
                printf("Enter the data that we want to write : \n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = WriteFile(atoi(Command[1]), InputBuffer,strlen(InputBuffer)-1);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : There is no such file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no permission\n");
                }
                else if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Unable to write as there is no space\n");

                }
                else
                {
                    printf("%d bytes gets succesfully writtened\n",iRet);
                }
            }
            else
            {
                printf("There is no such command\n");
            }

        } // End of else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > creat Ganesh.txt 3
            if(strcmp("creat",Command[0]) == 0)
            {
                iRet = CreatFile(Command[1],atoi(Command[2])); // atoi is ascii to integer

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to create the file as parameters invalid\n");
                    printf("Please refer man page\n");
                }

                if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there is no inode\n");
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file because the file is already present\n");
                }

                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("Error : Unable to create file\n");
                    printf("Error : Max opened files limit reached\n");
                }

                if(iRet >= 0)
                {
                    printf("Files gets succesfully created with FD %d\n", iRet);
                }

            }
            

            // read 3 10
            if(strcmp("read",Command[0]) == 0)
            {
                EmptyBuffer = (char *)malloc(atoi(Command[2]));

                iRet = ReadFile(atoi(Command[1]),EmptyBuffer, atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid Parameter\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FIle not exist\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Permission denied");
                }
                else if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficeint data\n");
                }
                else
                {
                    printf("Read operation is succesfully\n");
                    printf("Data from file is : %s\n",EmptyBuffer);

                    free(EmptyBuffer);
                }
            }
            else
            {
                printf("There is no such commmand\n");
            }
            
        } // End of else if 3
        else if(iCount == 4)
        {

        } // End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information\n");
        } // End of else
    } // End of while

    return 0;
} // End of main