//P1-SSOO-22/23

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    // Checking if there are too many arguments, as the program can take 1 argument or none from the user (Path)
    if (argc > 2) {
        printf("Too many arguments.\n");
        return -1;
    }

    //char * path;
    char cwd[PATH_MAX];
    // If there is a path passed to the program, then, that will be the path
    if (argc == 2){
        //path = malloc(strlen(argv[1])+1);
        strcpy(cwd, argv[1]);
    }
    else{
        //path = malloc(PATH_MAX);
        getcwd(cwd, PATH_MAX);
        //strcpy(path, cwd);
    }
    // printf("%s\n", path);
    DIR *pDir;
    struct dirent *pDirent;

    pDir = opendir(cwd);
    if (pDir == NULL) {
        printf("Cannot open directory '%s'\n", cwd);
        return -1;
    }
    while ((pDirent = readdir(pDir)) != NULL) {
        printf("%s\n", pDirent->d_name);
    }
    closedir (pDir);
    return 0;
}
