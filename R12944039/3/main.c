#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int arr[], int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
int getMinIndex(int arr[], int l, int r){
    int m = l;
    for(int i=l+1;i<=r;i++){
        if(arr[m] > arr[i]) m = i;
    }
    return m;
}

int selectionSort(int arr[], int N, int B){
    int m;
    int count = 0;
    int temp = B;
    for(int i=0;i<N;i++){
        m = getMinIndex(arr,i,N-1);
        if(i!=m && temp>0) {
            count++;
            swap(arr, i, m);
            temp--;
        } 
    }
    return count;
}

int main(){
    int N,B;
    scanf("%d %d",&N,&B);
    int arr[N];
    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    int count = selectionSort(arr, N, B);
    printf("The array is ");
    for(int i=0;i<N;i++){
        printf("%d ",arr[i]);
    }
    printf("after %d swaps.\n",count);
    return 0;
}