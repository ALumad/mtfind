#pragma once
#include <set>
#include <string>
#include "parser.h"
#include <random>
#include <vector>
class TextProcessor {
public:
    TextProcessor(const std::string& pattern);
    void Add(const std::string& s);
    std::set<Result> GetAllResult();
private:
    std::vector<Parser> _parsers;

    std::random_device _rd;
    std::mt19937 _mt;
};