#pragma once

#include "invertedindex.hpp"
#include "result.hpp"

class UpdateTransaction;

class IndexStore
{
  private:
    InvertedIndex index_;

  public:
    UpdateTransaction begin_update();
    Result<void> add_document(Document doc)
    {
        return index_.add_document(std::move(doc));
    }

    Result<void> remove_document(size_t doc_id)
    {
        return index_.remove_document(doc_id);
    }

    Result<std::unordered_map<size_t, size_t>> search(const std::string& word) const
    {
        return index_.search(word);
    }

    Result<size_t> get_word_count(const std::string& word, size_t doc_id) const
    {
        return index_.get_word_count(word, doc_id);
    }

    InvertedIndex& get_index()
    {
        return index_;
    }
    const InvertedIndex& get_index() const
    {
        return index_;
    }
};