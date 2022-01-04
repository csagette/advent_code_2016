#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dico.h"



int main () {

    char *line = "a-b-c-g-e-a-d-f-z-d-977[dabce]";
    

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
        if ((find_rank(best, *(line+i)) > 1 + l || find_rank(best, *(line+i)) < 1) || *(line+i) < *(line+i-1)) {
            flag = 0;
        }
        i++;
        l++;
    }
    res = insert(res, 'I', (int) ID);
    res = insert(res, 'F', flag);
    print_dico(best);
    printf("\n");
    print_dico(res);

    return 0;
}