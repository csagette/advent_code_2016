#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 10000

int char_to_int(char c);

int main()
{
    FILE* fichier = NULL;

    char chaine[TAILLE_MAX] = "";

    fichier = fopen("input.txt", "r");
    int S2=0;
    int j=0;
    int f=0;
    int t=0;
    int k=0;
    int* table=malloc(3*1908*sizeof(int));

    if (fichier != NULL)
    {

       while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
       {

         int i=0;

         while (*(chaine+i)==' '){
                      i=i+1;
         }
         int a=0;
         while (*(chaine+i)!=' '){//on recolte la direction
           int s=*(chaine+i)-48;
           a=10*a+s;
           i=i+1;
         }
         while (*(chaine+i)==' '){
                      i=i+1;
         }
         int b=0;
         while (*(chaine+i)!=' ' ){//on recolte la direction
           int s=*(chaine+i)-48;
           b=10*b+s;
           i=i+1;

         }
         while (*(chaine+i)==' '){
                      i=i+1;
         }
         int c=0;
         while (*(chaine+i)!='\n'){//on recolte la direction

           int s=*(chaine+i)-48;
           c=10*c+s;
           i=i+1;

         }

         if ((b+c)>a & (a+c)>b & (a+b)>c){
                     S2=S2+1;
                     t=t+1;
                     f=f-1;
         }
         *(table+k)=a;
         k=k+1;
         *(table+k)=b;
         k=k+1;
         *(table+k)=c;
         k=k+1;
         //printf("%d\t", a);
         //printf("%d\t", b);
         //printf("%d\t", c);
         //printf("%d\n",t);
         //printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
         j=j+1;
         f=f+1;
       }

       fclose(fichier);
    }
    printf("reponse 1 : %d\n",S2);
    //printf("%d\n",j);
    //printf("%d\n",f);


    //----------------------
    int S3=0;
    for (int t=0;t<1908*3;t=t+9){
        int a1=*(table+t);

        int a2=*(table+t+1);
        int a3=*(table+t+2);
        int b1=*(table+t+3);
        int b2=*(table+t+4);
        int b3=*(table+t+5);
        int c1=*(table+t+6);
        int c2=*(table+t+7);
        int c3=*(table+t+8);
        if ((b1+c1)>a1 & (a1+c1)>b1 & (a1+b1)>c1){
                    S3=S3+1;
        }
        if ((b2+c2)>a2 & (a2+c2)>b2 & (a2+b2)>c2){
                    S3=S3+1;
        }
        if ((b3+c3)>a3 & (a3+c3)>b3 & (a3+b3)>c3){
                    S3=S3+1;
        }
    }
    printf("reponse2: %d \n",S3);
    //printf("%d\n",char_to_int('3')+2);



    return 0;
}

int char_to_int(char c){
    if (c=='1'){
            return 1;
}
    if (c=='0'){
        return 0;
}
    if (c=='1'){
            return 1;
}
    if (c=='2'){
            return 2;
}
    if (c=='3'){
            return 3;
}
    if (c=='4'){
            return 4;
}
    if (c=='5'){
            return 5;
}
    if (c=='6'){
            return 6;
}
    if (c=='7'){
            return 7;
}
    if (c=='8'){
            return 8;
}
    if (c=='9'){
            return 9;
}
    return 0;

}
