#pragma once
#include "ControlBlock.hpp"
#include <stdexcept>

template<typename T>
class SharedPtr
{
public:
    SharedPtr(): cb_{nullptr}{
        
    }

    SharedPtr(T* ptr): cb_{ptr ? new ControlBlock<T>{ptr} : nullptr}{
        
    }

    // make sure you delete allocated memory for ControlBlock ptr
    ~SharedPtr(){
        // checks to see if we this is the last SharedPtr pointing to the
        // ControlBlock
        if(cb_ && cb_->ref_count_.fetch_sub(1) == 1){
            delete cb_;
        }
        cb_ = nullptr;
    }
    
    // copy constructor
    SharedPtr(const SharedPtr& other){
        this->cb_ = other.cb_;
        this->cb_->ref_count_.fetch_add(1);
    }
    
    // copy assignment operator
    SharedPtr& operator=(const SharedPtr& other){
        if(this == &other){
            return *this;
        }
        
        // need to decrement and replace the old cb that it was pointing to
        if(this->cb_ && this->cb_->ref_count_.fetch_sub(1) == 1){
            delete cb_;
            cb_ = nullptr;
        }

        this->cb_ = other.cb_;
        this->cb_->ref_count_.fetch_add(1);

        return *this;
    }
    
    // implement move constructor
    SharedPtr(SharedPtr&& other) noexcept{
        this->cb_ = std::move(other.cb_);
        other.cb_ = nullptr;
    } 
    
    // implement move assignment operator
    SharedPtr& operator=(SharedPtr&& other) noexcept{
        if(this == &other){
            return *this;
        }
        // need to decrement and replace the old cb that it was pointing to
        if(this->cb_ && this->cb_->ref_count_.fetch_sub(1) == 1){
            delete cb_;
            cb_ = nullptr;
        }

        this->cb_ = std::move(other.cb_);
        other.cb_ = nullptr;

        return *this;
    }

    T& operator*(){
        if(!cb_ || !cb_->ptr_){
            throw std::runtime_error("Dereferencing nullptr!");
        }

        return *(cb_->ptr_);
    }
    
    T* operator->(){
        if(!cb_){
            return nullptr;
        } 
        return cb_->ptr_;
    }

    int RefCount(){
        if(!cb_){
            return -1;
        }

        return cb_->ref_count_.load();
    }    

private:
    ControlBlock<T>* cb_{};
};
