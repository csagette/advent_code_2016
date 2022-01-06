#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "md5.h"

std::string contain_3_same(std::string str) {
    int i = 0;
    int size = str.size();
    std::string res = "-1";
    std::string t_0;
    std::string t_1;
    std::string t_2;
    while (i+2 < size && res == "-1") {
        t_0 = str[i];
        t_1 = str[i+1];
        t_2 = str[i+2];
        if (t_0 == t_1 && t_1 == t_2) {
            res = t_0;
            i++;
        }
        else {
            i++;
        }
    }
    return res;
}

std::vector<int> contain_5_same_cond(std::string str, std::string x) {
    int i = 0;
    int size = str.size();
    int res = 0;
    int res2 = 0;
    std::string t_0;
    std::string t_1;
    std::string t_2;
    std::string t_3;
    std::string t_4;
    while (i+4 < size && res == 0) {
        t_0 = str[i];
        t_1 = str[i+1];
        t_2 = str[i+2];
        t_3 = str[i+3];
        t_4 = str[i+4];
        if (t_0 == t_1 && t_1 == t_2 && t_2 == t_3) {
            res2 = 1;
        }
        if (x == t_0 && t_0 == t_1 && t_1 == t_2 && t_2 == t_3 && t_3 == t_4) {
            res = 1;
            i++;
        }
        else {
            i++;
        }
    }
    if (str[size-1] == str[size-2] && str[size-2] == str[size-3]) {
        res2 = 1;
    }
    else if (str[size-2] == str[size-3] && str[size-3] == str[size-4]) {
        res2 = 1;
    }
    else if (str[size-2] == str[size-3] && str[size-3] == str[size-4]) {
        res2 = 1;
    }
    std::vector<int> res_f = {res, res2};
    return res_f;
}




int main() {
    /*std::string salt = "abc39";
    std::string saltMD5 = md5(salt);
    std::cout << saltMD5 << std::endl;
    std::cout << md5("abc816") << std::endl;
    std::cout << contain_3_same(saltMD5) << std::endl;
    std::cout << contain_5_same_cond(md5("abc816"), contain_3_same(saltMD5))[0][0] << std::endl;*/
    
    std::string salt = "abc";
    std::vector<int> next_to_use_index = {0};
    int size_next_index = next_to_use_index.size();
    int i_index = 0;
    int stop = 0;
    int flag = 0;
    std::string saltMD5;
    std::string temp1;
    std::string temp2;
    int current_index;
    std::string three_times;
    int five_times;
    std::vector<int> five_times_in_row;
    int next_1000_hashes = 0;
    int flag_next_index;

    // condition tant qu'on a pas trouvé la 64-ème clé
    while (stop <= 64) {

        // on enregistre la prochaine clé avec probablement un doublé grâce au passage dans la fonction contain_5_same_cond
        current_index = next_to_use_index[i_index];
        // on crée le nouveau hachage
        temp1 = salt + std::to_string(current_index);
        saltMD5 = md5(temp1);
        // On vérifie si ce hachage contient un triplet, ie si three_times != "-1" car si il y a pas de triplet, la fonction contain_3_times renvoie -1
        three_times = contain_3_same(saltMD5);

        if (three_times != "-1") {
            std::cout << current_index << " " << three_times <<std::endl;
            // Si c'est le cas, on vérifie alors la condition de quintuplet sur les 1000 prochains hachages
            while (next_1000_hashes < 1000 && flag == 0) {

                temp2 = md5(salt + std::to_string(current_index+next_1000_hashes+1));

                five_times_in_row = contain_5_same_cond(temp2, three_times);
                five_times = five_times_in_row[0];
                flag_next_index = five_times_in_row[1];

                // on ajoute ou non l'index current_index+next_1000_hashes+1 si ce dernier possède un triplet
                if (flag_next_index == 1 && std::find(next_to_use_index.begin(), next_to_use_index.end(), current_index+next_1000_hashes+1) == next_to_use_index.end()) {
                    next_to_use_index.push_back(current_index+next_1000_hashes+1);
                }

                // on vérifie si on a trouvé un quintuplet, 0 == non, 1 == oui
                if (five_times == 1) {
                    flag = 1;
                    stop++;
                    next_1000_hashes++;
                }
                else {
                    next_1000_hashes++;
                }
            }
            //Condition de sécurité au cas où si sur les 1000 index on venait à rencontrer aucun triplet
            if (size_next_index == next_to_use_index.size()) {
                next_to_use_index.push_back(current_index + 1);
                size_next_index = next_to_use_index.size();
            }
            flag = 0;
            next_1000_hashes = 0;
        }
        else {
            next_to_use_index.push_back(current_index + 1);
            size_next_index = next_to_use_index.size();
        }
        i_index++;
    }

    return current_index;
}