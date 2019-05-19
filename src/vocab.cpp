//
// Created by Young Mo Kang on 2019-05-18.
//

#include "vocab.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

Vocabulary::Vocabulary(const std::string &corpus) {
    process(corpus);
}

void Vocabulary::process(const std::string &corpus) {
    ifstream infile(corpus);
    if(!infile) {
        cerr << "reading " << corpus << " error!" << endl;
        exit(-1);
    }
    
    int i = 0;
    std::string buffer;
    while (getline(infile, buffer)) {
        istringstream iss(buffer);
        vector<string> tokens{istream_iterator<string>{iss},
            istream_iterator<string>{}};

        for (const auto& word : tokens) {
            add(word);
        }

        if (++i % 100000 == 0) {
            cout << "processing line #" << (int) i / 1000 << "k" << endl;
        }
    }
    
    cout << idx2word.size() << endl;
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

vocab_idx_t Vocabulary::idx(const std::string &word) {
    if (word2idx.find(word) == word2idx.end()) {
        return -1;
    } else {
        return word2idx[word];
    }
}

std::string Vocabulary::word(vocab_idx_t idx) {
    return idx2word[idx];
}

size_t Vocabulary::size() {
    return idx2word.size();
}

std::vector<std::string> Vocabulary::vocab() {
    return idx2word;
}

int main(int argc, const char** argv) {
    Vocabulary vocab(argv[1]);
    for (const auto & word : vocab.vocab()) {
        cout << word << endl;
    }
    return 0;
}
