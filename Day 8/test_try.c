#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dico.h"


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
    
    Dico_2_key *dico = NULL;
    dico = insert(dico, 0, 0, 0);
    dico = insert(dico, 0, 1, 0);
    dico = insert(dico, 1, 0, 1);
    dico = insert(dico, 1, 1, 1);
    print_dico(dico);
    printf("\n");
    dico = pixel_off(dico, 1, 1);
    print_dico(dico);
    printf("\n");
    dico = pixel_on(dico, 0, 0);
    print_dico(dico);
    int a = find_value(dico, 0, 0);
    printf("a = %d", a);
    /*
    char *rule = malloc(10*sizeof(char));
    int x;
    int y;
    int nb_val_read;
    //char *line = "rotate column y=48 by 6";
    char *line = "rect 1x3";
    nb_val_read = sscanf(line, "%*s %dx%d", &x, &y);
    //nb_val_read = sscanf(line, "rotate %s y = %d by %d", rule, &x, &y);
    //nb_val_read = sscanf(line, "rotate %s x = %d by %d", rule, &x, &y);
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("rule = %s\n", rule);
    printf("%d", nb_val_read);
    */
    return 0;
}