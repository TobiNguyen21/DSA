#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}

void docFile(int arr[], int &length)
{
    ifstream inputFile;
    inputFile.open("input.txt");
    inputFile >> length;

    for (int i = 0; i < length; i++)
    {
        inputFile >> arr[i];
    }

    inputFile.close();
}

void ghiFile(int arr[], int length)
{
    ofstream outputFile;
    outputFile.open("output.txt");
    for (int i = 0; i < length; i++)
    {
        outputFile << arr[i] << " ";
    }

    outputFile.close();
}

//------------Select Sort---------------
void selectionSort(int a[], int n)
{
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            swap(a[min], a[i]);
        }
    }
}

//------------Insert Sort---------------
void insertSort(int a[], int n)
{
    int pos;
    int x;
    for (int i = 0; i < n; i++)
    {
        x = a[i];
        pos = i;
        while (pos >= 0 && a[pos - 1] > x)
        {
            a[pos] = a[pos - 1];
            pos--;
        }
        a[pos] = x;
    }
}

//------------Bubble Sort---------------
void bubbleSort(int a[], int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (a[j - 1] > a[j])
                swap(a[j - 1], a[j]);
        }
    }
}

//------------Quick Sort----------------
void quickSort(int a[], int left, int right)
{
    int i, j, x;
    if (left >= right)
        return;
    i = left;
    j = right;
    x = a[(left + right) / 2];
    do
    {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }

    } while (i < j);

    if (i > right)
        quickSort(a, i, right);
    if (left < j)
        quickSort(a, left, j);
}

//-------------heapSort----------------
// Shift of Heap Sort  ---> build max heap
void shift(int a[], int l, int r)
{
    int x, i, j;
    i = l;
    j = 2 * i + 1; // child of node i
    x = a[i];      // value at node i
    while (j <= r)
    {
        if ((j < r) && (a[j] < a[j + 1]))
            j = j + 1; // chon child node lon
        if (a[j] <= x)
            break; // neu ko co child nao lon hon x thi
        else
        {
            swap(a[i], a[j]);
            i = j;
            j = 2 * i + 1;
        }
    }
}

// max heap init
void createHeap(int a[], int n)
{
    int l = (n / 2 - 1); // start: last parent node
    while (l >= 0)
    {
        shift(a, l, n - 1);
        l = l - 1;
    }
}

// heap sort main
void heapSort(int a[], int n)
{
    int r;
    r = n - 1;
    createHeap(a, n); // build Heap
    cout << "\n";
    printArray(a, n);
    while (r > 0)
    {
        swap(a[0], a[r]);
        r = r - 1;
        shift(a, 0, r);
    }
}

//-------------Merge Sort----------------
// merge 2 array
void merge(int arr[], int arr_b[], int size_b, int arr_c[], int size_c, int i)
{
    int ib = 0;
    int ic = 0;
    int size_arr = size_b + size_c;
    for (int j = 0; j < size_arr; j++)
    {
        if (ib == size_b) // mang b da duyet het roi thi bo mang c vao arr[]
        {
            arr[i + j] = arr_c[ic++];
        }
        else if (ic == size_c) // mang c da duyet het roi thi bo mang b vao arr[]
        {
            arr[i + j] = arr_b[ib++];
        }
        else if (arr_b[ib] <= arr_c[ic]) // phan tu mang b nho hon thi bo phan tu do vao mang arr[] truoc
        {
            arr[i + j] = arr_b[ib++];
        }
        else // phan tu mang c nho hon thi bo vo truoc
        {
            arr[i + j] = arr_c[ic++];
        }
    }
}

// merge main
void mergeSort(int arr[], int length)
{
    int k = 1; // so luong phan tu lay lay tu mang arr[] bo vao 2 mang a[] va b[]
    while (k < length)
    {
        for (int i = 0; i < length; i += 2 * k)
        {
            int size_b = min(k, length - i); // size array b < size arr[] and <=k
            int size_c = min(k, length - i - size_b);

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

            // merge
            merge(arr, arr_b, size_b, arr_c, size_c, i);

            delete[] arr_b;
            delete[] arr_c;
        }
        k *= 2;
    }
}

//-------------------Radix Sort----------------
// lấy chữ số thứ k của number  --> vd: number = 123 và k = 1 ===> getDigit = 2
int getDigit(int number, int k)
{
    int digit = 0;
    for (int i = 0; i <= k; i++)
    {
        digit = number % 10;
        number /= 10;
    }
    return digit;
}

// Tìm giá trị lớn nhất trong mảng đó
int maxValueOfArray(int arr[], int length)
{
    int max = arr[0];
    for (int i = 1; i < length; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// Đếm có bao nhiêu chữ số của value đó
int countDigit(int value) // ex: 1234
{
    int count = 0;
    while (value > 0)
    {
        value = value / 10; //-->123-->12-->1-->0
        count++;            // 1-->2-->3-->4
    }
    return count; //==>4
}

void radixSort(int arr[], int length)
{
    int maxValue = maxValueOfArray(arr, length); // ex: 1234
    int maxDigit = countDigit(maxValue);         // 4
    int bucket[10][length];                      // lô lưu trữ
    int size_bucket[10];                         // lưu kích thước của các lô

    for (int k = 0; k < maxDigit; k++)
    {
        // khởi tạo kích thước của các bucket (lô)  ===> Phân lô
        for (int i = 0; i < 10; i++)
        {
            size_bucket[i] = 0; // size_bucket[0] =0 ---> size_bucket[9] = 0;
        }

        // kiểm tra các phần từ array và bỏ vào lô  ====> Bán nền
        for (int i = 0; i < length; i++)
        {
            int digit = getDigit(arr[i], k);
            int index = size_bucket[digit];
            bucket[digit][index] = arr[i];
            size_bucket[digit]++;
        }

        // lấy từ lô bỏ ngược vào array (tức là sắp xếp các vị trí digit của các số)  ===> láy nển bỏ vào lại array
        int index = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < size_bucket[i]; j++)
            {
                arr[index] = bucket[i][j];
                index++;
            }
        }
    }
}

int main()
{
    int arr[100];
    int length = 0;

    docFile(arr, length);
    cout << "Mang sau khi doc tu file: ";
    printArray(arr, length);

    //----------Sort Algorithm-----------------//

    // selectionSort(arr,length);
    // insertSort(arr,length);
    // bubbleSort(arr,length);
    // quickSort(arr, 0, length - 1);
    // heapSort(arr,length);
    mergeSort(arr, length);
    // radixSort(arr, length);

    cout << "\nMang sau khi sap xep: ";
    printArray(arr, length);

    ghiFile(arr, length);

    system("pause");
    return 0;
}