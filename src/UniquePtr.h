#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>

// Your implementation here
template<class T>
class UniquePtr {
public:
    // Constructors: start unmangaged
    UniquePtr()
        : mPtr(nullptr) {}    

    UniquePtr(T* p) : mPtr(p) {}

    // Deconstructor: clean up owned memory if valid
    ~UniquePtr() {
        if (mPtr != nullptr) {
            delete mPtr;
        }    
    }

    // Disable the copy semantics
    // Copy Constructor
    UniquePtr(const UniquePtr&) = delete;
    
    // Copy Assignment Operator
    UniquePtr& operator = (const UniquePtr&) = delete;


    // Source: https://uofa-cmput350.github.io/materials/lab/3/cpp.html#example-of-a-class-with-move-constructor-assignment
    // Move constructor
    UniquePtr(UniquePtr&& other) : mPtr{other.mPtr}
    {
        other.mPtr = nullptr;
    }

    // Move Assignment: free old resource first, then take the new one
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete mPtr;
            mPtr = other.mPtr;
            other.mPtr = nullptr;
        }
        return *this;
    }
    
    // Converting move constructor
    template<class U>
    UniquePtr(UniquePtr<U>&& other): 
        mPtr{other.release()} {}

    // Standard pointer access operators
    // Deference
    T& operator*() const {
        return *mPtr;
    }

    // Arrow
    T* operator->() const {
        return mPtr;
    }

    // get()
    T* get() const {
        return mPtr;
    }

    // Equality
    bool operator==(const UniquePtr<T>& other) const {
        return mPtr == other.mPtr;
    }

    // Nonempty check
    explicit operator bool() const {
        return mPtr != nullptr;
    }

    // Mutators
    T* release() {
        return std::exchange(mPtr, nullptr);
    }

    void reset(T* newPtr = nullptr) {
        T* old = std::exchange(mPtr, newPtr);
        delete old;
    }

    void swap(UniquePtr<T>& other) {
        using std::swap;
        swap(mPtr, other.mPtr);
    }

private:
    T* mPtr;
    template<class U>
    friend class UniquePtr;

};

// makeUnique template function
template<typename T, typename... Args>
    UniquePtr<T> makeUnique(Args&&... args) {
        return UniquePtr<T>(new T(std::forward<Args>(args)...));
    }

#endif
