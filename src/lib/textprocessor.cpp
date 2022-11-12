#include "textprocessor.h"
#include <functional>
#include <thread>
#include <iostream>
TextProcessor::TextProcessor(const std::string& pattern):
_mt(_rd()), 
_parsers(std::thread::hardware_concurrency(),{pattern})

{

}

void TextProcessor::Add(const std::string& s){
    std::uniform_int_distribution<int> dist(0,_parsers.size()-1);
    int idx = dist(_mt);
    _parsers.at(idx).add(s);
}


std::set<Result> TextProcessor::GetAllResult(){
    std::set<Result> res;

    for (auto& p: _parsers) {
        while (p.is_proccessing()) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(100ms);
        }
        while (!p.empty()) {
            res.insert(p.pop());
        }
    }
    return res;

}