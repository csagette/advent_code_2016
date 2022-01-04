#ifndef DICO_H
#define DICO_H
#include <stdio.h>
#include <stdlib.h>

// Création d'une structure de dictionnaire à 2 clés
typedef struct Dico_2_key Dico_2_key;
struct Dico_2_key {
    char key1;
    int key2;
    int value;
    Dico_2_key *next;
};

Dico_2_key *insert(Dico_2_key *dico, char key1, int key2, int value);
Dico_2_key *append(Dico_2_key *dico, char key1, int key2);
Dico_2_key *delete(Dico_2_key *dico, char key1, int key2);
int find_value(Dico_2_key *dico, char key1, int key2);
void print_dico(Dico_2_key *dico);


#endif