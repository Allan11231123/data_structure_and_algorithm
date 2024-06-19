#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct attackNode{
    long long gain;
    int count;
    struct attackNode* previous;
    struct attackNode* next;
} attackNode;

typedef struct classmateNode{
    long long power;
    int label;
    attackNode* start;
    attackNode* tail;
    attackNode* head;
} classmateNode;


void attack(int label, classmateNode* power[], int N, 
int position[],int* reward,long long accumulate[],int M){
    long long gain=N-1;

    for(int i=0;i<N;i++){
        power[i]->power += gain*(*(reward));
        gain--;
    }

    *(reward) = 0;
    int rank;
    if(position[label-1]==0) return;
    else rank = position[label-1];
    // for(int i=0;i<N;i++){
    //     if(power[i]->label == label && i==0) return;
    //     else if(power[i]->label==label){
    //         rank = i;
    //     }
    // }
    classmateNode* temp1;
    classmateNode* temp2;
    temp1 = power[rank-1];
    temp2 = power[rank];
    long long gap;
    gap = (temp1->power) - (temp2->power);

    attackNode* temp;
    temp = (attackNode*)malloc(sizeof(attackNode));
    temp->gain = gap;
    temp->next = NULL;
    temp->previous = NULL;
    if(temp2->tail==NULL && temp2->head==NULL){
        temp->count = 1;
        temp->previous = temp2->tail;
        temp2->head = temp;
        temp2->tail = temp;
        temp2->start = temp;
        accumulate[temp2->label-1] += gap;
    }else{
        temp->count = temp2->tail->count+1;
        if(temp->count<= M){
            accumulate[temp2->label-1] += gap;
            // temp2->start = temp2->start->next;
        }else{
            accumulate[temp2->label-1] += gap;
            accumulate[temp2->label-1] -= temp2->start->gain;
            temp2->start = temp2->start->next;
        }
        temp->previous = temp2->tail;
        temp2->tail->next = temp;
        temp2->tail = temp;
    }
    temp2->power = temp1->power;
    power[rank-1] = temp2;
    power[rank] = temp1;
    position[temp2->label-1] = rank-1;
    position[temp1->label-1] = rank;
}
// void reward(classmateNode* power[],int N){
//     // to enhance processing time
//     // add reward when a attack happen
//     long long gain = N-1;
//     for(int i=0;i<N;i++){
//         power[i]->power += gain;
//         gain--;
//     }
// }
void lastRankPower(classmateNode* power[],long long value, 
int N,int* reward){
    // print rank and label 
    // TLE solve: keep a value list and use binary search algorithm
    long long gain=N-1;

    for(int i=0;i<N;i++){
        power[i]->power += gain*(*(reward));
        gain--;
    }

    *(reward) = 0;
    // classmateNode* temp;
    int rank=-1;
    int l = 0;
    int h = N-1;
    while(l<=h){
        int mid = (l+h)/2;
        if(power[mid]->power==value){
            rank = mid;
            break;
        }else if(power[mid]->power<value){
            h = mid-1;
        }else{
            l = mid+1;
        }
    }
    if(rank == -1) rank = h;
    while(power[rank+1]->power>=value){
        rank++;
        if(rank==N-1) break;
    }
    // for(int i=0;i<N;i++){
    //     if(power[i]->power<value) break;
    //     else{
    //         temp = power[i];
    //         rank = i;
    //     }
    // }

    if(rank!=-1) printf("%d %d\n",rank+1,power[rank]->label);
    else printf("%d %d\n",0,0);
}

void getAttackGain(long long accumulate[],int label){
    // TLE solve: keep a gain list to directly access
    // classmateNode* temp;
    // temp = power[position[label-1]];
    // // for(int i=0;i<N;i++){
    // //     if(power[i]->label == label){
    // //         temp = power[i];
    // //     }
    // // }
    // attackNode* record = temp->tail;
    // long long total=0;
    // while(record!=NULL && m>0){
    //     total += record->gain;
    //     record = record->previous;
    //     m--;
    // }
    // printf("%lld \n",total);
    printf("%lld \n",accumulate[label-1]);
}
void printAll(classmateNode* power[],int N){
    for(int i=0;i<N;i++){
        printf("%d %lld ",power[i]->label,power[i]->power);
        attackNode* temp = power[i]->tail;
        while(temp!=NULL){
            printf("|%d %lld|",temp->count,temp->gain);
            temp = temp->previous;
        }
        printf("\n");
    }
}
void printAttack(attackNode* tail,attackNode* head){
    if(tail==NULL){
        printf("%d\n",0);
        return;
    }else{
        int count = tail->count;
        printf("%d ",count);
    }
    attackNode* current = head;
    while(current!=NULL){
        attackNode* temp = current;
        printf("%lld ",current->gain);
        current = current->next;
        free(temp);
    }
    printf("\n");
}
int main(){
    int M,N,T;
    scanf("%d %d %d",&N,&T,&M);
    classmateNode* power[N];
    int position[N];
    for(int i=0;i<N;i++){
        long long value;
        scanf("%lld",&value);
        classmateNode* temp;
        temp = (classmateNode*)malloc(sizeof(classmateNode));
        temp->power = value;
        temp->label = i+1;
        temp->tail = NULL;
        temp->head = NULL;
        temp->start = NULL;
        power[i] = temp;
        position[i] = i;
    }
    long long accumulate[N];
    for(int i=0;i<N;i++){
        accumulate[i] = 0;
    }
    long long value;
    int label;
    int m;
    int* reward;
    reward = (int *)malloc(sizeof(int));
    *(reward) = 0;
    for(int i=0;i<T;i++){
        int op;
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            scanf("%d",&label);
            attack(label,power,N,position,reward,accumulate,M);
            // printAll(power,N);
            break;
        case 2:
            *(reward)+=1;
            // reward(power,N);
            // printAll(power,N);
            break;
        case 3:
            scanf("%lld",&value);
            lastRankPower(power,value,N,reward);
            // printAll(power,N);
            break;
        case 4:
            scanf("%d %d",&label,&m);
            getAttackGain(accumulate,label);
            // printAll(power,N);
            break;
        default:
            break;
        }
    }
    printf("\n");
    for(int i=0;i<N;i++){
        classmateNode* temp_t = power[position[i]];
        printAttack(power[position[i]]->tail,power[position[i]]->head);
        free(temp_t);
    }
    free(reward);
    return 0;
}