#include <iostream>
#include <fstream>
#include <regex>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int main() {
    std::ifstream file("in");
    std::string line, text;

    rapidjson::Document doc;

    int sum = 0;

    while (getline(file, line)) {
        text += line;
    }
    const char* data = text.c_str();

    doc.Parse(data);

    for (auto e = doc.Begin(); e != doc.End(); ++e) {
        std::cout << e << std::endl;
    }

    return sum;
}
