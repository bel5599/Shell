#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int cantcomad = 0;
int Control;
int true = 0;
int false = -1;
int PidEject;

int CD(char *dir) //cd
{
    //if(arg[0] == NULL)
    //return 0;
    //if (chdir(arg[1]) == -1)
    if (chdir(dir) == -1)
    {
        perror("cd");
        return -1;
    }
    return 0;
}

int Help(char *arg) //Help
{
    FILE *fd;

    if (strcmp(arg, " "))
    {
        fd = fopen("Help", "r");
    }
    else if (strcmp(arg, "basic") == 0 || strcmp(arg, "spaces") == 0)
    {
        fd = fopen("Help_Basic", "r");
    }
    else if (strcmp(arg, "multi-pipe") == 0)
    {
        fd = fopen("Help_MultiPipe", "r");
    }
    else if (strcmp(arg, "background") == 0)
    {
        fd = fopen("Help_Background", "r");
    }
    else if (strcmp(arg, "history") == 0)
    {
        fd = fopen("Help_History", "r");
    }
    else if (strcmp(arg, "control+c") == 0)
    {
        fd = fopen("Help_Control", "r");
    }
    else if (strcmp(arg, "chain") == 0)
    {
        fd = fopen("Help_Chain", "r");
    }
    else if (strcmp(arg, "if") == 0 || strcmp(arg, "multi-if") == 0)
    {
        fd = fopen("Help_IF", "r");
    }
    else if (strcmp(arg, "variables") == 0)
    {
        fd = fopen("Help_Var", "r");
    }
    int c;
    if (fd == NULL)
    {
        perror("Error");
        return -1;
    }
    do
    {
        c = fgetc(fd);
        if (feof(fd))
            break;
        printf("%c", c);
    } while (1);

    fclose(fd);
    return 0;
}

void Exit() //exit
{
    exit(0);
}

void SaveHistory(char *comand, int *cantcomand) //modificar la cantcomand ,no es necesario pasarlo
{
    FILE *fichero;
    FILE *temp;
    int n = 0;

    if (*cantcomand == 10) //Si ya hay 10 elemento hay que quitar el primero
    {
        fichero = fopen("History", "r");
        if (fichero == NULL) //verificar si el fichero existe
        {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        temp = fopen("Temp", "a");
        char comand[100];
        while (fscanf(fichero, "%99s", comand) != EOF) //lee
        {
            if (n > 0)
                fprintf(temp, "%s \n", comand); //escribe
            n++;
        }

        fclose(temp);
        fclose(fichero);

        remove("History");
        rename("Temp", "History");
    }
    //En cualquier otro caso se agrega al txt
    fichero = fopen("History", "a");
    fprintf(fichero, "%s \n", comand);
    fclose(fichero);
    *cantcomand = *cantcomand + 1;
}

void ShowHistory()
{
    int n = 1;
    FILE *fichero;
    fichero = fopen("History", "r");

    if (fichero == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char comand[100];
    while (fscanf(fichero, "%99s", comand) != EOF)
    {
        printf("%d : %s \n", n, comand);
        n++;
    }

    fclose(fichero);
}

void Again(char *arg) //***Falta codigo
{
    int n = atoi(arg);
    if (n > cantcomad || n == 0)
    {
        perror("Not Found");
    }

    int i = 1;
    char comand[100];
    FILE *fichero;
    fichero = fopen("History", "r");
    while (i <= n && fscanf(fichero, "%99s", comand) != EOF)
    {
        //if (i == n)
        // break;

        i++;
    }

    //Poner el m\'etodo de ejecutar el comando
}

void ControlC()
{
    if (Control)
    {
        kill(PidEject, SIGKILL);
    }
    else
    {
        Control = 1;
    }
}

int main()
{
    // printf("\n B&D@Shell $");
    signal(SIGINT, ControlC);

    //char ** arg = (char **)malloc(3*sizeof(char *));
    // char *arg = "feo"; int n = 0;
    /*
    //Probar history
    char arg[] = "help";
    int n = 0;
    int i = 0;
    while ((i <= 10))
    {
        if (i == 10)
        {
            SaveHistory("hola", &n);
            break;
        }
        if (i == 0)
            SaveHistory("uno", &n);
        else
            SaveHistory(arg, &n);
        i++;
        }
    ShowHistory();
    */
    int i = 0;
    while (i < 3)
    {
        i++;
    }
    printf("%d", i);

    return 0;
}