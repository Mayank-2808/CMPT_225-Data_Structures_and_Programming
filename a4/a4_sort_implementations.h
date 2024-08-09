// a4_sort_implementations.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Mayank Mayank>
// St.# : <301563549>
// Email: <mayank_mayank@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "a4_base.h"

using namespace std;

//
// Returns true if v[0] <= v[1] <= ... <= v[n-1], and false otherwise.
// Returns true if v is empty, i.e. an empty vector is considered sorted.
//
template <typename T>
bool is_sorted(vector<T> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i - 1] > v[i])
        {
            return false;
        }
    }
    return true;
}
// is_sorted algorithm used from Toby Donaldson's CMPT225 Week 9 Lecture Notes.

//
// Sorting algorithm headers. Each algorithm implements the named algorithm as
// described in the textbook (iquick sort is described in the assignment), and
// returns a SortStats object containing statistics about the run.
//

template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Bubble sort", v.size(), num_comps, elapsed_cpu_time_sec};
}
// bubble_sort algorithm used from Assignment 4 webpage:
// https://tjd1234.github.io/cmpt225summer2023/assignments/a4/

template <typename T>
SortStats insertion_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();
    
    for(int i = 1; i < v.size(); i++)
    {
        T temp = v[i]; //Pick the element at index i and find its right place among v[0], v[1],. ..,v[i-1]
        int j;
        
        for( j = i-1; j >= 0; j--)
        {
            num_comps++; // <--- num_comps is incremented here
            
            if(v[j] > temp)
                v[j+1] = v[j];
            else
                break;
        }
        
        v[j+1] = temp; //Now insert the element that was at index i, in its right location; which is at index j+1
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Insertion sort", v.size(), num_comps, elapsed_cpu_time_sec};
}
// insertion_sort algorithm used from Yonal Weldeselassie's CMPT130 notes

template <typename T>
SortStats selection_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();
    
    for(int i = 0; i < v.size(); i++)
    {
        int index = i; // select index of minimum element among v[0], v[1],. ..,v[i-1]
    
        for(int j = i + 1; j < v.size(); j++)
        {
            num_comps++; // <--- num_comps is incremented here
            
            if(v[j] < v[index])
                index = j;
        }
        
        T temp = v[i];
        v[i] = v[index];
        v[index] = temp;
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Selection sort", v.size(), num_comps, elapsed_cpu_time_sec};
}
// selection_sort algorithm used from Yonal Weldeselassie's CMPT130 notes

//
// This merges two vectors.
//
ulong num_comps_mergeSort = 0; // <--- num_comps for merge_sort is initialized to 0 here

template <typename T>
vector<T> merge(vector<T> &v1, vector<T> &v2)
{
    vector<T> v;
    int i = 0;
    int j = 0;
    while (i < v1.size() && j < v2.size())
    {
        num_comps_mergeSort++;
        
        if (v1[i] < v2[j])
        {
            v.push_back(v1[i]);
            i++;
        }
        else
        {
            v.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size())
    {
        v.push_back(v1[i]);
        i++;
    }
    while (j < v2.size())
    {
        v.push_back(v2[j]);
        j++;
    }
    return v;
}

template <typename T>
SortStats merge_sort(vector<T> &v)
{
    clock_t start = clock();
    
    if (v.size() <= 1)
    {
        return SortStats();
    }
    int mid = v.size() / 2;
    vector<T> v1(v.begin(), v.begin() + mid);
    vector<T> v2(v.begin() + mid, v.end());
    merge_sort(v1);
    merge_sort(v2);
    v = merge(v1, v2);
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Merge sort", v.size(), num_comps_mergeSort, elapsed_cpu_time_sec};
}
// merge_sort algorithm used from Toby Donaldson's CMPT225 Week 9 lecture notes

//
// Partitions a sub-vector of vector (for quick_sort).
//
// The pivot is the last element in the sub-vector.
//
// Returns the index of the pivot.
//
ulong num_comps_quickSort = 0; // <--- num_comps for quick_sort is initialized to 0 here

template <typename T>
int partition(vector<T> &v, int start, int end)
{
    T pivot = v[end];
    int i = start;
    for (int j = start; j < end; j++)
    {
        num_comps_quickSort++;
        
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[end]);
    return i;
}

template <typename T>
void quick_sort(vector<T> &v, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int pivot = partition(v, start, end);
    quick_sort(v, start, pivot - 1);
    quick_sort(v, pivot + 1, end);
}

template <typename T>
SortStats quick_sort(vector<T> &v)
{
    clock_t start = clock();
    
    quick_sort(v, 0, v.size() - 1);
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Quick sort", v.size(), num_comps_quickSort, elapsed_cpu_time_sec};
}
// quick_sort algorithm used from Toby Donaldson's CMPT225 Week 9 lecture notes

template <typename T>
SortStats shell_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();
    
    for(int gap = v.size()/2; gap >= 1; gap = gap/2)
    {
        for(int j = gap; j < v.size(); j++)
        {
            for(int i = j - gap; i >= 0; i = i - gap)
            {
                num_comps++;
                
                if(v[i+gap] > v[i])
                    break;
                else
                    swap(v[i+gap], v[i]);
            }
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Shell sort", v.size(), num_comps, elapsed_cpu_time_sec};
}
// shell_sort algorithm reference : https://www.youtube.com/watch?v=9crZRd8GPWM

ulong num_comps_iQuickSort = 0; // <--- num_comps for iquick_sort is initialized to 0 here

template <typename T>
int iQuickSort_partition(vector<T> &v, int start, int end)
{
    T pivot = v[end];
    int i = start;
    for (int j = start; j < end; j++)
    {
        num_comps_iQuickSort++;
        
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[end]);
    return i;
}

template <typename T>
void iquick_sort(vector<T> &v, int start, int end)
{
    if(end - start + 1 <= 15)
    {
        for(int i = start; i <= end; i++)
        {
            T temp = v[i]; //Pick the element at index i and find its right place among v[0], v[1],. ..,v[i-1]
            int j;
            
            for( j = i-1; j >= start; j--)
            {
                num_comps_iQuickSort++; // <--- num_comps is incremented here
                
                if(v[j] > temp)
                    v[j+1] = v[j];
                else
                    break;
            }
            
            v[j+1] = temp; //Now insert the element that was at index i, in its right location; which is at index j+1
        }
    }
    else
    {
        if (start >= end)
        {
            return;
        }
        int pivot = iQuickSort_partition(v, start, end);
        iquick_sort(v, start, pivot - 1);
        iquick_sort(v, pivot + 1, end);
    }
}

template <typename T>
SortStats iquick_sort(vector<T> &v)
{
    clock_t start = clock();
    
    iquick_sort(v, 0, v.size() - 1);
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"iQuick sort", v.size(), num_comps_iQuickSort, elapsed_cpu_time_sec};
}

vector<int> rand_vec(int n, int min, int max)
{
    vector<int> answer(n);
    srand(time(0));
    
    for(int i = 0; i < n; i++)
        answer[i] = (rand() % (max - min + 1)) + min;
    
    return answer;
}
