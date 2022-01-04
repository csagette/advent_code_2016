#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

/* On choisit de remplacer A, B, C et D par 10, 11, 12 et 13. */

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
            /** Lecture de la direction **/
            current = fgetc(file);

            /** Lecture à la suite des chemins menant à un nombre du code **/
            while (current != 10 && current != EOF) {

                /** Réalsation des tests pour savoir si on sort ou non du cadre du keypad **/

                if (current == 85) {    /* UP = U = 85 (dec) */
                    if (temp_button == 3 || temp_button == 13) {
                        temp_button = temp_button - 2;
                    }
                    else if (temp_button == 6  || temp_button == 7 || temp_button == 8 || temp_button == 10 || temp_button == 11 || temp_button == 12) {
                        temp_button = temp_button - 4;
                    }
                }

                else if (current == 68) {    /* DOWN = D = 68 (dec) */
                    if (temp_button == 1 || temp_button == 11) {
                        temp_button = temp_button + 2;
                    }
                    else if (temp_button == 2  || temp_button == 3 || temp_button == 4 || temp_button == 6 || temp_button == 7 || temp_button == 8) {
                        temp_button = temp_button + 4;
                    }
                }

                else if (current == 82) {    /* RIGHT = R = 82 (dec) */
                    if (temp_button != 1 && temp_button != 4 && temp_button != 9 && temp_button != 12 && temp_button != 13) {
                        temp_button = temp_button + 1;
                    }
                }

                else {                      /* LEFT = L */
                    if (temp_button != 1 && temp_button != 2 && temp_button != 5 && temp_button != 10 && temp_button != 13) {
                        temp_button = temp_button - 1;
                    }
                }
                current = fgetc(file);
            }
            if (current != EOF) {
                code = append(code, temp_button);
            }
        }
        print_list_spec(code);
        fclose(file);
        return 0;
    }
}