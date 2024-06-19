#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct MoveNode{
    int total;
    int count;
} moveNode;
void insert(int arr[], int m, moveNode* ptr){
    int data = arr[m];
    int i = m-1;
    while(i>=0 && arr[i]>data && ptr->total>0){
        arr[i+1] = arr[i];
        i--;
        ptr->count++;
        ptr->total--;
    }
    arr[i+1] = data;
}

void insertSort(int arr[], int N, moveNode* ptr){
    int count = 0;
    for(int i=0;i<N;i++){
        if(ptr->total>0) {
            insert(arr,i,ptr);
            // ptr->count += t;
            // ptr->total -= t;
        }
    }
}
int main(){
    int N,B;
    scanf("%d %d",&N,&B);
    moveNode* ptr;
    ptr = (moveNode*)malloc(sizeof(moveNode));
    ptr->total = B;
    ptr->count = 0;
    int arr[N];
    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    insertSort(arr,N,ptr);
    printf("The array is ");
    for(int i=0;i<N;i++){
        printf("%d ",arr[i]);
    }
    printf("after %d back-moves.\n",ptr->count);
    free(ptr);
    return 0;
}