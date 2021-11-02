#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void print_list(List* list) {
    if (list == NULL) {
        printf("%s\n", "liste vide");
    }
    else if (list->next == NULL) {
        printf("%d\n", list->value);
    }
    else {
        while (list->next != NULL) {
            printf("%d ", list->value);
            list = list->next;
        }
        printf("%d ", list->value);
    }
}

List *insert (List *list, int e) {
    List *res = malloc(sizeof(List));
    res->value = e;
    res->next = list;
    return res;
}


List *append(List *list, int e) {
    if (list == NULL) {
        return insert(NULL, e);
    }
    else {
        return insert(append(list->next, e) ,list->value);
    }
}


List* reverse(List*list) {
    if (list == NULL) {
        return NULL;
    }
    else if (list->next == NULL) {
        return list;
    }
    else {
        return append(reverse(list->next), list->value);
    }
}