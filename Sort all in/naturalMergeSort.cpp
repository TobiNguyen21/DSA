#include <iostream>
#include <stdlib.h>
using namespace std;

void print(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Trộn hai mảng con arr[l..m] và arr[m+1..r] đã được sắp xếp lại
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int size_b = m - l + 1;
    int size_c = r - m;

    // Tạo hai mảng tạm arr_b và arr_c để lưu trữ mảng con arr[l..m] và arr[m+1..r]
    int *arr_b = new int[size_b];
    int *arr_c = new int[size_c];

    // Sao chép các phần tử của mảng con arr[l..m] và arr[m+1..r] vào hai mảng tạm b và c
    for (i = 0; i < size_b; i++)
        arr_b[i] = arr[l + i];
    for (j = 0; j < size_c; j++)
        arr_c[j] = arr[m + 1 + j];

    // Trộn hai mảng b và c để tạo mảng đã được sắp xếp lại
    i = 0; // index ban đầu của arr_b
    j = 0; // index ban đầu của arr_c
    k = l; // index ban đầu của arr
    while (i < size_b && j < size_c)
    {
        if (arr_b[i] <= arr_c[j])
        {
            arr[k] = arr_b[i];
            i++;
        }
        else
        {
            arr[k] = arr_c[j];
            j++;
        }
        k++;
    }
    // Sao chép các phần tử còn lại của mảng b vào arr
    while (i < size_b)
    {
        arr[k] = arr_b[i];
        i++;
        k++;
    }
    // Sao chép các phần tử còn lại của mảng c vào arr
    while (j < size_c)
    {
        arr[k] = arr_c[j];
        j++;
        k++;
    }

    // Giải phóng bộ nhớ của hai mảng tạm b và c
    delete[] arr_b;
    delete[] arr_c;
}

void naturalMergeSort(int arr[], int n)
{
    int i, j, k;
    bool isSorted = false;
    int l, m, r;

    // loop đến khi mảng đã được xếp
    while (!isSorted)
    {
        isSorted = true;
        l = 0;

        while (l < n)
        {
            m = l + 1;
            while (m < n && arr[m - 1] <= arr[m])
            {
                m++;
            }

            if (m == n)
            {
                break;
            }

            r = m + 1;
            while (r < n && arr[r - 1] <= arr[r])
            {
                r++;
            }

            // thực hiện trộn hai mảng lại
            merge(arr, l, m - 1, r - 1);

            l = r;
            isSorted = false;
        }
    }
}

int main()
{
    int arr[] = {1, 54, 12, 767, 988, 23, 11, 8, 100, 29};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Mang chua sap xep: ";
    print(arr, n);

    naturalMergeSort(arr, n);

    cout << "\nMang da sap xep: ";
    print(arr, n);
    system("pause");
    return 0;
}
