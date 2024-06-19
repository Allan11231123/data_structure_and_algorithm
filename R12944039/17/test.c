#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int time = 0;
typedef struct Node{
    int index;
    struct Node* next;
} node;

typedef struct Graph{
    node** adjlist;
} graph;

typedef struct Block{
    int discover;
    int finish;
    int color; // 1 stands for white, 2 for gray, and 3 for black
}block;

node* constructNode(int index){
    node* result;
    result = (node*)malloc(sizeof(node));
    result->index = index;
    result->next = NULL;
    return result;
}
graph* constructEmptyGraph(int N){
    graph* result;
    result = (graph*)malloc(sizeof(graph));
    result->adjlist = (node**)malloc(sizeof(node*)*N);
    for(int i=0;i<N;i++){
        result->adjlist[i] = NULL;
    }
    return result;
}
block* constructBlock(){
    block* result;
    result = (block*)malloc(sizeof(block));
    result->color = 0;
    result->discover = 0;
    result->finish = 0;
    return result;
}
void depthFirstSearchVisit(graph* G, block* blocks[], int index){
    time++;
    blocks[index]->discover = time;
    blocks[index]->color = 2;
    node* temp = G->adjlist[index];
    while(temp!=NULL){
        if(blocks[temp->index]->color==1) depthFirstSearchVisit(G,blocks,temp->index);
        temp = temp->next;
    }
    blocks[index]->color = 3;
    time++;
    blocks[index]->finish = time;
    return;
}
void depthFirstSearch(graph* G, block* blocks[], int N){
    for(int i=0;i<N;i++){
        blocks[i]->color = 1;
    }
    time = 0;
    for(int i=0;i<N;i++){
        if(blocks[i]->color == 1) depthFirstSearchVisit(G,blocks,i);
    }
    return;
}

void showGraph(graph* G,int N){
    printf("There are %d edges in the given graph.",N);
    node* temp;
    for(int i=0;i<N;i++){
        printf("(%d) ",i+1);
        temp = G->adjlist[i];
        while(temp!=NULL){
            printf("%d ",temp->index+1);
        }
        printf("\n");
    }
    return;
}
int main(){
    int N,num;
    scanf("%d",&N); 

    graph* original;
    original = constructEmptyGraph(N);
    block* heads[N];
    for(int i=0;i<N;i++){
        scanf("%d",&num);
        int index;
        for(int j=0;j<num;j++){
            scanf("%d",&index);
            node* node1;
            
            node1 = constructNode(index-1);
            node* temp = original->adjlist[i];
            if(original->adjlist[i]==NULL) original->adjlist[i] = node1;
            else {
                temp->next = node1;
                temp = temp->next;
            }
        }
    }
    showGraph(original,N);
    return 0;
}