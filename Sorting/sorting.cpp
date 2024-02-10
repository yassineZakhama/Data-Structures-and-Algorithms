#include "sorting.h"



namespace sorting {

	//************
	// QuickSort *
	//************   
	int partition(vector<int>& arr, int low, int high)
	{		
		int middle = (low + high) / 2;
		if ((arr[low] <= arr[middle] && arr[low] >= arr[high]) ||
			(arr[low] >= arr[middle] && arr[low] <= arr[high])) 
			swap(arr[low], arr[high]);

		else if ((arr[middle] <= arr[low] && arr[middle] >= arr[high]) ||
			(arr[middle] >= arr[low] && arr[middle] <= arr[high])) 
			swap(arr[middle], arr[high]);
	
		int pivot = arr[high]; 

		int i = (low - 1);

		for (int j = low; j <= high - 1; j++) {
			if (arr[j] < pivot) {
				i++;
				swap(arr[i], arr[j]);
			}
		}

		swap(arr[i + 1], arr[high]);

		return (i + 1);
	}
	void QuickSort(vector<int>& arr, int low, int high)
	{
		if (low < high)
		{
			int pivot_index = partition(arr,low, high);
 			QuickSort(arr, low, pivot_index-1);
			QuickSort(arr, pivot_index + 1, high);
		}
	}

	void InsertionSort(vector<int>& arr)
	{
		for (size_t i = 1; i < arr.size(); ++i)
		{
			int tmp = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > tmp)
			{
				arr[j + 1] = arr[j];
				--j;
			}
			arr[j + 1] = tmp;
		}
	}

	void HybridQuickSort(vector<int>& arr, int left, int right)
	{
		size_t size = arr.size();

		if (size > 1000)
			QuickSort(arr, 0, size - 1);
		else
			InsertionSort(arr);
	}
	
	//************
	// MergeSort *
	//************
	void Merge(vector<int>& vec, vector<int>& tmp, int left, int mid, int right)
	{
		int i = left;        // Index for the left subarray
		int j = mid + 1;     // Index for the right subarray
		int k = left;        // Index for the merged subarray

		// Merge the two subarrays into the temporary array
		while (i <= mid && j <= right) {
			if (vec[i] <= vec[j]) {
				tmp[k] = vec[i];
				++i;
			}
			else {
				tmp[k] = vec[j];
				++j;
			}
			++k;
		}

		// Copy the remaining elements from the left subarray, if any
		while (i <= mid) {
			tmp[k] = vec[i];
			++i;
			++k;
		}

		// Copy the remaining elements from the right subarray, if any
		while (j <= right) {
			tmp[k] = vec[j];
			++j;
			++k;
		}

		// Copy the merged elements back to the original array
		for (int x = left; x <= right; ++x) {
			vec[x] = tmp[x];
		}
	}

	void MergeSort(vector<int>& vec, vector<int>& tmp, int left, int right)
	{
		if (left < right) {
			int mid = left + (right - left) / 2;

			MergeSort(vec, tmp, left, mid);
			MergeSort(vec, tmp, mid + 1, right);

			Merge(vec, tmp, left, mid, right);
		}
	}

	
	//************
	// Heapsort  *
	//************
	void maxHeapify(vector<int>& arr, int n, int i)
	{
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		// left child > root
		if (left < n && arr[left] > arr[i])
			largest = left;

		// right child > largest so far
		if (right < n && arr[right] > arr[largest])
			largest = right;

		// largest != root
		if (largest != i) {
			swap(arr[i], arr[largest]);

			// heapify affected sub-tree
			maxHeapify(arr, n, largest);
		}
	}


	void HeapSort(vector<int>& vec, int n)
	{
		n = vec.size();

		// Build heap
		for (int i = n / 2 - 1; i >= 0; i--)
			maxHeapify(vec, n, i);

		// sort (delete all nodes)
		while (n != 0)
		{
			swap(vec[n - 1], vec[0]);
			maxHeapify(vec, --n, 0);
		}
	}
	
	//************
	// Shellsort *
	//************
	void ShellSort_2n(vector<int>& A, int n)
	{
		auto N = A.size();
		// Schleife über die Abstandsfolge
		for (auto gap = N / 2; gap > 0; gap /= 2) {
			// Insertion Sort von Elementen mit Abstand gap
			for (auto i = gap; i < N; i++) {
				int tmp = A[i];
				auto j = i;
				for (; j >= gap && tmp < A[j - gap]; j -= gap) {
					A[j] = A[j - gap];
				}
				A[j] = tmp;
			}
			// Elemente sind im Abstand gap sortiert
		}
	}


	void ShellSort_3n(vector<int>& vec, int n)
	{
		size_t size = vec.size();

		for (size_t gap = 1; gap < size; gap = gap * 2 + 1)
		{
			for (size_t i = gap; i < size; ++i)
			{
				int tmp = vec[i];

				size_t j = i;

				for (; j >= gap && tmp < vec[j - gap]; j -= gap)
					vec[j] = vec[j - gap];
				vec[j] = tmp;
			}
		}
	}


	void randomizeVector(vector<int>& array, int n) {
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}



	void natMerge(vector<int>& a, vector<int>& b, int left, int middle, int right)
	{
		int l = left;
		int r = middle + 1;
		for (int i = left; i <= right; i++) {
			if (r > right || (l <= middle && a[l] <= a[r])) {
				b[i] = a[l++];
			}
			else if (l > middle || (r <= right && a[r] <= a[l])) {
				b[i] = a[r++];
			}
		}

		for (int i = left; i <= right; i++) {
			a[i] = b[i];
		}
	}

	void natMergeSort(vector<int>& a, vector<int>& b)
	{
		int n = a.size();
		int left = 0;
		int right = n - 1;
		bool sorted = false;
		int l = 0;
		int r = right;
		do {
			sorted = true;
			left = 0;
			while (left < right) {
				l = left;
				while (l < right && a[l] <= a[l + 1])
					l++;

				r = l + 1;
				while (r == right - 1 || r < right && a[r] <= a[r + 1])
					r++;

				if (r <= right) {
					natMerge(a, b, left, l, r);
					sorted = false;
				}
				left = r + 1;
			}
		} while (!sorted);
	}

}





