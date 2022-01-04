#include <stdio.h>
#include <stdlib.h>
#include "dico.h"

// Fonction permettant d'afficher les éléments du dictionnaire
void print_dico(Dico* dico) {
    if (dico == NULL) {
        printf("%s\n", "dico empty");
    }
    else if (dico->next == NULL) {
        printf("key = %c, value = %d\n", dico->key, dico->value);
    }
    else {
        while (dico->next != NULL) {
            printf("key = %c, value = %d\n", dico->key, dico->value);
            dico = dico->next;
        }
        printf("key = %c, value = %d\n", dico->key, dico->value);
    }
}


// Fonction permettant d'insérer dans un dictionnaire une clé ainsi que sa valeur associée
Dico *insert (Dico *dico, char key, int value) {
    Dico *res = malloc(sizeof(Dico));
    res->key = key;
    res->value = value;
    res->next = dico;
    return res;
}


// Fonction permettant d'incrémenter de 1 la valeur d'une clé si elle existe, sinon celle-ci est rajouté au dictionnaire avec une valeur 1
Dico *append(Dico *dico, char key) {
    if (dico == NULL) {
        return insert(NULL, key, 1);
    }
    else if (dico->key == key) {
        return insert(dico->next ,dico->key, dico->value + 1);
    }
    else {
        return insert(append(dico->next, key) ,dico->key, dico->value);
    }
}


// Fonction permettant de supprimer une clé d'un dictionnaire
Dico *delete(Dico *dico, char key) {
    if (dico == NULL) {
        printf("dico empty");
        return NULL;
    }
    else {
        Dico *res = NULL;
        Dico *current = dico;
        while (current->next != NULL) {
            if (current->key != key) {
                res = insert(res, current->key, current->value);
            }
            current = current->next;
        }
        if (current->key != key) {
                res = insert(res, current->key, current->value);
        }
        return res;
    }
}


// Fonction permettant d'obtenir les 5 clés d'un dictionnaire avec les meilleurs value. On renvoie alors un nouveau dictionnaire contenant
// ces clés avec leur classement: 1 si elle avait la meilleure valeur et ainsi de suite.
Dico *best_five(Dico *dico) {
    int i = 0;
    int max = 0;
    int past_max = max;
    Dico *res = NULL;
    Dico *temp = dico;
    Dico *current = temp;
    int classement = 1;
    /* on cherche les 5 lettres avec les plus grandes fréquences*/
    while (i < 5) {
        char current_c;

        while (current->next != NULL) {
            /*printf("cur_v = %c, cur_c = %c et test = %d\n", current->key, current_c, current->value < current_c);*/
            if (current->value > max) {
                max = current->value;
                current_c = current->key;
            }
            else if (current->value == max && current->key < current_c) {
                max = current->value;
                current_c = current->key;
            }
            current = current->next;
        }
        if (current->value > max) {
                max = current->value;
                current_c = current->key;
        }
        else if (current->value == max && current->key < current_c) {
                max = current->value;
                current_c = current->key;
        }
        if (res == NULL) {
            res = insert(res, current_c, classement);
        }
        else if (past_max == max) {
            res = insert(res, current_c, classement);
        }
        else {
            classement = classement + 1;
            res = insert(res, current_c, classement);
        }
        i = i + 1;
        past_max = max;
        max = 0;
        temp = delete(temp, current_c);
        current = temp;
        /*printf("delete = %c\n", current_c);
        print_dico(temp);
        printf("\n");*/
    }
    return res;
}


// Fonction permettant de trouver la valeur associée à une clé.
int find_rank(Dico *dico, char key) {
    if (dico == NULL) {
        return -1;
    }
    else if (dico->next == NULL) {
        if (dico->key == key) {
            return dico->value;
        }
    }
    else {
        while (dico->next != NULL) {
            if (dico->key == key) {
                return dico->value;
            }
            else {
                dico = dico->next;
            }
        }
        if (dico->key == key) {
            return dico->value;
        }
    }
    return -1;
}