#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 1000000

int mylen(char* s);

long long int char_to_int(char c);

int length1(char* chaine);
long long int length2(char* chaine);

int main()
{
    FILE* fichier = NULL;

    char chaine[TAILLE_MAX] = "";

    fichier = fopen("input2.txt", "r");

    if (fichier != NULL)
    {
       fgets(chaine, TAILLE_MAX, fichier);
    }
    //printf("%s",chaine);

    printf("reponse 1 : %d\n",length1(chaine));
    printf("reponse 2 : %lld\n",length2(chaine));


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

long long int char_to_int(char c){
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




int length1(char* chaine){
    int j=0;
    int i=-1;
    while (i<mylen(chaine)){
      //printf("%c\t",*(chaine+i));
      i=i+1;
      j=j+1;
      if (*(chaine+i)=='('){
          j=j-1;//pour pas compter la parenthese
          i=i+1;
          int a=0;

          while (*(chaine+i)!='x'){//on recolte le nombre
            a=10*a+char_to_int(*(chaine+i));
            i=i+1;
          }
          i=i+1;
          int b=0;
          while (*(chaine+i)!=')'){//on recolte le nombre
            b=10*b+char_to_int(*(chaine+i));
            i=i+1;

          }
          //printf("%dx%d\t",a,b);


          j=j+a*b;
          //printf("%d\t",j);
          if (i+a+2<mylen(chaine)){
              //printf("%d\t",j);
              i=i+a;
          }
          else
          {
               //printf("%d\t",j);
              break;
          }
      }
    }
    //printf("%s\n\n\n",chaine);
    return j;
}

long long int length2(char* chaine){
    long long int j=0;
    int i=-1;
    while (i<mylen(chaine)){
      //printf("%c\t",*(chaine+i));
      i=i+1;
      j=j+1;
      if (*(chaine+i)=='('){
          j=j-1;//pour pas compter la parenthese
          i=i+1;
          int a=0;

          while (*(chaine+i)!='x'){//on recolte le nombre
            a=10*a+char_to_int(*(chaine+i));
            i=i+1;
          }
          i=i+1;
          long long int b=0;
          while (*(chaine+i)!=')'){//on recolte le nombre
            b=10*b+char_to_int(*(chaine+i));
            i=i+1;

          }
          //printf("%dx%d   ",a,b);

          char* chaine2=malloc(10000*sizeof(char));
          for (int op=0;op<a;op++){
                   *(chaine2+op)=*(chaine+i+1);
              i=i+1;


          }
          *(chaine2+a)='\0';
          j=j+length2(chaine2)*b;
          //printf("%s\n",chaine2);
          //printf("%I64d\n",length2(chaine2));


      }
    }
    //printf("%s\n\n\n",chaine);
    return j-1;
}


