#include <stdio.h>
/*Ce fichier a vocation à devenir une bibliothèque contenant les différentes fonctions effectuant différents test sur la matrice dans laquelle sont
stockés les valeurs*/

void rechercheZero(int ** plateau, int N, int * coordLi,int * coordCo)/*Cette fonction nous sert à déterminer l'emplacement d'une zero une fois que nous 
avons fais le mélance aléatoire de la matrice*/
{
    int i,j;
    for (i = 0; i < N; i++)/*Cette double boucle for parcours simplement toute la matrice et teste si chaque case est égal à 0, si c'est le cas alors nous notons
    ses coordonnées dans deux variables "coordLi" pour la ligne et "coordCo" pour la colonne*/
    {
        for (j = 0; j < N; j++)
        {
            if (plateau[i][j]==0)
            {
                *coordLi=i;
                *coordCo=j;
            }
        }
    }
}

int testPlateau(int ** plateau, int N)/*Cette fonction nous permet de vérifier sie le jeu est complété*/
{
    /*SI le jeu est complété alors en le parcourant ligne par ligne de gauche à droite nous obtiendront une suite montante partant de 1 et finissant sur l'avant 
    dernière case, cette dernière aura pour valeur (N*N)-1. Nous allons tester si nous retrouvons cette suite dans cette fonction*/
    int i,j;
    int outil = 1;/*Nous initialisons une variable que nous incrémenteront à chaque passage dans la boucle afin pouvoir tester si les cases forment bien une 
    la suite montante que nous désirons obtenir*/
    int verif = 0;/*Nous initialisons une variable nous permettant de stocker l'information suivante : la suite est-elle complète ou non ? is la variable vaut 0 
    alors la réponse est oui, sinon la réponse est non.*/
    for (i = 0; i < N; i++)/*Cette double boucle for nous permet de parcourir toute les cases de la matrice*/
    {
        for (j = 0; j < N; j++)
        {
            if (i!= N-1 || j!=N-1)/*Nous excluons la dernière case de notre premier test */
            {
                if (plateau[i][j]!=outil)/*Nous testons si la case a la bonne valeur afin de continuer la suite*/ 
                {
                    verif = -1;/*Si ce n'est pas le cas alors le joueur n'a pas encore réussi le jeu de taquin et nous changoeons donc la valeur de la variable
                    à -1.*/ 
                }
            }
            else
            {
                if (plateau[i][j]!=0)/*Si nous entrons dans ce else c'est que nous sommes à la dernière case de la matrice, cette dernière doit donc valloir 0 
                pour que le jeu soit réussi*/
                {
                    verif = -1;/*Si ce n'est pas le cas, nous stockons cette informations dans notre variable de vérification*/
                }
            }
            outil++;
        }
    }
    return verif;/*Nous retournons la valeur de la variable de vérification afin de savoir dans notre programme principal si le joueur à reussi ou non 
    à chaque appelle de cette fonction*/ 
}

