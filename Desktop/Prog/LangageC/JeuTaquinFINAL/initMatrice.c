#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "mouvement.h"
#include "testsPlateau.h"
#define LONG 1250
#define LARG 1000

SDL_Surface * rectangle = NULL;
SDL_Rect position;
SDL_Surface * ecran = NULL;
SDL_Surface * zoneTexte = NULL;
TTF_Font * police = NULL;
SDL_Color noir = {0,0,0,0};
SDL_Surface * image = NULL;

void victoire ();

int ** generationPlateau(int N, int diff)
{
    srand(time(NULL)); //initialisation des randoms

    //DEFINITION DU PLATEAU IDENTITE POUR LA TAILLE N
    int ** plateau = calloc(N, sizeof(int *));
    int j,i,outil;
    outil=1;
    for (i=0 ; i<N ; i++)
    {
        plateau[i] = calloc(N,sizeof(int));
        j=0;
        while (j < N)
        {
            if(outil != N*N)
            {
                plateau[i][j] = outil;
            }
            outil++;
            j++;
        }
    }

    int nbModif;
     //nombre de modifications effectuées sur le plateau identité en fonction de la difficulté choisie
    if (diff == 1)
    {
        nbModif = 5;
    }
    else if (diff == 2)
    {
        nbModif = 30;
    }
    else if (diff == 3)
    {
        nbModif = 100;
    }
    else if (diff == 4)
    {
        nbModif = rand()%500 + 500;
    }
    else
    {
        printf("Erreur lors du choix de la difficulté. Veuillez entrer un chiffre valide.\n");
        exit(0);
    }
    
    int randEchange;

    //coordonnées de la case vide
    int coordLigne = N-1; 
    int coordColonne = N-1;

    //MODIFICATIONS DU PLATEAU
    for (i=0; i<nbModif; i++)
    {
        randEchange = rand()%4; //variable à valeur aléatoire pour déterminer le mouvement à effectuer sur le plateau

        //CAS DU DEPLACEMENT VERS LE HAUT (donc case vide vers le bas)
        if (randEchange == 0 && coordLigne != N-1) 
        {
            haut(&coordLigne,&coordColonne,plateau);
        }

        //CAS DU DEPLACEMENT VERS LE BAS (donc case vide vers le haut)
        else if (randEchange == 1 && coordLigne > 0)
        {
            bas(&coordLigne,&coordColonne,plateau);
        }

        //CAS DU DEPLACEMENT VERS LA GAUCHE (donc case vide vers la droite)
        else if (randEchange == 2 && coordColonne != N-1)
        {
            gauche(&coordLigne,&coordColonne,plateau);
        }

        //CAS DU DEPLACEMENT VERS LA DROITE (donc case vide vers la gauche)
        else if (randEchange == 3 && coordColonne != 0)
        {
            droite(&coordLigne,&coordColonne,plateau);
        }
    }

    //CAS D'UN PLATEAU OBTENU CORRESPONDANT A L'IDENTITE
    if (testPlateau(plateau,N)==0)
    {
        bas(&coordLigne,&coordColonne,plateau);//on fait un seu mouvement pour éviter un problème
    }
    return plateau;
}

void updatePlateau(int ** plateau, int tailleCase, int N, int diff)
{
    int i,j;
    position.x=10 ;
    position.y=10 ;

    //INITIALISATION DES ENVIRONNEMENTS SDL
    if(SDL_Init(SDL_INIT_VIDEO) !=0)
    {
        fprintf(stderr,"\nUnable to initialize SDL:  %s\n", SDL_GetError()  );
        exit(EXIT_FAILURE) ;
    }

    if((ecran = SDL_SetVideoMode(LONG,LARG,32, SDL_HWSURFACE))==NULL)
    {
         fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
         exit(EXIT_FAILURE) ;
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr,"\nUnable to initialize TTF:  %s\n", TTF_GetError());
    }

    police = TTF_OpenFont("/usr/share/fonts/truetype/abyssinica/AbyssinicaSIL-Regular.ttf",80);

    //REMPLISSAGE DE L'ECRAN EN NOIR
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));

    //REMPLISSAGE D'UN CARRE DE LA TAILLE D'UNE CASE D'UNE TEINTE MOINS FONCEE 
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, tailleCase, tailleCase, 32,0,0,0,0);
    SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format, 200,200,200));

    //CREATION DU MODIF DES CASES SUR LA SURFACE ECRAN
    for (i = 0; i < N; i++)
    {   
        for (j = 0; j < N; j++)
            {
                SDL_BlitSurface(rectangle,NULL,ecran,&position) ;
                position.x += LARG / N;
            }
        position.y += LARG /N;
        position.x = 10;
    }

    //AFFICHAGE DU MENU A DROITE SELON LA DIFFICULTE CHOISIE
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,tailleCase,LARG,32,0,0,0,0);
    if (diff == 1)
    {
        rectangle = SDL_LoadBMP("resources/affichageFacile.bmp");
    }
    else if (diff == 2)
    {
        rectangle = SDL_LoadBMP("resources/affichageMoyen.bmp");
    }
    else if (diff==3)
    {
        rectangle = SDL_LoadBMP("resources/affichageDifficile.bmp");
    }
    else
    {
        rectangle = SDL_LoadBMP("resources/affichageChuck.bmp");
    }
    position.x = LARG;
    position.y = 0;
    SDL_BlitSurface(rectangle,NULL,ecran,&position);

    //AFFICHAGE DES VALEURS DANS LE DAMIER
    position.x = tailleCase/2-20;
    position.y = tailleCase/2-20;
    
    char stockValeur[5];
    for (i = 0; i < N ; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (plateau[i][j]!=0)
            {
                sprintf(stockValeur,"%d",plateau[i][j]);
                zoneTexte = TTF_RenderText_Blended(police,stockValeur,noir);
                SDL_BlitSurface(zoneTexte,NULL,ecran,&position);
            }
            position.x += 1000 / N;
        }
        position.y += 1000 / N;
        position.x = 1000/N/2-20;
    }

    //MISE A JOUR DES MODIFICATIONS
    SDL_Flip(ecran);
}

void updatePuzzle(int ** plateau)
{
    //INITIALISATION DES ENVIRONNEMENTS SDL
    if(SDL_Init(SDL_INIT_VIDEO) !=0)
    {
        fprintf(stderr,"\nUnable to initialize SDL:  %s\n", SDL_GetError()  );
        exit(EXIT_FAILURE) ;
    }
    if((ecran = SDL_SetVideoMode(LONG,LARG,32, SDL_HWSURFACE))==NULL)
    {
         fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
         exit(EXIT_FAILURE) ;
    }

    position.x=0;
    position.y=0;
    int tailleCase = 250;
    int i,j;
    int N = 4;
    
    //AFFICHAGE DU MENU A DROITE POUR PUZZLE
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,tailleCase,LARG,32,0,0,0,0);
    rectangle = SDL_LoadBMP("resources/affichagePuzzle.bmp");
    position.x = LARG; //on le colle à droite de la zone du plateau
    position.y = 0;
    SDL_BlitSurface(rectangle,NULL,ecran,&position);
    
    //AFFICHAGE DES IMAGES
    position.x=0 ;
    position.y=0 ;
    char nomImage[30];
    char stockValeur[7];
    for (i = 0; i < N ; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (plateau[i][j]!=0)
            {
                
                sprintf(stockValeur,"%d",plateau[i][j]);
                strcat(stockValeur,".bmp");
                strcpy(nomImage,"resources/");
                strcat(nomImage,stockValeur);
                image  = SDL_LoadBMP(nomImage);
                SDL_BlitSurface(image,NULL,ecran,&position);

            }
            position.x += tailleCase;
        }
        position.y += tailleCase;
        position.x = 0;
    }

    //MISE A JOUR DES MODIFICATIONS
    SDL_Flip(ecran);
}

void plateauFULL(int ** plateau, int N, int tailleCase,char * type,int diff)
{
    int coordLi, coordCo;
    rechercheZero(plateau,N,&coordLi,&coordCo);//afin de pouvoir se déplacer correctement, on change les valeurs de coordLi et coordCo à leur adresse
    int verif = -1;
    SDL_Event event ;

    while (verif!=0)
    {   
        SDL_WaitEvent(&event);//on attend un évènement avant de continuer
        switch(event.type)
        {
            case SDL_QUIT :
                verif = 0;
                break;
            case SDL_KEYDOWN : 
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP :
                        if(coordLi!=N-1)//on vérifie si la case vide est en bas du tableau, cas dans lequel on ne peut pas se déplacer vers le haut
                            {
                                haut(&coordLi, &coordCo,plateau);//on échange les deux cases
                                verif=testPlateau(plateau,N);// on vérifie si le tableau obtenu est l'identité
                                if (strcmp("plateau",type)==0)//condition pour update de la bonne façon le tableau selon le mode choisi
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }
                            }
                        break;
                    case SDLK_DOWN : //même raisonnement que pour haut
                        if(coordLi!=0)
                            {
                                bas(&coordLi, &coordCo,plateau);
                                verif=testPlateau(plateau,N);
                                if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }               
                            }
                        break;
                    case SDLK_LEFT ://même raisonnement que pour haut
                        if(coordCo!=N-1)
                            {
                                gauche(&coordLi, &coordCo,plateau);
                                verif=testPlateau(plateau,N);
                                if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }    
                            }
                        break;
                    case SDLK_RIGHT ://même raisonnement que pour haut
                        if(coordCo!=0)
                        {
                            droite(&coordLi, &coordCo,plateau);
                            verif=testPlateau(plateau,N);
                            if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }     
                        }
                        break;
                    case SDLK_h ://on change juste la touche, mais le raisonnement est exactement le même que pour haut
                        if(coordLi!=N-1)
                            {
                                haut(&coordLi, &coordCo,plateau);
                                verif=testPlateau(plateau,N);
                                if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }
                            }
                        break;
                    case SDLK_b :
                        if(coordLi!=0)
                            {
                                bas(&coordLi, &coordCo,plateau);
                                verif=testPlateau(plateau,N);
                                if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }               
                            }
                        break;
                    case SDLK_g :
                        if(coordCo!=N-1)
                            {
                                gauche(&coordLi, &coordCo,plateau);
                                verif=testPlateau(plateau,N);
                                if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                                else
                                {
                                    updatePuzzle(plateau);
                                }    
                            }
                        break;
                    case SDLK_d :
                        if(coordCo!=0)
                        {
                            droite(&coordLi, &coordCo,plateau);
                            verif=testPlateau(plateau,N);
                            if (strcmp("plateau",type)==0)
                                {
                                    updatePlateau(plateau,tailleCase,N,diff);
                                }
                            else
                            {
                                updatePuzzle(plateau);
                            }     
                        }
                        break;
                    default :
                        break;
                }
        }
    }
    //afin d'éviter tout problème, on affiche l'écran de victoire uniquement si le plateau est l'identité
    if (testPlateau(plateau,N)==0)
    {
        victoire();//on affiche l'écran de victoire
    }
}

void victoire ()
{
    SDL_Event event;
    int outil=1;
    if(SDL_Init(SDL_INIT_VIDEO) !=0)
    {
        fprintf(stderr,"\nUnable to initialize SDL:  %s\n", SDL_GetError()  );
        exit(EXIT_FAILURE) ;
    }
    position.x = 0;
    position.y = 0;
    rectangle = SDL_LoadBMP("resource/victoire.bmp");
    if((ecran = SDL_SetVideoMode(1500,842,32, SDL_HWSURFACE))==NULL)
    {
         fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
         exit(EXIT_FAILURE) ;
    }
    SDL_BlitSurface(rectangle,NULL,ecran,&position);

    //AFFICHAGE DE L'ECRAN DE VICTOIRE TANT QUE LE JOUEUR NE QUITTE PAS
    while (outil)
    {
        SDL_Flip(ecran);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                outil =0;
                break;
            default :
                outil = 1;
        }
    }
}