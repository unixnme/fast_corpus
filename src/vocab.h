//
// Created by Young Mo Kang on 2019-05-18.
//

#ifndef FAST_CORPUS_VOCAB_H
#define FAST_CORPUS_VOCAB_H

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include "dictionary.h"

using Item_t = std::pair<std::string, size_t>;

class Compare {
    bool operator()(const Item_t &a, const Item_t &b) const {
        return a.second > b.second;
    }
};

class Vocabulary {
public:
    explicit Vocabulary(const std::string &corpus_file);
    void print_vocab_by_count();

private:
    bool readWord(std::istream& in, std::string& word) const;

    std::string corpus_file;
    std::map<std::string, size_t> vocab_count;
};

#endif //FAST_CORPUS_VOCAB_H
