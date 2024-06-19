#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int count;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int l, int r){
    int pivot = arr[l];
    int i = l+1;
    int j = r;
    while(i<j){
        while(i<=r && arr[i]<=pivot){
            i++;
        }
        while(j>l && arr[j]>pivot){
            j--;
        }
        if(i>=j) break;
        if(count>0){
            swap(&arr[i],&arr[j]);
            count--;
        }else{
            return -1;
        }
        
    }
    if(l<j && arr[l]>arr[j] && count>0) {
        swap(&arr[l],&arr[j]);
        count--;
    }
    return j;
}
void quickSort(int arr[],int l, int r){
    if(l<r && count>0){
        int m = partition(arr,l,r);
        if(count==0) return;
        quickSort(arr,l,m-1);
        quickSort(arr,m+1,r);
    }
    return;
}
int main(){
    int N;
    scanf("%d %d",&N,&count);
    int temp = count;
    int arr[N];
    for(int i=0;i<N;i++){
        scanf("%d ",&arr[i]);
    }
    quickSort(arr,0,N-1);
    printf("The array is ");
    for(int i=0;i<N;i++){
        printf("%d ",arr[i]);
    }
    printf("after %d swaps.",temp-count);
    return 0;
}