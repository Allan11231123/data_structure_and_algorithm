#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define max 1000002

typedef struct heap{
    long long arr[max];
    int size;
}heap;
// int parent(int index){
//     return index/2;
// }
heap* swap(heap* head, int a, int b){
    long long temp;
    temp = head->arr[a];
    head->arr[a] = head->arr[b];
    head->arr[b] = temp;
    return head;
}

heap* heapIncreaseKey(heap* head,int index, long long key){
    head->arr[index] = key;
    while(index>0 && head->arr[(index-1)/2] < head->arr[index]){
        head = swap(head,(index-1)/2,index);
        index = (index-1)/2;
    }
    return head;
}
heap* maxHeapInsert(heap* head,long long value){
    head->size += 1;
    head->arr[head->size] = -__LONG_LONG_MAX__;
    head = heapIncreaseKey(head,head->size,value);
    return head;
}


int main(){
    int N;
    scanf("%d",&N);
    long long value;
    heap* head = (heap*)malloc(sizeof(heap));
    head->size = -1;
    for(int i=0;i<N;i++){
        scanf("%lld",&value);
        head = maxHeapInsert(head,value);
    }
    for(int i=0;i<N;i++){
        printf("%lld ",head->arr[i]);
    }
    free(head);
}