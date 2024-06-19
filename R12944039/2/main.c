#include <stdio.h>
#include <stdlib.h>

// 定義牌組的結構
typedef struct Card {
    int value;
    struct Card* next;
} card;

// 初始化一個空的牌組
// struct Card* createDeck() {
//     return NULL;
// }

// 新增一張牌到牌組的頂端 checked(1)
card* addCard(card *deck, int value) {
    card *newCard = (card *)malloc(sizeof(card));
    newCard->value = value;
    newCard->next = deck;
    // printf("%d\n",value);
    return newCard;
}

// 移除牌組頂端的牌 checked(2)
card* removeCard(card *deck) {
    if (deck != NULL) {
        card *temp = deck;
        deck = deck->next;
        free(temp);
    }
    return deck;
}

// 將第 i 個牌組的所有牌移動到第 j 個牌組的頂端 checked(3)
card* moveCards(card *deck_i, card *deck_j, card *tail_i, card *tail_j) {
    if (deck_i!=NULL){
        // if (deck_j == NULL){
        //     *(&tail_j) = tail_i;
        // }
        card *tail = tail_i;
        card *head = deck_i;
        // while(tail->next!=NULL){
        //     tail = tail->next;
        // }
        tail->next = deck_j;
        deck_j = head;
    }     
    return deck_j;
}

// 合併第 i 個牌組和第 j 個牌組
card* mergeDecks(card *deck_i, card *deck_j, card *tail_i, card **tail_j) {
    card *head = deck_i;
    card *temp = deck_i;
    card *temp1 = deck_i;
    card *temp2 = deck_j;
    int check = 0;
    if(temp1 == NULL){
        return deck_j;
    }else if(temp2 == NULL){
        *tail_j = tail_i;
        return deck_i;
    }
    while((temp1!=NULL) && (temp2!=NULL)){
        if(check == 0){
            temp1 = temp1->next;
            temp->next = temp2;
            temp = temp->next;
            check = 1;
        }else {
            temp2 = temp2->next;
            temp->next = temp1;
            temp = temp->next;
            check = 0;
        }
    }
    if(temp1!=NULL){
        *tail_j = tail_i;
    }
    return head;
    // moveCards(deck_i, deck_j);
}

// Function to count the number of given deck
int countDeck(card *deck){
    int count=0;
    card *temp=deck;
    
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    return count;
}
// 輸出牌組的牌數和牌面
void printDeck(card *deck) {
    card *current = deck;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // 創建 N 個空的牌組
    card *decks[N];
    for (int i = 0; i < N; i++) {
        decks[i] = NULL;
    }
    // create an array to save tails for all decks
    card *tails[N];
    for (int i=0; i<N; i++){
        tails[i]=NULL;
    } 

    for (int i = 0; i < N; i++) {
        if(decks[i]!=NULL){
            int count = countDeck(decks[i]);
            printf("%d ", count);
            printDeck(decks[i]);
        }
        // int count = countDeck(decks[i]);
        // printf("%d ", count);
        // printDeck(decks[i]);
    }
    // 執行 M 次操作
    for (int k = 0; k < M; k++) {
        int op, u, i, j;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &i, &u);
            if (decks[i-1]!=NULL){
                decks[i-1] = addCard(decks[i - 1], u);
            }else {
                decks[i-1] = addCard(decks[i-1],u);
                tails[i-1] = decks[i-1];
            }
            
        } else if (op == 2) {
            scanf("%d", &i);
            decks[i-1] = removeCard(decks[i - 1]);
        } else if (op == 3) {
            scanf("%d %d", &i, &j);
            if(decks[j-1]==NULL) tails[j-1] = tails[i-1];

            decks[j-1] = moveCards(decks[i - 1], decks[j - 1], tails[i-1], tails[j-1]);
            
            decks[i-1] = NULL;
            tails[i-1] = NULL;
        } else if (op == 4) {
            scanf("%d %d", &i, &j);
            decks[j-1] = mergeDecks(decks[i - 1], decks[j - 1], tails[i-1], &(tails[j-1]));
            decks[i-1] = NULL;
            tails[i-1] = NULL;
        }
        
    }

    // 輸出每個牌組的牌數和牌面
    for (int i = 0; i < N; i++) {
        if(decks[i]!=NULL){
            int count = countDeck(decks[i]);
            printf("%d ", count);
            printDeck(decks[i]);
        }else{
            printf("%d\n",0);
        }
        // int count = countDeck(decks[i]);
        // printf("%d ", count);
        // printDeck(decks[i]);
    }
    // printf("tails:\n");

    // for (int i=0; i<N; i++){
    //     if (tails[i]!=NULL) printf("%d ",(tails[i])->value);
    //     else printf("%d ",0);
        
    // }
    // 釋放內存
    for (int i = 0; i < N; ++i) {
        card* current = decks[i];
        while (current != NULL) {
            card* temp = current;
            current = current->next;
            free(temp);
        }
        // while (decks[i] != NULL) {
        //     removeCard(decks[i]);
        // }
    }

    return 0;
}