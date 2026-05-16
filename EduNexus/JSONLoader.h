#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class JSONLoader {
public:
    static json load(std::string filename);
};

#endif
