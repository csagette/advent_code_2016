#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int steps_opti;

int main()
{


    liste *l=malloc(sizeof(liste));
    l->next=NULL;
    /*
    int pos=1;
    l=insert('p','g',1,l);
    l=insert('t','g',1,l);
    l=insert('t','c',1,l);
    l=insert('e','g',1,l);
    l=insert('r','g',1,l);
    l=insert('r','c',1,l);
    l=insert('c','g',1,l);
    l=insert('c','c',1,l);
    l=insert('p','c',2,l);
    l=insert('e','c',2,l);
    print_state(l,pos);

    printf("length : %d\n",mylen(l));
    printf("c'est fait : %d\n",is_done(l));

    liste* l0=new_list(l);

    //l0=l0->next;

    print_state(l,pos);
    printf("\n");
    print_state(l0,pos);
    //printf("min : %d\n",min(2,3));

    change(l0,1,1);
    change(l0,0,1);
    change(l0,0,1);
    print_state(l0,2);

    lliste* L=malloc(sizeof(lliste));
    L->next=NULL;
    printf("%d\n",is_legal(l,pos, L));
    */

    l=insert('l','c',1,l);
    l=insert('h','g',2,l);
    l=insert('l','g',3,l);


    lliste* L=malloc(sizeof(lliste));
    L->next=NULL;

    printf("reponse 1 : %d",path(l,1,0,100000,L));

    return 0;
}
