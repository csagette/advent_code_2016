#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <bitset>
#include <cmath>
#include <map>
#include "matrice.hpp"
#include <algorithm>
#include <cassert>
#include <ostream>
#include <numeric>


int count_1(std::string str) {
    int count = 0;
    for (int i=0; i < str.size(); i++) {
        if (str[i] == '1') {
            count++;
        }
    }
    return count;
}


Matrice initialisation(Matrice plan, int fav_nb, int size_x, int size_y) {
    Matrice res {size_y, size_x};
    std::bitset<32> temp;
    int count;
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            temp = x*x + 3*x + 2*x*y + y + y*y + fav_nb;
            count = count_1(temp.to_string());
            if (count % 2 == 0) {
                res(y, x) = 0;
                std::cout << "ok" << std::endl;
            }
            else {
                res(y, x) = 1;
                std::cout << "ok" << std::endl;
            }
        }
    }
    return res;
}

std::vector<std::vector<int>> cherche_voisin(std::vector<int> node, Matrice &plan) {
    std::vector<std::vector<int>> res;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!(node[0] + i < 0 && node[0] + i >= plan.nb_colonnes() && node[1] + j < 0 && node[1] + j >= plan.nb_lignes()) && plan(j, i) == 0) {
                res.push_back({node[0]+i, node[1]+j, node[2]+1, 0, node[0], node[1]});
            }
        }
    }
    return res;
}


int find(std::queue<std::vector<int>> list, std::vector<int> node) {
    int res = 0;
    std::vector<int> temp;
    temp = list.front();
    list.pop();
    int size = list.size();
    while (size > 0) {
        if (node[0] == temp[0] && node[1] == temp[1]) {
            res = 1;
        }
        temp = list.front();
        list.pop();
        size = list.size();
    }
    return res;
}


int better_node(std::queue<std::vector<int>> list, std::vector<int> node) {
    int res = 0;
    std::vector<int> temp;
    temp = list.front();
    list.pop();
    int size = list.size();
    while (size > 0) {
        if (node[0] == temp[0] && node[1] == temp[1] && node[2] > temp[2]) {
            res = 1;
        }
        temp = list.front();
        list.pop();
        size = list.size();
    }
    return res;
}


std::queue<std::vector<int>> push_special(std::queue<std::vector<int>> list, std::vector<int> node) {
    std::queue<std::vector<int>> res;
    std::vector<int> temp;
    temp = list.front();
    list.pop();
    int size = list.size();
    while (size > 0) {
        if (node[3] > temp[3]) {
            res.push(temp);
        }
        else {
            res.push(node);
        }
        temp = list.front();
        list.pop();
        size = list.size();
    }
    return res;
} 


void print_plan(Matrice plan) {
    for (int y = 0; y < plan.nb_lignes(); y++) {
        for (int x = 0; x > plan.nb_lignes(); x++) {
            if (plan(y,x) == 0) {
                std::cout << ".";
            }
            else {
                std::cout << "#";
            }
        }
        std::cout << " " << std::endl;
    }
}

int main() {
    Matrice plan {10, 7};
    int fav_nb = 10;
    //plan = initialisation(plan, fav_nb, 10, 7);
    //print_plan(plan);
    /*
    std::vector<int> depart = {0, 0, 0, 0, 0, 0};
    std::queue<std::vector<int>> closed_list;
    std::queue<std::vector<int>> open_list;
    open_list.push(depart);
    int size = open_list.size();
    std::vector<std::vector<int>> voisin;
    std::cout << voisin.size() <<std::endl;*/
}