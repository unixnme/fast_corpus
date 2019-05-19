#include "corpus.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

Corpus::Corpus(const std::string &corpus_file, const Vocabulary &vocab) {
    ifstream infile(corpus_file);
    if(!infile) {
        cerr << "reading " << corpus_file << " error!" << endl;
        exit(-1);
    }
    
    std::string buffer;
    while (getline(infile, buffer)) {
        istringstream iss(buffer);
        vector<string> tokens{istream_iterator<string>{iss},
            istream_iterator<string>{}};
        
        std::vector<vocab_idx_t> sentence;
        for (const auto& word : tokens) {
            sentence.emplace_back(vocab.idx(word));
        }
        if (!sentence.empty())
            data.emplace_back(sentence);
        
        if (data.size() % 1000000 == 0) {
            cout << "processing line #" << (int) data.size() / 1000000 << "M" << endl;
        }
    }
}

std::vector<vocab_idx_t> Corpus::sentence(size_t idx) const {
    return data.at(idx);
}

size_t Corpus::size() const {
    return data.size();
}

int main(int argc, const char** argv) {
    Vocabulary vocab(argv[1]);
    Corpus corpus(argv[2], vocab);
    for (size_t i=0; i<corpus.size(); i++) {
        for (const auto &idx : corpus.sentence(i)) {
            cout << idx << " ";
        }
        cout << endl;
    }
    return 0;
}
