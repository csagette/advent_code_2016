#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"


int main () {

    FILE *file = NULL;
    int current = 0;
    double x = 0;
    double y = 0;
    /** On note 0->Est, 1->Nord, 2->Ouest, 3->Sud **/
    int past_dir = 1;
    int len = 0;
    /* Liste chainée du chemin parcouru */
    List* list = malloc(sizeof(List));
    list->x = 0;
    list->y = 0;
    list->next = NULL;
    int dep_temp = 1;

    file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("ouverture du fichier impossible");
    }
    else {
        while (current != EOF) {

            /** Lecture de la direction **/
            current = fgetc(file);

            /** Mise à jour du changement de direction **/
            if (current == 82) {    /** Si on tourne à droite (R = 82 en dec) **/
                past_dir = (past_dir - 1 + 4) % 4;
            }
            else {
                past_dir = (past_dir + 1 + 4) % 4;
            }
            /** Lecture du nombre de pas **/
            current = fgetc(file);
            char *temp = malloc(4*sizeof(int));
            while (current != 44 && current != 10) { 
                char* str = malloc(sizeof(int));
                sprintf(str, "%d", current-48);
                strcat(temp, str);
                current = fgetc(file);
            }
            /*printf("temp = %s\n", temp);*/
            len = strlen(temp);
            /*printf("len = %d\n", len);*/
            double deplacement = 0;
            int i;
            for (i=0; i < len; i++) {
                deplacement = deplacement + (*(temp+i) - 48) * pow(10, len-i-1);
            }
            /*printf("deplacement = %lf\n", deplacement);*/
            /** Ajustement de la nouvelle position **/
            /*printf("past_dir = %d\n", past_dir);*/
            int bool = 0;
            if (past_dir == 0){
                while (dep_temp <= deplacement) {
                    bool = contain(list, x+dep_temp, y);
                    if (bool == 1) {
                        printf("Le point (x,y) = (%lf,%lf) a déjà été visité\n", x+dep_temp, y);
                        printf("La distance est de %lf blocs\n", fabs(x+dep_temp-y));
                        return 0;
                    }
                    else {
                        list = append(list, x+dep_temp, y);
                        dep_temp = dep_temp + 1;
                    }
                }
                x=x+deplacement;
                dep_temp = 1;
            }
            else if (past_dir == 1){
                while (dep_temp <= deplacement) {
                    bool = contain(list, x, y+dep_temp);
                    if (bool == 1) {
                        printf("Le point (x,y) = (%lf,%lf) a déjà été visité\n", x, y+dep_temp);
                        printf("La distance est de %lf blocs\n", fabs(x-dep_temp-y));
                        return 0;
                    }
                    else {
                        list = append(list, x, y+dep_temp);
                        dep_temp = dep_temp + 1;
                    }
                }
                y=y+deplacement;
                dep_temp = 1;
            }
            else if (past_dir == 2){
                while (dep_temp <= deplacement) {
                    bool = contain(list, x-dep_temp, y);
                    if (bool == 1) {
                        printf("Le point (x,y) = (%lf,%lf) a déjà été visité\n", x-dep_temp, y);
                        printf("La distance est de %lf blocs\n", fabs(x-dep_temp-y));
                        return 0;
                    }
                    else {
                        list = append(list, x-dep_temp, y);
                        dep_temp = dep_temp + 1;
                    }
                }
                x=x-deplacement;
                dep_temp = 1;
            }
            else {
                while (dep_temp <= deplacement) {
                    bool = contain(list, x, y-dep_temp);
                    if (bool == 1) {
                        printf("Le point (x,y) = (%lf,%lf) a déjà été visité\n", x, y-dep_temp);
                        printf("La distance est de %lf blocs\n", fabs(x+dep_temp-y));
                        return 0;
                    }
                    else {
                        list = append(list, x, y-dep_temp);
                        dep_temp = dep_temp + 1;
                    }
                }
                y=y-deplacement;
                dep_temp = 1;
            }
            current = fgetc(file);
            }
            print_list(list);
            /*printf("x = %lf\n", x);
            printf("y = %lf\n", y);*/
            printf("La distance est de %lf blocs", fabs(y)+fabs(x));
        }
    fclose(file);

    return 0;
}