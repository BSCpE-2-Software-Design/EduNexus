#include "JSONLoader.h"
#include <iostream>

json JSONLoader::load(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << "\n";
        exit(1);
    }

    json data;

    try {
        file >> data;
    }
    catch (json::parse_error& e) {
        std::cerr << "JSON Error in " << filename << "\n";
        std::cerr << e.what() << "\n";
        exit(1);
    }

    return data;
}