#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>



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
        std::map<std::string,int> dico = {{"a", 0}, {"b", 0}, {"c", 0}, {"d", 0}}; 

        // On peut alors créer une boucle while commençant à la position i=0 et suivant les instructions données
        // et qui s'arrête lorsqu'on arrive à la fin du vector
        int i = 0;
        int temp;
        int size = tab_txt.size();
        std::string decision;
        std::string cond1;
        std::string cond2;
        std::string cond3;
        while(i < size) {
            line = tab_txt[i];
            decision = line.substr(0, 3);
            // Extraction des informations intéressantes
            cond1 = line.substr(4,1);
            cond2 = line.substr(line.size()-1);
            cond3 = line.substr(4);
            // Amelioration des find dans le dico
            auto search1 = dico.find(cond1);
            auto search2 = dico.find(cond2);

            std::cout << line << std::endl;
            if(decision == "cpy") {
                if(search1 == dico.end()) {
                    dico[cond2] = std::stoi(cond3);
                    i++;
                }
                else {
                    temp = search2->second;
                    dico[cond2] = temp + search1->second;
                    i++;
                }
            }
            else if(decision == "inc") {
                temp = search1->second;
                dico[cond1] = temp + 1;
                i++;
            }
            else if(decision == "dec") {
                temp = search1->second;
                dico[cond1] = std::abs(temp - 1);
                i++;
            }
            else if(search1 == dico.end() && std::stoi(cond1) == 0) {
                i++;
            }
            else if(search1->second == 0) {
                i++;
            }
            else {
                cond3 = line.substr(5);
                i = i + std::stoi(cond3);
            }
            /*
            std::cout << "i="<< i << std::endl;
            std::cout << "a=" << dico.find("a")->second;
            std::cout << ", b=" << dico.find("b")->second;
            std::cout << ", c=" << dico.find("c")->second;
            std::cout << ", d=" << dico.find("d")->second << '\n' << std::endl;
            */
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