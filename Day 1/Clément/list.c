#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void print_list(List* list) {
    if (list == NULL) {
        printf("%s\n", "liste vide");
    }
    else if (list->next == NULL) {
        printf("(x = %d, y = %d)\n", list->x, list->y);
    }
    else {
        while (list->next != NULL) {
            printf("(x = %d, y = %d)\n", list->x, list->y);
            list = list->next;
        }
        printf("(x = %d, y = %d)\n", list->x, list->y);;
    }
}

List *insert (List *list, double x, double y) {
    List *res = malloc(sizeof(List));
    res->x = x;
    res->y = y;
    res->next = list;
    return res;
}


List *append(List *list, double x, double y) {
    if (list == NULL) {
        return insert(NULL, x, y);
    }
    else {
        return insert(append(list->next, x, y) ,list->x, list->y);
    }
}


List* reverse(List *list) {
    if (list == NULL) {
        return NULL;
    }
    else if (list->next == NULL) {
        return list;
    }
    else {
        return append(reverse(list->next), list->x, list->y);
    }
}


int contain(List *list, double x, double y) {
    if (list->next == NULL) {
        if (list->x == x && list->y == y) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (list->x == x && list->y == y) {
            return 1;
        }
    else {
            return contain(list->next, x, y);
        }
    }