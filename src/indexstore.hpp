#pragma once

#include "invertedindex.hpp"
#include "result.hpp"

class UpdateTransaction;

class IndexStore
{
  private:
    InvertedIndex index_;
    bool has_active_transaction_ = false;

  public:
    Result<UpdateTransaction> begin_update();
    Result<void> add_document(Document doc)
    {
        if (has_active_transaction_)
        {
            return std::unexpected(IndexError::TransactionAlreadyActive);
        }
        return index_.add_document(std::move(doc));
    }

    Result<void> remove_document(size_t doc_id)
    {
        if (has_active_transaction_)
        {
            return std::unexpected(IndexError::TransactionAlreadyActive);
        }
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

    // Даём доступ только транзакции
  private:
    InvertedIndex& get_index_unsafe()
    {
        return index_;
    }
    const InvertedIndex& get_index_unsafe() const
    {
        return index_;
    }

    // Дружественный класс для доступа к флагу
    friend class UpdateTransaction;
};