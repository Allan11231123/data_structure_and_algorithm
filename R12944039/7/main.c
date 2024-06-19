#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void binarySearch(int arr[], int key, int l, int r){
    while(l<=r){
        printf("Searching %d in range [%d, %d].\n",key,l+1,r+1);
        int m = (l+r)/2;
        if(arr[m] == key){
            printf("Found at index %d.\n",m+1);
            return;
        }else if(arr[m]>key){
            r = m-1;
        }else if(arr[m]<key){
            l = m+1;
        }
    }
    printf("Searching %d in range [%d, %d].\n",key,l+1,r+1);
    printf("Not found.\n");
    return;
}

int main(){
    int N,key;
    scanf("%d %d",&N,&key);
    int arr[N];
    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    binarySearch(arr,key,0,N-1);
    return 0;
}