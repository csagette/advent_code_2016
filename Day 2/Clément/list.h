#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
struct List {
    int value;
    List *next;
};

List *insert (List *list, int e);
List *append (List *list, int e);
List *reverse (List *list);
void print_list(List *list);
void print_list_spec(List *list);


#endif