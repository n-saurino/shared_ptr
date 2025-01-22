#pragma once
#include <iostream>
#include <atomic>

template<typename T>
class ControlBlock
{
public:
    ControlBlock(T* ptr): ptr_{ptr}, ref_count_{1}{

    }

    ~ControlBlock(){
        delete ptr_;
    }

private:
    T* ptr_{};
    std::atomic<int> ref_count_{};
};