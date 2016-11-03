#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

//print out the file size with appropriate units
char * fileSize(off_t size) {
    char *list[5] = {"","K","M","G","T"};
    unsigned long num = size;
    int i = 0;
    if (num / 1024 > 0) {
        num /= 1024;
        i++;
    }
    char *ret = malloc(10);
    sprintf(ret, "%lu%sB",num,list[i]);
    return ret;
}

//makes a stat using path in buf, returns size from buf
//helper in print directory
int get_size(char *path) {
    
    struct stat buf;

    stat(path, &buf);

    return buf.st_size;
    
}

int print_directory(DIR *directory, int type) { //type used to determine file or directory 
    struct dirent *dir = readdir(directory); //initialize file directory
    int total = 0; //market for total byte size to be printed
    while (dir) { 
        char *name = dir->d_name; 
        int size = get_size(name); 
        total += size; 

        if (dir->d_type == type) {
            printf("%s\t%s\n", fileSize(size), name);
        }

        dir = readdir(directory);
    }
    return total;
}

int main() {
    
    char *path = "."; //"." -> meaning current director

    DIR *directory;
    directory = opendir(path);

    int fileSizeTotal = 0;
    printf("Statistics for directory:\n");
    printf("Directories:\n");
    fileSizeTotal += print_directory(directory, DT_DIR); //DT_DIR signals to print out directories

    rewinddir(directory); //reset position to go through one more time

    printf("\nFiles:\n");
    fileSizeTotal += print_directory(directory, DT_REG);//DT_REG signals to print out regular files

    printf("Total size: %s\n", fileSize(fileSizeTotal));
    
    return 0;
}