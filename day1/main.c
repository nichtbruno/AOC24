#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

typedef struct {
    LinkedNode *head;
} LinkedList;

void initLL(LinkedList *list) {
    list->head = NULL;
}

void insert(LinkedList *list, int value) {
    LinkedNode *newNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    newNode->value = value;

    if(list->head == NULL) {
        list->head = newNode;
        newNode->next = NULL;
        return;
    }
    if(list->head->value > value) {
        newNode->next = list->head;
        list->head = newNode;
        return;
    }

    LinkedNode *tempNode = list->head;
    while(tempNode->next != NULL && value > tempNode->next->value) {
        tempNode = tempNode->next;
    }
    newNode->next = tempNode->next;
    tempNode->next = newNode;
}

void output(LinkedList *list) {
    printf("List");
    LinkedNode *tempNode = list->head;
    while(tempNode != NULL) {
        printf("-> %d ", tempNode->value);
        tempNode = tempNode->next;
    }
    printf("\n");
}

int front(LinkedList *list) {
    LinkedNode *tempNode = list->head;
    int num = tempNode->value;
    list->head = tempNode->next;
    free(tempNode);
    return num;
}

int countInList(LinkedList *list, int value) {
    int count = 0;
    LinkedNode *tempNode = list->head;
    while(tempNode != NULL) {
        if(tempNode->value == value) {
            count++;
        }
        tempNode = tempNode->next;
    }

    return count;
}

int main() {
    LinkedList left, right;
    initLL(&left);
    initLL(&right);

    FILE *file = fopen("input.txt", "r");
    if(file == NULL) {
        printf("Couldn't open file!");
        return 1;
    }

    char line[256];
    while(fgets(line, sizeof(line), file) != 0) {
        // printf("%s", line);
        int x, y;
        if(sscanf(line, "%d %d", &x, &y) != 2) {
            printf("Couldn't read numbers!");
            return 1;
        }
        insert(&left, x);
        insert(&right, y);
    }

    // printf("\n");
    // output(&left);
    // output(&right);
    fclose(file);

    int sum = 0;
    while(left.head != NULL) {
        // if(left.head->value > right.head->value) {
        //     sum += front(&left) - front(&right);
        // } else {
        //     sum += front(&right) - front(&left);
        // }
        sum += countInList(&right, left.head->value) * front(&left);
    }
    printf("%d\n", sum);

    return 0;
}
