#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <atomic>
#include <stdexcept>

template <typename T>
class WeakPtr;

template <typename T_arg>
class SharedPtr
{
    friend class WeakPtr<T_arg>;

    friend int TestSharedPtr();
    friend int TestWeakPtr();

    template <typename T>
    friend bool operator==(std::nullptr_t, const SharedPtr<T> &rarg);

    template <typename T>
    friend bool operator==(const SharedPtr<T> &larg, std::nullptr_t);

    template <typename T>
    friend bool operator!=(std::nullptr_t, const SharedPtr<T> &rarg);

    template <typename T>
    friend bool operator!=(const SharedPtr<T> &larg, std::nullptr_t);

protected:
    struct CtrlBlock
    {
        std::atomic<unsigned int> mWeakRefCount;
        std::atomic<unsigned int> mSharedRefCount;
        std::atomic<T_arg *> mManagedPtr;
    };

public:
    SharedPtr(T_arg *managedPtr = nullptr)
    {
        if (managedPtr != nullptr)
        {
            mCtrlBlk = new CtrlBlock;
            static_cast<CtrlBlock *>(mCtrlBlk)->mManagedPtr = managedPtr;
            static_cast<CtrlBlock *>(mCtrlBlk)->mWeakRefCount = 0;
            static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount = 1;
        }
    }

    ~SharedPtr()
    {
        if (mCtrlBlk != nullptr)
        {
            if (static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount.fetch_sub(1) == 1)
            {
                delete static_cast<CtrlBlock *>(mCtrlBlk)->mManagedPtr.exchange(nullptr);

                if (static_cast<CtrlBlock *>(mCtrlBlk)->mWeakRefCount == 0)
                {
                    delete static_cast<CtrlBlock *>(mCtrlBlk);
                }
            }
        }
    }

    SharedPtr(const SharedPtr &other)
    {
        mCtrlBlk.exchange(other.mCtrlBlk);
        if (mCtrlBlk != nullptr)
        {
            static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount++;
        }
    }

    SharedPtr(SharedPtr &&other)
    {
        mCtrlBlk.exchange(other.mCtrlBlk.exchange(nullptr));
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this == &other)
        {
            return *this;
        }

        CtrlBlock *old = mCtrlBlk.exchange(other.mCtrlBlk);
        if (mCtrlBlk != nullptr)
        {
            static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount++;
        }

        if (old != nullptr)
        {
            if (old->mSharedRefCount.fetch_sub(1) == 1)
            {

                delete old->mManagedPtr.exchange(nullptr);

                if (old->mWeakRefCount == 0)
                {
                    delete old;
                }
            }
        }

        return *this;
    }

    SharedPtr &operator=(SharedPtr &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        CtrlBlock *old = mCtrlBlk.exchange(other.mCtrlBlk.exchange(nullptr));

        if (old != nullptr)
        {
            if (old->mSharedRefCount.fetch_sub(1) == 1)
            {

                delete old->mManagedPtr.exchange(nullptr);

                if (old->mWeakRefCount == 0)
                {
                    delete old;
                }
            }
        }

        return *this;
    }

    T_arg *get() const
    {
        if (mCtrlBlk != nullptr && static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount != 0)
        {
            return static_cast<CtrlBlock *>(mCtrlBlk)->mManagedPtr;
        }
        return nullptr;
    }

    T_arg &operator*() const
    {
        if (mCtrlBlk != nullptr && static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount != 0)
        {
            return *(static_cast<CtrlBlock *>(mCtrlBlk)->mManagedPtr);
        }
        throw std::runtime_error("Access null pointer");
    }

    T_arg *operator->() const
    {
        if (mCtrlBlk != nullptr && static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount != 0)
        {
            return static_cast<CtrlBlock *>(mCtrlBlk)->mManagedPtr;
        }
        return nullptr;
    }

protected:
    SharedPtr(CtrlBlock *ctrlBlk) {
        mCtrlBlk.exchange(ctrlBlk);
        if (mCtrlBlk != nullptr)
        {
            static_cast<CtrlBlock *>(mCtrlBlk)->mSharedRefCount++;
        }
    }

    std::atomic<CtrlBlock *> mCtrlBlk;
};

template <typename T_arg>
class WeakPtr
{
    friend int TestWeakPtr();
    
public:
    WeakPtr() {
        mCtrlBlk.exchange(nullptr);
    }
    
    WeakPtr(const SharedPtr<T_arg> &sharedPtr)
    {
        mCtrlBlk.exchange(sharedPtr.mCtrlBlk);

        if (sharedPtr.mCtrlBlk != nullptr)
        {
            static_cast<typename SharedPtr<T_arg>::CtrlBlock *>(sharedPtr.mCtrlBlk)->mWeakRefCount++;
        }
    }
    ~WeakPtr()
    {
        if (mCtrlBlk != nullptr)
        {
            if (static_cast<typename SharedPtr<T_arg>::CtrlBlock *>(mCtrlBlk)->mWeakRefCount.fetch_sub(1) == 1)
            {
                if (static_cast<typename SharedPtr<T_arg>::CtrlBlock *>(mCtrlBlk)->mSharedRefCount == 0)
                {
                    delete static_cast<typename SharedPtr<T_arg>::CtrlBlock *>(mCtrlBlk)->mManagedPtr.exchange(nullptr);
                }
            }
        }
    }

    WeakPtr(const WeakPtr &other)
    {
        mCtrlBlk.exchange(other.mCtrlBlk);
        if (mCtrlBlk != nullptr)
        {
            static_cast<typename SharedPtr<T_arg>::CtrlBlock *>(mCtrlBlk)->mWeakRefCount++;
        }
    }
    WeakPtr(WeakPtr &&other)
    {
        mCtrlBlk.exchange(other.mCtrlBlk.exchange(nullptr));
    }

    WeakPtr &operator=(const WeakPtr &other)
    {
        if (this == &other)
        {
            return *this;
        }

        typename SharedPtr<T_arg>::CtrlBlock *old = mCtrlBlk.exchange(other.mCtrlBlk);
        if (mCtrlBlk != nullptr)
        {
            static_cast<typename SharedPtr<T_arg>::CtrlBlock *>(mCtrlBlk)->mWeakRefCount++;
        }

        if (old != nullptr)
        {
            if (old->mWeakRefCount.fetch_sub(1) == 1)
            {
                if (old->mSharedRefCount == 0)
                {
                    delete old->mManagedPtr.exchange(nullptr);
                }
            }
        }

        return *this;
    }

    WeakPtr &operator=(WeakPtr &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        typename SharedPtr<T_arg>::CtrlBlock *old = mCtrlBlk.exchange(other.mCtrlBlk.exchange(nullptr));

        if (old != nullptr)
        {
            if (old->mWeakRefCount.fetch_sub(1) == 1)
            {
                if (old->mSharedRefCount == 0)
                {
                    delete old->mManagedPtr.exchange(nullptr);
                }
            }
        }

        return *this;
    }

    SharedPtr<T_arg> lock()
    {
        return SharedPtr<T_arg>(mCtrlBlk);
    }

protected:
    std::atomic<typename SharedPtr<T_arg>::CtrlBlock *> mCtrlBlk;
};

template <typename T>
bool operator==(std::nullptr_t, const SharedPtr<T> &rarg)
{
    if (rarg.mCtrlBlk == nullptr || static_cast<typename SharedPtr<T>::CtrlBlock *>(rarg.mCtrlBlk)->mManagedPtr == nullptr)
    {
        return true;
    }

    return false;
}

template <typename T>
bool operator==(const SharedPtr<T> &larg, std::nullptr_t)
{
    if (larg.mCtrlBlk == nullptr || static_cast<typename SharedPtr<T>::CtrlBlock *>(larg.mCtrlBlk)->mManagedPtr == nullptr)
    {
        return true;
    }

    return false;
}

template <typename T>
bool operator!=(std::nullptr_t, const SharedPtr<T> &rarg)
{
    return !operator==(nullptr, rarg);
}

template <typename T>
bool operator!=(const SharedPtr<T> &larg, std::nullptr_t)
{
    return !operator==(larg, nullptr);
}

#endif