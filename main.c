#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define DEFAULT_FILE "password.txt"

#define DEBUT_ASCII 48
#define FIN_ASCII 122
#define TAILLE_ASCII FIN_ASCII-DEBUT_ASCII
#define erase() printf("\033[H\033[2J");

void man(void);

int writeFile(char str, const char* fileName);
int strFile(char *str, const char* filename);

int Genere(int NbCharMax, const char* fileName);
int randGen(int nbPassword, int maxPass, const char* fileName);
uint64_t numPass(int length);

int main(int argc, char** argv)
{
    int validArg = 0;
    char* fileName = NULL;
    int maxPass = 0;

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
            if((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0))
            {
                man();
                return EXIT_SUCCESS;
            }

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

                if(fileName != NULL)
                {
                    if(Genere(atoi(argv[i+1]), fileName) == -1)
                    {
                        printf("Error opening file.\n");
                        return EXIT_FAILURE;
                    }
                }
                else
                {
                    if(Genere(atoi(argv[i+1]), DEFAULT_FILE) == -1)
                    {
                        printf("Error opening file.\n");
                        return EXIT_FAILURE;
                    }
                }
            }

            if(strcmp(argv[i], "-r") == 0)
            {
                validArg = 1;
                int nbPassword = atoi(argv[i+1]);

                maxPass  = atoi(argv[i+2]);

                if(fileName != NULL)
                {
                    if(randGen(nbPassword, maxPass, fileName) == -1)
                    {
                        printf("Error opening file.\n");
                        return EXIT_FAILURE;
                    }
                }
                else
                {
                    if(randGen(nbPassword, maxPass, DEFAULT_FILE) == -1)
                    {
                        printf("Error opening file.\n");
                        return EXIT_FAILURE;
                    }
                }

            }
        }

        if(validArg == 0)
        {
            man();
            return EXIT_SUCCESS;
        }
        else
        {
            free(fileName);
        }
    }
    else
    {
        man();
        return EXIT_SUCCESS;
    }

    free(fileName);
    return EXIT_SUCCESS;
}

int Genere(int NbCharMax, const char* fileName)
{
  char *mdp = NULL;
  mdp = malloc(NbCharMax*sizeof(char));

  int nbPass = 0;
  FILE* fichier = NULL;

  fichier = fopen(fileName, "a");

  if(fichier == NULL)
      return -1;

  for(int nbChar=0;nbChar<NbCharMax;nbChar++)
  {
    int cursorCara = 0;
    mdp = realloc(mdp, (nbChar+1)*sizeof(char));

    for(int compt = 0; compt<=nbChar; compt++)
      mdp[compt] = DEBUT_ASCII;

    for(cursorCara=nbChar; cursorCara>=0; cursorCara--)
    {
       for(int cursorAscii=DEBUT_ASCII; cursorAscii<=FIN_ASCII; cursorAscii++)
       {
         mdp[cursorCara] = cursorAscii;

         if(fprintf(fichier, "%s\n", mdp) < 0)
             return -2;

         ++nbPass;

         printf("%d: %s\n", nbPass, mdp);
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

  fclose(fichier);
  free(mdp);

  return 0;
}

int randGen(int nbPassword, int maxPass, const char* fileName)
{
    int character = 0;
    char password[maxPass];

    FILE* fichier = NULL;
    fichier = fopen(fileName, "a");

    if(fichier == NULL)
        return -1;

    srand(time(NULL));

    for(int i=0; i<nbPassword; ++i)
    {
        for(int j=0; j<maxPass; ++j)
        {
            character = (rand()%(FIN_ASCII - DEBUT_ASCII + 1)) + DEBUT_ASCII;
            password[j] = character;
        }

        if(fprintf(fichier, "%s\n", password) < 0)
            return -2;

        printf("%d: %s\n", i+1, password);
    }

    fclose(fichier);

    return 0;
}

uint64_t numPass(int length)
{
    return(pow(TAILLE_ASCII, length));
}

void man(void)
{
    printf("Usage : passGen [OPTION]...\n");
    printf("Exemples:\n");
    printf("        passGen -o passlist -n 4\n");
    printf("        passgen -r 1000 5\n\n");
    printf("-o <file>                      Change output file for <file>. 'password.txt' is the default output if none is specified\n");
    printf("-n <number>                    Create passwords for <number> max char\n");
    printf("-r <number> <length>           Create <number> random passwords of <length> characters\n");
    printf("-h or --help                   Display the help menu\n");
}
