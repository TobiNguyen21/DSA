#include <iostream>
#include <time.h>
#include <iomanip>
#include "sort_algorithrm.h"

using namespace std;

int main()
{
    int length;
    cout << "Nhap so luong du lieu vao: ";
    cin >> length;

    // khai báo 5 mảng dữ liệu động để làm dữ liệu đầu vào cho 5 thuật toán
    int *arr1 = new int[length];
    int *arr2 = new int[length];
    int *arr3 = new int[length];
    int *arr4 = new int[length];
    int *arr5 = new int[length];

    // random giá trị cho 5 mảng dữ liệu này, giá trị trong khoảng 0 --> 999 gồm length phần tử
    for (int i = 0; i < length; i++)
    {
        arr1[i] = rand() % 1000;
        arr2[i] = rand() % 1000;
        arr3[i] = rand() % 1000;
        arr4[i] = rand() % 1000;
        arr5[i] = rand() % 1000;
    }

    // khai báo biến tính thời gian chạy các thuật toán
    double timetakenQuickSort, timetakenMergeSort, timetakenNaturalMergeSort, timetakenHeapSort, timetakenRadixSort;
    int soLanSoSanh[5] = {0}; // mảng chứa số lần lặp của 5 thuật toán
    int soLanSwap[5] = {0};   // mảng chứa số lần swap của 5 thuật toán

    // Quick sort
    quickSort(arr1, 0, length - 1, soLanSoSanh[0], soLanSwap[0]);
    time_t time1 = clock();
    timetakenQuickSort = (double)(time1) / CLOCKS_PER_SEC;

    // Merge sort
    mergeSort(arr2, length, soLanSoSanh[1], soLanSwap[1]);
    time_t time2 = clock();
    timetakenMergeSort = (double)(time2) / CLOCKS_PER_SEC;

    // Natural merge sort
    naturalMergeSort(arr3, length, soLanSoSanh[2], soLanSwap[2]);
    time_t time3 = clock();
    timetakenNaturalMergeSort = (double)(time3) / CLOCKS_PER_SEC;

    // Heap sort
    heapSort(arr4, length, soLanSoSanh[3], soLanSwap[3]);
    time_t time4 = clock();
    timetakenHeapSort = (double)(time4) / CLOCKS_PER_SEC;

    // Radix sort
    radixSort(arr5, length, soLanSoSanh[4], soLanSwap[4]);
    time_t time5 = clock();
    timetakenRadixSort = (double)(time5) / CLOCKS_PER_SEC;

    cout << "\n---------------------------------------------------------------------------------------------\n";
    cout << "| Thuat toan          | " << setw(30) << " Thoi gian chay (seconds)"
         << " | " << setw(15) << "So lan so sanh "
         << " | " << setw(15) << "So lan swap"
         << " |\n";
    cout << "---------------------------------------------------------------------------------------------\n";
    cout << "| Quick Sort          | " << setw(30) << setprecision(10) << timetakenQuickSort << " | " << setw(15) << soLanSoSanh[0] << " | " << setw(15) << soLanSwap[0] << " |\n";
    cout << "| Merge Sort          | " << setw(30) << setprecision(10) << timetakenMergeSort << " | " << setw(15) << soLanSoSanh[1] << " | " << setw(15) << soLanSwap[1] << " |\n";
    cout << "| Natural Merge Sort  | " << setw(30) << setprecision(10) << timetakenNaturalMergeSort << " | " << setw(15) << soLanSoSanh[2] << " | " << setw(15) << soLanSwap[2] << " |\n";
    cout << "| Heap Sort           | " << setw(30) << setprecision(10) << timetakenHeapSort << " | " << setw(15) << soLanSoSanh[3] << " | " << setw(15) << soLanSwap[3] << " |\n";
    cout << "| Radix Sort          | " << setw(30) << setprecision(10) << timetakenRadixSort << " | " << setw(15) << soLanSoSanh[4] << " | " << setw(15) << soLanSwap[4] << " |\n";
    cout << "-----------------------------------------------------------------------------------------------\n";

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    system("pause");
    return 0;
}
