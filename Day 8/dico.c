#include <stdio.h>
#include <stdlib.h>
#include "dico.h"

// Fonction permettant d'afficher les éléments du dictionnaire
void print_dico(Dico_2_key *dico) {
    if (dico == NULL) {
        printf("%s\n", "dico empty");
    }
    else if (dico->next == NULL) {
        printf("key1 = %d, key2 = %d, value = %d\n", dico->key1, dico->key2, dico->value);
    }
    else {
        while (dico->next != NULL) {
            printf("key1 = %d, key2 = %d, value = %d\n", dico->key1, dico->key2, dico->value);
            dico = dico->next;
        }
        printf("key1 = %d, key2 = %d, value = %d\n", dico->key1, dico->key2, dico->value);
    }
}


// Fonction permettant d'insérer dans un dictionnaire une clé ainsi que sa valeur associée
Dico_2_key *insert (Dico_2_key *dico, int key1, int key2, int value) {
    Dico_2_key *res = malloc(sizeof(Dico_2_key));
    res->key1 = key1;
    res->key2 = key2;
    res->value = value;
    res->next = dico;
    return res;
}


// Fonction permettant d'incrémenter de 1 la valeur d'une clé double si elle existe, sinon celle-ci est rajouté au dictionnaire avec une valeur 1
Dico_2_key *append(Dico_2_key *dico, int key1, int key2) {
    if (dico == NULL) {
        return insert(NULL, key1, key2, 1);
    }
    else if (dico->key1 == key1 && dico->key2 == key2) {
        return insert(dico->next ,dico->key1, dico->key2, dico->value + 1);
    }
    else {
        return insert(append(dico->next, key1, key2) ,dico->key1, dico->key2, dico->value);
    }
}


// Fonction permettant de supprimer une clé double d'un dictionnaire
Dico_2_key *delete_key(Dico_2_key *dico, int key1, int key2) {
    if (dico == NULL) {
        printf("dico empty");
        return NULL;
    }
    else {
        Dico_2_key *res = NULL;
        Dico_2_key *current = dico;
        while (current->next != NULL) {
            if (current->key1 != key1 && current->key2 != key2) {
                res = insert(res, current->key1, current->key2, current->value);
            }
            current = current->next;
        }
        if (current->key1 != key1 && current->key2 != key2) {
                res = insert(res, current->key1, current->key2, current->value);
            }
        return res;
    }
}


// Fonction permettant de trouver la valeur associée à une clé double.
int find_value(Dico_2_key *dico, int key1, int key2) {
    if (dico == NULL) {
        return -1;
    }
    else if (dico->next == NULL) {
        if (dico->key1 == key1 && dico->key2 == key2) {
            return dico->value;
        }
    }
    else {
        while (dico->next != NULL) {
            if (dico->key1 == key1 && dico->key2 == key2) {
                return dico->value;
            }
            else {
                dico = dico->next;
            }
        }
        if (dico->key1 == key1 && dico->key2 == key2) {
            return dico->value;
        }
    }
    return -1;
}
