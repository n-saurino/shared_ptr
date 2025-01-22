#pragma once
#include <iostream>

template<typename T>
class SharedPtr
{
public:
    // constructor initializes the shared pointer with a raw pointer
    SharedPtr(T* ptr): ref_count_{new int{1}}, ptr_{ptr}{

    }
    // copy constructor increases reference count
    SharedPtr(const SharedPtr<T>& other):
                        ref_count_{other.ref_count_}, 
                        ptr_{other.ptr_}{
        ++(*ref_count_);
    }
    // move constructor transfers ownership without increasing reference count
    SharedPtr(SharedPtr<T>&& other): ptr_{other.ptr_},
                        ref_count_{other.ref_count_}{
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }
    // destructor
    ~SharedPtr(){
        // if there are no longer any pointers to the object
        // delete the object and our reference counter
        if(!(--ref_count_)){
            delete ptr_;
            delete ref_count_;
        }
    }
    // * operator overload for dereferencing
    T& operator*(){
        return *ptr_;
    }
    // -> operator overloading for ptr access
    T* operator->(){
        return ptr_;
    }
    // copy assignment operator
    SharedPtr& operator=(const SharedPtr<T>& other){
        if(this != &other){
            if(!(--(*ref_count_))){
                delete ptr_;
                delete ref_count_;
            }
        this->ptr_ = other.ptr_;
        this->ref_count_ = other.ref_count_; 
        (*ref_count_)++;
        }
        
        return *this;
    }
    // move assignment operator
    SharedPtr& operator=(SharedPtr<T>&& other){
        if(this != &other){
            if(!(--(*ref_count_))){
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }   

        return *this; 
    }
    // get reference count
    int ReferenceCount() const{
        return *ref_count_;
    }
    
private:
    int* ref_count_{0};
    T* ptr_{};
};
