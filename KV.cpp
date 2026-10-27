//
// Created by MOHAK GUPTA on 27/10/26.
//

#include "KV.h"

#include <iostream>
#include <unordered_map>
template<typename T>
std::unordered_map<std::string,T> store;

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
       std::cout<<it.first<<"="<<it.second<<std::endl;
    }
}

template class KV<std::string>;
