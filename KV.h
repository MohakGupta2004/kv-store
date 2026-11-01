//
// Created by MOHAK GUPTA on 27/10/26.
//

#ifndef KV_STORE_KV_H
#define KV_STORE_KV_H
#include <iostream>
#include <string>
#include <map>

template<typename T>
std::map<std::string,T> store;

template <typename T>
class KV {
public:
    std::string put(std::string key, T value);
    T get(std::string key);
    std::string del(std::string key);
    void list();
    void scan(const std::string& first, const std::string& second);
    void prefix(const std::string& key);
    int count();
};

template<typename T>
std::string KV<T>::put(std::string key, T value) {
    store<T>[key] = value;
    return "OK";
}

template<typename T>
T KV<T>::get(std::string key) {
    if (store<T>.find(key)!=store<T>.end()) {
        return store<T>[key];
    }
    return "<nil>";
}

template<typename T>
std::string KV<T>::del(std::string key) {
    store<T>.erase(key);
    return "OK";
}

template<typename T>
int KV<T>::count() {
    return store<T>.size();
}

template<typename T>
void KV<T>::list() {
    for (const auto& it:store<T>) {
       std::cout<<it.first<<"="<<it.second<<"\n";
    }
}

template<typename T>
void KV<T>::scan(const std::string& start,const std::string& end) {
    for (const auto& it:store<T>) {
        if (start<=it.first && it.first<end) {
            std::cout << it.first<<"="<<it.second<<std::endl;
        }
    }
}

template<typename T>
void KV<T>::prefix(const std::string &key) {
    for (const auto& it:store<T>) {
        if (it.first.rfind(key, 0)==0) {
            std::cout << it.first<<"="<<it.second<<std::endl;
        }
    }
}


#endif //KV_STORE_KV_H
