#include <stdio.h>
#include <stdlib.h>

// 定義鏈接列表中節點的結構
struct Node {
    int data;
    struct Node* next;
};

// 在鏈接列表的開頭插入新節點的函數
struct Node* insert(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

int main() {
    // 創建一個指標陣列來存儲多個鏈接列表
    struct Node* lists[3]; // 假設我們要存儲 3 個鏈接列表

    // 初始化每個列表為空（NULL）
    for (int i = 0; i < 3; i++) {
        lists[i] = NULL;
    }

    // 向第一個鏈接列表插入一些元素
    lists[0] = insert(lists[0], 10);
    lists[0] = insert(lists[0], 20);
    lists[0] = insert(lists[0], 30);

    // 向第二個鏈接列表插入一些元素
    lists[1] = insert(lists[1], 5);
    lists[1] = insert(lists[1], 15);

    // 向第三個鏈接列表插入一些元素
    lists[2] = insert(lists[2], 100);
    lists[2] = insert(lists[2], 200);
    lists[2] = insert(lists[2], 300);

    // 打印每個鏈接列表的元素
    for (int i = 0; i < 3; i++) {
        printf("鏈接列表 %d: ", i + 1);
        struct Node* current = lists[i];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }

    // 釋放為鏈接列表分配的內存
    for (int i = 0; i < 3; i++) {
        struct Node* current = lists[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
