#include <sstream>
#include "alg.h"
std::vector<size_t> fprefix(const std::string& s){
    size_t n = s.length();
    std::vector<size_t> res(n,0);

    for (size_t i = 1; i < n; ++i){
        size_t j = res[i-1];

        while (j > 0 && s[i] != s[j] &&  s[j] != '?')
            j = res[j-1];

        if (s[i] == s[j] || s[j] == '?')
            ++j;
        
        res[i] = j;
    }
    return res;

}

std::vector<std::pair<size_t, std::string>> KMP(const std::string& pattern, const std::string& s){
    std::stringstream ss;
    ss << pattern << -1 << s;
    auto prefix = fprefix(ss.str());
    std::vector<std::pair<size_t, std::string>> res;
    std::size_t n = pattern.size();
    for (int i = 2*n+1; i < prefix.size(); ++i){
        if (prefix[i] == pattern.size()){
            int idx = i -1- 2*n;
            res.push_back({idx+1, s.substr(idx,n)});
        }
    }
    return res;
}


std::vector<std::pair<size_t, std::string>> find(const std::string& pattern, const std::string& s){
    if (pattern.size() > s.size()) return {};
    std::vector<std::pair<size_t, std::string>> res;
    
    for (int i = 0; i < s.size()+1-pattern.size(); i++){
        if (s[i] != pattern[0] &&  pattern[0] != '?')  continue;
        bool b = true;
        for (int j = 1; j < pattern.size() && b; j++){
            b = (s[i+j] == pattern[j] ||  pattern[j] == '?');
        }
        if (b) res.push_back({i+1,s.substr(i,pattern.size())});
    }
    return res;           
}