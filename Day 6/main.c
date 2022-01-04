#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dico.h"

// Fonction qui renvoie pour chaque colonne (indicé par key2) l'élément avec la plus grande fréquence (donnée par value)
char *most_common(Dico_2_key *dico, int nb_col) {
    Dico_2_key *temp = malloc(sizeof(Dico_2_key));
    temp = dico;
    int max = 0;
    char *res = malloc(10*sizeof(char));

    for (int ind_col=0; ind_col < nb_col; ind_col++) {
        if (temp == NULL) {
            printf("Wait what ? Dico vide");
        }
        else {
            while (temp->next != NULL) {
                if (temp->key2 == ind_col && temp->value > max) {
                    max = temp->value;
                    *(res+ind_col) = temp->key1;
                }
                temp = temp->next;
            }
        }
        max = 0;
        temp = dico;
    }
    return res;
}


// Fonction qui renvoie pour chaque colonne (indicé par key2) l'élément avec la plus petite fréquence (donnée par value)
// La condition "&& temp->value >= 1" est ajouté ici pour ne pas avoir de problème avec la dernière ligne du fichier qui est seulement un espace
char *least_common(Dico_2_key *dico, int nb_col) {
    Dico_2_key *temp = malloc(sizeof(Dico_2_key));
    temp = dico;
    int min = 10000000;
    char *res = malloc(10*sizeof(char));

    for (int ind_col=0; ind_col < nb_col; ind_col++) {
        if (temp == NULL) {
            printf("Wait what ? Dico vide");
        }
        else {
            while (temp->next != NULL) {
                if (temp->key2 == ind_col && temp->value < min && temp->value >= 1) {
                    min = temp->value;
                    *(res+ind_col) = temp->key1;
                }
                temp = temp->next;
            }
        }
        min = 10000000;
        temp = dico;
    }
    return res;
}


int main() {
    FILE *file = NULL;
    char *line = malloc(10*sizeof(char));
    Dico_2_key *colonnes = malloc(sizeof(Dico_2_key));

    file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("ouverture du fichier impossible");
    }
    else {
        while (fgets(line, 10, file) != NULL) {
            int pos = 0;
            while (*(line+pos) != '\n') {
                colonnes = append(colonnes, *(line+pos), pos);
                pos++;
            }
            pos = 0;
        }
        //print_dico(colonnes);
        char *most_message = malloc(10*sizeof(char));
        char *least_message = malloc(10*sizeof(char));
        most_message = most_common(colonnes, 8);
        printf("\n");
        least_message = least_common(colonnes, 8);
        printf("most common = %s\n", most_message);
        printf("least common = %s", least_message);
    }
    return 0;
}

