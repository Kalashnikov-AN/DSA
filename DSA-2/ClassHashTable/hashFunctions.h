#pragma once
#include <string>  

//  Хеш-функция по умолчанию для произвольного типа Key
template <typename T>
size_t djb2(const T& key) {
    const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
    size_t h = 5381;
    for (size_t i = 0; i < sizeof(T); ++i) {
        h = ((h << 5) + h) + data[i];
    }
    return h;
}

//  Хеш-функция по умолчанию для string
template<>
size_t djb2(const std::string& s);