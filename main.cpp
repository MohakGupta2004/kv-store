#include <iostream>
#include <set>
#include <string>
#include <sstream>

#include "KV.h"

// TODO (kv-basics): implement per the lesson description.
int main() {
    std::string line;
    while (getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream input(line);
        std::string command;
        std::string key;
        std::string value;
        input>>command;
        input>>key;
        input>>value;
        KV<decltype(value)> kv;
        if (command == "PUT") {
            std::cout << kv.put(key, value);
        } else if (command=="GET") {
            std::cout <<kv.get(key);
        } else if (command=="DELETE") {
            std::cout <<
            kv.del(key);
        } else if (command=="LIST") {
            kv.list();
        } else if (command=="COUNT") {
            std::cout<<kv.count();
        }
        std::cout << std::endl;
    }
}
