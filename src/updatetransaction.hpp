#pragma once

#include "indexstore.hpp"
#include "result.hpp"
#include <vector>

class IndexStore;

class UpdateTransaction
{
  private:
    IndexStore& store_;
    InvertedIndex backup_;
    std::vector<Document> pending_adds_;
    std::vector<size_t> pending_removes_;
    bool committed_ = false;

  public:
    explicit UpdateTransaction(IndexStore& index) : store_(index), backup_(index.get_index()) {}

    ~UpdateTransaction()

    Result<void> add_document(Document doc)
    Result<void> remove_document(size_t doc_id)
    Result<void> commit()
};