#pragma once
#include <vector>
#include <string>



//O(n+m)
std::vector<std::pair<size_t, std::string>> KMP(const std::string& pattern, const std::string& s);

//O(n*m)
std::vector<std::pair<size_t, std::string>> find(const std::string& pattern, const std::string& s);
