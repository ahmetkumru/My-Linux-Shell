#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (atoi(argv[1]) == 0)
    { //Tekrar sayısı kontrolü.

        printf("Wrong repetition count.\n");
    }
    else
    {
        for (int i = 0; i < atoi(argv[1]); i++)
        {

            printf("%s\n", argv[0]);
        }
    }

    return 0;
}
