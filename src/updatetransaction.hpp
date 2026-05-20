#pragma once

#include "invertedindex.hpp"

class UpdateTransaction
{
  private:
    InvertedIndex& target_index_;
    InvertedIndex backup_;
    bool committed_ = false;

  public:
    explicit UpdateTransaction(InvertedIndex& index) : target_index_(index), backup_(index) {}

    ~UpdateTransaction()
    {
        if (!committed_)
        {
            target_index_ = backup_;
        }
    }

    Result<void> add_document(Document doc)
    {
        auto res = target_index_.add_document(std::move(doc));
        return res;
    }

    void commit()
    {
        committed_ = true;
    }
};