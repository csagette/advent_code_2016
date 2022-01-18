
#include <set>
#include <iostream>
#include <limits>
#include <bitset>
#include <algorithm>
#include <map>
#include <array>

constexpr size_t num_assemblies=7;
//constexpr size_t num_assemblies=5;

uint32_t solver_time = 100;//on se donne un maximum de 100 étapes pour résoudre le problème

class State
{
public:
  std::bitset<32> bitset;//chaque state est un bitset contenant les coordonnées de chaque objet

  uint8_t get_my_floor() const
  {//donne notre etage
    return get_item_floor(num_assemblies*2);// car num_assemblies*2 est la place de l'etage dans le bitset 
  }

  uint8_t get_item_floor(const size_t &item) const
  {
    return ((bitset >> (item*2)).to_ullong() & 3);//donne l'etage de l'objet
  }

  void set_item_floor(const size_t &item, const uint8_t &new_floor)
  {//transforme le numero de l'etage en nombre binaire et le stocke sur 2 bits
    bitset[item*2] = new_floor & 1;
    bitset[item*2+1] = new_floor & 2;
  }

  void set_my_floor(const uint8_t &new_floor)
  {
    set_item_floor(num_assemblies*2, new_floor);//num_assemblies*2 c'est pour dire que notre position se trouve en dernier dans la liste des bits
  }

  bool operator<(const State &state) const
  {
    return bitset.to_ullong() < state.bitset.to_ullong();   //compare le bitset actuel avec le bitset d'un autre state(etat plus ou moins avance?)
  }

  bool is_valid() const
  {
    for (size_t m=0; m<num_assemblies; ++m)//on checke pour tous les objets
      {
        if(get_item_floor(m*2)!=get_item_floor(m*2+1))//IMPORTANT les elements qui se suivent sont les gen et rec respectifs
        //ici on rentre que si le gen n'est pas au meme etage que le rec
          {
            for (size_t g=0; g<num_assemblies; ++g)
              {
                if(get_item_floor(m*2+1)==get_item_floor(g*2))
                  return false;//si un recepteur est tout seul avec un autre generateur sur le meme etage, la position n'est pas valide
              }
          }
      }
    return true;
  }

  bool is_solved() const
  {
    std::bitset<32> position_only;
    for (size_t p=0; p<(num_assemblies)*2 + 2; ++p)
      position_only[p]=true;
    return (bitset & position_only)
      == position_only;//return true si notre bitset est composé que de 1 donc toutes les positions sont en 3 c'est a dire au 4eme etage
     
  }

  bool same_position(const State &s) const
  {//retourne true si la position obtenue est la meme que celle actuelle (auquel cas on ne passe pas dessus)
    return bitset== s.bitset;
  }

  bool lower_floors_empty(const uint8_t &floor) const
  {//si il n'y a rien dans les étages d'en dessous on descend pas
    for(size_t item=0; item<num_assemblies*2; ++item)
      {
        if(get_item_floor(item)<floor)
          return false;
      }
    return true;
  }

  void repack()
  {
    std::array<uint8_t,num_assemblies> temp;
    for(size_t a=0; a<num_assemblies; ++a)
      temp[a]=get_item_floor(a*2) + 4*get_item_floor(a*2+1);//temp[a] contient l'étage du générateur et du microchip correspondant, bien séparé
    std::sort(temp.begin(), temp.end());//on trie temp par numéro d'étage de générateur croissant puis parpar numéro d'étage de microchip croissant 
  
    for(size_t a=0; a<num_assemblies; ++a)//on replace dans le bitset les items triés
      {
        set_item_floor(a*2,temp[a] & 3);//on ne garde que les deux derniers bits de temp[a] qui correspond a l'etage du generateur
        set_item_floor(a*2+1,temp[a] >> 2 & 3);//on ne garde que les deux premiers bits de temp[a] qui correspond a l'etage du microchip
      }
  }
};



void explore(const State &current_state, const uint32_t &time,
             std::map<uint32_t,uint32_t> &states);

void try_new_state(const State &new_state, const uint32_t &time,
                   std::map<uint32_t,uint32_t> &states)
{
  if(new_state.is_valid())
    {
      State repacked_state(new_state);
      repacked_state.repack();

      uint32_t new_uint32_t (repacked_state.bitset.to_ulong());//on check si le nouveau state a deja été parcouru
  
      auto match (states.find(new_uint32_t));
      if(match!=states.end())//si on l'a trouvé,...
        {
          if (time < match->second)//si on l'a trouvé plus vite que la première fois, on garde le meilleur temps et on explore à partir de là, sinon on fait rien
            {
              match->second=time;
              explore(repacked_state, time, states);
            }
        }
      else//si on l'a pas trouvé, on l'ajoute à notre map et on continue à explorer
        {
          states.insert(std::make_pair(new_uint32_t,time));
          explore(repacked_state, time, states);
        }
    }
}

void explore(const State &current_state, const uint32_t &time,
             std::map<uint32_t,uint32_t> &states)
{
  if (time>solver_time)
    return;//pour ne pas continuer à explorer si on a déja trouvé une solution qui met moins longtemps

  if (current_state.is_solved())
    {
      solver_time=time;//on met à jour solver_time
      return;
    }
  // On tente toutes les permutations haut et bas jusqu'a trouver le resultat

  uint8_t current_floor=current_state.get_my_floor();//
  int8_t new_floor(current_floor==3 ? 2 : current_floor+1);//si on est en étage 3 on ne peut que descendre, sinon, on essaie de monter
  for (new_floor=new_floor; new_floor>=0 && new_floor>=current_floor-1; new_floor-=2)//l'étage est toujours supérieur à 0 
  // par étape on peut aller soit en haut (current_floor+1), soit en bas (current_floor-1), on ne passe donc que 2 fois dans la boucle

    {
      if(!(new_floor<current_floor
           && current_state.lower_floors_empty(current_floor)))//on ne descend pas s'il n'y a pas d'objets en dessous de notre étage
           //et on ne monte pas sans objet avec nous
        {
          for(size_t item=0; item<num_assemblies*2; ++item)//on fais bouger le premier objet
            {
              if(current_floor==current_state.get_item_floor(item))//on ne peut prendre que des objets à notre étage
                {
                  auto new_state(current_state);// on créé un nouvel état identique à l'état actuel
                  new_state.set_item_floor(item,new_floor);//on change l'étage de l'objet 1
                  new_state.set_my_floor(new_floor);// on change notre étage
                  try_new_state(new_state,time+1,states);//on vérifie si l'état respecte les règles
                  //std::cout << time << "\n";
                  for(size_t item2=item+1; item2<num_assemblies*2; ++item2)//on fait bouger le deuxième objet
                    {
                      if(current_floor==current_state.get_item_floor(item2))//on ne prend que des objet de notre étage
                        {//idem que pour l'item 1
                          auto new_state2(new_state);
                          new_state2.set_item_floor(item2,new_floor);
                          try_new_state(new_state2,time+1,states);
                        }
                    }
                }
            }
        }
    }
}

int main()
{
  std::map<uint32_t,uint32_t> states;// on stocke les états dans une map
  State initial_state;

  /*
  initial_state.set_item_floor(0,1);
  initial_state.set_item_floor(1,0);
  initial_state.set_item_floor(2,2);
  initial_state.set_item_floor(3,0);
   */
  

  //en première position on place le numéro de l'objet.
  //Les nombres pairs sont les générateurs 
  //les nombres impairs qui les suivent sont les chips correspondants
  //en deuxième position est l'étage de l'objet qui va de 0 à 3.
  initial_state.set_item_floor(0,0);
  initial_state.set_item_floor(1,1);
  initial_state.set_item_floor(2,0);
  initial_state.set_item_floor(3,0);
  initial_state.set_item_floor(4,0);
  initial_state.set_item_floor(5,1);
  initial_state.set_item_floor(6,0);
  initial_state.set_item_floor(7,0);
  initial_state.set_item_floor(8,0);
  initial_state.set_item_floor(9,0);
  

  initial_state.set_item_floor(10,0);
  initial_state.set_item_floor(11,0);
  initial_state.set_item_floor(12,0);
  initial_state.set_item_floor(13,0);
  
//on commence à l'étage 0
  initial_state.set_my_floor(0);


  states.insert(std::make_pair(static_cast<uint32_t>(initial_state.bitset.to_ulong()),uint32_t(0)));
  //la liste des états contient les paires des états parcourus avec le time que cela a mis pour arriver là

  explore(initial_state, 0, states);
  std::cout << "reponse: "
                << solver_time << "\n";
  //obtenir des nombres impairs decroissants c'est normal parce que si tu  arrive en n fois a destination tu peux aussi arriver en n+2 fois a destination mais pas en n+1 fois 
}
