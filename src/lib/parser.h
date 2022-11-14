#pragma once
#include <string>
#include <mutex>
#include <utility>
#include <atomic>
#include <mutex>  
#include "queue.h"
#include <memory>
struct Result {
    size_t line;
    size_t pos;
    std::string str;

    bool operator< (const Result& other);
};
bool operator< (const Result& a,const Result& b);
class Parser {
public:
    Parser(const std::string& pattern, std::shared_ptr<ThreadSafeQueue<std::string>> qstring);
    Parser(const Parser& other);

    void add(const std::string& s);
    bool empty();
    bool is_proccessing();

    Result pop();
private:
    void processing();
    std::shared_ptr<ThreadSafeQueue<std::string>> _qstring;
    ThreadSafeQueue<Result> _qresult;

    std::string _pattern;
    bool _is_processing = false;

    std::mutex _b_mtx;
    
};