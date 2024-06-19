#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int time = 0;
int ind = 0;
int count = 0;
typedef struct queueNode{
    struct queueNode* previous;
    struct queueNode* next;
    int index;
} queuenode;

typedef struct Queue{
    queuenode* head;
    queuenode* tail;
    int count;
} queue;

queue* constructEmptyQueue(){
    queue* result;
    result = (queue*)malloc(sizeof(queue));
    result->head = NULL;
    result->tail = NULL;
    result->count = 0;
    return result;
}
queuenode* constructQueueNode(int index){
    queuenode* result;
    result = (queuenode*)malloc(sizeof(queuenode));
    result->index = index;
    result->next = NULL;
    result->previous = NULL;
    return result;
}
bool isEmpty(queue* target){
    if(target->head==NULL) return true;
    else return false;
}
void enqueue(queue* target, queuenode* node){
    if(target->head==NULL){
        target->head = node;
        target->tail = node;
        return;
    }
    target->tail->next = node;
    node->previous = target->tail;
    target->tail = node;
    return;
}
void dequeue(queue* target){

}


typedef struct Node{
    int index;
    int used; // 0 means that the node is not used yet, while 1 stands for opposite
    struct Node* next;
} node;

typedef struct Graph{
    node** adjlist;
} graph;

typedef struct Block{
    int indegree;
    int outdegree;
    int discover;
    int finish;
    int color; // 1 stands for white, 2 for gray, and 3 for black
}block;

node* constructNode(int index){
    node* result;
    result = (node*)malloc(sizeof(node));
    result->index = index;
    result->used = 0;
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
    result->indegree = 0;
    result->outdegree = 0;
    return result;
}
// edgelist* constructEmptyEdgeList(int M){
//     edgelist* result;
//     result = (edgelist*)malloc(sizeof(edgelist));
//     result->list = (edge**)malloc(sizeof(edge*)*M);
//     for(int i=0;i<M;i++){
//         result->list[i] = NULL;
//     }
//     return result;
// }
void depthFirstSearchVisit(graph* G,block* blocks[], int order[], int index){
    time++;
    // printf("visiting node %d\n",index+1);
    blocks[index]->discover = time;
    blocks[index]->color = 2; // change the color of discoverd block into gray
    node* temp = G->adjlist[index];
    while(temp!=NULL){
        if(blocks[temp->index]->color==1) depthFirstSearchVisit(G,blocks,order,temp->index);
        temp = temp->next;
    }
    blocks[index]->color = 3;
    time++;
    blocks[index]->finish = time;
    order[ind] = index;
    ind++;
    return;
}
void depthFirstSearch(graph* G, block* blocks[], int order[], int N){
    // printf("there are %d blocks.......\n",N);
    for(int i=0;i<N;i++){
        blocks[i]->color = 1;
    }
    time = 0;
    for(int i=0;i<N;i++){
        if(blocks[i]->color==1) depthFirstSearchVisit(G,blocks,order,i);
    }
}
void depthFirstSearchVisitScc(graph* G,block* blocks[],int index){// todo: need to modified for specific scc usage. 
    // time++;
    // printf("visiting node %d\n",index+1);
    // blocks[index]->discover = time;
    blocks[index]->color = 2; // change the color of discoverd block into gray
    node* temp1=G->adjlist[index];
    if(temp1==NULL){
        blocks[index]->color = 3;
        // count++;
        // time++;
        // blocks[index]->finish = time;
        return;
    }
    node* temp2 = temp1->next;
    while(temp2!=NULL){
        if(blocks[temp2->index]->finish>blocks[temp1->index]->finish) temp1 = temp2;
        temp2 = temp2->next;
    }
    if(blocks[temp1->index]->color==1) depthFirstSearchVisitScc(G,blocks,temp1->index);
    else{
        blocks[index]->color = 3;
        // count++;
        return;
    }
    // while(temp2!=NULL){
    //     if(blocks[temp->index]->color==1) depthFirstSearchVisitScc(G,blocks,temp->index);
    //     temp2 = temp2->next;
    // }
    // blocks[index]->color = 3;
    // time++;
    // blocks[index]->finish = time;
    // return;
}
void depthFirstSearchScc(graph* G,block* blocks[],int order[],int N){
    for(int i=0;i<N;i++){
        blocks[i]->color = 1;
    }
    // time = 0;
    for(int i=N-1;i>=0;i--){
        if(blocks[order[i]]->color==1) {
            count++;
            depthFirstSearchVisitScc(G,blocks,order[i]);
        }
    }
}

bool allVisited(block* blocks[],int N){
    for(int i=0;i<N;i++){
        if(blocks[i]->color!=3) return false;
    }
    return true;
}

void showGraph(graph* G,int N){
    node* temp;
    printf("there are %d directed edges in the given graph\n",N);
    for(int i=0;i<N;i++){
        printf("(%d) ",i+1);
        temp = G->adjlist[i];
        while(temp!=NULL){
            printf("%d ",temp->index+1);
            temp = temp->next;
        }
        printf("\n");
    }
    return;
}
void clearGraph(graph* G1,graph* G2,block* blocks[], int N){
    node* pointer;
    for(int i=0;i<N;i++){
        block* tmp;
        tmp = blocks[i];
        if(tmp!=NULL) free(tmp);
    }
    for(int i=0;i<N;i++){
        node* temp;
        pointer = G1->adjlist[i];
        if(pointer==NULL) continue;
        while(pointer!=NULL){
            temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
    free(G1->adjlist);
    for(int i=0;i<N;i++){
        node* temp;
        pointer = G2->adjlist[i];
        if(pointer==NULL) continue;
        while(pointer!=NULL){
            temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
    free(G2->adjlist);
    free(G1);
    free(G2);
}
int main(){
    int N,M,mode;
    scanf("%d %d %d",&N,&M,&mode);
    graph* original;
    graph* transposed;
    original = constructEmptyGraph(N);
    transposed = constructEmptyGraph(N);
    block* heads[N];
    int order[N];
    for(int i=0;i<N;i++){
        heads[i] = constructBlock();
    }
    int src,dst;
    for(int i=0;i<M;i++){
        scanf("%d %d",&src,&dst);
        node* node1;
        node* node2;
        node1 = constructNode(dst-1);
        node2 = constructNode(src-1);
        heads[src-1]->outdegree++;
        heads[dst-1]->indegree++;
        if(original->adjlist[src-1]==NULL) original->adjlist[src-1] = node1;
        else original->adjlist[src-1]->next = node1;
        if(transposed->adjlist[dst-1]==NULL) transposed->adjlist[dst-1] = node2;
        else transposed->adjlist[dst-1]->next = node2;
    }
    // showGraph(original,N);
    // showGraph(transposed,N);
    depthFirstSearch(original,heads,order,N);
    
    // printf("showing the indegree and outdegree for all node\n");
    // for(int i=0;i<N;i++){
    //     printf("(%d,%d) ",heads[i]->indegree,heads[i]->outdegree);
    // }
    // printf("\n");
    // printf("showing the order table of the graph after dfs.\n");
    // for(int i=0;i<N;i++){
    //     printf("%d ",order[i]+1);
    // }
    // printf("\n");
    depthFirstSearchScc(transposed,heads,order,N);
    printf("%d\n",count);
    // printf("showing the discover time, fiinish time, and color for all node\n");
    // for(int i=0;i<N;i++){
    //     printf("(%d,%d,%d) ",heads[i]->discover,heads[i]->finish,heads[i]->color);
    // }
    // printf("\n");

    clearGraph(original,transposed,heads,N);
    return 0;
}