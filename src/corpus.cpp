#include "corpus.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <ctime>

using namespace std;

Corpus::Corpus(const std::string &corpus_file, const Vocabulary &vocab) {
    time_t tstart, tend;
    tstart = time(0);

    ifstream infile(corpus_file);
    if(!infile) {
        cerr << "reading " << corpus_file << " error!" << endl;
        exit(-1);
    }
    
    std::string buffer;
    while (getline(infile, buffer)) {
        istringstream iss(buffer);
        
        std::vector<vocab_idx_t> sentence;
        auto it = istream_iterator<string>(iss);
        while (it != istream_iterator<string>()) {
            sentence.emplace_back(vocab.idx(*it));
            it++;
        }
        if (!sentence.empty())
            data.emplace_back(sentence);
        
        if (data.size() % 1000000 == 0) {
            cout << "processing line #" << (int) data.size() / 1000000 << "M" << endl;
        }
    }

    tend = time(0);
    std::cout << "It took "<< difftime(tend, tstart) <<" second(s)."<< std::endl;
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
