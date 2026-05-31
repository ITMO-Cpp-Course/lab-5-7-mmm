#include "updatetransaction.hpp"
#include "indexstore.hpp"

UpdateTransaction::UpdateTransaction(IndexStore& index) : store_(index), working_copy_(index.get_index()) {}

UpdateTransaction::UpdateTransaction(UpdateTransaction&& other) noexcept
    : store_(other.store_), working_copy_(std::move(other.working_copy_)),
      pending_adds_(std::move(other.pending_adds_)), pending_removes_(std::move(other.pending_removes_)),
      finished_(other.finished_)
{
    other.finished_ = true; // перемещенная транзакция = завершенная
}

UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& other) noexcept
{
    if (this != &other)
    {
        if (!finished_)
        {
            rollback(); // откатываем текущую транзакцию
        }

        store_ = other.store_;
        working_copy_ = std::move(other.working_copy_);
        pending_adds_ = std::move(other.pending_adds_);
        pending_removes_ = std::move(other.pending_removes_);
        finished_ = other.finished_;
        other.finished_ = true;
    }
    return *this;
}

UpdateTransaction::~UpdateTransaction()
{
    if (!finished_)
    {
        // откатываем если не завершена явно
        rollback();
    }
}

Result<void> UpdateTransaction::add_document(Document doc)
{
    if (finished_)
    {
        return std::unexpected(IndexError::TransactionAlreadyFinished);
    }

    if (working_copy_.has_document(doc.id))
    {
        return std::unexpected(IndexError::DocumentAlreadyExists);
    }
    // Работаем с рабочей копией
    auto res = working_copy_.add_document(doc);
    if (res)
    {
        pending_adds_.push_back(std::move(doc));
    }
    return res;
}

Result<void> UpdateTransaction::remove_document(size_t doc_id)
{
    if (finished_)
    {
        return std::unexpected(IndexError::TransactionAlreadyFinished);
    }

    if (!working_copy_.has_document(doc_id))
    {
        return std::unexpected(IndexError::DocumentNotFound);
    }
    // Работаем с рабочей копией
    auto res = working_copy_.remove_document(doc_id);
    if (res)
    {
        pending_removes_.push_back(doc_id);
    }
    return res;
}

Result<void> UpdateTransaction::commit()
{
    if (finished_)
    {
        return std::unexpected(IndexError::TransactionAlreadyFinished);
    }

    // Все операции уже применены к working_copy_
    // Просто подменяем индекс в store_
    store_.get_index() = std::move(working_copy_);

    finished_ = true;
    successful_ = true;

    // Очищаем векторы
    pending_adds_.clear();
    pending_removes_.clear();

    return {};
}

void rollback()
{
    if (finished_)
    {
        return; // завершена
    }

    // Отказываемся от working_copy_
    finished_ = true;
    successful_ = false;

    // Очищаем векторы
    pending_adds_.clear();
    pending_removes_.clear();
    // working_copy_ просто удалится
}