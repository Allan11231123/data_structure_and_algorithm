#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define max_l 64


// 定義跳躍列表節點
typedef struct SkipListNode {
    long long value;
    struct SkipListNode* next;
    struct SkipListNode* down;
} SkipListNode;
// Define the struct of skip list
typedef struct Skiplist {
    SkipListNode* list[max_l];
    int fastLayer; 
} Skiplist;
typedef struct CollectedNode{
    long long value;
    struct CollectedNode* next;
} CollectedNode;

// typedef struct collected{
//     long long list[max_l];
// } collected;

// 創建一個新的跳躍列表節點
SkipListNode* createNode(long long value) {
    SkipListNode* newNode = (SkipListNode*)malloc(sizeof(SkipListNode));
    newNode->value = value;
    newNode->next = NULL;
    newNode->down = NULL;
    return newNode;
}
// implement coinflip function
bool coinFlip(long long value){
    long long temp = value&1;
    if(temp==1) return true;
    else return false;
}

// implement the slowGet function
SkipListNode* slowGet(Skiplist* list, long long value){
    SkipListNode* current = list->list[0];
    long long *arr;
    int size = max_l;
    int index = 0;
    while ((current->next!=NULL) && (value <= (current->next)->value)){
        if(current->value!=__LONG_LONG_MAX__) printf("%lld ",current->value);
        current = current->next;
    }
    if (value == current->value) {
        printf("%lld \n",current->value);
        return current;
    }
    else if(current->value!=__LONG_LONG_MAX__){
        printf("%lld \n",current->value);
        return NULL;
    }else{
        printf("%d \n",-1);
        return NULL;
    }
}
// implement suplement function of fastGet
void previousGet(Skiplist* list, SkipListNode** previous, long long value){
    int index = list->fastLayer;
    int i = 0;
    SkipListNode* current = list->list[index];
    while(current->down!=NULL){
        while(current->next != NULL && value < current->next->value){
            current = current->next;
        }
        previous[index] = current;
        index--;
        current = current->down;
    }
    while(current->next != NULL && value < current->next->value){
        current = current->next;
    }
    previous[index] = current;
}
// implement the fastGet function
SkipListNode* fastGet(Skiplist* list, SkipListNode** previous, CollectedNode* collected, long long value) {
    int index = list->fastLayer;
    CollectedNode* temp = collected;
    previousGet(list,previous,value);
    SkipListNode* current = list->list[index];
    while(current->down!=NULL){
        while(current->next != NULL && value <= current->next->value){
            if(current->value!=__LONG_LONG_MAX__){
                CollectedNode* tempNode;
                tempNode = (CollectedNode*)malloc(sizeof(CollectedNode));
                tempNode->next = NULL;
                temp->value = current->value;
                temp->next = tempNode;
                temp = tempNode;
            }
            current = current->next;
        }
        if(current->value!=__LONG_LONG_MAX__){
            CollectedNode* tempNode;
            tempNode = (CollectedNode*)malloc(sizeof(CollectedNode));
            tempNode->next = NULL;
            temp->value = current->value;
            temp->next = tempNode;
            temp = tempNode;
        }
        current = current->down;
    }
    while(current->next != NULL && value <= current->next->value){
        if(current->value!=__LONG_LONG_MAX__){
            CollectedNode* tempNode;
            tempNode = (CollectedNode*)malloc(sizeof(CollectedNode));
            tempNode->next = NULL;
            temp->value = current->value;
            temp->next = tempNode;
            temp = tempNode;
        }
        current = current->next;
    }
    if(current->value!=__LONG_LONG_MAX__){
        CollectedNode* tempNode;
        tempNode = (CollectedNode*)malloc(sizeof(CollectedNode));
        tempNode->next = NULL;
        temp->value = current->value;
        temp->next = tempNode;
        temp = tempNode;
    }
    temp->value = -1;
    if (current->value == value) return current;
    else return NULL;
    // while (current != NULL) {
    //     if (current->value == value) {
    //         visitedLayer[index] = 1;
    //         return current;
    //     } else if (current->next == NULL || current->next->value < value) {
    //         previous[index] = current;
    //         visitedLayer[index] = 1;
    //         index--;
    //         current = current->down;
    //     } else {
    //         current = current->next;
    //     }
    // }
    // return NULL;
}
void updateFirstLayer(Skiplist* list){
    int index = 0;
    SkipListNode* current = list->list[index];
    while (current->next != NULL){
        index++;
        current = list->list[index];
    }
    index--;
    if (index > list->fastLayer) list->fastLayer = index;
}
// implement insert function
void insertValue(Skiplist* list, long long value) {
    SkipListNode* node = createNode(value);
    SkipListNode** previous;
    previous = (SkipListNode**)malloc(sizeof(SkipListNode*)*max_l);
    for (int i=0;i<max_l;i++){
        previous[i] = NULL;
    }
    SkipListNode* current;
    CollectedNode* collected;
    collected = (CollectedNode *)malloc(sizeof(CollectedNode));
    collected->next = NULL;
    current = fastGet(list,previous,collected,value);
    int index = 0;
    if(previous[index]->value == __LONG_LONG_MAX__){
        node->next = list->list[index]->next;
        list->list[index]->next = node;
    }else{
        current = previous[index];
        node->next = current->next;
        current->next = node;
        node->down = NULL;
    }
    SkipListNode* temp = node;
    long long t = value;
    while((t&1)){
        index++;
        SkipListNode* tempNode = createNode(value);
        if(previous[index]==NULL){
            list->list[index]->next = tempNode;
            tempNode->down = temp;
            temp = tempNode;
            t = t >> 1;
            continue;
        }
        if(previous[index]->value ==__LONG_LONG_MAX__) {
            tempNode->next = list->list[index]->next;
            list->list[index]->next = tempNode;
            tempNode->down = temp;    
        }else if(previous[index]!=NULL){
            current = previous[index];
            tempNode->next = current->next;
            current->next = tempNode;
            tempNode->down = temp;
        }
        temp = tempNode;
        t = t >> 1;
    }
    updateFirstLayer(list);
    free(previous);
    CollectedNode* tem = collected;
    while(tem!=NULL){
        CollectedNode* temp_t = tem;
        tem = tem->next;
        free(temp_t);
    }
}

// implement remove function
void removeValue(Skiplist* list, long long value){
    SkipListNode** previous;
    previous = (SkipListNode**)malloc(sizeof(SkipListNode*)*max_l);
    for(int i=0;i<max_l;i++){
        previous[i] = NULL;
    }
    SkipListNode* current;
    CollectedNode* collected;
    collected = (CollectedNode*)malloc(sizeof(CollectedNode));
    collected->next = NULL;
    current = fastGet(list,previous,collected,value);
    if (current==NULL) {
        free(previous);
        CollectedNode* temp = collected;
        while(temp!=NULL){
            CollectedNode* temp_t = temp;
            temp = temp->next;
            free(temp_t);
        }
        return;
    }
    
    int index=0;
    while(previous[index]!=NULL){
        // printf("%lld \n",previous[index]->value);
        if(previous[index]->next!=NULL && previous[index]->next->value==value){
            current = previous[index]->next;
            previous[index]->next = current->next;
            free(current);
        }
        index++;
    }
    updateFirstLayer(list);
    CollectedNode* temp = collected;
    while(temp!=NULL){
        CollectedNode* temp_t = temp;
        temp = temp->next;
        free(temp_t);
    }
    free(previous);
}

void printList(Skiplist* list){
    for(int i=0;i<max_l;i++){
        SkipListNode* temp = list->list[i];
        while(temp!=NULL){
            printf("%lld ",temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("....................\n");
}

// 主函數
int main() {
    Skiplist* skiplist = (Skiplist*)malloc(sizeof(Skiplist));
    skiplist->fastLayer = 0;
    for(int i=0;i<max_l;i++){
        SkipListNode* node = createNode(__LONG_LONG_MAX__);
        skiplist->list[i] = node;
        if(i>0) node->down = skiplist->list[i-1];
    }
    // SkipListNode* previous[max_l]=NULL;
    int m;
    scanf("%d",&m);
    SkipListNode* output;
    for (int i=0;i<m;i++){
        int op;
        long long value;
        scanf("%d %lld",&op,&value);
        SkipListNode** previous;
        switch (op){
        case 1:
            // printf("case 1 operation(slowGet) is performed");
            output = slowGet(skiplist,value);
            break;
        case 2:
            // printf("case 2 operation(fastGet) is performed");
            previous = (SkipListNode**)malloc(sizeof(SkipListNode*)*max_l);
            for (int i=0;i<max_l;i++){
                previous[i] = NULL;
            }
            CollectedNode *collected;
            collected = (CollectedNode*)malloc(sizeof(CollectedNode));
            collected->next = NULL;
            output = fastGet(skiplist,previous,collected,value);
            int i=0;
            
            CollectedNode* temp = collected;
            if(temp->value == -1){
                printf("%lld ",temp->value);
            }
            while(temp->next!=NULL){
                printf("%lld ",temp->value);
                temp = temp->next;
            }
            printf("\n");
            free(previous);
            temp = collected;
            while(temp!=NULL){
                CollectedNode* temp_t = temp;
                temp = temp->next;
                free(temp_t);
            }
            break;
        case 3:
            // printf("case 3 operation(insert) is performed");
            insertValue(skiplist,value);
            // printList(skiplist);
            // printf("the first layer is %d, value is %lld\n",skiplist->fastLayer,skiplist->list[skiplist->fastLayer]->next->value);
            break;
        case 4:
            // printf("case 4 operation(remove) is performed");
            removeValue(skiplist,value);
            // printList(skiplist);
            break;

        default:
            break;
        }
    }
    for(int i=0;i<max_l;i++){
        SkipListNode* temp = skiplist->list[i];
        while(temp!=NULL){
            SkipListNode* temp_t = temp;
            temp = temp->next;
            free(temp_t);
        }
    }
    free(skiplist);
    return 0;
}
