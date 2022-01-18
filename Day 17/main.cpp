#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <bitset>
#include <cmath>
#include <map>
#include "md5.h"


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
void initialisation(std::vector<int> &plan, int size_x, int size_y) {
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            if (x%2 == 0 && y%2 == 0) {
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
            else if (plan[size_x*y+x] == 1 && y%2 == 0) {
                std::cout << "|";
            }
            else {
                std::cout << "-";
            }
        }
        std::cout << " " << std::endl;
    }
}


int is_blocked(char c) {
    if (c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f') {
        return 0;
    }
    else {
        return 1;
    }
}


std::vector<std::vector<float>> cherche_voisin(std::vector<float> node, std::vector<int> &plan, int size_x, int size_y, std::map<std::vector<float>, std::string> &dico) {
    std::vector<std::vector<float>> res;
    std::vector<float> temp_node;
    std::string code = md5(dico.find(node)->second);
    for (float i = -1; i < 2; i++) {
        for (float j = -1; j < 2; j++) {
            if ((i == j) || (i == -j)) {
            }
            else if (i == 0 && j == 1) {
                if (!(node[0] + 2*i < 0) && !(node[0] + 2*i >= size_x) && !(node[1] + 2*j < 0) && !(node[1] + 2*j >= size_y)) {
                    if (is_blocked(code[1]) == 0) {
                        temp_node = {node[0]+2*i, node[1]+2*j, node[2]+1, 0, node[0], node[1], 0, 0, i, j};
                        res.push_back(temp_node);
                        
                    }
                }
            }
            else if (i == 0 && j == -1) {
                if (!(node[0] + 2*i < 0) && !(node[0] + 2*i >= size_x) && !(node[1] + 2*j < 0) && !(node[1] + 2*j >= size_y)) {
                    if (is_blocked(code[0]) == 0) {
                        temp_node = {node[0]+2*i, node[1]+2*j, node[2]+1, 0, node[0], node[1], 0, 0, i, j};
                        res.push_back(temp_node);
                        
                    }
                }
            }
            else if (i == -1 && j == 0) {
                if (!(node[0] + 2*i < 0) && !(node[0] + 2*i >= size_x) && !(node[1] + 2*j < 0) && !(node[1] + 2*j >= size_y)) {
                    if (is_blocked(code[2]) == 0) {
                        temp_node = {node[0]+2*i, node[1]+2*j, node[2]+1, 0, node[0], node[1], 0, 0, i, j};
                        res.push_back(temp_node);
                        
                    }
                }
            }
            else if (i == 1 && j == 0) {
                if (!(node[0] + 2*i < 0) && !(node[0] + 2*i >= size_x) && !(node[1] + 2*j < 0) && !(node[1] + 2*j >= size_y)) {
                    if (is_blocked(code[3]) == 0) {
                        temp_node = {node[0]+2*i, node[1]+2*j, node[2]+1, 0, node[0], node[1], 0, 0, i, j};
                        res.push_back(temp_node);
                        
                    }
                }
            }
        }
    }
    return res;
}


// Fonction permettant de vérifier si un noeud est déjà dans un liste, ie qu'on a déjà fait le déplacement voulu
int is_in(std::queue<std::vector<float>> list, std::vector<float> node) {
    int res = 0;
    std::vector<float> temp;
    int size = list.size();
    while (size > 0) {
        temp = list.front();
        list.pop();
        if (node[0] == temp[0] && node[1] == temp[1] && node[2] == temp[2] && node[3] == temp[3]) {
            res = 1;
        }
        size = list.size();
    }
    return res;
}


// Fonction permettant de trouver le meilleur noeud dans une liste au sens du coût du noeud
int better_node(std::queue<std::vector<float>> list, std::vector<float> node) {
    int res = 0;
    std::vector<float> temp;
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


// Fonction permettant d'ajouter un élément dans une file en respectant l'ordre de comparaison heuristique
std::queue<std::vector<float>> push_special(std::queue<std::vector<float>> list, std::vector<float> node) {
    std::queue<std::vector<float>> res;
    std::vector<float> temp;
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


// Fonction qui permet de retrouver un noeud dans une liste et le renvoyer à condition qu'on sache au préalable que ce dernier soit bien dedans!
std::vector<float> find_parent(std::queue<std::vector<float>> list, std::vector<float> node) {
    std::vector<float> res;
    std::vector<float> temp;
    int size = list.size();
    while (size > 0) {
        temp = list.front();
        list.pop();
        if (node[4] == temp[0] && node[5] == temp[1] && temp[6] == node[0] && temp[7] == node[1]) {
            res = node;
        }
        size = list.size();
    }
    return res;
}


/*
// Fonction permettant de reconstituer le chemin en partant du noeud d'arrivée
void reconstituer_chemin(std::vector<float> &courant, std::vector<float> &depart, std::queue<std::vector<float>> closed_list) {
    std::vector<float> temp = courant;
    // Tant qu'on a pas atteint le noeud initial initalisé que par des 0, alors...
    while (temp[0] != depart[0] && temp[1] != depart[1] && temp[8] == depart[8] && temp[9] == depart[9]) {
        // Affiche du mouvement réalisé
        if (temp[8] == 0 && temp[9] == 1) {
            std::cout << "U";
        }
        else if (temp[8] == 0 && temp[9] == -1) {
            std::cout << "D";
        }
        else if (temp[8] == 1 && temp[9] == 0) {
            std::cout << "R";
        }
        else if (temp[8] == -1 && temp[9] == 0) {
            std::cout << "L";
        }
        else {}
        temp = find_parent(closed_list, temp);
    }
}
*/


int main() {
    // Initialisation du plan
    int size_x_plan = 7;
    int size_y_plan = 7;
    std::vector<int> plan (size_x_plan*size_y_plan, 0);
    initialisation(plan, size_x_plan, size_y_plan);
    //print_plan(plan, size_x_plan, size_y_plan);
    std::string code = "ulqzkmiv";
    std::cout << "password: " << code << std::endl;

    // Initialisation des objectifs initiaux du problèmes
    // Un noeud est représenté par une liste de points: Node = {position_x, position_y, cout, heuristique, parent_x, parent_y, fils_x, fils_y, mouvement fait avec Up : (1, 0), Down: (0, -1), ..}
    std::vector<float> depart = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<float> objectif = {6, 6, 0, 0, 0, 0, 0, 0, 0, 0};
    std::queue<std::vector<float>> closed_list;
    std::queue<std::vector<float>> open_list;
    std::vector<float> courant = depart;
    courant[3] = std::sqrt((objectif[0] - courant[0])*(objectif[0] - courant[0]) + (objectif[1] - courant[1])*(objectif[1] - courant[1]));
    open_list.push(courant);
    int size = open_list.size();
    std::vector<std::vector<float>> voisin;

    std::map<std::vector<float>, std::string> dico = {{courant, code}};
    

    // Algorithme A* du plus court chemin
    int flag = 0;
    while (size > 0 && flag == 0) {
        courant = open_list.front();
        //std::cout << "\ncourant:" << std::endl;
        //std::cout << "x : " << courant[0] << " y : " << courant[1] << " " << " cout : " << courant[2] << " " << dico.find(courant)->second << std::endl;
        open_list.pop();
        if (courant[0] == objectif[0] && courant[1] == objectif[1]) {
            std::string result = dico.find(courant)->second;
            std::cout << "chemin : " << result.substr(code.size(),result.size() - code.size()) << ", nb pas: " << courant[2] << std::endl;
            flag = 1;
        }
        else {
            //std::cout << "voisin:" << std::endl;
            voisin = cherche_voisin(courant, plan, size_x_plan, size_y_plan, dico);
            for (std::vector<float> node_voisin : voisin) {
                
                if (!(is_in(closed_list, node_voisin) == 1 || better_node(open_list, node_voisin) == 1)) {
                    node_voisin[3] = node_voisin[2] + std::sqrt((objectif[0] - node_voisin[0])*(objectif[0] - node_voisin[0]) + (objectif[1] - node_voisin[1])*(objectif[1] - node_voisin[1]));
                    open_list = push_special(open_list, node_voisin);

                    if (node_voisin[8] == 0 && node_voisin[9] == 1) {
                        dico[node_voisin] = dico.find(courant)->second + "D";
                    }
                    else if (node_voisin[8] == 0 && node_voisin[9] == -1) {
                        dico[node_voisin] = dico.find(courant)->second + "U";
                    }
                    else if (node_voisin[8] == 1 && node_voisin[9] == 0) {
                        dico[node_voisin] = dico.find(courant)->second + "R";
                    }
                    else if (node_voisin[8] == -1 && node_voisin[9] == 0) {
                        dico[node_voisin] = dico.find(courant)->second + "L";
                    }
                }
                
                
                closed_list.push({courant[0], courant[1], courant[2], courant[3], courant[4], courant[5], node_voisin[0], node_voisin[1], courant[8], courant[9]});
                //std::cout << "x : " << node_voisin[0] << " y : " << node_voisin[1] << " " << " cout : " << node_voisin[2] << " " << dico.find(node_voisin)->second << std::endl;
            }
        }
        size = open_list.size();
    }
    

}