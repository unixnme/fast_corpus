//
// Created by ykang7 on 5/19/19.
//

#ifndef FAST_CORPUS_DICTIONARY_H
#define FAST_CORPUS_DICTIONARY_H

#include <string>

class Dictionary {
public:
    Dictionary(const std::string &corpus_file);
    const static std::string BOS, EOS, UNK;

private:
    bool readWord(std::istream& in, std::string& word) const;
    void readFromFile(std::istream& in);
    void add(const std::string &word);
    size_t ntokens_;
};


#endif //FAST_CORPUS_DICTIONARY_H
