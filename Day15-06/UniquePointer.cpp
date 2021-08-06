#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <stdexcept>
#include <atomic>

template <typename T_arg>
class UniquePtr 
{
    
    template <typename T>
    friend bool operator==(std::nullptr_t, const UniquePtr<T>& rarg);

    template <typename T>
    friend bool operator==(const UniquePtr<T>& larg, std::nullptr_t);

    template <typename T>
    friend bool operator!=(std::nullptr_t, const UniquePtr<T>& rarg);

    template <typename T>
    friend bool operator!=(const UniquePtr<T>& larg, std::nullptr_t);

    template <typename T>
    friend bool operator!=(const UniquePtr<T>& larg, const UniquePtr<T>& rarg);

    public:
        UniquePtr(T_arg *managedPtr = nullptr) : mManagedPtr(managedPtr) {

        }
        ~UniquePtr() {
            delete mManagedPtr.exchange(nullptr); 
        }                                         

        UniquePtr(UniquePtr&& other) {
            delete mManagedPtr.exchange(other.mManagedPtr.exchange(nullptr));
        }

        UniquePtr& operator=(UniquePtr&& other) {
            if (this == &other) {
                return *this;
            }
            delete mManagedPtr.exchange(other.mManagedPtr.exchange(nullptr));
            return *this;
        }

        T_arg* get() const {
            return mManagedPtr;
        }

        T_arg& operator *() const {
            return *mManagedPtr;
        }

        T_arg* operator->() const {
            return mManagedPtr;
        }
    protected:
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(UniquePtr& other) = delete;

        std::atomic<T_arg*> mManagedPtr;
        
};

template <typename T>
bool operator==(std::nullptr_t, const UniquePtr<T>& rarg)
{
    if (rarg.mManagedPtr == nullptr) {
        return true;
    }
    
    return false;
}

template <typename T>
bool operator==(const UniquePtr<T>& larg, std::nullptr_t)
{
    if (larg.mManagedPtr == nullptr) {
        return true;
    }
    
    return false;
}

template <typename T>
bool operator!=(std::nullptr_t, const UniquePtr<T>& rarg)
{
    return !operator==(nullptr,rarg);   
}

template <typename T>
bool operator!=(const UniquePtr<T>& larg, std::nullptr_t)
{
    return !operator==(larg,nullptr);
}

#endif