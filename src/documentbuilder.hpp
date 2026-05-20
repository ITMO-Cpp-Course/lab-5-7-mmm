#pragma once

#include "document.hpp"
#include <string>
#include <vector>

class DocumentBuilder
{
  public:
    static std::vector<std::string> tokenize(std::string& text);
    static Document build(size_t id, std::string name, std::string text);
};