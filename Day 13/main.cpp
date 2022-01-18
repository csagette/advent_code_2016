#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <bitset>
#include <cmath>
#include <map>


int count_1(std::string str) {
    int count = 0;
    for (int i=0; i < str.size(); i++) {
        if (str[i] == '1') {
            count++;
        }
    }
    return count;
}

// Représentation d'un plan sous la forme d'un tableau de taille nxm où l'élément de position (x,y) se trouve dans le tableau
// en position nxy+x
void initialisation(std::vector<int> &plan, int fav_nb, int size_x, int size_y) {
    std::bitset<32> temp;
    int count;
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            temp = x*x + 3*x + 2*x*y + y + y*y + fav_nb;
            count = count_1(temp.to_string());
            if (count % 2 == 0) {
                plan[size_x*y+x] = 0;
            }
            else {
                plan[size_x*y+x] = 1;
            }
        }
    }
}


void print_plan(std::vector<int> &plan, int size_x, int size_y) {
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            if (plan[size_x*y+x] == 0) {
                std::cout << ".";
            }
            else {
                std::cout << "#";
            }
        }
        std::cout << " " << std::endl;
    }
}


std::vector<std::vector<int>> cherche_voisin(std::vector<int> node, std::vector<int> &plan, int size_x, int size_y) {
    std::vector<std::vector<int>> res;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i == j) || (i == -j)) {
            }
            else {
                if (!(node[0] + i < 0) && !(node[0] + i >= size_x) && !(node[1] + j < 0) && !(node[1] + j >= size_y) && plan[(node[1]+j)*size_x+(node[0]+i)] == 0) {
                    res.push_back({node[0]+i, node[1]+j, node[2]+1, 0, node[0], node[1]});
                }
            }
        }
    }
    return res;
}


int find(std::queue<std::vector<int>> list, std::vector<int> node) {
    int res = 0;
    std::vector<int> temp;
    int size = list.size();
    while (size > 0) {
        temp = list.front();
        list.pop();
        if (node[0] == temp[0] && node[1] == temp[1]) {
            res = 1;
        }
        size = list.size();
    }
    return res;
}


int better_node(std::queue<std::vector<int>> list, std::vector<int> node) {
    int res = 0;
    std::vector<int> temp;
    int size = list.size();
    while (size > 0) {
        temp = list.front();
        list.pop();
        if (node[0] == temp[0] && node[1] == temp[1] && node[2] > temp[2]) {
            res = 1;
        }
        size = list.size();
    }
    return res;
}


std::queue<std::vector<int>> push_special(std::queue<std::vector<int>> list, std::vector<int> node) {
    std::queue<std::vector<int>> res;
    std::vector<int> temp;
    int size = list.size();
    int flag = 0;
    while (size > 0) {
        temp = list.front();
        list.pop();
        if (flag == 1) {
            res.push(temp);
        }
        else {
            if (node[3] > temp[3]) {
                res.push(temp);
            }
            else {                
                res.push(node);
                res.push(temp);
                flag = 1;
            }
        }
        size = list.size();
    }
    if (flag == 0) {
        res.push(node);
    }
    return res;
} 


int main() {
    // Initialisation du plan
    int size_x_plan = 50;
    int size_y_plan = 50;
    std::vector<int> plan (size_x_plan*size_y_plan, 0);
    int fav_nb = 1364;
    initialisation(plan, fav_nb, size_x_plan, size_y_plan);
    //print_plan(plan, size_x_plan, size_y_plan);

    // Initialisation des objectifs initiaux du problèmes
    std::vector<int> depart = {1, 1, 0, 0, 0, 0};
    std::vector<int> objectif = {31, 39, 0, 0, 0, 0};
    std::queue<std::vector<int>> closed_list;
    std::queue<std::vector<int>> open_list;
    std::vector<int> courant = depart;
    courant[2] = std::sqrt((objectif[0] - courant[0])*(objectif[0] - courant[0]) + (objectif[1] - courant[1])*(objectif[1] - courant[1]));
    open_list.push(depart);
    int size = open_list.size();
    std::vector<std::vector<int>> voisin;

    // Algorithme A* du plus court chemin
    int flag = 0;
    while (size > 0 && flag == 0) {
        courant = open_list.front();
        open_list.pop();
        if (courant[0] == objectif[0] && courant[1] == objectif[1]) {
            //reconstituer_chemin(courant);
            std::cout << "il faut au moins " << courant[2] << " pas" << std::endl;
            flag = 1;
        }
        else {
            voisin = cherche_voisin(courant, plan, size_x_plan, size_y_plan);
            for (std::vector<int> node_voisin : voisin) {
                if (!(find(closed_list, node_voisin) == 1 || better_node(open_list, node_voisin) == 1)) {
                    node_voisin[3] = node_voisin[2] + std::sqrt((objectif[0] - node_voisin[0])*(objectif[0] - node_voisin[0]) + (objectif[1] - node_voisin[1])*(objectif[1] - node_voisin[1]));
                    open_list = push_special(open_list, node_voisin);
                }
            }
            closed_list.push(courant);
        }
        size = open_list.size();
    }


}