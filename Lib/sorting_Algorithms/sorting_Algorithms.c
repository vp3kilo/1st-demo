// C sorting algorithms
// A collection of sorting algorithms written in C
#include <stdio.h>
// A utility function to swap two elements
// Hàm đổi chỗ, sử dụng XOR để không dùng biến tạm
void swap (int *x, int *y) {
	if (x != y) {
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
        if(i != size - 1)
        	printf("%d ", arr[i]);
        else
        	printf("%d", arr[i]);
}

/*
***************Bubble sort***************
Worst case performance: O(n^2) - Hiệu năng trường hợp xấu nhất
Best case performance: Ω(n) - Hiệu năng trường hợp tốt nhất
Average performance: Θ(n^2) - Hiệu năng trung bình
Worst case space complexity: O(1) - Độ phức tạp trường hợp xấu nhất
*/
// A function to implement bubble sort
/*
Ý tưởng chính, đổi chỗ cặp phần tử kế cận nếu chúng
không đúng thử tự sắp xếp, để đưa phần tử phần tử lớn nhất
về đúng vị trí cuối cùng, sau đó sẽ ko xét đến nó ở bước tiếp theo
*/
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; ++i)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; ++j) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

/*
***************Cocktail sort***************
A variation of bubble sort
Worst case performance: O(n^2)
Best case performance: Ω(n)
Average performance: Θ(n^2)
Worst case space complexity: O(1)
*/
// Sorts arrar a[0..n-1] using Cocktail sort
void cocktailSort(int arr[], int n)
{
    int swapped = 1;
    int start = 0;
    int end = n - 1;
 
    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = 0;
 
        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
 
        // if nothing moved, then array is sorted.
        if (!swapped)
            break;
 
        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = 0;
 
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
 
        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}

/*
***************Comb sort***************
Worst case performance: O(n^2)
Best case performance: Ω(n log(n))
Average performance: Θ(n^2)
Worst case space complexity: O(1)
*/
// To find gap between elements
int getNextGap(int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap*10)/13;
 
    if (gap < 1)
        return 1;
    return gap;
}
// Function to sort a[0..n-1] using Comb Sort
void combSort(int arr[], int n)
{
    // Initialize gap
    int gap = n;
 
    // Initialize swapped as true to make sure that
    // loop runs
    int swapped = 1;
 
    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == 1)
    {
        // Find next gap
        gap = getNextGap(gap);
 
        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = 0;
 
        // Compare all elements with current gap
        for (int i = 0; i < n - gap; ++i)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}

/*
***************Heap sort***************
Worst case performance: O(n log(n))
Best case performance: Ω(n log(n))
Average performance: Θ(n log(n))
Worst case space complexity: O(1)
*/
// A heap has current size and array of elements
struct MaxHeap
{
    int size;
    int* array;
};
// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
    int largest = idx;  // Initialize largest as root
    int left = (idx << 1) + 1;  // left = 2*idx + 1
    int right = (idx + 1) << 1; // right = 2*idx + 2

    // See if left child of root exists and is greater than
    // root
    if (left < maxHeap->size &&
        maxHeap->array[left] > maxHeap->array[largest])
        largest = left;

    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->size &&
        maxHeap->array[right] > maxHeap->array[largest])
        largest = right;

    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}

// A utility function to create a max heap of given capacity
struct MaxHeap* createAndBuildHeap(int *array, int size)
{
    int i;
    struct MaxHeap* maxHeap =
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// The main function to sort an array of given size
void heapSort(int* array, int size)
{
    // Build a heap from the input data.
    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

    // Repeat following steps while heap size is greater than 1.
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
    }
}

/*
***************Insertion sort***************
Worst case performance: О(n^2)
Best case performance: Ω(n)
Average performance: Θ(^2)
Worst case space complexity: O(n)
*/
/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; ++i)
   {
       key = arr[i];
       j = i-1;
 
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

/*
***************Merge sort***************
Worst case performance: O(n log(n))
Best case performance: Ω(n log(n))
Average performance: Θ(n log(n))
Worst case space complexity: O(n)
*/
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

/*
***************Quick sort***************
Worst case performance: O(n^2)
Best case performance: Ω(n)
Average performance: Θ(n log(n))
Worst case space complexity: O(n)
*//* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; ++j)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
/*
Time Complexity: O(n2) as there are two nested loops.
Auxiliary Space: O(1)
The good thing about selection sort is it never makes more than
O(n) swaps and can be useful when memory write is a costly operation.
*/

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; ++i)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; ++j)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

/*
***************Shell sort***************
Worst case performance: O(n(log(n))^2)
Best case performance: Ω(n log(n))
Average performance: Θ(n(log(n))^2)
Worst case space complexity: O(1)
*/
void shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < n; ++i)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];
 
            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
             
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {1, 26, 28, 82, 6, 44, 30, 53, 50, 99, 91, 63, 40, 74, 36, 92, 50, 69, 36, 82, 68, 99, 74, 16, 73, 15, 80, 5, 54, 79, 51, 30, 84, 50, 86, 81, 18, 3, 60, 99, 41, 25, 93, 93, 1, 36, 52, 57, 91, 63, 69, 42, 53, 43, 87, 16, 69, 33, 82, 16, 31, 23, 66, 29, 5, 38, 17, 51, 86, 39, 71, 19, 32, 36, 28, 13, 52, 98, 65, 55, 29, 32, 44, 59, 13, 77, 94, 84, 31, 94, 22, 61, 3, 83, 48, 32, 24, 35, 59, 69};
    int n = sizeof(arr)/sizeof(arr[0]);
    // bubbleSort(arr, n);
    // cocktailSort(arr, n);
    // combSort(arr, n);
    // heapSort(arr, n);
    // insertionSort(arr, n);
    // mergeSort(arr, 0, n - 1);
    // quickSort(arr, 0, n-1);
    // shellSort(arr, n);
    // selectionSort(arr, n);
    printf("\nSorted array is: \n");
    printArray(arr, n);
    return 0;
}