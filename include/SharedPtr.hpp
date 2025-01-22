#pragma once
#include "ControlBlock.hpp"

template<typename T>
class SharedPtr
{
public:
    // instantiates a new control block and points out cb_ptr_ at it
    // or if T* is nullptr, we set cb_ptr_ to nullptr
    SharedPtr(T* ptr): cb_ptr_{ptr ? new ControlBlock<T>{} : nullptr}{

    }

    // copy constructor
    SharedPtr(const SharedPtr& other){
        // need to decrease the count of the ref_count_ and then
        // if this is the last ref_count, we need to delete the 
        // control block
        if(cb_ptr_ && cb_ptr_->ref_count_.fetch_sub(1) == 1){
            delete cb_ptr_;
            cb_ptr_ = nullptr;
        }
        cb_ptr_ = other.cb_ptr_;
        cb_ptr_->ref_count_.fetch_add(1);
    }

    ~SharedPtr(){
        delete cb_ptr_;
    }
    
    // copy assignment operator
    SharedPtr& operator=(const SharedPtr& other){
        // check for self assignment
        if(this != &other){
            if(cb_ptr_ && cb_ptr_->ref_count_.fetch_sub(1) == 1){
                delete cb_ptr_;
            }    
            
            cb_ptr_ = other.cb_ptr_;
            if(cb_ptr_){
                cb_ptr_->ref_count_.fetch_add(1);
            }
        }
        
        return *this;
    }
    
    // move assignment operator
    SharedPtr& operator=(const SharedPtr&& other) noexcept{
        if(this != &other){
            if(cb_ptr_ && cb_ptr_->ref_count_.fetch_sub(1) == 1){
                delete cb_ptr_;
            }
            cb_ptr_ = other.cb_ptr_;
            other.cb_ptr_ = nullptr;
        } 
        
        return *this;
    }

    T& operator*(){
        if(cb_ptr_){
            return *(cb_ptr_->ptr_);
        }

        return nullptr; 
    }

    T* operator->(){
        if(cb_ptr_){
            return cb_ptr_->ptr_;
        } 
        
        return nullptr;
    }
    
    int RefCount() const{
        if(cb_ptr_){
            return cb_ptr_->ref_count_.load();
        }
        
        return -1;
    }

private:
    ControlBlock<T>* cb_ptr_{};
};
