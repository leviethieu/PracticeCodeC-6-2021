#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int SearchMinNonNeg(vector<int> arr)
{
    for (size_t i = 0; i < arr.size(); i++) 
    {
        while (arr[i] >= 1 && arr[i] <= arr.size() && arr[i] != arr[arr[i] - 1]) 
        {
            swap(arr[i], arr[arr[i] - 1]);
        }
    }
   
    for (size_t i = 0; i < arr.size(); i++) 
    {
        if (arr[i] != i + 1) 
        {
            return i + 1;
        }
    }
   
    return arr.size() + 1;
}
 

int main()
{
    vector <int> arr = {-8,-7,1 ,4 ,7 ,5 ,2 ,3 };
 
    int MinNonNeg = SearchMinNonNeg(arr);
 
    cout << MinNonNeg;
 
     return 0;
}
