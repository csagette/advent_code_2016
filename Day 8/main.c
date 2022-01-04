#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dico.h"

// Fonction qui allume un pixel
Dico_2_key *pixel_on(Dico_2_key *dico, int x, int y) {
    Dico_2_key *temp = NULL;
    if (dico == NULL) {
        return temp;
    }
    else if (dico->next == NULL) {
        if (dico->key1 == x && dico->key2 == y) {
            temp = insert(temp, dico->key1, dico->key2, 1);
        }
        else {
            temp = insert(temp, dico->key1, dico->key2, dico->value);
        }
    }
    else {
        while (dico->next != NULL) {
            if (dico->key1 == x && dico->key2 == y) {
                temp = insert(temp, dico->key1, dico->key2, 1);
            }
            else {
                 temp = insert(temp, dico->key1, dico->key2, dico->value);
            }
            dico = dico->next;
        }
        if (dico->key1 == x && dico->key2 == y) {
            temp = insert(temp, dico->key1, dico->key2, 1);
        }
        else {
            temp = insert(temp, dico->key1, dico->key2, dico->value);
        }
    }
    return temp;
}


// Fonction qui éteint un pixel
Dico_2_key *pixel_off(Dico_2_key *dico, int x, int y) {
    Dico_2_key *temp = NULL;
    if (dico == NULL) {
        return temp;
    }
    else if (dico->next == NULL) {
        if (dico->key1 == x && dico->key2 == y) {
            temp = insert(temp, dico->key1, dico->key2, 0);
        }
        else {
            temp = insert(temp, dico->key1, dico->key2, dico->value);
        }
    }
    else {
        while (dico->next != NULL) {
            if (dico->key1 == x && dico->key2 == y) {
                temp = insert(temp, dico->key1, dico->key2, 0);
            }
            else {
                 temp = insert(temp, dico->key1, dico->key2, dico->value);
            }
            dico = dico->next;
        }
        if (dico->key1 == x && dico->key2 == y) {
            temp = insert(temp, dico->key1, dico->key2, 0);
        }
        else {
            temp = insert(temp, dico->key1, dico->key2, dico->value);
        }
    }
    return temp;
}


int count_light_screen(Dico_2_key *dico) {
    int compteur = 0;
    if (dico == NULL) {
        return 0;
    }
    else if (dico->next == NULL) {
        if (dico->value == 1) {
            return 1;
        }
    }
    else {
        while (dico->next != NULL) {
            if (dico->value == 1) {
                compteur++;
            }
            dico = dico->next;
        }
        if (dico->value == 1) {
            compteur++;
        }
    }
    return compteur;
}


int main() {
    FILE *file = NULL;
    FILE *file2 = NULL;
    char *line = malloc(200*sizeof(char));
    char *rule = malloc(10*sizeof(char));
    char *rule1 = "column";
    int x;
    int y;
    int nb_val_read;

    // création de l'écran sous forme d'un dico à 2 clés
    Dico_2_key *screen = NULL;
    int size_x = 50;
    int size_y = 6;
    int i;
    int j;
    for (i = 0; i < size_x; i++) {
        for (j = 0; j < size_y; j++) {
            screen = insert(screen, i, j, 0);
        }
    }

    // lecture du fichier et analyse de chaque ligne
    file = fopen("input.txt", "r");
    file2 = fopen("imput3.txt", "w");

    if (file == NULL) {
        printf("ouverture du fichier impossible");
    }
    else {
        while (fgets(line, 200, file) != NULL) {
            // printf("%s", line);
            // test de scan d'un rectangle (le deuxième caractère de la ligne doit absolument être un 'e')
            if (*(line+1) == 101) {
                // la commande %*s permet de sauter la valeur 'rect' qu'on sait déjà avoir atteinte
                nb_val_read = sscanf(line, "%*s %dx%d", &x, &y);
                /*
                printf("x = %d\n", x);
                printf("y = %d\n", y);
                printf("rule = %s\n", rule);
                printf("nb = %d\n", nb_val_read);
                */
                for (i = 0; i < x ; i++) {
                    for (j = 0; j < y ; j++) {
                        screen = pixel_on(screen, i, j);
                    }
                }
            }
            // ou test de scan d'une rotation d'une colonne
            else if (*(line) != 32) {
                nb_val_read = sscanf(line, "rotate %s y= %d by %d", rule, &x, &y);
                nb_val_read = sscanf(line, "rotate %s x= %d by %d", rule, &x, &y);
                /*
                printf("x = %d\n", x);
                printf("y = %d\n", y);
                printf("rule = %s\n", rule);
                printf("nb = %d\n", nb_val_read);
                */
                if (strcmp(rule, rule1) == 0) {
                    // temp permet d'avoir une copie de screen à lire
                    Dico_2_key *temp = screen;
                    // temp2 sera modifier comme screen et permettra de savoir si il on ne revient pas sur une case qui a été modifié au début sur une même ligne ou colonne
                    Dico_2_key *temp2 = NULL;
                    for (j=size_y-1; j > -1; j--) {
                        temp2 = insert(temp2, x, j, 0);
                        }
                    //print_dico(temp2);
                    for (j=size_y-1; j > -1; j--) {
                        if (find_value(temp, x, j) == 1 && j+y >= size_y) {
                            screen = pixel_off(screen, x, j);
                            temp2 = pixel_on(temp2, x, (j+y)%size_y);
                        }
                        else if (find_value(temp, x, j) == 1) {
                            screen = pixel_off(screen, x, j);
                            screen = pixel_on(screen, x, j+y);
                        }
                    }
                    for (j=size_y-1; j > -1; j--) {
                        if (find_value(temp2, x, j) == 1) {
                            screen = pixel_on(screen, x, j);
                        }
                    } 
                }
                // sinon test de scan d'une rotation d'une ligne
                else {
                    Dico_2_key *temp = screen;
                    Dico_2_key *temp2 = NULL;
                    for (i=size_x-1; i > -1; i--) {
                        temp2 = insert(temp2, i, x, 0);
                        }

                    for (i=size_x-1; i > -1; i--) {
                        if (find_value(temp, i, x) == 1 && i+y >= size_x) {
                            screen = pixel_off(screen, i, x);
                            temp2 = pixel_on(temp2, (i+y)%size_x, x);
                        }
                        else if (find_value(temp, i, x) == 1) {
                            screen = pixel_off(screen, i, x);
                            screen = pixel_on(screen, i+y, x);
                        }
                    }
                    for (i=size_x-1; i > -1; i--) {
                        if (find_value(temp2, i, x) == 1) {
                            screen = pixel_on(screen, i, x);
                        }
                    }
                    //print_dico(temp2);
                    //printf("\n");
                }
            }
        }
        // print_dico(screen);
        // printf("\n");
        int compteur = count_light_screen(screen);
        printf("%d", compteur);
    }

    // La variable pos permet de savoir à quelle lettre on se trouve
    int pos = 0;
    // La variable essai permet de savoir à que ligne on se trouve
    int essai = 0;
    // La variable nb_traite est un compteur qui permet d'avoir une condition d'arrêt lorsqu'on a traité l'ensemble des pixels.
    int nb_traite = 0;
    // La variable useless conserve le booléen de retour de la fonction fputc qu'on utilisera pas 
    int useless;

    if (file2 == NULL) {
        printf("ouverture du fichier impossible");
    }
    else {
        while (nb_traite != size_x*size_y) {
            while (essai < 6) {
                for (int i = 5*pos; i < 5*(pos+1) ; i++) {
                    nb_traite++;
                    if (find_value(screen, i, essai) == 1) {
                        useless = fputc('+', file2);
                    }
                    else {
                        useless = fputc('-', file2);
                    }
                }
                essai++;
                useless = fputc('\n', file2);
            }
            essai = 0;
            pos++;
            useless = fputc('\n', file2);
        }
    }
    return 0;
}