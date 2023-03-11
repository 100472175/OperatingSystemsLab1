#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    // Check if the program was called with at least one argument (the input file).
    if (argc < 2) {
        printf("Too few arguments. \nUsage: %s <string> <output file>\n", argv[0]);
        return -1;
    }
    // Open the input file for reading
    int fd = open("env.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error opening file for reading env.txt\n");
        return -1;
    }

    // Open the output file, and if it already exists, it only opens it (O_CREAT),
    // and if it already exists, it truncates it (O_TRUNC)
    int fdo = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0664);
    if (fdo < 0) {
        printf("Error opening file to write %s\n", argv[2]);
        return -1;
    }

    char character; // Where the character from the file is stored temporarily
    char *linea; // Each of the lines individually processed
    char *pointer;
    int line_length = 0;
    int j;
    int correct;

    char *needle;
    // Setting up the needle we will search for
    needle = malloc(strlen(argv[1])+2);
    strncpy(needle, argv[1], strlen(argv[1]));
    strncat(needle, "=",1);

    ssize_t n;
    linea = malloc(2);
    strcpy(linea, "");

    // Reading the file where the environment variables are stored
    n = read(fd, &character, 1);
    if (n == 0){
        printf("File is empty");
        return(-1);
    }
    while (n > 0) {
        correct = 0;
        // If the character is a newline, we have reached the end of the line, so this loop will be executing until we reach the end a the line
        while ((character != '\n') && (n > 0)){
            line_length++;
            pointer = realloc(linea, strlen(linea)+2);
            linea = pointer;
            strncat(linea, (const char *) &character, 1);
            n = read(fd, &character, 1);
        }
        // Comparing the line with the needle (haystack vs needle)
        if ((strstr(linea, needle) != NULL) && (linea[0] == needle[0])){
            correct = 1;
            // Checking if the variable is the same as the needle
            for(j = 0; j < strlen(needle); j++){
                if (needle[j] != linea[j]){
                    correct = 0;
                }
            }
            if (correct == 1) {
                // If the start of the line (variable name + "=") is the same as the needle, then it is written to the output file
                if (write(fdo, linea, line_length) < line_length) {
                    perror("Writing File");
                    close(fd);
                    close(fdo);
                    exit(-1);
                }
                //Adds a new line, as the exercise was understood as all the variable with the same name
                write(fdo, "\n", 1);
                /*
                If no variables could have the same name, this exit and close functions help speeding up the
                process as if an occurrence is found, it is written, and it will exit immediately.
                This works if we only wanted one instance of the variable, as it is not the case,
                we can't use this approach
                 */
                //close(fd);
                //close(fdo);
                //exit(0);
            }
        }
        // Preparing for the next line, freeing the memory and setting the line_length to 0 and reading the next character
        free(linea);
        linea = malloc(2);
        strcpy(linea, "");
        line_length = 0;
        n = read(fd, &character, 1);
    }
    close(fd);
    close(fdo);
    return 0;
}

