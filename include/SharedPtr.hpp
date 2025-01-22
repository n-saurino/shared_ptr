#pragma once
#include <iostream>

template<typename T>
class SharedPtr
{
public:
    // constructor initializes the shared pointer with a raw pointer
    SharedPtr(T* ptr);
    // copy constructor increases reference count
    SharedPtr(const SharedPtr& other);
    // move constructor transfers ownership without increasing reference count
    SharedPtr(SharedPtr&& other);
    // destructor
    ~SharedPtr();
    // * operator overload for dereferencing
    T& operator*();
    // -> operator overloading for ptr access
    T* operator->();
    // copy assignment operator
    SharedPtr& operator=(const SharedPtr& other);
    // move assignment operator
    SharedPtr& operator=(const SharedPtr&& other);
    // get reference count
    int ReferenceCount() const;
    
private:
    int* ref_count_{0};
    T* ptr_{};
};
