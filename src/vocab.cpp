//
// Created by Young Mo Kang on 2019-05-18.
//

#include "vocab.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

Vocabulary::Vocabulary(const std::string &vocab_file) {
    process(vocab_file);
}

void Vocabulary::process(const std::string &vocab_file) {
    ifstream infile(vocab_file);
    if(!infile) {
        cerr << "reading " << vocab_file << " error!" << endl;
        exit(-1);
    }
    
    std::string buffer;
    while (getline(infile, buffer)) {
        istringstream iss(buffer);
        auto it = istream_iterator<string>(iss);
        while (it != istream_iterator<string>()) {
            add(*it);
            it++;
        }
    }
}

Vocabulary::Vocabulary(const std::string &corpus, const std::vector<std::string> &tokens) :
    idx2word(tokens) {
    for (vocab_idx_t i=0; i<tokens.size(); i++) {
        word2idx[tokens[i]] = i;
    }
    process(corpus);
}

vocab_idx_t Vocabulary::add(const std::string &word) {
    vocab_idx_t idx = this->idx(word);
    if (idx < 0) {
        idx = size();
        word2idx[word] = idx;
        idx2word.emplace_back(word);
    }
    return idx;
}

vocab_idx_t Vocabulary::idx(const std::string &word) const {
    vocab_idx_t idx;
    if (word2idx.find(word) == word2idx.end()) {
        idx = -1;
    } else {
        idx = word2idx.at(word);
    }
    return idx;
}

std::string Vocabulary::word(vocab_idx_t idx) const {
    return idx2word[idx];
}

size_t Vocabulary::size() const {
    return idx2word.size();
}

std::vector<std::string> Vocabulary::vocab() const {
    return idx2word;
}
