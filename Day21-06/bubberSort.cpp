#include <stdio.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   bool swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           swapped = true;
        }
     }
 
     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
   }
}
 
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}
 
// Driver program to test above functions
int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
// struct node* swap(struct node* node1, struct node* node2) {
//   struct node* temp;
//   temp = node1->next;
//   node1->next = node2->next;
//   node2->next = temp;
//   if (node1->next != NULL)
//     node1->next->prev = node1;
//   if (node2->next != NULL)
//     node2->next->prev = node2;
//   temp = node1->prev;
//   node1->prev = node2->prev;
//   node2->prev = temp;
//   if (node1->prev != NULL)
//     node1->prev->next = node1;
//   if (node2->prev == NULL)
//     return node2;
//   node2->prev->next = node2;
//   return node1;
// }