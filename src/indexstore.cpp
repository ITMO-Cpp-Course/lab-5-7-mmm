#include "indexstore.hpp"
#include "updatetransaction.hpp"

Result<UpdateTransaction> IndexStore::begin_update()
{
    if (has_active_transaction_)
    {
        return std::unexpected(IndexError::TransactionAlreadyActive);
    }
    has_active_transaction_ = true;
    return UpdateTransaction(*this); // вернет объект транзакции
}