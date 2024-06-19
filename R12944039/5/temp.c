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
    attackNode* tail;
    attackNode* head;
} classmateNode;


void attack(int label, classmateNode* power[], int N, int position[]){
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
    }else{
        temp->count = temp2->tail->count+1;
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
void reward(classmateNode* power[],int N){
    long long gain = N-1;
    for(int i=0;i<N;i++){
        power[i]->power += gain;
        gain--;
    }
}
void lastRankPower(classmateNode* power[],long long value, int N){
    // print rank and label 
    classmateNode* temp;
    int rank=-1;
    for(int i=0;i<N;i++){
        if(power[i]->power<value) break;
        else{
            temp = power[i];
            rank = i;
        }
    }
    if(rank!=-1) printf("%d %d\n",rank+1,temp->label);
    else printf("%d %d\n",0,0);
}

void getAttackGain(classmateNode* power[],int label,int m,int N,int position[]){
    classmateNode* temp;
    temp = power[position[label-1]];
    // for(int i=0;i<N;i++){
    //     if(power[i]->label == label){
    //         temp = power[i];
    //     }
    // }
    attackNode* record = temp->tail;
    long long total=0;
    while(record!=NULL && m>0){
        total += record->gain;
        record = record->previous;
        m--;
    }
    printf("%lld \n",total);
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
        power[i] = temp;
        position[i] = i;
    }
    long long value;
    int label;
    int m;
    for(int i=0;i<T;i++){
        int op;
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            scanf("%d",&label);
            attack(label,power,N,position);
            // printAll(power,N);
            break;
        case 2:
            reward(power,N);
            // printAll(power,N);
            break;
        case 3:
            scanf("%lld",&value);
            lastRankPower(power,value,N);
            // printAll(power,N);
            break;
        case 4:
            scanf("%d %d",&label,&m);
            getAttackGain(power,label,m,N,position);
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
    return 0;
}