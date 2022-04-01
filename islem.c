#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *innerOpArgs[4];
    int t;
    int result;

    innerOpArgs[0] = argv[0];
    innerOpArgs[1] = argv[1];
    innerOpArgs[2] = argv[2];
    innerOpArgs[3] = NULL;

    int f;
    f = fork();
    if (f == 0)
    {
        t = execv(argv[0], innerOpArgs);
        if (t<0){
                printf("Missing parametres.\n");
            }
    }
    else
    {
        int cpid = wait(&t);
        result = WEXITSTATUS(t);
        
    }

    return result;
}