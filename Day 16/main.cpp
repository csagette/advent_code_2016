#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

// Fonction qui permet d'inverser une chaîne de caractère
std::string reverse_str(std::string str) {
    std::string reverse = str;
    int size = str.size();
    for (int i = 0; i < size; i++) {
        reverse[i] = str[size-i-1];
    }
    return reverse;
}


// Fonction permettant d'écrire la négation d'une chaine de caractère binaire (0 remplacé par 1 et inversement)
std::string negation_str(std::string str) {
    std::string res;
    int size = str.size();
    for (int i = 0; i < size; i++) {
        if (str[i] == '0') {
            res.push_back('1');
        }
        else {
            res.push_back('0');
        }
    }
    return res;
} 


// Fonction réalisant la méthode dragon_curve jusqu'à obtenir une chaîne de taille au moins supérieure à lentgh, et renvoie la chaîne tronquée avec la taille voulue
std::string dragon_curve(std::string str, int length) {
    std::string res = str;
    int size = res.size();
    while (size < length) {
        res = res + "0" + negation_str(reverse_str(res));
        size = res.size();
    }
    return res.substr(0, length);
}


// Fonction permettant de calcul le checksum 
std::string checksum(std::string str) {
    std::string res;
    int size = str.size();
    int i = 0;
    while (i < size) {
        if ((str[i] == '0' && str[i+1] == '0') || (str[i] == '1' && str[i+1] == '1')) {
            res.push_back('1');
        }
        else {
            res.push_back('0');
        }
        i = i + 2;
    }
    return res;
}

int main() {
    std::string str = "10000";
    int length = 20;
    str = dragon_curve(str, length);
    while (length % 2 == 0) {
        str = checksum(str);
        length = str.size();
    }
    std::cout << "Le résultat est: " << str << std::endl;
    return 0;
}