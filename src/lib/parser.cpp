
#include "parser.h"
#include "alg.h"
#include <thread>
bool Result::operator< (const Result& other){
    if (line != other.line)
        return line < other.line;
    return pos < other.pos; 
}
bool operator< (const Result& a,const Result& b){
    if (a.line != b.line)
        return a.line < b.line;
    return a.pos < b.pos; 
}

Parser::Parser(const std::string& pattern, std::shared_ptr<ThreadSafeQueue<std::string>> qstring):
_qstring(qstring), _pattern(pattern){
}


Parser::Parser(const Parser& other):
    _pattern(other._pattern),
    _qstring(other._qstring)
{

}


void Parser::add(const std::string& s){
    _qstring->push(s);
    std::scoped_lock lk(_b_mtx);
    if (!_is_processing) {
        _is_processing = true;
        std::thread t([&](){ processing();});
        t.detach();
    }
}

bool Parser::is_proccessing(){
    std::scoped_lock lk(_b_mtx);
    return _is_processing;
}

void Parser::processing(){
     
    while (true)
    {
        auto linestr = _qstring->pop();
        auto res = KMP(_pattern,linestr.second);
        for (auto& w: res) {
            Result e;
            e.line = linestr.first,
            e.pos = w.first, 
            e.str = w.second,
            _qresult.push(e);
        }        
        if (_qstring->empty())  break;

    }   
    std::scoped_lock lk(_b_mtx);
    _is_processing = false; 
    
}    

bool Parser::empty(){
    return _qresult.empty();
}

Result Parser::pop(){
    return _qresult.pop().second;
}   