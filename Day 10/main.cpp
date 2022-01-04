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
        // on crée le tableau des instructions car on va devoir lire plusieurs fois le fichier
        std::vector<std::string> tab_txt;
        // création de ligne courante
        std::string line;
        // On lit une ligne complète tant qu'il en reste encore une
        while(std::getline(file, line)) {
            tab_txt.push_back(line);
        }

        // Initialisation d'un dictionnaire contenant les couples (bot X - [microship_low, microship_high]). Par hypothèse, si le robot n'a qu'une
        // microship, alors cette dernière est au choix dans low ou high et on insère -1 comme valeur pour signifier que dans l'un des cas, il
        // n'en a pas.
        std::map<std::string, int[2]> dico_bot;
        // Initialisation d'un dictionnaire contenant 
        std::map<std::string,int> dico_output;

        // On peut alors créer une boucle while commençant à la position i=0 et suivant les instructions données
        // et qui s'arrête lorsqu'on arrive à la fin du vector
        int i = 0;
        int size = tab_txt.size();

        // première lecture des conditions pour donner à chacun des bots leur(s) microships(s)
        std::string decision;
        while(i < size) {
            line = tab_txt[i];
            std::vector<std::string> line_vec = split(line, ' ');
            decision = line_vec[0];
            if(decision == "value") {
                int value = std::stoi(line_vec[1]);
                std::string bot = line_vec[5];
                auto search = dico_bot.find(bot);
                if(search == dico_bot.end()) {
                    dico_bot[bot][0] = value;
                    dico_bot[bot][1] = -1;
                    i++;
                }
                else if(search->second[1] == -1 && search->second[0] < value) {
                    dico_bot[bot][1] = value;
                    i++;
                }
                else {
                    dico_bot[bot][1] = dico_bot[bot][0];
                    dico_bot[bot][0] = value;
                    i++;
                }
            }
            else {
                i++;
            }
        }

        // fin boucle while
        i = 0;
        // seconde lecture des conditions pour réaliser les transferts de microships
        std::string who_donate;
        std::string who_receive_low;
        std::string who_receive_high;
        while(i < size) {
            line = tab_txt[i];
            std::vector<std::string> line_vec = split(line, ' ');
            who_donate = line_vec[1];
            // on vérifie si ce bot réalise la comparaison voulue
            if(dico_bot.find(who_donate)->second[0] == 17 && dico_bot.find(who_donate)->second[1] == 61) {
                std::cout << "Le bot " << who_donate << " est responsable de la comparaison" << std::endl;
            }
            // Début des tests de transmission de microships
            if(line_vec[0] == "value") {
                i++;
            }

            // cas où ce sont des bots qui recoivent les microships low and high
            else if(line_vec[5] != "output") {
                std::cout << "who_donate " << who_donate << " : " << dico_bot.find(who_donate)->second[0] << " ; "<< dico_bot.find(who_donate)->second[1] << "\n" << std::endl;
                who_donate = line_vec[1];
                who_receive_low = line_vec[6];
                who_receive_high = line_vec[11];
                auto bot_donator = dico_bot.find(who_donate);
                // mise à jour de celui qui recoit low
                auto search = dico_bot.find(who_receive_low);
                if(search == dico_bot.end()) {
                    dico_bot[who_receive_low][0] = bot_donator->second[0];
                    dico_bot[who_receive_low][1] = -1;
                }
                else if(search->second[1] == -1 && search->second[0] < bot_donator->second[0]) {
                    dico_bot[who_receive_low][1] = bot_donator->second[0];
                }
                else {
                    dico_bot[who_receive_low][1] = dico_bot[who_receive_low][0];
                    dico_bot[who_receive_low][0] = bot_donator->second[0];
                }
                // mise à jour de celui qui reçoit high
                search = dico_bot.find(who_receive_high);
                if(search == dico_bot.end()) {
                    dico_bot[who_receive_high][0] = bot_donator->second[1];
                    dico_bot[who_receive_high][1] = -1;
                }
                else if(search->second[1] == -1 && search->second[0] < bot_donator->second[1]) {
                    dico_bot[who_receive_high][1] = bot_donator->second[1];
                }
                else {
                    dico_bot[who_receive_high][1] = dico_bot[who_receive_high][0];
                    dico_bot[who_receive_high][0] = bot_donator->second[1];
                }
                dico_bot[who_donate][0] = -1;
                dico_bot[who_donate][1] = -1;
                i++;
            }

            // cas où c'est un output qui recoit le low et un bot qui recoit le high
            else if(line_vec[10] == "bot") {
                std::cout << "who_donate " << who_donate << " : " << dico_bot.find(who_donate)->second[0] << " ; "<< dico_bot.find(who_donate)->second[1] << "\n" << std::endl;
                who_donate = line_vec[1];
                who_receive_low = line_vec[6];
                who_receive_high = line_vec[11];
                auto bot_donator = dico_bot.find(who_donate);
                // mise à jour de celui qui recoit low
                dico_output[who_receive_low] = bot_donator->second[0];
                // mise à jour de celui qui reçoit high
                auto search = dico_bot.find(who_receive_high);
                if(search == dico_bot.end()) {
                    dico_bot[who_receive_high][0] = bot_donator->second[1];
                }
                else if(search->second[1] == -1 && search->second[0] < bot_donator->second[1]) {
                    dico_bot[who_receive_high][1] = bot_donator->second[1];
                }
                else {
                    dico_bot[who_receive_high][1] = dico_bot[who_receive_high][0];
                    dico_bot[who_receive_high][0] = bot_donator->second[1];
                }
                dico_bot[who_donate][0] = -1;
                dico_bot[who_donate][1] = -1;
                i++;
            }

            // cas où ce sont deux outputs qui recoivent low and high
            else {
                std::cout << "who_donate " << who_donate << " : " << dico_bot.find(who_donate)->second[0] << " ; "<< dico_bot.find(who_donate)->second[1] << "\n" << std::endl;
                who_donate = line_vec[1];
                who_receive_low = line_vec[6];
                who_receive_high = line_vec[11];
                auto bot_donator = dico_bot.find(who_donate);
                // mise à jour de celui qui recoit low
                dico_output[who_receive_low] = bot_donator->second[0];
                // mise à jour de celui qui reçoit high
                dico_output[who_receive_high] = bot_donator->second[1];
                dico_bot[who_donate][0] = -1;
                dico_bot[who_donate][1] = -1;
                i++;
            }
        }
        /*std::cout << "bot0 : " << dico_bot.find("0")->second[0] << " ; "<< dico_bot.find("0")->second[1] << std::endl;
        std::cout << "bot1 : " << dico_bot.find("1")->second[0] << " ; "<< dico_bot.find("1")->second[1] << std::endl;
        std::cout << "bot2 : " << dico_bot.find("2")->second[0] << " ; "<< dico_bot.find("2")->second[1] << "\n" << std::endl;
        std::cout << dico_output.find("0")->second << std::endl;
        std::cout << dico_output.find("1")->second << std::endl;
        std::cout << dico_output.find("2")->second << std::endl;*/
        file.close();
    }
    else {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }
 return 0;
}