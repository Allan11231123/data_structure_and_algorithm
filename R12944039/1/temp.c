#include <stdio.h>
#include <stdlib.h>

// Function to check if an array is beautiful
int isBeautiful(int arr[], int n) {
    if(n<=2){
        return 1;
    }
    for (int i = 0; i < n - 2; i++) {
        long long int result=(arr[i + 1] - arr[i]) * (arr[i + 2] - arr[i + 1]);
        if (result >= 0) {
            return 0; // Not beautiful
        }
    }
    return 1; // Beautiful
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to right-rotate the array segment.
void rightRotate(int arr[], int i, int j){
    int temp = arr[j];
    for (int k=j; k>i; k--){
        arr[k]=arr[k-1];
    }
    arr[i]=temp;
}

// Function to left-rotate the array segment.
void leftRotate(int arr[], int i, int j){
    int temp = arr[i];
    for (int k=i;k<j;k++){
        arr[k]=arr[k+1];
    }
    arr[j]=temp;
}

// Function to generate the count of total beautiful permutations.
void countPermutations(int arr[], int start, int end, int* count) {
    if(!(isBeautiful(arr,start))) return;
    if (start == end) {
        if (isBeautiful(arr, end + 1)) {
            (*count)++;
            return;
        } else{
            return;
        }
    }
    if(arr[start]==arr[start+1]){
        start++;
    }
    countPermutations(arr, start+1, end,count);
    for(int j=start+1;j<end+1;j++){
        rightRotate(arr, start, j);
        countPermutations(arr, start+1, end,count);
        leftRotate(arr, start, j);
    }
}

// Function to generate all permutations of an array
void generatePermutations(int arr[], int start, int end) {
    if(!(isBeautiful(arr,start))) return;
    if (start == end) {
        if (isBeautiful(arr, end + 1)) {
            for (int i = 0; i <= end; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
            return;
        } else{
            return;
        }
    }
    if(arr[start]==arr[start+1]){
        start++;
    }
    generatePermutations(arr, start+1, end);
    for(int j=start+1;j<end+1;j++){
        rightRotate(arr, start, j);
        generatePermutations(arr, start+1, end);
        leftRotate(arr, start, j);
    }
}

// Comparation function to use qsort function.
int compare(const void *a, const void *b){
    return (*(int*) a-*(int*) b);
}

int main() {
    int N;
    scanf("%d", &N);

    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr,N,sizeof(int),compare);
    int count = 0;
    countPermutations(arr, 0, N-1, &count);
    printf("%d\n", count);

    generatePermutations(arr, 0, N - 1);

    return 0;
}