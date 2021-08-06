#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
 
template <typename T_arg>
class MyWeakPtr;
 
template <typename T_arg>
class MyUniquePtr 
{
 public:
 MyUniquePtr(T_arg *managedPtr) : mManagedPtr(managedPtr) {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 }
 ~MyUniquePtr() {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 delete mManagedPtr;
 }
 
 T_arg* Get() {
 return mManagedPtr;
 }
 T_arg& operator *() {
 return *mManagedPtr;
 }
 T_arg* operator->() {
 return mManagedPtr;
 }
 protected:
 T_arg *mManagedPtr;
};
 
template <typename T_arg>
class MySharedPtr {
 friend class MyWeakPtr<T_arg>;
 
 protected:
 struct SharedPtrCtrl {
 T_arg* mManagedPtr;
 int mSharedRefCount;
 int mWeakRefCount;
 };
 
 SharedPtrCtrl* mCtrlRef;
 
 public:
 MySharedPtr() {
 mCtrlRef = nullptr;
 }
 MySharedPtr(T_arg *managedPtr) {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 mCtrlRef = new SharedPtrCtrl();
 mCtrlRef->mManagedPtr = managedPtr;
 mCtrlRef->mSharedRefCount = 1;
 mCtrlRef->mWeakRefCount = 0;
 }
 
 MySharedPtr(SharedPtrCtrl* ctrlRef) {
 mCtrlRef = ctrlRef;
 mCtrlRef->mSharedRefCount++;
 printf("%s:%d - mSharedRefCount= %d\n",__FUNCTION__,__LINE__,mCtrlRef->mSharedRefCount);
 }
 
 MySharedPtr(const MySharedPtr& other)
 {
 mCtrlRef = other.mCtrlRef;
 mCtrlRef->mSharedRefCount++;
 printf("%s:%d - mSharedRefCount= %d\n",__FUNCTION__,__LINE__,mCtrlRef->mSharedRefCount);
 }
 
 MySharedPtr& operator=(const MySharedPtr& other){
 mCtrlRef = other.mCtrlRef;
 mCtrlRef->mSharedRefCount++;
 
 printf("%s:%d - mSharedRefCount= %d\n",__FUNCTION__,__LINE__,mCtrlRef->mSharedRefCount);
 
 return *this;
 }
 
 ~MySharedPtr() {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 if (mCtrlRef == nullptr) {
 return;
 }
 
 if ( mCtrlRef->mSharedRefCount > 0) {
 mCtrlRef->mSharedRefCount--;
 
 printf("%s:%d - mSharedRefCount= %d\n",__FUNCTION__,__LINE__,mCtrlRef->mSharedRefCount);
 
 if (mCtrlRef->mSharedRefCount <= 0) {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 delete mCtrlRef->mManagedPtr;
 printf("%s:%d - mWeakRefCount= %d\n",__FUNCTION__,__LINE__,mCtrlRef->mWeakRefCount);
 if (mCtrlRef->mWeakRefCount == 0) {
 delete mCtrlRef;
 }
 }
 } 
 }
 
 T_arg* Get() {
 if (mCtrlRef == nullptr || mCtrlRef->mSharedRefCount <= 0) {
 return nullptr;
 }
 return mCtrlRef->mManagedPtr;
 }
 T_arg& operator *() {
 if (mCtrlRef == nullptr || mCtrlRef->mSharedRefCount <= 0) {
 throw std::runtime_error("Invalid pointer");
 }
 return *mCtrlRef->mManagedPtr;
 }
 T_arg* operator->() {
 if (mCtrlRef == nullptr || mCtrlRef->mSharedRefCount <= 0) {
 return nullptr;
 }
 return mCtrlRef->mManagedPtr;
 }
};
 
template <typename T_arg>
class MyWeakPtr 
{
 public:
 MyWeakPtr() {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 mCtrlRef = nullptr;
 }
 
 MyWeakPtr(MySharedPtr<T_arg>& sharedPtr){
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 mCtrlRef = sharedPtr.mCtrlRef;
 mCtrlRef->mWeakRefCount++;
 printf("%s:%d - mWeakRefCount: %d\n",__FUNCTION__,__LINE__,mCtrlRef->mWeakRefCount);
 }
 
 ~MyWeakPtr() {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 if (mCtrlRef == nullptr) {
 return;
 }
 
 if ( mCtrlRef->mWeakRefCount > 0) {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 mCtrlRef->mWeakRefCount--;
 printf("%s:%d - mWeakRefCount= %d\n",__FUNCTION__,__LINE__,mCtrlRef->mWeakRefCount);
 if (mCtrlRef->mWeakRefCount == 0) {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 delete mCtrlRef;
 }
 }
 }
 
 MySharedPtr<T_arg> lock() {
 return MySharedPtr<T_arg>(mCtrlRef);
 }
 
 MyWeakPtr& operator=(MySharedPtr<T_arg>& sharedPtr){
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 mCtrlRef = sharedPtr.mCtrlRef;
 mCtrlRef->mWeakRefCount++;
 printf("%s:%d - mWeakRefCount: %d\n",__FUNCTION__,__LINE__,mCtrlRef->mWeakRefCount);
 return *this;
 } 
 
 protected:
 typename MySharedPtr<T_arg>::SharedPtrCtrl* mCtrlRef;
};
 
class Foo {
 public:
 ~Foo() {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 }
 void printHello()
 {
 printf("Hello the world\n");
 }
};
 
void myProcess(MySharedPtr<Foo> input)
{
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 input->printHello();
}
 
int main() {
 MyWeakPtr<Foo> weakPtr;
 
 do {
 MySharedPtr<Foo> abc;
 
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 MySharedPtr<Foo> myptr(new Foo());
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 myptr->printHello();
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 
 do {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 MySharedPtr<Foo> otherPtr = myptr;
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 
 otherPtr->printHello();
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 }
 while(0);
 
 do {
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 weakPtr = myptr;
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 weakPtr.lock()->printHello();
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 }
 while(0);
 
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 // do {
 // MySharedPtr<Foo> originalRef = myptr;
 // myProcess(myptr);
 
 // MySharedPtr<Foo> ref2;
 // ref2 = myptr;
 
 
 
 // }
 // while(0); 
 }
 while(0);
 printf("%s:%d\n",__FUNCTION__,__LINE__);
 
 
 // do {
 // printf("%s:%d\n",__FUNCTION__,__LINE__);
 // MyUniquePtr<Foo> myptr(new Foo());
 // printf("%s:%d\n",__FUNCTION__,__LINE__);
 // (*myptr).printHello();
 // myptr->printHello();
 // printf("%s:%d\n",__FUNCTION__,__LINE__);
 // }
 // while(0); 
 
}