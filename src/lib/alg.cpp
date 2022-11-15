#include "alg.h"
inline std::vector<unsigned> fprefix(const std::string& p){
    size_t n = p.length();
    std::vector<unsigned> res(n,0);

    for (size_t i = 1; i < n; ++i){
        size_t j = res[i-1];
        if (p[i] == p[i-1] || p[i] == '?'){
            ++j;
            res[i] = j;
        } else if (j == 0){
            continue;
        } else {
            j = res[j-1];
        }
    }
    return res;

}

std::vector<std::pair<size_t, std::string>> KMP(const std::string& p, const std::string& s){
    auto prefix = fprefix(p);
    std::vector<std::pair<size_t, std::string>> res;
    std::size_t n = p.size();
    for (unsigned i = 0, j=0; i < s.size();) {
        if (s[i]==p[j] || p[j]=='?'){
            ++i,++j;   
            if (j == p.size()){
                res.push_back({i-p.size()+1,s.substr(i-p.size(),p.size())});
                j = 0;
                i = res.back().first;

            }                     
        } else if (j == 0) {
            ++i;
        } else {
            do {
                j = prefix[j-1];
            }
            while (j != 0 && p[j-1] != '?');
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


