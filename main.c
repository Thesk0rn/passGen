#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define DEFAULT_FILE "password.txt"

#define DEBUT_ASCII 48
#define FIN_ASCII 122
#define TAILLE_ASCII FIN_ASCII-DEBUT_ASCII
#define erase() printf("\033[H\033[2J");

void man(void);

void writeFile(char str, char* fileName);
void Genere(int NbCharMax, char* fileName);
uint64_t numPass(int length);

int main(int argc, char** argv)
{
    int validArg = 0;
    char* fileName = NULL;

    if(argc < 2)
    {
        man();
        return EXIT_SUCCESS;
    }
    if(argc == 2)
    {
        if((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0))
        {
            man();
            return EXIT_SUCCESS;
        }
        else
        {
            man();
            return EXIT_SUCCESS;
        }
    }
    else if(argc > 2)
    {
        for(int i = 1; i<argc; i++)
        {
            if(strcmp(argv[i], "-o") == 0)
            {
                if(argc>=i+1)
                {
                    fileName = malloc(strlen(argv[i+1])*sizeof(char));
                    strcpy(fileName, argv[i+1]);
                }
                else
                {
                    man();
                    return EXIT_SUCCESS;
                }
            }

            if(strcmp(argv[i], "-n") == 0)
            {
                int nbPassword = 0;
                validArg = 1;

                for(int j = 1; j < atoi(argv[i+1])+1; j++)
                    nbPassword += numPass(j);

                printf("%d passwords will be generated.\n", nbPassword);

                if(fileName != NULL)
                    Genere(atoi(argv[i+1]), fileName);
                else
                    Genere(atoi(argv[i+1]), DEFAULT_FILE);
            }
        }

        if(validArg == 0)
        {
            man();
            return EXIT_SUCCESS;
        }
    }
    else
    {
        man();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

void writeFile(char str, char* fileName){
    FILE* fichier = NULL;

    fichier = fopen(fileName, "a");
    fputc(str, fichier);

    fclose(fichier);
}

void Genere(int NbCharMax, char* fileName)
{
  char *mdp = NULL;
  mdp = malloc(NbCharMax*sizeof(char));

  int nbPass = 0;

  FILE* fichier = NULL;

  fichier = fopen(fileName, "w");
  fclose(fichier);

  fichier = fopen(fileName, "a");

  for(int nbChar=0;nbChar<NbCharMax;nbChar++)
  {
    int cursorCara = 0;
    mdp = realloc(mdp, (nbChar+1)*sizeof(char));

    for(int compt = 0; compt <=nbChar; compt++)
      mdp[compt] = DEBUT_ASCII;

    for(cursorCara=nbChar; cursorCara>=0; cursorCara--)
    {
       for(int cursorAscii=DEBUT_ASCII; cursorAscii<=FIN_ASCII; cursorAscii++)
       {
         mdp[cursorCara] = cursorAscii;

         for(int i=0;i<=nbChar;i++)
           writeFile(mdp[i], fileName);

         writeFile('\n', fileName);

         ++nbPass;

         erase();
         printf("%d passwords created.\n", nbPass);
       }

       if(cursorCara > 0)
       {
         if(mdp[cursorCara-1] < FIN_ASCII)
         {
           mdp[cursorCara-1]++;

           for(cursorCara=cursorCara;cursorCara<=nbChar;cursorCara++)
           {
             mdp[cursorCara] = DEBUT_ASCII;
           }
         }
       }
    }
  }
}

uint64_t numPass(int length)
{
    return(pow(TAILLE_ASCII, length));
}

void man(void)
{
    printf("Usage : passGen [OPTION]...\n");
    printf("        passGen -o <file> -n <number>\n\n");
    printf("-o <file>         Change output file for <file>. 'password.txt' is the default output if none is specified\n");
    printf("-n <number>       Create passwords for <number> max char\n");
    printf("-h or --help      Display the help menu\n");
}
