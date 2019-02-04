#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define NOM_FICHIER "password.txt"

#define DEBUT_ASCII 48
#define FIN_ASCII 122
#define TAILLE_ASCII FIN_ASCII-DEBUT_ASCII
#define erase() printf("\033[H\033[2J");

void help(void);

void writeFile(char str);
void Genere(int NbCharMax);
uint64_t nombresPass(int taille);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Saisissez « passGen --help » pour afficher l'aide.\n");
        return EXIT_SUCCESS;
    }
    if(argc == 2)
    {
        if((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0))
        {
            help();
            return EXIT_SUCCESS;
        }
        else
        {
            printf("Saisissez « passGen --help » pour afficher l'aide.\n");
            return EXIT_SUCCESS;
        }
    }
    else if(argc == 3)
    {
        if(strcmp(argv[1], "-n") == 0)
        {
            int nbPassword = 0;

            for(int i = 1; i < atoi(argv[2])+1; i++)
                nbPassword += nombresPass(i);

            printf("Vous allez générer %d mots de passes.\n", nbPassword);

            Genere(atoi(argv[2]));
        }
        else
        {
            printf("Saisissez « passGen --help » pour afficher l'aide.\n");
            return EXIT_SUCCESS;
        }
    }
    else
    {
        printf("Saisissez « passGen --help » pour afficher l'aide.\n");
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

void writeFile(char str){
    FILE* fichier = NULL;

    fichier = fopen(NOM_FICHIER, "a");
    fputc(str, fichier);

    fclose(fichier);
}

void Genere(int NbCharMax)
{
  char *mdp = NULL;
  mdp = malloc(NbCharMax*sizeof(char));

  int nbPass = 0;

  FILE* fichier = NULL;

  fichier = fopen(NOM_FICHIER, "w");
  fclose(fichier);

  fichier = fopen(NOM_FICHIER, "a");

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
           writeFile(mdp[i]);

         writeFile('\n');

         ++nbPass;
         erase();
         printf("%d mots de passes créés.\n", nbPass);
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

uint64_t nombresPass(int taille)
{
    return(pow(TAILLE_ASCII, taille));
}

void help(void)
{
    printf("Utilisation : passGen [OPTION]...\n");
    printf("-n [nombre]       Créé tous les mots de passes possibles pour [nombre] caractères maximum.\n");
    printf("-o [fichier]      Change le fichier de sortie pour [fichier]. 'password.txt' est généré automatiquement sans.\n");
    printf("-h ou --help      Affiche ce menu d'aide.\n\n");
}
