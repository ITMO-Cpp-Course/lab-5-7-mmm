#pragma once

#include "document.hpp"
#include "result.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class InvertedIndex
{
  private:
    std::unordered_map<size_t, Document> documents_;
    std::unordered_map<std::string, std::unordered_map<size_t, size_t>> index_;
    std::unordered_map<size_t, std::vector<std::string>> doc_to_words_;

  public:
    Result<void> add_document(Document doc);
    Result<void> remove_document(size_t doc_id);
    std::unordered_map<size_t, size_t> search(std::string word) const;
    size_t get_word_count(std::string word, size_t doc_id) const;

    bool has_document(size_t doc_id) const
    {
        return documents_.find(doc_id) != documents_.end();
    }

    InvertedIndex() = default;
    InvertedIndex(const InvertedIndex&) = default;
    InvertedIndex& operator=(const InvertedIndex&) = default;
};