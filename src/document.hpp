#pragma once

#include <string>

struct Document
{
    size_t id;
    std::string name;
    std::string text;

    Document(size_t doc_id, std::string doc_name, std::string doc_text)
        : id(doc_id), name(std::move(doc_name)), text(std::move(doc_text))
    {
    }
};