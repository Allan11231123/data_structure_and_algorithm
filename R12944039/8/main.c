#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int value;
    struct Node* next;
} Node;

// bool floydCycleDetection(Node* head){ //Modify this function to take two array as input.
//     Node* hare = head;
//     Node* tortoise = head;
//     while(hare != NULL && hare->next != NULL){
//         hare = hare->next->next;
//         tortoise = tortoise->next;
//         if(hare == tortoise) return true;
//     }
//     return false;
// }
bool floydCycleDetection(int data[],int point[],int head){
    int hare = head;
    int tortoise = head;
    while(hare!=-1 && point[hare]!=-1){
        printf("%d ",data[hare]);
        hare = point[point[hare]];
        tortoise = point[tortoise];
        if(hare==tortoise) {
            printf("%d\n",data[hare]);
            return true;
        }
    }
    printf("\n");
    return false;
}

int main(){
    int N;
    scanf("%d",&N);
    int data[N];
    int point[N];
    int head = 0;
    for(int i=0;i<N;i++){
        scanf("%d %d",&data[i],&point[i]);
    }
    for(int i=0;i<N;i++){
        point[i] = point[i] - 1;
    }
    bool found = floydCycleDetection(data,point,head);  

    return 0;
}