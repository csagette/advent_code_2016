
#include <set>
#include <iostream>
#include <limits>
#include <bitset>
#include <algorithm>
#include <map>
#include <array>

std::bitset<128> process(std::string inpt_);

std::bitset<128> step(std::bitset<128> input,int n);

int main()
{
  //question 1
  //int n_rows=40;   
  //quastion 2
  int n_rows=400000;
  
  std::string input_ (".^..^....^....^^.^^.^.^^.^.....^.^..^...^^^^^^.^^^^.^.^^^^^^^.^^^^^..^.^^^.^^..^.^^.^....^.^...^^.^.");
  int len=input_.size();
  //std::cout << "len " << len << "\n";
  //std::string input_(".^.");
  
  std::bitset<128> input=process(input_);
  std::cout <<"notre input:"<< input << "\n";

  //std::bitset<128> new_input=step(input,input_.size());
  
  int s=0;//s est le nombre total de piège
  s=s+len-input.count();
  //std::cout << "s " << s << "\n";
  
  for (int i=0;i<n_rows-1;i++){
      std::bitset<128> new_input=step(input,len);
      s=s+len-new_input.count();
      input=new_input;
      
  }
  
  std::cout << "reponse: " << s << "\n";
}

std::bitset<128> process(std::string inpt_)//le bitset est encodé en sens inverse
{
    std::bitset<128> input;
    int len=inpt_.size();
    input[0]=0;//on considère que les bords sont safe donc l'abscisse 0 qui sera le premier bord sera 0 donc safe
    for (int i=0;i<len;i++){
        if (inpt_[i]=='.'){
            input[i+1]=0;
        }
        else if (inpt_[i]=='^'){
            input[i+1]=1;
        }

    }
    return(input);
}

std::bitset<128> step(std::bitset<128> input,int n)
{
      std::bitset<128> new_input;
      new_input[0]=0;//on prend le bord comme safe

      for (int i=1;i<n+1;++i){
          //std::cout  << input[i] << "\t";
          int sum=input[i-1]+input[i]+input[i+1];
          
          if (sum==0){
              new_input[i]=0;
          }
          
          if (sum==3){
              new_input[i]=0;
          }
          if (sum==1){
              if (input[i]==1){
              new_input[i]=0;
              }
              else
              {
                  new_input[i]=1;
              }
          }
          if (sum==2){
              if (input[i]==1){
                new_input[i]=1;
              }
              else
              {
                  new_input[i]=0;
              }
          }
      }
      //std::cout  << new_input << "\n";
      return(new_input);
}