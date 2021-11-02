#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"


int main () {
    FILE *file = NULL;
    int current = 0;
    int temp_button = 5;
    List* code = NULL;
    file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("ouverture du fichier impossible");
    }
    else {
        while (current != EOF) {
            current = fgetc(file);
            printf("%d\n", current);
            while (current != 10 && current != EOF) {
                /** Réalsation des tests pour savoir si on sort ou non du cadre du keypad **/
                if (current == 85) {    /* UP = U = 85 (dec) */
                    if (temp_button != 1 && temp_button != 2 && temp_button != 3) {
                        temp_button = temp_button - 3;
                    }
                }
                current = fgetc(file);
            }
            code = append(code, temp_button);
        }
    }
    return 0;
}
