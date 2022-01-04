#ifndef HEADER_H
#define HEADER_H


int steps_opti;

typedef struct _objet{
    char mat;
    char type;
    int floor;



}objet;

typedef struct _list_objet{
    objet * curr;
    struct _list_objet* next;



}liste;

typedef struct _list_list{
    liste* curr;
    struct _list_list* next;

}lliste;

void print_state(liste * l,int pos);
void print_floor(liste * l, int pos, int floor);
objet* create_objet(char mat,char type, int floor);
liste* insert(char mat,char type, int floor, liste* l);
int path(liste * l,int pos,int steps,int steps_opti,lliste* L);
int is_legal(liste * l,int pos,lliste* L);
int mylen(liste* l);
int is_done(liste*l);
liste* new_list(liste*l);
void change(liste* l, int rang,int dir);
int is_empty(liste* liste, int floor);
int is_equal(liste* l1,liste* l2);
int in(liste* l, lliste* L);
lliste* iinsert(liste* l, lliste* L);



#endif // HEADER_H
