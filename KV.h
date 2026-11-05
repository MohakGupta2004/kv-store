//
// Created by MOHAK GUPTA on 27/10/26.
//

#ifndef KV_STORE_KV_H
#define KV_STORE_KV_H
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
enum State {
    ACTIVE,
    EXPIRED,
};
template<typename T>
struct Entry {
    T value;
    std::size_t expiry;
};

template<typename T>
std::map<std::string,Entry<T>> store;
std::unordered_map<std::string, State> keyStatus;
template <typename T>
class KV {
private:
    size_t time;
public:
    std::string put(std::string key, T value, std::size_t expiry);
    T get(std::string key);
    std::string del(std::string key);
    void list();
    void setTime(size_t t);
    int getTime(const std::string& key);
    void expiry_count();
    void scan(const std::string& start, const std::string& end);
    void prefix(const std::string& key);
    int count();
};

template<typename T>
std::string KV<T>::put(std::string key, T value, std::size_t expiry) {
    store<T>[key] = Entry<T>{value,expiry};
    keyStatus[key] = State::ACTIVE;
    return "OK";
}

template<typename T>
T KV<T>::get(std::string key) {
    auto it = store<T>.find(key);
    if (it!=store<T>.end()) {
        if (it->second.expiry>time) {
            return it->second.value;
        } else {
            store<T>.erase(key);
        }
    }
    return "<nil>";
}

template<typename T>
void KV<T>::setTime(size_t t) {
   time = t;
}

template<typename T>
int KV<T>::getTime(const std::string& key) {
    return store<T>[key].expiry;
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
    auto it = store<T>.begin();
    while (it!=store<T>.end()) {
        if (it->second.expiry<time) {
            it = store<T>.erase(it);
            continue;
        }
        std::cout << it->first<<"="<<it->second.value<<"\n";
        ++it;
    }
}

template<typename T>
void KV<T>::scan(const std::string& start,const std::string& end) {
    for (const auto& it:store<T>) {
        if (start<=it.first && it.first<end) {
            std::cout << it.first<<"="<<it.second.value<<std::endl;
        }
    }
}

template<typename T>
void KV<T>::prefix(const std::string &key) {
    for (const auto& it:store<T>) {
        if (it.first.rfind(key, 0)==0) {
            std::cout << it.first<<"="<<it.second.value<<std::endl;
        }
    }
}

template<typename T>
void KV<T>::expiry_count() {
    for (const auto& it:store<T>) {
        if (it.second.expiry>time && it.second.expiry!=1e9) {
            keyStatus[it.first] = State::EXPIRED;
        }
    }
    int count = 0;
    for (const auto& it:keyStatus) {
       if (it.second == State::EXPIRED) {
           count++;
       }
    }

    std::cout << count<<std::endl;
}


#endif //KV_STORE_KV_H
