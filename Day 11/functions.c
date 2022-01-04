#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"




objet* create_objet(char mat,char type, int floor){
    objet *t=malloc(sizeof(objet));
    t->floor=floor;
    t->type=type;
    t->mat=mat;
    return t;
}

liste* insert(char mat,char type, int floor, liste* l){
    objet* a=create_objet(mat,type,floor);
    liste *lu=malloc(sizeof(liste));
    lu->curr=a;
    lu->next=l;

    return  lu;


}

void print_floor(liste * l,int pos,int floor){//c est de taille 4*12*sizeof(char)

    printf("F%d: ",floor);
    if (pos==floor){
        printf("E ");
    }
    else{
        printf("  ");
    }


    while(l->next!=NULL){
        if (l->curr->floor==floor){
            printf("%c%c  ",l->curr->mat,l->curr->type);
        }
        l=l->next;
    }
    printf("\n");
}

void print_state(liste*l,int pos){
    print_floor(l,pos,4);
    print_floor(l,pos,3);
    print_floor(l,pos,2);
    print_floor(l,pos,1);
    printf("\n");

}

int mylen(liste* l){
    int S=0;
    while(l->next!=NULL){
        S++;
        l=l->next;
    }
    return S;
}
int is_done(liste*l){
    int S=0;
    for(int i=0;i<mylen(l);i++){
        if (l->curr->floor==4){
            S++;
        }
        l=l->next;
    }
    int t=0;
    if (S==10){
        t=1;
    }
    return t;
}


liste* new_list(liste*l){
    liste* l0=malloc(sizeof(liste));
    l0->next=NULL;
    while (l->next!=NULL){
        l0=insert(l->curr->mat,l->curr->type,l->curr->floor,l0);
        l=l->next;
    }
    return l0;
}

void change(liste* l, int rang,int dir){

    int i=0;
    while (l->next!=NULL & i<rang){
        l=l->next;
        i++;
    }
    l->curr->floor=l->curr->floor+dir;


}

//#---------------------------------------------------------------------------------------------------------------------------------------------------------
int path(liste * l,int pos,int steps,int steps_opti,lliste* L){//steps_opti=min(path(l,pos,steps,steps_opti),steps_opti))   return steps_opti

    L=iinsert(l,L);

    if (is_done(l)==1){
        return steps;
    }
    steps=steps+1;

    liste* l2=new_list(l);
    liste* list_floor=malloc(sizeof(liste));
    list_floor->next=NULL;
    while (l2->next!=NULL){
        if (l2->curr->floor==pos){
                list_floor=insert(l2->curr->mat,l2->curr->type,l2->curr->floor,list_floor);
        }
        l2=l2->next;
    }


    l2=new_list(list_floor);

    //print_state(l2,pos);
    int i;

    for (i=0;i<mylen(l2);i++){
         pos=pos+1;
         change(l2,i,1);
         if (is_legal(l2,pos,L)==1){
             printf("%d\n",path(l,pos,steps,steps_opti,L));
         }
         pos=pos-1;
    }

    l2=new_list(list_floor);
    for (i=0;i<mylen(l2);i++){
         change(l2,i,-1);
         pos=pos-1;
         if (is_legal(l2,pos,L)==1){
             printf("%d\n",path(l,pos,steps,steps_opti,L));

         }
         pos=pos+1;
    }

    int j;
    l2=new_list(list_floor);
    for (i=0;i<mylen(l2);i++){
       for(j=0;j<mylen(l2) && j!=i;j++){

            change(l2,i,1);
            change(l2,j,1);

            pos=pos+1;
            if (is_legal(l2,pos,L)==1){
               printf("%d\n",path(l,pos,steps,steps_opti,L));
            }
            pos=pos-1;
       }
    }

    l2=new_list(list_floor);
    for (i=0;i<mylen(l);i++){
        for(j=0;j<mylen(l) && j!=i;j++){
            pos=pos-1;
            change(l2,i,-1);
            change(l2,j,-1);
            if (is_legal(l,pos,L)==1){
               printf("%d\n",path(l,pos,steps,steps_opti,L));
            }
            pos=pos+1;
        }
    }
    l2=new_list(list_floor);

    pos=pos+1;
    if (is_legal(l,pos,L)==1){
               printf("%d\n",path(l,pos,steps,steps_opti,L));
    }

    pos=pos-1;

    pos=pos-1;
    if (is_legal(l,pos,L)==1){
           printf("%d\n",path(l,pos,steps,steps_opti,L));
    }
    pos=pos+1;
    return 100000000;
}

int is_legal(liste* l,int pos,lliste* L){//regle 1 pas d'etage -1 ou 5
    //regle 2 pas de g et de c pas de meme nom au meme etage si ils n'ont pas la meme mat sauf si ils sont pairés

    if (in(l,L)==1){
        return 0;
    }
    liste* l2=new_list(l);
   // printf("%d\n",l2->next->next->next->next->next->next->next->next->curr->floor);

    if (pos<=0  | pos>=5){
        return 0;
    }
    while (l2->next!=NULL){
        if ((l2->curr->floor<=0)  | (l2->curr->floor>=5)){
            return 0;
        }
        l2=l2->next;
    }//ça marche
    if (in(l,L)==1){
        return 0;
    }


   // print_state(list_floor,pos);
    l2=new_list(l);
    liste* list_floor=malloc(sizeof(liste));
    list_floor->next=NULL;
    while (l2->next!=NULL){
        if (l2->curr->floor==pos){
                list_floor=insert(l2->curr->mat,l2->curr->type,l2->curr->floor,list_floor);
        }
        l2=l2->next;
    }


    liste* lt=new_list(list_floor);
    liste* lj=new_list(list_floor);

    liste* l_chips=malloc(sizeof(liste));
    liste* l_gen=malloc(sizeof(liste));

    l_chips->next=NULL;
    l_gen->next=NULL;

    while (lj->next!=NULL){
        //printf("%c\n",lj->curr->type);
        if (lj->curr->type=='c'){
               l_chips=insert(lj->curr->mat,lj->curr->type,lj->curr->floor,l_chips);
        }

        lj=lj->next;
    }
    while (lt->next!=NULL){
        if (lt->curr->type=='g'){
                l_gen=insert(lt->curr->mat,lt->curr->type,lt->curr->floor,l_gen);
        }
        lt=lt->next;
    }

   // print_state(l_chips,1);
    //print_state(l_gen,pos);


    while (l_chips->next!=NULL){
        int i=1;
        liste*lg=new_list(l_gen);
        while (lg->next!=NULL){
            if (lg->curr->mat==l_chips->curr->mat){
                i=200;
            }

            if (lg->curr->mat!=l_chips->curr->mat){
                i=i-1;

            }
            lg=lg->next;


        }
        if (i<=0){
            return 0;
        }
        l_chips=l_chips->next;

    }






    return 1;//ça marche

}


//#--------------------------------------------------------------------------------------------------------------------------------------------------------

int is_empty(liste* liste, int floor){
    while (liste->next!=NULL){
          if   (liste->curr->floor==floor){
              return 0;
          }
          liste=liste->next;
    }
    return 1;

}
int is_equal(liste* l1,liste* l2){//pour la liste entiere


    while (l1->next!=NULL){
        if (l1->curr->floor!=l2->curr->floor){
            return 0;
        }
        l1=l1->next;
        l2=l2->next;
    }
    return 1;
}

int in(liste* l, lliste* L){
    while (L->next!=NULL){
        if (is_equal(L->curr,l)==1){
            return 1;
        }
        L=L->next;
    }
    return 0;

}

lliste* iinsert(liste* l, lliste* L){

    lliste *lù=malloc(sizeof(lliste));
    lù->curr=l;
    lù->next=L;

    return  lù;


}




