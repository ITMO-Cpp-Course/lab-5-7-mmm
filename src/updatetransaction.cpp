#include "updatetransaction.hpp"
#include "indexstore.hpp"

UpdateTransaction(IndexStore& index) : store_(index), backup_(index.get_index()) {}

UpdateTransaction::~UpdateTransaction()
{
    if (!committed_)
    {
        store_.get_index() = backup_; // восстанавливаем индекс из резервной копии
    }
}

Result<void>::UpdateTransaction add_document(Document doc)
{
    if (backup_.has_document(doc.id))
    {
        return std::unexpected(IndexError::DocumentAlreadyExists);
    }
    pending_adds_.push_back(std::move(doc)); // добавляем в список ожиданий
    return {};
}

Result<void>::UpdateTransaction remove_document(size_t doc_id)
{
    if (!backup_.has_document(doc_id))
    {
        return std::unexpected(IndexError::DocumentNotFound);
    }
    pending_removes_.push_back(doc_id); // добавляем ID на удаление
    return {};
}

Result<void>::UpdateTransaction commit()
{
    for (auto& doc : pending_adds_) // добавляем документ
    {
        auto res = store_.get_index().add_document(std::move(doc));
        if (!res)
            return res;
    }
    for (auto doc_id : pending_removes_) // удаляем документ
    {
        auto res = store_.get_index().remove_document(doc_id);
        if (!res)
            return res;
    }
    committed_ = true;
    return {};
}