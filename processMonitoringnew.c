//Process and activity monitor

#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define size 1000000
char headers[52][2000]={
    "pid",
    
    "comm",

    "state",

    "ppid",

    "pgrp",

    "Session ID",

    "controlling terminal",

    "tgpid",

    "flags",

    "minflt",

    "cminflt ",

    "majflt",

    "cmajflt",

    "utime",

    "stime",

    "cutime",  
                        
    "priority",

    "nice",

    "num_threads",

    "itrealve",

    "starttime",

    "vsize",

    "rss",

    "rsslim",

    "startcode",

    "endcode",

    "startstack",

    "kstkesp",

    "kstkeip",

    "signal",

    "blocked",

    "sigignore",

    "sigcatch",

    "wchan",

    "nswap",

    "cnswap",

    "exit_signal",

    "processor",

    "rt_priority",

    "policy",

    "delayacct_blkio_ticks",

    "guest_time",

    "cguest_time",

    "start_data",

    "end_data",

    "start_brk",

    "arg_start",

    "arg_end",

    "env_start",

    "env_end",

    "exit_code"
};

extern  int alphasort(); //Inbuilt sorting function

char pathname[MAXPATHLEN];

void die(char *msg)
{
  perror(msg);
  exit(0);
}

int file_select(struct direct *entry)
{
    if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
        return (FALSE);
    else
        return (TRUE);
}

void listProcesses(){
    int count,i,j,procChoice;
    struct direct **files;
    int fd,fd1;
    char buf[size],tempPath[100];
    char pid[10],pathOfProcess[20];
    
    if(!getcwd(pathname, sizeof(pathname)))
        die("Error getting pathname\n");

    //current pathname is /proc 
    strcpy(pathname,"/proc");
    strcpy(tempPath,pathname);
    printf("Currently running processes:\n");
    printf("Current Working Directory = %s\n",pathname);
    count = scandir(pathname, &files, file_select, alphasort);

    /* If no files found, make a non-selectable menu item */
    if(count <= 0)
      die("No files in this directory\n");
    
    printf("Number of files = %d\n",count);
    printf("\nPID\t Command\n");
    printf("--------------------------------------------------------------------------\n");


    for (i=1; i<count+1-57; ++i){
        strcat(tempPath,"/");
        strcat(tempPath,files[i-1]->d_name);
        strcat(tempPath,"/comm");

        if(fd = open(tempPath,O_RDONLY)){
             

            if(read(fd,&buf,sizeof(buf))){
                
                //reading commands for each process
                
            }
            
           
        }
        else{
            printf("\nError occurred while opening file.");
        }

        printf("%s\t %s\n",files[i-1]->d_name,buf);
        
        strcpy(tempPath,"/proc");
     
    }
     printf("\nEnter the PID of the process to gather information: \n");
        scanf("%s",pid);
    //opening process file
        
while(1){
        printf("\n\n1.List Basic details\n2.List all details\n3.See process stack\n4.Exit\nEnter your choice: ");
            scanf("%d",&procChoice);

    switch(procChoice){
        
    case 1: printf("Executing case 1\n");

        for(i = 0;i < size;i++){
            buf[i] = '\0';
        }
        strcpy(pathOfProcess,"/proc/");
        strcat(pathOfProcess,pid);
        strcat(pathOfProcess,"/status");
        printf("Current path : %s\n", pathOfProcess);

        if(fd = open(pathOfProcess,O_RDONLY)){
             

            if(read(fd,&buf,sizeof(buf))){
                
                printf("%s\n",buf);
                
            }
            
            else{
                printf("Zombie process.\n");
            }
           
        }
        else{
            printf("\nError occurred while opening file.");
        }
        break;

    case 2: printf("Executing case 2\n");
        
        for(i = 0;i < size;i++){
            buf[i] = '\0';
        }
        strcpy(pathOfProcess,"/proc/");
        strcat(pathOfProcess,pid);
        strcat(pathOfProcess,"/stat");
        printf("Current path : %s\n", pathOfProcess);

        if(fd = open(pathOfProcess,O_RDONLY)){
             
            if(read(fd,&buf,sizeof(buf))){
                
                j=0;

                for(i = 0;buf[i] != '\0';i++){

                    if(buf[i] == ' '){
                        printf("---->%s\n", headers[j++]);
                    }
                    else{
                        printf("%c", buf[i]);
                    }
                }
                
            }
            
            else{
                printf("Zombie process.\n");
            }
           
        }
        else{
            printf("\nError occurred while opening file.");
        }

        break;

    case 3:

       for(i = 0;i < size;i++){
            buf[i] = '\0';
        }
        strcpy(pathOfProcess,"/proc/");
        strcat(pathOfProcess,pid);
        strcat(pathOfProcess,"/stack");
        printf("Current path : %s\n", pathOfProcess);

        if(fd1 = open(pathOfProcess,O_RDONLY)){

            if(read(fd,&buf,sizeof(buf))){
                
                printf("%s\n",buf);
                
            }
           
        }
        else{
            printf("\nError occurred while opening file.");
        }
        break;

    case 4: exit(0);

    default:    printf("Wrong choice.\n");

    }
}
}

void printCPUInfo(){
    int fd;
    char buf[size],tempPath[100];
        strcpy(tempPath,"/proc");
        strcat(tempPath,"/cpuinfo");

        if(fd = open(tempPath,O_RDONLY)){
             

            if(read(fd,&buf,sizeof(buf))){
                
                printf("%s\n", buf);
                
            }
            
           
        }
        else{
            printf("\nError occurred while opening file.");
        }

}

void printMemoryInfo(){
    int fd;
     char buf[size],tempPath[100];
        strcpy(tempPath,"/proc");
        strcat(tempPath,"/meminfo");

        if(fd = open(tempPath,O_RDONLY)){
             

            if(read(fd,&buf,sizeof(buf))){
                
                printf("%s\n", buf);
                
            }
            
           
        }
        else{
            printf("\nError occurred while opening file.");
        }
}
void menu(){
    int mainChoice;
    
    //listing out the PIDs of all processes.
     printf("\n\n1.CPU info\n2.Memory info\n3.Process monitor\n4.Exit\nEnter your choice: ");
            scanf("%d",&mainChoice);
    switch(mainChoice){
    case 1: printCPUInfo();
            break;
    case 2: printMemoryInfo();
            break;
    case 3:listProcesses();
            break;
    case 4: exit(0);
     
    }

   
    printf("\n"); /* sh buffer */
}
int main()
{
    menu();
    return 0;
}