#include "documentbuilder.hpp"
#include <algorithm>
#include <cctype>

std::vector<std::string> DocumentBuilder::tokenize(const std::string& text)
{
    std::vector<std::string> words;
    std::string current_word;

    for (char ch : text) // пойдем по каждому символу
    {
        if (std::isalnum(static_cast<unsigned char>(ch))) // смотрит корректный ли символ
        {
            current_word += std::tolower(static_cast<unsigned char>(ch)); // часть слова
        }
        else if (!current_word.empty()) // разделитель
        {
            words.push_back(std::move(current_word)); // перемещаем слово
            current_word.clear();                     // чистим для следующего
        }
    }

    if (!current_word.empty())
    {
        words.push_back(std::move(current_word)); // добавляем последнее слово
    }
    return words;
}

Document DocumentBuilder::build(size_t id, std::string name, std::string text)
{
    return Document(id, std::move(name), std::move(text)); // передает параментры
}