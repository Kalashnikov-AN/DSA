#include "hashFunctions.h"


//  Хеш-функция по умолчанию для string
template<>
size_t djb2(const std::string& s) {
    size_t h = 5381;
    for (unsigned char c : s) {
        h = ((h << 5) + h) + c; // h * 33 + c
    }
    return h;
}