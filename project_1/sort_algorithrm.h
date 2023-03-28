#include <stdio.h>
#include <iostream>
#include <cstring>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void print(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// ========================QUICK SORT================================
void quickSort(int arr[], int left, int right, int &soLanSoSanh, int &soLanSwap)
{
    if (left >= right)
        return;
    int i = left;
    int j = right;
    int x = arr[(left + right) / 2];
    do
    {
        while (arr[i] < x)
        {
            soLanSoSanh++;
            i++;
        }
        while (arr[j] > x)
        {
            soLanSoSanh++;
            j--;
        }

        if (i <= j)
        {
            swap(arr[i], arr[j]);
            soLanSwap++;
            i++;
            j--;
        }
    } while (i < j);

    if (i < right)
        quickSort(arr, i, right, soLanSoSanh, soLanSwap);
    if (j > left)
        quickSort(arr, left, j, soLanSoSanh, soLanSwap);
}

// ========================MERGE SORT================================
void merge1(int arr[], int arr_b[], int size_b, int arr_c[], int size_c, int i, int &soLanSoSanh, int &soLanSwap)
{
    int ib = 0;
    int ic = 0;
    int size_arr = size_b + size_c;
    for (int j = 0; j < size_arr; j++)
    {
        soLanSoSanh++; // Tăng số lần so sánh
        if (size_b == ib)
        {
            arr[i + j] = arr_c[ic++];
        }
        else if (size_c == ic)
        {
            arr[i + j] = arr_b[ib++];
        }
        else if (arr_b[ib] <= arr_c[ic])
        {
            arr[i + j] = arr_b[ib++];
        }
        else if (arr_b[ib] > arr_c[ic])
        {
            arr[i + j] = arr_c[ic++];
            soLanSwap++; // Tăng số lần swap
        }
    }
}

void mergeSort(int arr[], int length, int &soLanSoSanh, int &soLanSwap)
{
    int k = 1;
    while (k < length)
    {
        for (int i = 0; i < length; i = i + 2 * k)
        {
            int size_b = std::min(k, length - i);
            int size_c = std::min(k, length - size_b - i);

            int *arr_b = new int[size_b];
            int *arr_c = new int[size_c];

            if (size_b == 0 || size_c == 0)
            {
                break;
            }

            for (int ib = 0; ib < size_b; ib++)
            {
                arr_b[ib] = arr[i + ib];
            }

            for (int ic = 0; ic < size_c; ic++)
            {
                arr_c[ic] = arr[i + size_b + ic];
            }

            merge1(arr, arr_b, size_b, arr_c, size_c, i, soLanSoSanh, soLanSwap);

            delete[] arr_b;
            delete[] arr_c;
        }
        k *= 2;
    }
}

// ========================NATURAL MERGE SORT================================
// Trộn hai mảng con arr[l..m] và arr[m+1..r] đã được sắp xếp lại
void merge2(int arr[], int l, int m, int r, int &soLanSoSanh, int &soLanSwap)
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
        soLanSoSanh++;
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
    soLanSwap += r - l + 1;
}

void naturalMergeSort(int arr[], int n, int &soLanSoSanh, int &soLanSwap)
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
                soLanSoSanh++; // tăng số lần so sánh
            }

            if (m == n)
            {
                break;
            }

            r = m + 1;
            while (r < n && arr[r - 1] <= arr[r])
            {
                r++;
                soLanSoSanh++; // tăng số lần so sánh
            }

            // thực hiện trộn hai mảng lại
            merge2(arr, l, m - 1, r - 1, soLanSoSanh, soLanSwap);

            l = r;
            isSorted = false;
        }
    }
}

//===========================HEAP SORT=========================
// Shift of Heap Sort  ---> build max heap
void shift(int arr[], int l, int r, int &soLanSoSanh, int &soLanSwap)
{
    int x, i, j;
    i = l;
    j = 2 * i + 1; // child of node i
    x = arr[i];    // value at node i
    while (j <= r)
    {
        if ((j < r) && (arr[j] < arr[j + 1]))
            j = j + 1; // chon child node lon
        if (arr[j] <= x)
            break; // neu ko co child nao lon hon x thi
        else
        {
            swap(arr[i], arr[j]);
            i = j;
            j = 2 * i + 1;
            soLanSwap++; // tăng biến đếm số lần swap lên 1
        }
        soLanSoSanh++; // tăng biến đếm số lần so sánh lên 1
    }
}

// max heap init
void createHeap(int arr[], int n, int &soLanSoSanh, int &soLanSwap)
{
    int l = (n / 2 - 1); // start: last parent node
    while (l >= 0)
    {
        shift(arr, l, n - 1, soLanSoSanh, soLanSwap);
        l = l - 1;
    }
}

// heap sort main
void heapSort(int arr[], int n, int &soLanSoSanh, int &soLanSwap)
{
    int r;
    r = n - 1;
    createHeap(arr, n, soLanSoSanh, soLanSwap); // build Heap
    while (r > 0)
    {
        swap(arr[0], arr[r]);
        r = r - 1;
        soLanSwap++; // tăng biến đếm số lần swap lên 1
        shift(arr, 0, r, soLanSoSanh, soLanSwap);
    }
}

// ========================RADIX SORT================================
int findMax(int arr[], int length)
{
    int max = arr[0];
    for (int i = 1; i < length; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int countDigit(int num)
{
    int count = 0;
    while (num > 0)
    {                   // 1234
        num = num / 10; // 123--12--1--0
        count++;        // 1--2--3--4
    }
    return count;
}

int getDigit(int num, int k)
{
    int digit = 0;
    for (int i = 0; i <= k; i++)
    {                     // 1234 - k=3
        digit = num % 10; // 4--3--2--1 (i=0 1 2 3)
        num = num / 10;   // 123--12--1--0
    }
    return digit;
}

void radixSort(int arr[], int length, int soLanSoSanh, int soLanSwap)
{
    int valueMax = findMax(arr, length);
    int maxDigit = countDigit(valueMax);
    int bucket[10][length];
    int sizeBucket[10];

    for (int k = 0; k < maxDigit; k++)
    {
        for (int i = 0; i < 10; i++) // Phân lô
        {
            sizeBucket[i] = 0;
        }

        for (int i = 0; i < length; i++) // bán nền
        {
            int digit = getDigit(arr[i], k);
            int index = sizeBucket[digit];
            bucket[digit][index] = arr[i];
            sizeBucket[digit]++;
        }

        int index = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < sizeBucket[i]; j++)
            {
                arr[index] = bucket[i][j];
                index++;
            }
        }
    }
}