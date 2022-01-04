#ifndef DICO_H
#define DICO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Dico Dico;
struct Dico {
    char key;
    int value;
    Dico *next;
};

Dico *insert(Dico *dico, char key, int value);
Dico *append(Dico *dico, char key);
Dico *delete(Dico *dico, char key);
Dico *best_five(Dico *dico);
int find_rank(Dico *dico, char key);
void print_dico(Dico *dico);


#endif