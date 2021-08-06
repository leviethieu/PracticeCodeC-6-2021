#include <iostream>
#include <vector>
   /*
    *  Ý tưởng : số nguyêm nhỏ nhất không âm có trong mảng chắc chắn thuộc khoảng [0 - (n+1)];
    *  B1: duyệt mảng đã cho lấy số nguyên thuộc khoảng [0 - n];
    *  B2: swap vị trí của số tự nhiên lấy được tới vị trí bằng giá trị của số đó trừ 1; ví dụ như arr[i] = 0 thì gán vị trí arr[0];
    *  B3: sau swap thì ta có khoảng các giá trị liền nhau => ta check 2 giá trị liền nhau không
    *  => nếu có thì duyệt tiếp, không thì ta lấy vị trí cộng 1 là ra giá trị cần tìm 
    */
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
        while ( arr[i] >= 0 && arr[i] <= arr.size() && arr[i] != arr[arr[i]] ) 
        {
            swap(arr[i], arr[arr[i]]);
        }
    }
   
    for (size_t i = 0; i < arr.size(); i++) 
    {   
        if(arr[0] != 0)
        {
            return 0;
        }

        if (arr[i] != arr[i+1] - 1) 
        {
            return arr[i] + 1 ;
        }
    }
   
    return arr.size() + 1;
}
 

int main()
{
    vector <int> arr = {-8,-7,1 ,6 ,7 ,5 ,2 ,3 ,0 ,4};
 
    int MinNonNeg = SearchMinNonNeg(arr);
 
    cout << MinNonNeg;
 
     return 0;
}
