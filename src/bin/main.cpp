#include <iostream>
#include <fstream>
#include "lib/textprocessor.h"
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Need file and \"pattern\"" << std::endl;
        return 0;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "File " << argv[1] << " does not exist" << std::endl;
        return 0;
    }
    std::string pattern = argv[2];
    std::string line;
    TextProcessor tp(pattern);
    while (std::getline(file, line))
    {
        tp.Add(line);    
    }
    auto res = tp.GetAllResult();
    for (auto& l : res){
        std::cout << l.line << " " << l.pos << " " << l.str << std::endl;
    }

    
    return 0;
}