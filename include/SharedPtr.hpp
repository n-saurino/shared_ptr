#pragma once
#include "ControlBlock.hpp"

template<typename T>
class SharedPtr
{
public:
    SharedPtr(T* ptr): cb_{ptr}{
        
    }

    // make sure you delete allocated memory for ControlBlock ptr
    ~SharedPtr(){
        
    }
    
    T& operator*(){
        return *(cb_->ptr_);
    }
    
    T* operator->(){
        return cb->ptr_;
    }

private:
    ControlBlock* cb_{};
};
