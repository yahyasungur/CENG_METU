//#include "the1.h"
#include <climits>
#include <iostream>



using namespace std;

//You can add your own helper functions

void swapp(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// A class for Min Heap
class MinHeap{

public:
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
	// Constructor
	MinHeap(int capacity);

	// to heapify a subtree with the root at given index
	void MinHeapify(int );

	int parent(int i) { return (i-1)/2; }

	// to get index of left child of node at index i
	int left(int i) { return (2*i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2*i + 2); }

	// to extract the root which is the minimum element
	int extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap
	int getMin() { return harr[0]; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k);

	void heapify(int *arr, int n, int i, long &comparison, long &swap);
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the min heap property if it is violated
	// while (i != 0 && harr[parent(i)] > harr[i])
	// {
	// swap(&harr[i], &harr[parent(i)]);
	// i = parent(i);
	// }
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swapp(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the minimum value, and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MinHeapify(0);

	return root;
}

// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swapp(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

void MinHeap::heapify(int *arr, int n, int i, long &comparison, long &swap)
{
    int smallest = i; // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

	if(arr[r] == INT_MAX && arr[l] == INT_MAX) return;
    // If left child is smaller than root

    if (l < n && arr[l] < arr[smallest]){
		smallest = l;
	}

	if (l < n && arr[l] != INT_MAX){
		comparison++;
	}

    // If right child is smaller than smallest so far
    if (r < n  && arr[r] < arr[smallest]){
		smallest = r;
	}

	if (r < n && arr[r] != INT_MAX ){
		comparison++;
	}

    // If smallest is not root
    if (smallest != i) {
        swapp(&arr[i], &arr[smallest]);
		swap++;
        // Recursively heapify the affected sub-tree
		heapify(arr, n, smallest, comparison, swap);
    }
}

void insertionSort(int* arr, long &comparison, long & swap, int size) {
    int i = 1;
    int x;
    while (i < size){
        x = arr[i];
        int j = i - 1;
        while (j >= 0 && ++comparison && arr[j] > x){
			
            arr[j + 1] = arr[j];
            j--;
            swap++;
        }
        arr[j + 1] = x;
        i++;
    }
}


void helper_merge(int* arr, int K, int size, long& comparison, long& swap, int& calls){
    calls++;
	

    
	if (size < K){
		cout<<"h "<< swap <<" -- "<< comparison <<endl;
        for (int i = 0; i < size; i++){
			cout << arr[i] << " ";
		}
		cout << endl;
		
		insertionSort(arr, comparison, swap, size);
		
        for (int i = 0; i < size; i++){
			cout << arr[i] << " ";
		}
		cout << endl;
		cout<<"h "<< swap << " ++ " << comparison<<endl;
		return;

    }
    


	int sorted_array[size];
    int step = size / K;
    
    for (int i = 0; i < K; i++){
        int index = i * step;
        helper_merge(arr + index, K, step, comparison, swap, calls);
    }
    
    MinHeap h(K);
    int index_at_each_partition[K];
    for (int i = 0; i < K; i++){
        index_at_each_partition[i] = 0;
    }
    
    for (int i = 0; i < K; i++){
        int index = i * step;
        h.insertKey(arr[index]);
	}

	int start_ind = (K / 2) -1;

	for (int i = start_ind; i >= 0; i--){
		int ds = swap;
		h.heapify(h.harr, K, i, comparison, swap);
		ds-=swap;
		cout <<" heap2fy adde:"<< -ds << endl;
	}

    for (int i = 0; i < size; i++){
        sorted_array[i] = h.harr[0];

        for (int j = 0; j < K; j++){
            int index = j * step;
			if (index_at_each_partition[j] >= step){
				continue;
			}
            if (h.harr[0] == arr[index + index_at_each_partition[j]]){
                index_at_each_partition[j]++;
				if (index_at_each_partition[j] >= step){
					h.harr[0] = INT_MAX;
				}
				else{
					h.harr[0] = arr[index + index_at_each_partition[j]];
				}
				break;
            }
        }
        
        h.heapify(h.harr, K, 0, comparison, swap);
		
    }

    for (int i = 0; i < size; i++){
        arr[i] = sorted_array[i];
    }
	return;
}

int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap){
    int number_of_calls = 0;
    helper_merge(arr, K, size, comparison, swap, number_of_calls);
	
	//Your code here
	return number_of_calls;
}



int main()
{
	// int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	int arr[] =  {79, 63, 21, 78, 52, 63, 45, 10, 0, 1, 22, 100, 89, 66, 2, 63, 89, 98, 99, 785};
	// {20,22,24,0,1,2,7,8,9,3,5,40,16,18,19}
    int size = 20;
    int k = 5;
	long comparison = 0;
	long swap = 0;
	int calls = kWayMergeSortWithHeap(arr, k, size, comparison, swap);
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "comparison: " << comparison << endl;
	cout << "swap: " << swap << endl;
	cout << "calls: " << calls << endl;

	return 0;
}