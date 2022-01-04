#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


void split_(std::string &chaine, char delimiteur, std::vector<std::string> &elements)
{
    std::stringstream ss(chaine);
    std::string sousChaine;
    while (std::getline(ss, sousChaine, delimiteur))
    {
    elements.push_back(sousChaine);
    }
}

std::vector<std::string> split(std::string &chaine, char delimiteur) 
{
    std::vector<std::string> elements;
    split_(chaine, delimiteur, elements);
    return elements;
}


int main() {
    // on ouvre le fichier en lecture
    std::ifstream file("input.txt");
    // si l'ouverture a réussi
    if(file) {    

        // on crée le tableau des instructions
        std::vector<std::string> tab_txt;
        std::string line;
        // On lit une ligne complète tant qu'il en reste encore une
        while(std::getline(file, line)) {
            tab_txt.push_back(line);
        }

        // Initialisation d'un dictionnaire pour contenir les valeurs des variables
        std::map<std::string,int> dico ({{"a", 0}, {"b", 0}, {"c", 0}, {"d", 0}}); 

        // On peut alors créer une boucle while commençant à la position i=0 et suivant les instructions données
        // et qui s'arrête lorsqu'on arrive à la fin du vector
        int i = 0;
        int temp;
        int size = tab_txt.size();
        std::string decision;
        while(i < size) {
            line = tab_txt[i];
            std::vector<std::string> line_vec = split(line, ' ');
            decision = line_vec[0];
            if(decision == "inc") {
                temp = dico.find(line_vec[1])->second;
                dico[line_vec[1]] = temp + 1;
                i++;
            }
            else if(decision == "dec") {
                temp = dico.find(line_vec[1])->second;
                dico[line_vec[1]] = temp - 1;
                i++;
            }
            else if(decision == "cpy") {
                if(dico.find(line_vec[1]) == dico.end()) {
                    dico[line_vec[2]] = std::stoi(line_vec[1]);
                    i++;
                }
                else {
                    dico[line_vec[2]] = dico[line_vec[1]];
                    i++;
                }
            }
            else {
                if(dico.find(line_vec[1]) == dico.end() && std::stoi(line_vec[1]) != 0) {
                    i = i + std::stoi(line_vec[2]);
                }
                else if(dico.find(line_vec[1])->second != 0) {
                    i = i + std::stoi(line_vec[2]);
                }
                else {
                    i++;
                }

            }
            
            std::cout << "i="<< i << std::endl;
            std::cout << "a=" << dico.find("a")->second;
            std::cout << ", b=" << dico.find("b")->second;
            std::cout << ", c=" << dico.find("c")->second;
            std::cout << ", d=" << dico.find("d")->second << '\n' << std::endl;
            
        }

        std::cout << dico.find("a")->second;
        // on ferme le fichier
        file.close();
    }
    else {
            
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }
 
        return 0;
}