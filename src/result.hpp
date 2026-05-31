#pragma once

#include <expected>

enum class IndexError // это перечесления, поэтому не обычный класс
{
    DocumentAlreadyExists,
    DocumentNotFound,
    TransactionFailed,
    TransactionAlreadyActive,  // попытка начать транзакцию, когда уже есть активная
    TransactionAlreadyFinished // попытка использовать уже завершённую транзакцию
};

template <typename T>
using Result = std::expected<T, IndexError>; // разные типы данных без дублирования,  expected вернет ожидаемое значение
                                             // или тип ошибки