//
// Created by MOHAK GUPTA on 27/10/26.
//

#ifndef KV_STORE_KV_H
#define KV_STORE_KV_H
#include <string>
template <typename T>
class KV {
public:
    std::string put(std::string key, T value);
    T get(std::string key);
    std::string del(std::string key);
    void list();
    int count();
};


#endif //KV_STORE_KV_H
