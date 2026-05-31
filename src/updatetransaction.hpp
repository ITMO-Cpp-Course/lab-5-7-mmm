#pragma once

#include "indexstore.hpp"
#include "result.hpp"
#include <vector>

class IndexStore;

class UpdateTransaction
{
  private:
    IndexStore& store_;
    InvertedIndex working_copy_; // рабочая копия индекса
    std::vector<Document> pending_adds_;
    std::vector<size_t> pending_removes_;
    bool finished_ = false;   // завершена
    bool successful_ = false; // как завершена

  public:
    explicit UpdateTransaction(IndexStore& index);

    // Запрещаем копирование
    UpdateTransaction(const UpdateTransaction&) = delete;
    UpdateTransaction& operator=(const UpdateTransaction&) = delete;

    // Разрешаем перемещение
    UpdateTransaction(UpdateTransaction&& other) noexcept;
    UpdateTransaction& operator=(UpdateTransaction&& other) noexcept;

    ~UpdateTransaction();

    Result<void> add_document(Document doc);
    Result<void> remove_document(size_t doc_id);
    Result<void> commit();
    void rollback(); // явный откат
};