#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
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

int contain_5_same_cond(std::string str, std::string x) {
    int i = 0;
    int size = str.size();
    int res = 0;
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
        if (x == t_0 && t_0 == t_1 && t_1 == t_2 && t_2 == t_3 && t_3 == t_4) {
            res = 1;
            i++;
        }
        else {
            i++;
        }
    }
    return res;
}


int main() {
    std::string salt = "abc";
    int stop = 0;
    int flag = 0;
    std::string saltMD5;
    std::string temp1;
    std::string temp2;
    int current_index = 0;
    std::string three_times;
    int five_times;
    int next_1000_hashes = 0;

    // condition tant qu'on a pas trouvé la 64-ème clé
    while (stop < 64) {
        // on crée le nouveau hachage
        temp1 = salt + std::to_string(current_index);
        saltMD5 = md5(temp1);
        // On vérifie si ce hachage contient un triplet, ie si three_times >= 0 car si il y a pas de triplet, la fonction contain_3_times renvoie -1
        three_times = contain_3_same(saltMD5);
        if (three_times != "-1") {
            // Si c'est le cas, on vérifie alors la condition de quintuplet sur les 1000 prochains hachages
            while (next_1000_hashes < 1000 && flag == 0) {
                temp2 = md5(salt + std::to_string(current_index+next_1000_hashes+1));
                five_times = contain_5_same_cond(temp2, three_times);
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
            flag = 0;
            next_1000_hashes = 0;
        }
        current_index++;
    }

    std::cout << current_index - 1 << " " << three_times <<std::endl;
    
    return 0;
}