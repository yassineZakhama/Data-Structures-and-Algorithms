#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting {

	//************
	// QuickSort *
	//************
	int partition(vector<int>& arr, int low, int high);
	void QuickSort(vector<int>& arr, int low, int high);
	void InsertionSort(vector<int>& arr);
	void HybridQuickSort(vector<int>& arr, int left, int right);
	

	//************
	// MergeSort *
	//************
	void Merge(vector<int>& vec, vector<int>& tmp, int left, int mid, int right);
	void MergeSort(vector<int>& vec, vector<int>& tmp, int left, int right);

	//************************
	// Natuerliche Mergesort *
	//************************
	void natMerge(vector<int>& a, vector<int>& b, int left, int middle, int right);
	void natMergeSort(vector<int>& a, vector<int>& b);

	//************
	// Heapsort  *
	//************
	void maxHeapify(vector<int>& arr, int n, int i);
	void HeapSort(vector<int>& vec, int n);

	//************
	// Shellsort *
	//************
	void ShellSort_2n(vector<int>& A, int n);
	void ShellSort_3n(vector<int>& vec, int n);

	//*******************
	// Helper functions *
	//*******************
	void randomizeVector(vector<int>& array, int n);

}
#endif 
