#include "invertedindex.hpp"
#include "documentbuilder.hpp"
#include <algorithm>
#include <cctype>

Result<void> InvertedIndex::add_document(Document doc)
{
    if (has_document(doc.id))
    {
        return std::unexpected(IndexError::DocumentAlreadyExists);
    }

    size_t doc_id = doc.id;
    auto words = DocumentBuilder::tokenize(doc.text);

    for (const auto& word : words)
    {
        if (index_[word][doc_id] == 0)
        {
            doc_to_words_[doc_id].push_back(word);
        }
        index_[word][doc_id]++;
    }
    documents_.insert({doc_id, std::move(doc)});
    return Result<void>::success();
}

Result<void> InvertedIndex::remove_document(size_t doc_id)
{
    if (!has_document(doc_id))
    {
        return std::unexpected(IndexError::DocumentNotFound);
    }

    if (doc_to_words_.find(doc_id) != doc_to_words_.end())
    {
        for (const auto& word : doc_to_words_[doc_id])
        {
            auto& doc_entry = index_[word];
            doc_entry.erase(doc_id);
            if (doc_entry.empty())
            {
                index_.erase(word);
            }
        }
        doc_to_words_.erase(doc_id);
    }
    documents_.erase(doc_id);
    return {};
}

std::unordered_map<size_t, size_t> InvertedIndex::search(std::string word) const
{
    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });

    auto it = index_.find(word);
    if (it != index_.end())
    {
        return it->second;
    }
    return {};
}

size_t InvertedIndex::get_word_count(std::string word, size_t doc_id) const
{
    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });

    auto it = index_.find(word);
    if (it != index_.end())
    {
        auto word_it = it->second.find(doc_id);
        if (word_it != it->second.end())
        {
            return word_it->second;
        }
    }
    return 0;
}