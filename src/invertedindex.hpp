#pragma once

#include "document.hpp"
#include "result.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class InvertedIndex
{
  private:
    std::unordered_map<size_t, Document> documents_; // ключ id; значение документ
    std::unordered_map<std::string, std::unordered_map<size_t, size_t>>
        index_; // внешний - слово, внутренний - {id, частота вхождения}
    std::unordered_map<size_t, std::vector<std::string>>
        doc_to_words_; // ключ - id, значение - вектор слов в порядке появления, хранит список слов (токенов) для
                       // каждого элемента

  public:
    Result<void> add_document(Document doc);
    Result<void> remove_document(size_t doc_id);
    std::unordered_map<size_t, size_t> search(std::string word) const;
    size_t get_word_count(std::string word,
                          size_t doc_id) const; // сколько раз определенное слово встречается в документе

    bool has_document(size_t doc_id) const // существует ли документ с id
    {
        return documents_.find(doc_id) != documents_.end();
    }

    InvertedIndex() = default;                                // конструктор
    InvertedIndex(const InvertedIndex&) = default;            // копирующий коструктор
    InvertedIndex& operator=(const InvertedIndex&) = default; // копирующее присваивание
};