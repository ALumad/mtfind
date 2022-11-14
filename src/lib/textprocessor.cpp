#include "textprocessor.h"
#include <functional>
#include <thread>
#include <iostream>
TextProcessor::TextProcessor(const std::string& pattern):
_qstring(std::make_shared<ThreadSafeQueue<std::string>>()),
_parsers(std::thread::hardware_concurrency(),{pattern, _qstring})
{
}

void TextProcessor::Add(const std::string& s){
    for (auto& p : _parsers){
        if (p.is_proccessing()) continue;
        p.add(s);    
    }
    _parsers.back().add(s);
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