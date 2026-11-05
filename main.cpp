#include <iostream>
#include <set>
#include <string>
#include <vector>
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
        std::string expiry;
        input>>command;
        input>>key;
        std::string token;
        std::vector<std::string> parts;
        while (input >> token) {
           parts.push_back(token);
        }
        if (command == "PUT" && parts.size() > 1) {
            std::string last = parts.back();
            if (last.find_first_not_of("0123456789") == std::string::npos) {
                expiry = last;
                parts.pop_back();
            }
        }
        for (int i = 0; i < parts.size(); i++) {
            if (i > 0) value += ' ';
            value += parts[i];
        }
        KV<decltype(value)> kv;
        if (command == "PUT") {
            if (expiry.empty()) {
               expiry = "1000000000";
            }
            std::cout << kv.put(key, value, std::stoull(expiry));
        } else if (command=="GET") {
            std::cout <<kv.get(key);
        } else if (command=="NOW") {
            size_t time = static_cast<size_t>(std::stoull(key));
            kv.setTime(time);
            std::cout << "OK";
        } else if (command=="TTL") {
            std::cout << kv.getTime(key);
        }else if (command=="DELETE") {
            std::cout <<
            kv.del(key);
        } else if (command=="LIST") {
            kv.list();
        } else if (command=="EXPIRE-COUNT") {
            kv.expiry_count();
        } else if (command=="COUNT") {
            std::cout<<kv.count();
        } else if (command=="SCAN") {
            kv.scan(key, value);
        } else if (command=="PREFIX") {
            kv.prefix(key);
        }
        if (command != "LIST") std::cout << std::endl;
    }
}
