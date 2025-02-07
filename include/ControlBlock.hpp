#pragma once
#include <atomic>

template<typename T>
class ControlBlock
{
public:
    ControlBlock(T* ptr): ptr_{std::move(ptr)}, ref_count_{1}{

    }
    ~ControlBlock(){
        
    }

private:
    // need a T pointer
    T* ptr_{}; 
    
    // and an atomic integer for the reference counter
    std::atomic<int> ref_count_{};
};
