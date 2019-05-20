//
// Created by ykang7 on 5/19/19.
//

#include "dictionary.h"
#include <iostream>
#include <fstream>

const std::string Dictionary::BOS = "<s>";
const std::string Dictionary::EOS = "</s>";
const std::string Dictionary::UNK = "<unk>";

Dictionary::Dictionary(const std::string &corpus_file)
: ntokens_(0) {
    word2idx[BOS] = 0;
    word2idx[EOS] = 1;
    word2idx[UNK] = 2;

    std::ifstream ifs(corpus_file);
    if (!ifs.is_open()) {
        throw std::invalid_argument(
                corpus_file + " cannot be opened for training!");
    }
    readFromFile(ifs);
}

bool Dictionary::readWord(std::istream& in, std::string& word) const {
    int c;
    std::streambuf& sb = *in.rdbuf();
    word.clear();
    while ((c = sb.sbumpc()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' ||
            c == '\f' || c == '\0') {
            if (word.empty()) {
                if (c == '\n') {
                    word += EOS;
                    return true;
                }
                continue;
            } else {
                if (c == '\n')
                    sb.sungetc();
                return true;
            }
        }
        word.push_back(c);
    }
    // trigger eofbit
    in.get();
    return !word.empty();
}

void Dictionary::readFromFile(std::istream& in) {
    std::string word;
    while (readWord(in, word)) {
        add(word);
        if (ntokens_ % 1000000 == 0) {
            std::cerr << "\rRead " << ntokens_ / 1000000 << "M words" << std::flush;
        }
    }
}

void Dictionary::add(const std::string &word) {
    if (word2idx.find(word) == word2idx.end()) {
        word2idx[word] = word2idx.size();
    }
    ntokens_++;
}

int main(int argc, const char** argv) {
    Dictionary dictionary(argv[1]);
    return 0;
}