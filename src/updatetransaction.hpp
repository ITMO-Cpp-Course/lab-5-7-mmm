#pragma once

#include "indexstore.hpp"
#include <vector>

class UpdateTransaction
{
  private:
    IndexStore& store_;
    InvertedIndex backup_;
    std::vector<Document> pending_adds_;
    std::vector<size_t> pending_removes_;
    bool committed_ = false;

  public:
    explicit UpdateTransaction(IndexStore& index) : store_(store), backup_(store.get_index()) {}

    ~UpdateTransaction()
    {
        if (!committed_)
        {
            store_.get_index() = backup_;
        }
    }

    Result<void> add_document(Document doc)
    {
        if (backup_.has_document(doc.id))
        {
            return std::unexpected(IndexError::DocumentAlreadyExists);
        }
        pending_adds_.push_back(std::move(doc));
        return res;
    }

    Result<void> remove_document(size_t doc_id)
    {
        if (!backup_.has_document(doc_id))
        {
            return std::unexpected(IndexError::DocumentNotFound);
        }
        pending_removes_.push_back(doc_id);
        return {};
    }

    Result<void> commit()
    {
        for (auto& doc : pending_adds_)
        {
            auto res = store_.get_index().add_document(std::move(doc));
            if (!res)
                return res;
        }
        for (auto doc_id : pending_removes_)
        {
            auto res = store_.get_index().remove_document(doc_id);
            if (!res)
                return res;
        }
        committed_ = true;
        return {};
    }
};