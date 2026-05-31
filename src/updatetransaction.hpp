#pragma once

#include "indexstore.hpp"
#include "result.hpp"
#include <vector>

class IndexStore;

class UpdateTransaction
{
  private:
    IndexStore& store_;
    InvertedIndex backup_;                // резервная копия исходного состояния
    std::vector<Document> pending_adds_;  // документ на добавление
    std::vector<size_t> pending_removes_; // ID документов на удаление
    bool committed_ = false;              // применены ли изменения

  public:
    explicit UpdateTransaction(IndexStore& index);

    ~UpdateTransaction();

    Result<void> add_document(Document doc);
    Result<void> remove_document(size_t doc_id);
    Result<void> commit();
};