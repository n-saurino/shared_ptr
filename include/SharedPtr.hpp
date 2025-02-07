#pragma once
#include "ControlBlock.hpp"

template<typename T>
class SharedPtr
{
public:
    SharedPtr(T* ptr): cb_{std::move(ptr)}{
        
    }

    // make sure you delete allocated memory for ControlBlock ptr
    ~SharedPtr(){
        // checks to see if we this is the last SharedPtr pointing to the
        // ControlBlock
        if(cb_->ref_count_.fetch_sub(1) == 1){
            delete cb_;
        }
        cb_ = nullptr;
    }
    
    // delete copy constructor
    SharedPtr(const SharedPtr& other){
        if(this != &other){
            this->cb_ = other->cb_;
            this->cb_->ref_count_.fetch_add(1);
        }
    }
    
    // delete copy assignment operator
    SharedPtr& operator=(const SharedPtr& other){
        if(this == &other){
            return *this;
        }
    }
    
    // implement move constructor
    SharedPtr(SharedPtr&& other){
        if(this != &other){
            this->cb_ = std::move(other->cb_);
            other->cb_ = nullptr;
        }
    } 
    
    // implement move assignment operator
    SharedPtr& operator=(SharedPtr&& other){
        if(this == &other){
            return *this;
        }
        
        this->cb_ = std::move(other->cb_);
        other->cb_ = nullptr;

        return *this;
    }

    T& operator*(){
        return *(cb_->ptr_);
    }
    
    T* operator->(){
        return cb->ptr_;
    }

private:
    ControlBlock<T>* cb_{};
};
