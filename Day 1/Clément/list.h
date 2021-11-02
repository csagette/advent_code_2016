#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
struct List {
    int x;
    int y;
    List *next;
};

List *insert (List *list, double x, double y);
List *append (List *list, double x, double y);
List *reverse (List *list);
void print_list(List *list);
int contain(List *list, double x, double y);


#endif