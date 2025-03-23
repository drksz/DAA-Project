#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void rand_seq(long int *arr, unsigned int size, unsigned long int MAX_RANGE);
void increasing_seq(long int *arr, unsigned int size, int start_val);
void print_arr(long int *arr, unsigned int size);
void selection_sort(long int *arr, unsigned int size);
void insertion_sort(long int *arr, unsigned int size);
void bubble_sort(long int *arr, unsigned int size);
void merge(long int *arr, int arr1_start, int arr1_end, int arr2_start, int arr2_end, unsigned int size);
void merge_sort(long int *arr, int start, int end, unsigned int size);
void swap(long int *a, long int *b);
int hoare_partition(long int *arr, int start, int end);
void quick_sort(long int *arr, int start, int end, unsigned int size);
void heapify(long int *arr, unsigned int size, long int root);
void heap_sort(long int *arr, unsigned int size);
long int get_max(long int *arr, unsigned int size);
void counting_sort(long int *arr, unsigned int size);
void radix_sort(long int *arr, unsigned int size);
void bucket_sort(long int *arr, unsigned int size);


int main()
{
    clock_t start, end;
    double cpu_time_used;
    
    unsigned long int MAX_RANGE;    // ONLY HOLDS A MAX OF 4,294,967,295
                                    // use format specifier '%lu' for unsigned long int
    unsigned int size;
    int start_val;


    printf("Enter max range : ");
    scanf("%lu", &MAX_RANGE);
    printf("Enter size of arr : ");
    scanf("%u", &size);
    printf("Enter starting value : ");
    scanf("%d", &start_val);
    //be sure to initialize 'size' before reaching the statement(s) below
    long int arr[size];

    //rand_seq(arr, size, MAX_RANGE);
    increasing_seq(arr, size, start_val);
    print_arr(arr, size);
                   
    return 0;

}

void rand_seq(long int *arr, unsigned int size, unsigned long int MAX_RANGE) {

    for (int i = 0; i < size; i++)
        arr[i] = rand() % (MAX_RANGE + 1);

}

void increasing_seq(long int *arr, unsigned int size, int start_val) {

    int i;
    //loop-unrolling here
    //WAG NYONG GALAWIN MAANGAS TOH
    for (i = 0; i + 4 < size; i+=5) {
        arr[i] = start_val++;
        arr[i+1] = start_val++;
        arr[i+2] = start_val++;
        arr[i+3] = start_val++;
        arr[i+4] = start_val++;
    }

    for (; i < size; i++)
        arr[i] = start_val++;

}

void print_arr(long int *arr, unsigned int size) {

    for (int i = 0; i < size; i++)
        printf("%lu ", arr[i]);
    printf("\n");

}

void selection_sort(long int *arr, unsigned int size) {

    for (int i = 0; i < size - 1; i++) {

        int min = i;

        for (int j = i + 1; j < size; j++) {

            if (arr[j] < arr[min])
                min = j;

        }

        if (min != i) {
            long int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }

    }

}

void insertion_sort(long int *arr, unsigned int size) {

    int i, key;

    for (i = 1; i < size - 1; i++) {

        key = arr[i];
        int j = i - 1;

        while (j>= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

    }

}

void bubble_sort(long int *arr, unsigned int size) {

    for (int i = 0; i < size - 1; i++) {

        for (int j = 0; j < size - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                long int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

        }

    }

}

void merge(long int *arr, int arr1_start, int arr1_end, int arr2_start, int arr2_end, unsigned int size) {

    long int temp[size];
    int i = arr1_start, j = arr2_start, k = 0;

    while (i <= arr1_end && j <= arr2_end) {

        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else 
            temp[k++] = arr[j++];

    }

    while (i <= arr1_end)
        temp[k++] = arr[i++];
    while (j <= arr2_end)
        temp[k++] = arr[j++];
    
    for (i = arr1_start, j = 0; i <= arr2_end; i++, j++)
        arr[i] = temp[j];

}

void merge_sort(long int *arr, int start, int end, unsigned int size) {

    if (start < end) {
        merge_sort(arr, start, (start + end)/2, size);
        merge_sort(arr, start, (start + end)/2, size);
        merge(arr, start, (start + end)/2, (start + end)/2 + 1, end, size);
    }

}

void swap(long int *a, long int *b) {

    long int temp = *a;
    *a = *b;
    *b = temp;

}

int hoare_partition(long int *arr, int start, int end) {

    long int pivot = arr[(start+end)/2];
    int i = start - 1, j = end + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return;

        swap(&arr[i], &arr[j]);
    }

}

void quick_sort(long int *arr, int start, int end, unsigned int size) {

    if (start < end) {
        int partition_idx = hoare_partition(arr,start, end);
        quick_sort(arr, start, partition_idx, size);
        quick_sort(arr, partition_idx + 1, end, size);
    }

}

void heapify(long int *arr, unsigned int size, long int root) {

    long int max = root;
    int left_child = 2*root + 1, right_child = 2*root + 2;

    if (left_child < size && arr[left_child] > arr[max])
        max = left_child;
    if (right_child < size && arr[right_child] > arr[max])
        max = right_child;
    
    if (max != root) {
        swap(&arr[root], &arr[max]);
        heapify(arr, size, max);
    }

}

void heap_sort(long int *arr, unsigned int size) {

    for (int i = size/2 - 1; i >= 0; i--)
        heapify(arr, size, i);
    
    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

}

long int get_max(long int *arr, unsigned int size) {

    long int max = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

void counting_sort(long int *arr, unsigned int size) {

    int i;
    long int max = get_max(arr, size);

    long int count_arr[max + 1];
    for (i = 0; i <= max; i++)
        count_arr[i] = 0;
    
    for (i = 0; i < size; i++)
        count_arr[arr[i]]++;
    
    for (i = 1; i <= max; i++)
        count_arr[i] += count_arr[i - 1];
    
    long int sorted[size];

    for (i = size - 1; i >= 0; i--) {
        sorted[ count_arr[ arr[i] ] - 1 ] = arr[i];
        count_arr[ arr[i] ]--;
    } 

    for (i = 0; i < size; i++)
        arr[i] = sorted[i];

}

void radix_sort(long int *arr, unsigned int size) {

    long int max = get_max(arr, size);

    for (int exp = 1; max/exp > 0; exp *= 10)
        counting_sort(arr, size);

}

void bucket_sort(long int *arr, unsigned int size) {

    long int **buckets = (long int **)malloc(10 * sizeof(long int *));
    int bucket_count[10] = {0};

    for (int i = 0; i < 10; i++)
        buckets[i] = (long int*)malloc(size * sizeof(long int));
    
    long int max = get_max(arr, size);

    for (int i = 0; i < size; i++) {
        int bucket_idx = (arr[i] * 10) / (max + 1);
        buckets[bucket_idx][bucket_count[bucket_idx]++] = arr[i];
    }

    for (int i = 0; i < 10; i++)
        if (bucket_count[i] > 1)
            insertion_sort(buckets[i], bucket_count[i]);
    
    int idx = 0;
    for (int i = 0; i < 10; i++) {

        for (int j = 0; j < bucket_count[i]; j++)
            arr[idx++] = buckets[i][j];
        
        free(buckets[i]);

    }
    
    free(buckets);

}
