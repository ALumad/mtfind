#pragma once
#include <set>
#include <string>
#include <random>
#include <vector>
#include "parser.h"

class TextProcessor {
public:
    TextProcessor(const std::string& pattern);
    void Add(const std::string& s);
    std::set<Result> GetAllResult();
private:
    std::shared_ptr<ThreadSafeQueue<std::string>> _qstring;
    std::vector<Parser> _parsers;

    std::random_device _rd;
    std::mt19937 _mt;
};