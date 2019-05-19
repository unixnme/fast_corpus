//
// Created by Young Mo Kang on 2019-05-18.
//

#ifndef FAST_CORPUS_CORPUS_H
#define FAST_CORPUS_CORPUS_H

#include <cstdint>
#include <string>
#include <vector>

#include "vocab.h"

class Corpus {
public:
    Corpus(const std::string &corpus_file, const Vocabulary &vocab);
    std::vector<vocab_idx_t> sentence(size_t idx) const;
    size_t size() const;
    
private:
    std::vector<std::vector<vocab_idx_t>> data;
};

#endif //FAST_CORPUS_CORPUS_H
