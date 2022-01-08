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
    std::ifstream file("input.txt");
    int time = 0;
    std::vector<std::vector<int>> info;
    std::vector<std::string> line_vec;
    std::vector<int> temp;
    int flag = 0;
    int sum;
    int size;

    if(file) { 
        std::string line;
        while(std::getline(file, line)) {
            line_vec = split(line, ' ');
            temp.push_back(std::stoi(line_vec[3]));
            temp.push_back(std::stoi(line_vec[11]));
            info.push_back(temp);
            temp.clear();
        }
        size = info.size();
        while (flag == 0) {
            for (int i = 0; i < size; i++) {
                sum = sum + ((info[i][1] + time + i + 1) % info[i][0]);
            }
            if (sum == 0) {
                flag = 1;
            }
            sum = 0;
            time++;
        }
        std::cout << "Il faut jouer à partir du temps t=" << time - 1 << std::endl;
        file.close();
    }
    else {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }
 
    return 0;
}