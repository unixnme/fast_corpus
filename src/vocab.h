//
// Created by Young Mo Kang on 2019-05-18.
//

#ifndef FAST_CORPUS_VOCAB_H
#define FAST_CORPUS_VOCAB_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

typedef int32_t vocab_idx_t;

class Vocabulary {
public:
    /** read the corpus and create word2idx mapping
     *
     * @param corpus: corpus file to read
     */
    Vocabulary(const std::string &corpus);
    Vocabulary(const std::string &corpus, const std::vector<std::string> &tokens);

    /** add word to vocab and return its index
     *
     * @param word: word to add to vocab
     * @return: its index
     */
    vocab_idx_t add(const std::string &word);

    /** find the word in the vocab; if not found, return negative number
     *
     * @param word
     * @return
     */
    vocab_idx_t idx(const std::string &word);

    /** return word pointed by the index
     *
     * @return
     */
    std::string word(vocab_idx_t idx);

    /** return # of words
     *
     * @return
     */
    size_t size();

    /** return current vocabulary vector
     */
    std::vector<std::string> vocab();
    
private:
    void process(const std::string &corpus);
    std::unordered_map<std::string, vocab_idx_t> word2idx;
    std::vector<std::string> idx2word;
};

#endif //FAST_CORPUS_VOCAB_H
