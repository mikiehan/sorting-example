
//
//  main.cpp
//  ExampleCode
//
//  Created by Prof Han on 2/28/20.
//  Copyright © 2020 Prof Han. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void selectionSort(vector<int>& list) {
    for(int i = 0 ; i < list.size() - 1 ; i++) {
        //Before iteration with index i, list[0:i-1] is sorted
        //find min index from unsorted list[i:n-1]
        int min = i;
        for(int j = i + 1 ; j < list.size() ; j++) {
            if(list[min] > list[j]) {
                min = j;
            }
        }
        //send the min value to the start of unsorted list
        swap(list[i], list[min]);
        //After iteration with index i, list[0:i] is sorted
    }
}

void bubbleSort(vector<int>& list) {
    for(int i = (int) list.size() - 1 ; i > 0 ; i--) {
        //Before iteration with index i, list[i+1:n-1] is sorted
        //bubble up max of unsorted list[0:i] to list[i]
        for(int j = 0 ; j < i ; j++) {
            if(list[j] > list[j + 1]) {
                swap(list[j], list[j + 1]);
            }
        }
        //After iteration with index i, list[i:n-1] is sorted
    }
}

void insertionSort(vector<int>& list) {
    for(int i = 1 ; i < list.size() ; i++) {
        //Before iteration with index i, list[0:i-1] is sorted
        //find a hole to place list[i] from sorted list[0:i-1]
        int val = list[i];
        int hole = i;
        while (hole > 0 && val < list[hole - 1]) {
            list[hole] = list[hole - 1]; //shift right
            hole--;
        }
        list[hole] = val;
        //After iteration with index i, list[0:i] is sorted
    }
}

// Pre-condition: list[s1:e1] (left) and list[s2:e2] (right) are sorted
// Note: s1, e1, s2, e2 are inclusive and are valid indices
// Merges the left and the right into a sorted result[s1:e2].
void merge(const vector<int>& list, vector<int>& result, int s1, int e1, int s2, int e2) {
    int i1 = s1;   // index of left array
    int i2 = s2;   // index of right array
    for (int i = s1; i <= e2; i++) {
        if (i1 <= e1 &&
            (i2 > e2 || list[i1] <= list[i2] )) {
            result[i] = list[i1];   // take from left
            i1++;
        } else {
            result[i] = list[i2];    // take from right
            i2++;
        }
    }
}

//sort list[start:end] and save to result[start:end]
//start and end are inclusive and are valid
void mergeSort(vector<int>& list, vector<int>& result, int start, int end) {
    if (end - start <= 0) return; // base case (size 1 or 0 is already sorted)
    int mid = (start + end) / 2;
    
    // sort the two halves
    mergeSort(result, list, start, mid); //sort left and save to list
    mergeSort(result, list, mid + 1, end); //sort right and save to list
        
    // merge the sorted halves into a sorted whole
    merge(list, result, start, mid, mid + 1, end); //save the merged to result
}

void mergeSort(vector<int>& list){
    vector<int> copy(list);  // copy of array
    //copy is the source and list is the output
    mergeSort(copy, list, 0, (int) list.size() - 1);
}

//a version of merge (used for mergeSort2)
//merges two separate halves (left and right) into list
//pre-condition: 1) left and right is sorted
//               2) size of list is equal to size of left + size of right
void merge2(vector<int>& list, const vector<int> left, const vector<int> right){
    int i1 = 0; //left index
    int i2 = 0; //right index
    for(int i = 0 ; i < list.size(); i++){
        if(i1 < left.size() &&
           (i2 >= right.size() || left[i1] <= right[i2])) {
            list[i] = left[i1++]; //take from left
        } else {
            list[i] = right[i2++]; //take from right
        }
    }
}

//sub-optimal merge sort uses O(n log n) space
void mergeSort2(vector<int>& list){
    if(list.size() <= 1) return; //base case
    
    // copy list into two halves (left and right)
    vector<int> left(list.size()/2);
    vector<int> right(list.size() - left.size());
    std::copy(list.begin(), list.begin() + left.size() ,left.begin());
    std::copy(list.begin() + left.size(), list.end(), right.begin());
    
    // sort the two halves
    mergeSort2(left);
    mergeSort2(right);
    
    // merge the sorted havles into list
    merge2(list, left, right);
}

int main(int argc, const char * argv[]) {
    int numbers[10] = {22, 12, 30, 27, 18, 50, 36, -7, -4, 25};
    vector<int> list(10);
    std::copy(numbers, numbers + 10, list.begin());
    //selectionSort(list);
    //bubbleSort(list);
    //insertionSort(list);
    mergeSort(list);
    return 0;
}


