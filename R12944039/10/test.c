// Implement the queue operation for specific problem.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max 1000000
#define max_l 20
#define _max(i,j) (((i)>(j)) ? (i) : (j))

typedef struct heapNode{
    struct heapNode* child[max_l];
    int jobID;
    int priority;
    int degree;
} heapnode;

typedef struct binomialHeap{
    int degree;
    heapnode* arr[max_l];
}binomialheap;

heapnode* constructHeapNode(int job,int priority){
    heapnode* head;
    head = (heapnode*)malloc(sizeof(heapnode));
    for(int i=0;i<max_l;i++){
        head->child[i] = NULL;
    }
    head->degree = 0;
    head->jobID = job;
    head->priority = priority;
    return head;
}
binomialheap* constructEmptyHeap(){
    binomialheap* head;
    head = (binomialheap*)malloc(sizeof(binomialheap));
    for(int i=0;i<max_l;i++){
        head->arr[i] = NULL;
    }
    head->degree = -1;
    return head;
}
binomialheap* constructHeap(int job, int priority){
    binomialheap* head;
    head = (binomialheap*)malloc(sizeof(binomialheap));
    for(int i=0;i<max_l;i++){
        head->arr[i] = NULL;
    }
    heapnode* node = constructHeapNode(job,priority);
    head->arr[0] = node;
    head->degree = 0;
    return head;
}

heapnode* mergeHeapNode(heapnode* h1, heapnode* h2){
    if (h1->priority > h2->priority){
        h1->child[h1->degree] = h2;
        h1->degree += 1;
        return h1;
    }else{
        h2->child[h2->degree] = h1;
        h2->degree += 1;
        return h2;
    }
}

void printHeapNode(heapnode* head){
    printf("%d,%d ",head->jobID,head->priority);
    if(head->degree==0) return;
    for(int i=0;i<head->degree;i++){
        printHeapNode(head->child[i]);
    }
    return;
}
void printBinomialHeap(binomialheap* head){
    if(head==NULL) {
        printf("\n"); 
        return;
    }
    for(int i=0;i<=head->degree;i++){
        if(head->arr[i]!=NULL) {
            printf("(%d)",i);
            printHeapNode(head->arr[i]);
        }
    }
    printf("\n");
    return;
}

binomialheap* binomialHeapUnion(binomialheap* h1, binomialheap* h2){ 
    binomialheap* result = constructEmptyHeap(); 
    // printf("%d %d\n",h1->degree,h2->degree);
    if(h1==NULL) return h2;
    else if(h2==NULL) return h1;
    int target = _max(h1->degree,h2->degree);
    int index = 0;
    while(index<=target){
        if(h1->arr[index]==NULL && h2->arr[index]==NULL) {
            index++;
            continue;
        }else if(h1->arr[index]!=NULL && h2->arr[index]!=NULL){
            heapnode* temp = mergeHeapNode(h1->arr[index],h2->arr[index]);
            index++;
            result->arr[index] = temp;
            continue;
        }else if(h1->arr[index]==NULL){
            if(result->arr[index]==NULL){
                result->arr[index] = h2->arr[index];
                index++;
                continue;
            }else{
                heapnode* temp = mergeHeapNode(h2->arr[index],result->arr[index]);
                result->arr[index] = NULL;
                index++;
                result->arr[index] = temp;
                continue;
            }
        }else{
            if(result->arr[index]==NULL){
                result->arr[index] = h1->arr[index];
                index++;
                continue;
            }else{
                heapnode* temp = mergeHeapNode(h1->arr[index],result->arr[index]);
                result->arr[index] = NULL;
                index++;
                result->arr[index] = temp;
                continue;
            }
        }
    }
    while(result->arr[index]==NULL){
        index--;
    }
    result->degree = index;
    free(h1);
    free(h2);
    return result;
}
binomialheap* updateBinomial(binomialheap* head,int index){
    binomialheap* result = constructEmptyHeap();
    heapnode* t = head->arr[index];
    for(int i=0;i<t->degree;i++){
        result->arr[i] = t->child[i];
        result->degree = i;
    }

    int deg = max_l-1;
    while(result->arr[deg]==NULL){
        deg--;
    }
    result->degree = deg;

    head->arr[index] = NULL;
    deg = head->degree;
    while(head->arr[deg]==NULL){
        deg--;
    }
    head->degree = deg;
    

    // printf("simulate start\n");
    // printBinomialHeap(result);
    // printBinomialHeap(head);
    result = binomialHeapUnion(head,result);
    // printBinomialHeap(result);
    // printf("simulate over\n");
    free(t);
    return result;
}
int extractJob(binomialheap* biheap[],int number[],int printer){
    int priority,jobid,index;

    binomialheap* head = biheap[printer-1];
    if(head==NULL) return -1;
    else if(head->degree==0){
        jobid = head->arr[0]->jobID;
        free(head->arr[0]);
        free(head);
        biheap[printer-1] = NULL;
        number[printer-1] = 0;
        return jobid;
    }
    // printf("the degree is %d for extracted biheap\n",head->degree);
    priority = -1;
    for(int i=0;i<max_l;i++){
        if(head->arr[i]!=NULL && head->arr[i]->priority > priority){
            priority = head->arr[i]->priority;
            jobid = head->arr[i]->jobID;
            index = i;
        }
    }
    if(priority==-1) return -1;
    else{
        biheap[printer-1] = updateBinomial(head,index);
        number[printer-1] -= 1;
        return jobid;
    }
}

binomialheap* insertBinomial(binomialheap* head,int job, int priority){
    binomialheap* temp = constructHeap(job,priority);
    if(head==NULL) return temp;
    else{
        binomialheap* result = binomialHeapUnion(head,temp);
        return result;
    }
    // binomialheap* result = binomialHeapUnion(head,temp);
    // while(head->arr[index]!=NULL){
    //     temp = mergeHeap(head->arr[index],temp);
    //     index++;
    // }
    // head->arr[index] = temp;
    // int target;
    // for(int i=0;i<max_l;i++){
    //     if(head->arr[i]!=NULL) target = i;
    // }
    // head->degree = target;
    // return head;
    // return result;
}
// void printHeapNode(heapnode* head){
//     printf("%d,%d ",head->jobID,head->priority);
//     if(head->degree==0) return;
//     for(int i=0;i<head->degree;i++){
//         printHeapNode(head->child[i]);
//     }
//     return;
// }
// void printBinomialHeap(binomialheap* head){
//     if(head==NULL) {
//         printf("\n"); 
//         return;
//     }
//     for(int i=0;i<=head->degree;i++){
//         if(head->arr[i]!=NULL) {
//             printf("(%d)",i);
//             printHeapNode(head->arr[i]);
//         }
//     }
//     printf("\n");
//     return;
// }
void printBinomial(binomialheap* biheap[],int N){
    for (int i=0;i<N;i++){
        printf("printer%d -----",i+1);
        printBinomialHeap(biheap[i]);
    }
    printf("\n");
    return;
}
void freeHeapNode(heapnode* head){
    if(head==NULL) return;
    if (head->degree == 0){
        free(head);
        return;
    }
    for(int i=0;i<head->degree;i++){
        freeHeapNode(head->child[i]);
    }
    free(head);
    return;
}
void freeBinomialHeap(binomialheap* head){
    for(int i=0;i<=head->degree;i++){
        if(head->arr[i]!=NULL) freeHeapNode(head->arr[i]); 
    }
    free(head);
    return;
}

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    binomialheap* biheap[N];
    int number[N];
    for(int i=0;i<N;i++){
        biheap[i] = NULL;
        number[i] = 0;
    }
    int op;
    int job,priority,printer1,printer2;
    for(int i=0;i<M;i++){
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            scanf("%d %d %d",&job,&priority,&printer1);
            biheap[printer1-1] = insertBinomial(biheap[printer1-1],job,priority);
            number[printer1-1]++;
            // printf("the degree of a binomial heap is {%d} after insertion.\n",biheap[printer1-1]->degree);
            printf("%d jobs waiting on printer %d\n",number[printer1-1],printer1);
            // printBinomial(biheap,N);
            break;
        
        case 2:
            scanf("%d",&printer1);
            job = extractJob(biheap,number,printer1);
            if(job<0) printf("no documents in queue\n");
            else printf("%d printed\n",job);
            // printBinomial(biheap,N);
            break;
        
        case 3:
            scanf("%d %d",&printer1,&printer2);
            biheap[printer2-1] = binomialHeapUnion(biheap[printer1-1],biheap[printer2-1]);
            number[printer2-1] = number[printer1-1] + number[printer2-1];
            number[printer1-1] = 0;
            printf("%d jobs waiting on printer %d after moving\n",number[printer2-1],printer2);
            biheap[printer1-1] = NULL;
            break;

        default:
            break;
        }
    }
    for(int i=0;i<N;i++){
        if(biheap[i]!=NULL) freeBinomialHeap(biheap[i]);
    }
    return 0;
}