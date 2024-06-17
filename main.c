/**
 * Author: Zakaria Hammal
 * email: hammalzakaria06@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char read()
{
    char c = 0;

    c = getchar();
    c = toupper(c);

    while (getchar() != '\n');

    return c;
}

// -------------------------------------------------------------------------


char* choisirMot(FILE* fi, int* taille)
{
    int l = 0;
    char c = fgetc(fi);
    int choix;
    
    while (c != EOF)
    {
        if (c == '\n')
        {
            l++;
        }
        c = fgetc(fi);
    }

    rewind(fi);

    srand(time(NULL));
    choix = (rand () % (l));

    int i = 0;

    while(i < choix)
    {
        c = fgetc(fi);
        if (c == '\n')
        {
            i++;
        }
    }

    int n = 0;

    do
    {
        n++;
        c = fgetc(fi);
    } while (c != '\n');
    
    char* r = (char*) malloc(n * sizeof(char));
    *taille = n;

    rewind(fi);

    i = 0;

    while(i < choix)
    {
        c = fgetc(fi);
        if (c == '\n')
        {
            i++;
        }
    }

    i = 0;
    do
    {
        c = fgetc(fi);
        if(c != '\n')
        {
            r[i] = c;
        }
        i++;
    } while (c != '\n');

   return r; 
}  

// -------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char* motSecret;
    char* motCache;
    int j = 0;
    char c, r;
    FILE* file = NULL;
    file = fopen("dic.txt", "r+");

    if(file == NULL) 
    {
        printf("Erreur d'ouverture du fichier !!!\n");
        return EXIT_FAILURE;
    }


    do
    {
        system("clear");
        motSecret = NULL;
        motCache = NULL;

        motSecret = choisirMot(file, &j);

        motCache = (char*) malloc(j * sizeof(char));

        for (int i = 0; i < j - 1; i++)
        {
            motCache[i] = '*';
        }

        int coups = 10;

        printf("Welcome to Hangman Game !!!\n\n");

        while (coups > 0 && strcmp(motCache, motSecret) != 0)
        {
            if(coups > 1)
            {
                printf("You have %d tries\n", coups);
            }
            else
            {
                printf("You have one try\n");
            }
            printf("What is the secret word ? %s\n", motCache);
            printf("Propose a letter :\t");
            c = read();

            if (strchr(motSecret, c) == NULL)
            {
                coups--;
            }
            else
            {
                for (int i = 0; i < j - 1; i++)
                {
                    if (motSecret[i] == c)
                    {
                        motCache[i] = c;
                    }
                    
                }
                
            }

            printf("\n\n");
        }

        if (strcmp(motSecret, motCache) == 0)
        {
            printf("You Won :) The secret word was indeed : %s\n", motSecret);
        }
        else
        {
            printf("You lost :( The secret word was : %s\n", motSecret);
        }

        do
        {
          printf("Replay ? (y/n) :\t");
          r = read();
        }while(r != 'Y' && r!= 'N');

    }while (r == 'Y');
    
    fclose(file);

    return EXIT_SUCCESS;
}
