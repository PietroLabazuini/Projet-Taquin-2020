#include <stdio.h>
/*Ce fichier a vocation a être une bibliothèque regroupantles quatres fonctions permettant d'effectuer les déplacement vers le haut, 
le bas, la gauche et la droite
Dans chacune de ces 4 fonctions, i et j ont respectivement pour valeur, la ligne sur laquelle se situe la case vide et la colonne sur laquelle se situe 
cette même case*/

void haut (int * i, int * j, int** tab)
{
    tab[*i][*j]=tab[*i+1][*j];/*Nous mettons la valeur de la case du dessous dans la case actuelelemnt vide*/
    tab[*i+1][*j]=0;/*Nous mettons 0 en valeur de la case du dessous afin que cette dernière devienne la nouvelle case vide*/
    (*i)++;/*Nous incrémentons le pointeur i afin que ce dernier contienne la nouvelle ligne à laquelle se situe la case vide*/
}

void bas (int *i, int *j, int** tab)/*Comme pour la fonction haut ci-dessus, la fonction bas nous permet de déplacer une case de notre matrice vers le bas*/ 
{
    tab[*i][*j]=tab[*i-1][*j];
    tab[*i-1][*j]=0;
    (*i)--;
}

void gauche (int * i, int * j, int** tab)/*Cette fonction nous permet de déplacer une case vers la gauche*/
{
    tab[*i][*j]=tab[*i][*j+1];
    tab[*i][*j+1]=0;
    (*j)++;
}

void droite (int * i, int * j, int** tab)/*Cette fonction nous permet de déplacer une case de la matrice vers la droite*/ 
{
    tab[*i][*j]=tab[*i][*j-1];
    tab[*i][*j-1]=0;
    (*j)--;
}

