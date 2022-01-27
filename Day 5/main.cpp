

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include "MD5.h"

int main()
{
  std::string input = "abc"; //l'input donnee par aoc
  std::string attemp;//tentative de hash
  std::string password;//c'est l'output
  std::string password2 = "________";//output patie 2
  unsigned int index = 0;
  int m=0;//nombre de caracteres trouves pour le mot de passe de la partie 1
  int n=0;//nombre de caracteres trouves pour le mot de passe de la partie 2
  char attempt[32];//on ne hashera pas une chaine de plus de 32 caracteres
  MD5 md5;
  int partie1=1;
  while(index < 0xffffffff)//on tente pour tous les indices de 0 au maximum des entiers
  {
    snprintf(attempt, 32, "%s%u", input.data(), index);//compose l'input avec l'indice pour en faire une chaine de caractere a hasher

    attemp = md5.getMD5(attempt, strlen(attempt));//tentative de hash

    if (attemp.substr(0, 5) == "00000")//on ajoute le caractere au mot de passe si le hash debute par 5 zeros
    {
      char c = attemp[5];// le 6eme caractere du hash, celui qui est dans le mot de passe de la partie 1
      //et comme position du caractere dans le mot de passe de la partie 2
      
      //partie 1 
      if (partie1==1)
      {
        m=m+1;
        printf("symbole obtenu!\n");
        password += c;//on ajoute le premier caractere apres les 0
        if (m==8)//quand la taille est de 8 on peut print le mot de passe de la partie 1  
        {
          std::cout<<"reponse 1 : "<<password<<std::endl;
          partie1=0;//a partir de maintenant, on ne travaille plus que sur la partie 2
        }
      }

      //partie 2
      if ((c >= '0') && (c < '8'))//on ne garde c que si cela correspond a une position du mot de passe
      {
        int pos = c - '0';//on transforme c en entier
        if (password2[pos] == '_')//on ne change pas un caractere si il a deja ete trouve
        { 
          password2[pos] = attemp[6];//on ajoute le 7 eme caractere du hash dans le mot de passe a la ieme position
          n=n+1;//la longueur du mot de passe 2 trouve jusque la
        }

        if (n==8)//on s'arrete pour un mot de passe de longueur 8
        {
          std::cout<<"reponse 2 : "<<password2<<std::endl;
          return(0);
        }
      }
    }
    
    ++index;
  }

  return(0);
}