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

Vocabulary::Vocabulary(const std::string &corpus_file)
    : corpus_file(corpus_file) {
    std::ifstream ifs{corpus_file};
    std::string token;
    while (ifs >> token) {
        auto it = vocab_count.find(token);
        if (it == vocab_count.end()) {
            vocab_count[token] = 1;
        } else {
            vocab_count[token]++;
        }
    }

    for (const auto& token : vocab_count) {
        std::cout << token.first << " " << token.second << std::endl;
    }
}

int main(int argc, const char** argv) {
    auto vocab = Vocabulary(std::string(argv[1]));

    return 0;
}