//P1-SSOO-22/23

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>




int main(int argc, char *argv[])
{

    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("Too few arguments\n");
    	return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Error opening file %s\n", argv[1]);
        return -1;
    }

    int op= open(argv[2],O_CREAT | O_RDWR);

    if (op == -1) {
        printf("Error opening file %s\n", argv[1]);
        return -1;
    }

    char searching=argv[1];
    char buffer;
    int n;
    while ((n = read(fd, buffer, 1)) > 0) {
        ;
    }


    return 0;
}
