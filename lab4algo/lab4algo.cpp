#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef int elemtype;

typedef struct Node {
    elemtype value;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
    size_t size;
} DoublyLinkedList;

DoublyLinkedList* createList() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (list) {
        list->head = list->tail = NULL;
        list->size = 0;
    }
    return list;
}

void deleteList(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

bool isEmpty(DoublyLinkedList* list) {
    return list->size == 0;
}

void printList(DoublyLinkedList* list) {
    Node* current = list->head;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void pushFront(DoublyLinkedList* list, elemtype value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = list->head;
    newNode->prev = NULL;
    if (isEmpty(list)) {
        list->tail = newNode;
    }
    else {
        list->head->prev = newNode;
    }
    list->head = newNode;
    list->size++;
}

void pushBack(DoublyLinkedList* list, elemtype value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if (isEmpty(list)) {
        list->head = newNode;
    }
    else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->size++;
}

void popFront(DoublyLinkedList* list) {
    if (isEmpty(list)) return;
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    else {
        list->tail = NULL;
    }
    free(temp);
    list->size--;
}

void popBack(DoublyLinkedList* list) {
    if (isEmpty(list)) return;
    Node* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    else {
        list->head = NULL;
    }
    free(temp);
    list->size--;
}

typedef struct Stack {
    double arr[100];
    int top;
} Stack;

void push(Stack* s, double value) {
    if (s->top == 99) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

double pop(Stack* s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

double evaluateRPN(char* expression) {
    Stack stack;
    stack.top = -1;
    char* token;
    char* context;

    token = strtok_s(expression, " ", &context);

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atof(token));
        }
        else {
            double op2 = pop(&stack);
            double op1 = pop(&stack);
            switch (token[0]) {
            case '+': push(&stack, op1 + op2); break;
            case '-': push(&stack, op1 - op2); break;
            case '*': push(&stack, op1 * op2); break;
            case '/': push(&stack, op1 / op2); break;
            case '^': push(&stack, pow(op1, op2)); break;
            case 's': push(&stack, sqrt(op2)); break;
            default: printf("Неправильний оператор\n"); return -1;
            }
        }
        token = strtok_s(NULL, " ", &context);
    }
    return pop(&stack);
}

int main() {
    int choice;
    DoublyLinkedList* list = createList();

    while (1) {
        printf("1. Робота з двозв'язним списком\n");
        printf("2. Обчислення виразу у зворотній польській нотації\n");
        printf("3. Вийти\n");
        printf("Виберіть опцію: ");
        scanf_s("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            int listChoice, value;
            while (1) {
                printf("1. Додати елемент на початок\n");
                printf("2. Додати елемент в кінець\n");
                printf("3. Видалити елемент з початку\n");
                printf("4. Видалити елемент з кінця\n");
                printf("5. Вивести список\n");
                printf("6. Повернутися до головного меню\n");
                printf("Виберіть опцію: ");
                scanf_s("%d", &listChoice);

                switch (listChoice) {
                case 1:
                    printf("Введіть значення: ");
                    scanf_s("%d", &value);
                    pushFront(list, value);
                    break;
                case 2:
                    printf("Введіть значення: ");
                    scanf_s("%d", &value);
                    pushBack(list, value);
                    break;
                case 3:
                    popFront(list);
                    break;
                case 4:
                    popBack(list);
                    break;
                case 5:
                    printList(list);
                    break;
                case 6:
                    goto main_menu;
                default:
                    printf("Неправильний вибір!\n");
                }
            }
            break;
        }
        case 2: {
            char expression[100];
            printf("Введіть вираз у зворотній польській нотації: ");
            fgets(expression, 100, stdin);
            expression[strcspn(expression, "\n")] = 0;

            double result = evaluateRPN(expression);
            printf("Результат: %.2f\n", result);
            break;
        }
        case 3:
            deleteList(list);
            return 0;
        default:
            printf("Неправильний вибір!\n");
        }
    main_menu: continue;
    }

    return 0;
}
