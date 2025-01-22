#include "SharedPtr.hpp"

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr = nullptr): ref_count_{new int{1}}, ptr_{ptr}{

}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other):
                        ref_count_{other->ref_count_}, 
                        ptr_{other->ptr_}{
    ++(*ref_count_);
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other): ptr_{other->ptr_},
                        ref_count_{other->ref_count_}{
    other->ptr_ = nullptr;
    other->ref_count_ = nullptr;
}

template<typename T>
SharedPtr<T>::~SharedPtr(){
    // if there are no longer any pointers to the object
    // delete the object and our reference counter
    if(!(--ref_count_)){
        delete ptr_;
        delete ref_count_;
    }
}

template<typename T>
T& SharedPtr<T>::operator*(){
    return *ptr_;
}

template<typename T>
T* SharedPtr<T>::operator->(){
    return ptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other){
    if(this != &other){
        if(!(--(*ref_count__))){
            delete ptr_;
            delete ref_count_;
        }
       this->ptr_ = other->ptr_;
       this->ref_count_ = other->ref_count_; 
       (*ref_count)++;
    }
    
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>&& other){
    if(this != &other){
        if(!(--(*ref_count_))){
            delete ptr_;
            delete ref_count_;
        }
        ptr_ = other->ptr_;
        ref_count_ = other->ref_count_;
        other->ptr_ = nullptr;
        other->ref_count_ = nullptr;
    }   

    return *this; 
}

template<typename T>
int SharedPtr<T>::ReferenceCount() const{
    return *ref_count_;
}

