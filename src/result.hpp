#pragma once

#include <expected>

enum class IndexError
{
    DocumentAlreadyExists,
    DocumentNotFound,
    TransactionFailed
};

template <typename T> using Result = std::expected<T, IndexError>;