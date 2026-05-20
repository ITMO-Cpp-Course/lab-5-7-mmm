#pragma once 

#include "document.hpp"
#include <unordered_map>
#include <string>
#include <vector>

class InvertedIndex {
    private:
        std::unordered_map<size_t, Document> documents_;
        std::unordered_map<std::string, std::unordered_map<size_t, size_t>> index_;
        std::unordered_map<size_t, std::vector<std::string>> doc_to_words_;

    public:
        void add_document(Document doc);
        void remove_document(size_t doc_id);
        std::unordered_map<size_t, size_t> search(std::string word) const;
        size_t get_word_count(std::string word, size_t doc_id) const;
};