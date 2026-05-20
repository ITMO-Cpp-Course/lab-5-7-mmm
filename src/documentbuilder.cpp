#include "documentbuilder.hpp"
#include <algorithm>
#include <cctype>

std::vector<std::string> DocumentBuilder::tokenize(const std::string& text)
{
    std::vector<std::string> words;
    std::string current_word;

    for (char ch : text)
    {
        if (std::isalnum(static_cast<unsigned char>(ch)))
        {
            current_word += std::tolower(static_cast<unsigned char>(ch));
        }
        else if (!current_word.empty())
        {
            words.push_back(std::move(current_word));
            current_word.clear();
        }
    }

    if (!current_word.empty())
    {
        words.push_back(std::move(current_word));
    }
    return words;
}

Document DocumentBuilder(size_t id, std::string name, std::string text)
{
    return Document(id, std::move(name), std::move(text));
}