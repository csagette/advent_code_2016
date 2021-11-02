#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"


void change_dir(int current, int *past_dir) {
    if (current == 82) {    /* Si on tourne à droite (R = 82 en dec) */
        *past_dir = (*past_dir - 1) % 4;
    }
    else {
        *past_dir = (*past_dir + 1) % 4;
    }

}

int main() {
    /*
    int current = 82;
    int past_dir = 1;
    change_dir(current, &past_dir);
    printf("%d", past_dir);
    
    char* str = malloc(sizeof(int));
    sprintf(str, "%d", 52-48);
    printf("%s", str);
    
    char* temp = "54";
    int len = strlen(temp);
    printf("%d\n", *(temp+1) - 48);
    printf("%lf", (*temp - 48)*pow(10, 1) + (*(temp+1) - 48)*pow(10, 0));
    printf("%d", -1 % 4);
    
    List *list = malloc(sizeof(List));
    list->x = 3;
    list->y = 4;
    list->next = NULL;
    List* list2 = malloc(sizeof(List));
    list2->x = 1;
    list2->y = 3;
    list2->next = list;
    double x = 1;
    double y = 2;
    print_list(list2);
    int res = contain(list2, x, y);
    printf("(x,y) in list2 = %d", res);
    free(list);
    free(list2);
    */
    List *list = malloc(sizeof(List));
    list->x = 3;
    list->y = 4;
    list->next = NULL;
    list = append(list, 2, 4);
    print_list(list);
    return 0;
}

