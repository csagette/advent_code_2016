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

void print_list_spec(List *list) {
    if (list == NULL) {
        printf("%s\n", "liste vide");
    }
    else if (list->next == NULL) {
        if (list->value == 10) {
            printf("%c\n", 'A');
        }
        else if (list->value == 11){
            printf("%c\n", 'B');
        }
        else if (list->value == 12){
            printf("%c\n", 'C');
        }
        else if (list->value == 13){
            printf("%c\n", 'D');
        }
        else {
            printf("%d\n", list->value);
        }
    }
    else {
        while (list->next != NULL) {
            if (list->value == 10) {
            printf("%c\n", 'A');
            }
            else if (list->value == 11){
                printf("%c\n", 'B');
            }
            else if (list->value == 12){
                printf("%c\n", 'C');
            }
            else if (list->value == 13){
                printf("%c\n", 'D');
            }
            else {
                printf("%d\n", list->value);
            }
            list = list->next;
        }
        if (list->value == 10) {
            printf("%c\n", 'A');
            }
            else if (list->value == 11){
                printf("%c\n", 'B');
            }
            else if (list->value == 12){
                printf("%c\n", 'C');
            }
            else if (list->value == 13){
                printf("%c\n", 'D');
            }
            else {
                printf("%d\n", list->value);
            }
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