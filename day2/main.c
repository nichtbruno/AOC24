#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

typedef struct {
    LinkedNode *head;
    LinkedNode *tail;
} LinkedList;

void initLL(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

void insert(LinkedList *list, int value) {
    LinkedNode *newNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    newNode->value = value;
    newNode->next = NULL;

    if(list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    list->tail->next = newNode;
    list->tail = newNode;
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

void emptyList(LinkedList *list) {
    while(list->head != NULL) {
        LinkedNode *tempNode = list->head;
        list->head = list->head->next;
        free(tempNode);
    }
    list->tail = NULL;
}

int front(LinkedList *list) {
    LinkedNode *tempNode = list->head;
    int num = tempNode->value;
    list->head = tempNode->next;
    free(tempNode);
    if(list->head == NULL) {
        list->tail = NULL;
    }
    return num;
}

int checkSafety(LinkedList *list) {
    int checker = 0;
    LinkedNode *tempNode = list->head;
    while(list->head->next != NULL) {
        int diff = tempNode->value - tempNode->next->value;
        if(diff > 3 || diff < 1) {
            return 1;
        }
        checker = diff;
        tempNode = tempNode->next;
    }

    return 0;
}

int main() {
    LinkedList left;
    int sum = 0;
    initLL(&left);

    FILE *file = fopen("input.txt", "r");
    if(file == NULL) {
        printf("Couldn't open file!");
        return 1;
    }

    char line[256];
    while(fgets(line, sizeof(line), file) != 0) {
        printf("%s", line);
        int num;
        char *token;
        token = strtok(line, " ");
        while(token != NULL) {
            num = atoi(token);
            insert(&left, num);
            token = strtok(NULL, " ");
        }

        if(checkSafety(&left) == 0) {
            sum += 1;
        }
        output(&left);
        emptyList(&left);

        printf("\n");
    }

    fclose(file);
    printf("%d\n", sum);

    return 0;
}
