//
// Created by ykang7 on 5/19/19.
//

#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <ctime>

const std::string Dictionary::BOS = "<s>";
const std::string Dictionary::EOS = "</s>";
const std::string Dictionary::UNK = "<unk>";

Dictionary::Dictionary(const std::string &corpus_file)
: ntokens_(0) {
    time_t tstart, tend;
    tstart = time(0);

    word2idx[BOS] = 0;
    word2idx[EOS] = 1;
    word2idx[UNK] = 2;
    data.emplace_back(std::vector<size_t>());

    std::ifstream ifs(corpus_file);
    if (!ifs.is_open()) {
        throw std::invalid_argument(
                corpus_file + " cannot be opened for training!");
    }
    readFromFile(ifs);

    tend = time(0);
    std::cout << "It took "<< difftime(tend, tstart) <<" second(s)."<< std::endl;
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
    if (word == EOS) {
        if (!data.back().empty())
            data.emplace_back(std::vector<size_t>());
    } else {
        size_t idx;
        const auto it = word2idx.find(word);
        if (it == word2idx.end()) {
            idx = word2idx.size();
            word2idx[word] = idx;
        } else {
            idx = it->second;
        }
        data.back().emplace_back(idx);
    }
    ntokens_++;
}

int main(int argc, const char** argv) {
    Dictionary dictionary(argv[1]);
    return 0;
}