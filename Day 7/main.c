#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 10000

int mylen(char* s);

int main()
{
    int S=0;
    int S2=0;
    FILE* fichier = NULL;


    char chaine[TAILLE_MAX] = "";

    fichier = fopen("input2.txt", "r");

    if (fichier != NULL)
    {

       while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
       {
         //printf("%s\t", chaine);
         //printf("%d",mylen(chaine));
         //printf("%c",*(chaine+mylen(chaine)-1));
         int s=0;//=1 si l'IP supporte TLS
         int p=0;//=1 si l'IP supporte SSL
         int i=0;
         int j=0;
         int k=0;
         char* a=malloc(1000*sizeof(char));
         char* b=malloc(1000*sizeof(char));
         int t=0;
         while (i!=mylen(chaine)-1){//on recolte la direction
             int u=0;
             if (*(chaine+i)=='['){
                 t=1;
                 u=1;
                 *(a+j)='_';
                 j=j+1;

             }
             if (*(chaine+i)==']'){
                 t=0;
                 u=1;
                 *(b+k)='_';
                 k=k+1;
             }
             if (t==0 & u==0){
                 *(a+j)=*(chaine+i);
                 j=j+1;
             }
             if (t==1 & u==0){
                 *(b+k)=*(chaine+i);
                 k=k+1;

             }

             i=i+1;
         }
         *(a+j)='\0';
         *(b+k)='\0';

         //-------------------------
         i=0;
         while (i!=mylen(a)){
             if (*(a+i)==*(a+i+3) & *(a+i+1)==*(a+i+2) & *(a+i)!=*(a+i+1)){
                 s=1;
                 char* d=malloc(4*sizeof(char));
                 *(d)=*(a+i);
                 *(d+1)=*(a+i+1);
                 *(d+2)=*(a+i+2);
                 *(d+3)=*(a+i+3);
                 *(d+4)='\0';
                 //printf("%s\t",d);
             }



             i=i+1;
         }

         i=0;
         while (i!=mylen(b)){
             if (*(b+i)==*(b+i+3) & *(b+i+1)==*(b+i+2) & *(b+i)!=*(b+i+1)){
                 s=0;
                 char* c=malloc(4*sizeof(char));
                 *(c)=*(b+i);
                 *(c+1)=*(b+i+1);
                 *(c+2)=*(b+i+2);
                 *(c+3)=*(b+i+3);
                 *(c+4)='\0';
                 //printf("%s\n",c);
             }


             i=i+1;
         }


         i=0;
         while (i!=mylen(a)){
             if (*(a+i)==*(a+i+2) & *(a+i)!=*(a+i+1)){

                 int y=0;
                 while (y!=mylen(b)){
                     if (*(b+y)==*(b+y+2) & *(b+y)==*(a+i+1) & *(b+y+1)==*(a+i)){
                         p=1;
                         char* f=malloc(3*sizeof(char));
                         *(f)=*(a+i);
                         *(f+1)=*(a+i+1);
                         *(f+2)=*(a+i+2);

                         *(f+3)='\0';
                         //printf("%s\t",f);

                         char* h=malloc(3*sizeof(char));
                         *(h)=*(b+y);
                         *(h+1)=*(b+y+1);
                         *(h+2)=*(b+y+2);

                         *(h+3)='\0';
                         //printf("%s\t",h);
                     }
                     y=y+1;

                         //printf("%s\n",c);
                  }


             }
             i=i+1;

         }

         S=S+s;
         S2=S2+p;
         //printf("%s\n",b);
         //printf("%d\n",s);


       }

       fclose(fichier);
    }

    printf("S1=%d\n",S);
    printf("S2=%d\n",S2);


    return 0;
}



int mylen(char* s){
    char* p=s;
    int i=0;
    while (*p!='\0'){
        p=p+1;
        i=i+1;

}
    return i;
}


