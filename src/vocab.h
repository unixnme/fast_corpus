//
// Created by Young Mo Kang on 2019-05-18.
//

#ifndef FAST_CORPUS_VOCAB_H
#define FAST_CORPUS_VOCAB_H

#include <string>
#include <unordered_map>
#include <vector>
#include "dictionary.h"

class Vocabulary {
public:
    explicit Vocabulary(const std::string &corpus_file);

private:
    std::string corpus_file;
    std::unordered_map<std::string, size_t> vocab_count;
};

#endif //FAST_CORPUS_VOCAB_H
