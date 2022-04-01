#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseWithSpace(char *commandList, char **parsedCommandList) // " " karakterine göre parçalama işlemi yapan fonksiyon.
{
    int i;

    for (i = 0; i < 100; i++)
    {
        parsedCommandList[i] = strsep(&commandList, " ");

        if (parsedCommandList[i] == NULL)
            break;
        if (strlen(parsedCommandList[i]) == 0)
            i--;
    }
}

void parseWithPipe(char *commandString, char **parsedCommandList) // "|" karakterine göre parçalama işlemi yapan fonksiyon.
{
    int i;

    for (i = 0; i < 100; i++)
    {
        parsedCommandList[i] = strsep(&commandString, "|");
        if (parsedCommandList[i] == NULL)
            break;
        if (strlen(parsedCommandList[i]) == 0)
            i--;
    }
}

int exitControl = 0; //While döngüsünden çıkış yapılmasını kontrol eden integer değişken.

void runCommands(char *argv[]) // Argümanları argüman sayısına göre çalıştırmamızı sağlayan fonksiyon.
{
    int lengthOfArgv = 0; //Gelen argümanlarımızın sayısını tutacağımız değişken.

    while (argv[lengthOfArgv] != NULL) //Argüman sayısını bulmamızı sağlayan while döngüsü.
    {

        lengthOfArgv++;
    }

    if (lengthOfArgv == 3) //Tekrar programının kontrolü ve çağrılması.
    {
        char *repArgArray[3];
        int t;

        repArgArray[0] = argv[1];
        repArgArray[1] = argv[2];
        repArgArray[2] = NULL;

        int f;
        f = fork();
        if (f == 0) //Fork kontrolü.
        {
            t = execv(argv[0], repArgArray);
            if (t < 0)
            {
                printf("Command can not find.\n");
            }
        }
        else
        {
            int cpid = wait(&t);
        }
    }
    else if (lengthOfArgv == 4) //İslem programının kontrolü ve çağırılması.
    {
        char *operationArgList[4];
        int t;
        int result = 0;

        operationArgList[0] = argv[1];
        operationArgList[1] = argv[2];
        operationArgList[2] = argv[3];
        operationArgList[3] = NULL;

         if (strcmp(argv[0], "islem") == 0)
        {
            int f;
            f = fork();
            if (f == 0) //Fork kontrolü.
            {
                int a = 0;

                t = execv(argv[0], operationArgList);
                if (t < 0)
                {
                    printf("Command can not find.\n");
                }
            }
            else
            {
                int cpid = wait(&t);
                result = WEXITSTATUS(t); //Toplama / Çıkarma programlarından dönen değer.
                if (strcmp(argv[1], "cikar") == 0)
                {
                    if (atoi(operationArgList[1]) < atoi(operationArgList[2])) //Çıkar programında negatif sonuç kontrolü.
                    {
                        printf("%s - %s = -%d\n", argv[2], argv[3], 256 - result);
                    }
                    else
                    {
                        printf("%s - %s = %d\n", argv[2], argv[3], result);
                    }
                }
                else if (strcmp(argv[1], "topla") == 0)
                {
                    printf("%s + %s = %d\n", argv[2], argv[3], result);
                }
            }
        }
        else
        {
            printf("Missing parametres.\n");
        }
    }
    else if (lengthOfArgv == 2) //Cat programının bin üzerinden çağırılması.
    {

        if (strcmp(argv[0], "cat") == 0)
        {

            //cat i cagir.
            char *catArgList[3];
            int t;

            catArgList[0] = argv[0];
            catArgList[1] = argv[1];
            catArgList[2] = NULL;

            int f;
            f = fork();
            if (f == 0) //Fork kontrolü.
            {
                t = execv("/bin/cat", catArgList);
                if (t < 0)
                {
                    printf("Command can not find.\n");
                }
            }
            else
            {
                int cpid = wait(&t);
            }
        }
        else
        {
            printf("Command Fault.\n"); // Hata fırlatma işlemi.
        }
    }
    else if (lengthOfArgv == 1)
    {
        if (strcmp(argv[0], "clear") == 0) //Clear komutu geldiği zaman bin in altındaki clear programı çalışacaktır.
        {
            //clear i cagir.
            char *otherArgList[2];
            int t;

            otherArgList[0] = argv[0];
            otherArgList[1] = NULL;

            int f;
            f = fork();
            if (f == 0)
            {
                t = execv("/bin/clear", otherArgList);
                perror("Hatalı işlem.\n");
            }
            else
            {
                int cpid = wait(&t);
            }
        }

        else if (strcmp(argv[0], "exit") == 0) //Çıkış yapılması işlemi.
        {

            exitControl = 1;
            printf("See you again :)\n");
        }

        else
        {
            printf("Command fault.\n");
        }
    }
    else
    {
        printf("You entered missing parametres.\n");
    }
}

int main(int argc, char *argv[], char **envp)
{
    char *commandLine[100]; //Komut satırını aktardığımız char array.

    char *commandList[100]; //commandLine dizisinin "|" karakterine göre parçalanmış halini aktardığımız char array.

    char *wordList[100]; //commandList dizinin elemanlarının " " karakterine göre parçalanmış halini aktardığımız char array.

    printf("****************************************************************************************************** \n");
    printf("Welcome to KUMRUBUNTU... \n");
    printf(" Command List : \n  tekrar = (tekrar yazi tekrarSayisi) \n  islem : \n   topla = (islem topla sayi1 sayi2)\n   cikar = (islem cikar sayi1 sayi2)\n  cat \n  clean \n  exit \n");
    printf("Made by Ahmet Cemalettin Kumru \n");
    printf("******************************************************************************************************\n");

    while (exitControl == 0) //exit komutu girilene kadar çalışmaya devam eden while dizisi.
    {
        printf("myshell>>");
        gets(commandLine); //Komut satırına yazdığımız karakterleri commandLine dizisi içine atma işlemi.

        parseWithPipe(commandLine, commandList); // "|" işaretine göre parçlama işlemi.

        int i = 0;
        while (commandList[i] != NULL) //commandList dizisinin eleman sayısını bulmaya yarayan while döngüsü.
        {

            i++;
        }

        for (int j = 0; j < i; j++) //commandList dizisinin elemanlarının dönülmesini sağlayan for döngüsü.
        {
            parseWithSpace(commandList[j], wordList); // elamanları " " karakterine göre parçalanması işlemi.

            runCommands(wordList); //wordList dizisindeki elemanların argüman listesine gönderilip çalıştırılması.
        }
    }

    return 0;
}
