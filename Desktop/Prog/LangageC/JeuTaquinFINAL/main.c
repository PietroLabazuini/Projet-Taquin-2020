#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_types.h>
#include "mouvement.h"
#include "testsPlateau.h"
#include "initMatrice.h"
#define LONG 1000
#define LARG 1200

int main()
{
    int choix,i,j,tailleCase;
    int ** plateau;
    char nomFichier[20];
    int N = 1;
    char a;
    int valeur;
    int diff;
    
    printf("Bienvenue dans le jeu de taquin !\nVeuillez choisir une option parmi les suivantes :\n1 : Générer une grille aléatoire\n2 : Charger une grille\n3 : Puzzle image\n4 : Quitter le jeu\n");
    scanf("%d",&choix);
    //Nous allons découper les 4 cas possibles en 4 if afin d'afficher la grille correspondant au choix du joueur
    if (choix ==1)
    {
        printf("Choisir la taille de la grille :\n");
        scanf("%d",&N);
        tailleCase = 1000 / N-20;

        //ALLOCATION DU TABLEAU
        plateau = malloc( sizeof(char *) * N);
        for (i=0 ; i<N ; i++)
        {
            plateau[i] = malloc( sizeof(char) * N);
        }

        //CHOIX DE LA DIFFICULTE
        printf("Choisir la difficulté : \n1 : Facile\n2 : Moyen\n3 : Difficile\n4 : Chuck Norris\n");
        scanf("%d",&diff);
        plateau = generationPlateau(N,diff); //Nous utilisons notre fonction generationPlateau pour créer le plateau de jeu de base
        updatePlateau(plateau,tailleCase,N,diff); //affiche le tableau une première fois
        plateauFULL(plateau,N,tailleCase,"plateau",diff); //fonction de résolution
    }

    else if (choix == 2) //on supposera que la grille entrée est valide (réalisable et correcte)
    {
        printf("Entrer le nom du fichier de la grille :\n");
        scanf("%s",nomFichier);

        //COMPTAGE DU NOMBRE DE CASES DU TABLEAU
        FILE * fichier = fopen(nomFichier,"r+");
        while((a=fgetc(fichier))!='\n')
        {
            if (a==' ')
            {
                N++;
            }
        }

        fseek(fichier,0,SEEK_SET); //on remet le curseur au début 

        //ALLOCATION DU TABLEAU
        plateau = malloc( sizeof(char *) * N);
        for (i=0 ; i<N ; i++)
        {
            plateau[i] = malloc( sizeof(char) * N);
        }

        //RECUPERATION DES VALEURS DU FICHIER DANS LE TABLEAU
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                fscanf(fichier,"%d",&valeur);
                plateau[i][j]=valeur;
            }
        }
        tailleCase = 1000 / N - 20;
        updatePlateau(plateau,tailleCase,N,diff);
        plateauFULL(plateau,N,tailleCase,"plateau",diff);
    }
    
    else if (choix == 3) //choix du puzzle
    {
        N = 4;//on impose la taille et la difficulté
        diff = 2;
        tailleCase = 1000 / N;

        //ALLOCATION DU TABLEAU
        plateau = malloc( sizeof(char *) * N);
        for (i = 0 ; i < N ; i++)
        {
            plateau[i] = malloc( sizeof(char) * N);
        }
        
        plateau = generationPlateau(N,diff);
        updatePuzzle(plateau);
        plateauFULL(plateau,N,tailleCase,"puzzle",diff);
    }
    else if (choix == 4)//le joueur souhaite arrêter de jouer, nous mettons donc fin au programme 
    {
        return 0;
    }
    else
    {
        printf("Veuillez entrer une valeur valide.\n");
        return 0;
    }
    
    return 0;
}