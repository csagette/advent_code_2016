#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dico.h"


// Fonction vérifiant si on a bien une chambre réelle
Dico *is_real_room (char* line) {

    Dico *res = malloc(sizeof(Dico));
    int i = 0;
    Dico *dico = malloc(sizeof(Dico));
    Dico *best = malloc(sizeof(Dico));
    /* Récupération des 5 lettres les plus fréquentes */
    while (*(line+i) < 48 || *(line+i) > 57) {
        if (*(line+i) != 45) {
            dico = append(dico, *(line+i));
        }
        i = i + 1;
    }
    best = best_five(dico);
    int k = 2;
    double ID = 0;
    while ((*(line+i) >= 48 && *(line+i) <= 57)) {
        ID = ID + (*(line+i) - 48) * pow(10,k);
        k--;
        i++;
    }
    i++;

    /* Vérification des fréquences */
    int l = 0;
    int flag = 1;
    while (((*(line+i) < 48 || *(line+i) > 57)) && flag == 1 && *(line+i) != 93) {
        if (find_rank(best, *(line+i)) > 1 + l || find_rank(best, *(line+i)) < 1) {
            flag = 0;
        }
        else if (find_rank(best, *(line+i)) == find_rank(best, *(line+i) && *(line+i) < *(line+i-1))) {
            flag = 0;
        }
        i++;
        l++;
    }
    res = insert(res, 'I', (int) ID);
    res = insert(res, 'F', flag);
    /*
    print_dico(best);
    printf("\n");
    print_dico(res);
    printf("\n");
    */
    return res;
}


// Fonction décryptant le nom d'une chambre réelle
char *shift_cypher(char *line, int rotation) {
    char *res = malloc(100*sizeof(char));
    int i = 0;
    while ((*(line+i) < 48 || *(line+i) > 57)) {
        if (*(line+i) == 45) {
            *(res+i) = 32;
        }
        else if ((*(line+i) + (rotation%26)) < 123) {
            *(res+i) = *(line+i) + (rotation%26);
        }
        else {
            *(res+i) = 97 + ((*(line+i) + (rotation%26))%123);
        }
        i++;
    }
    return res;
}


int main () {

    FILE *file = NULL;
    char *line = malloc(100*sizeof(char));
    Dico *data = malloc(sizeof(Dico));
    int ID = 0;

    file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("ouverture du fichier impossible");
    }
    else {
        while (fgets(line, 100, file) != NULL) {
            data = is_real_room(line);
            char *decrypted_line = malloc(100*sizeof(char));
            if (data->value == 1) {
                ID = ID + data->next->value;
                decrypted_line = shift_cypher(line, data->next->value);
                char *to_find = "north pole object";
                if (*to_find == *decrypted_line) {
                    printf("%d\n", data->next->value);
                }
            }
        }
        printf("sum IDs = %d", ID);
    }
    return 0;
}