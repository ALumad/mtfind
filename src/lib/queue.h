#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <utility>

template<class T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue(){}

    ThreadSafeQueue(const  ThreadSafeQueue& other) {
        _counter = other._counter;
    }

    void push(const T& s){
        std::scoped_lock lk(_q_mtx);
        ++_counter;
        _q.push({_counter, s});
    }

    bool empty() {
        std::scoped_lock lk(_q_mtx);
        return _q.empty();
    }
    std::pair<std::size_t,T> pop(){
        std::scoped_lock lk(_q_mtx);
        if (_q.empty()) throw std::runtime_error("sadasdasdas");
        std::pair<std::size_t,T>  res = _q.front();
        _q.pop();
        return res;
    }
private:
    std::queue<std::pair<std::size_t,T>> _q;
    std::size_t _counter = 0;
    std::mutex _q_mtx;    
};