#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGEST_NAME 10

typedef struct Operate {
    enum { Add, Del } type;
    struct Node* node;
    struct Node* last;
} Operation;
struct StackNode {
    Operation operation;
    struct StackNode* next;
};
typedef struct Stack {
    struct StackNode* top;
}Stack;
struct Node {
    char name[LONGEST_NAME];
    struct Node* next;
};
void initialize(Stack* stack);
void push(Stack* stack, Operation operate);
Operation pop(struct Stack* stack);
void Menu();
void ShowInfos(struct Node* head);
struct Node* Create(char* name);
Operation Insert(struct Node** head, char* name);
Operation Delete(struct Node** head, char* name);
void Undo(struct Node** linkedList, struct Stack* stack);

int main() {
    char name[LONGEST_NAME];
    struct Node* linkedList = NULL;
    Stack stack;
    initialize(&stack);
    Menu();
    while (1) {
        ShowInfos(linkedList);
        int choice;
        printf("Please input your choice(num):");
        scanf("%d", &choice);
        rewind(stdin);
        switch (choice) {
            case 1:
                printf("Please input the name:");
                scanf("%s", name);
                rewind(stdin);
                Operation insert = Insert(&linkedList, name);
                push(&stack, insert);
                printf("Add student successfully!\n");
                break;
            case 2:
                printf("Please input the name:");
                scanf("%s", name);
                rewind(stdin);
                Operation del = Delete(&linkedList, name);

                if (del.node != NULL) {
                    push(&stack, del);
                    printf("Delete successfully !\n");
                }
                else {
                    printf("The name is not exists...\n");
                }
                break;
            case 3:
                Undo(&linkedList, &stack);
                break;
            case 4:
            default:
                while (stack.top != NULL) {
                    struct StackNode* top = stack.top;
                    stack.top = top->next;
                    free(top);
                }
                while (linkedList != NULL) {
                    struct Node* next = linkedList->next;
                    free(linkedList);
                    linkedList = next;
                }
                return 0;
        }
    }

}

void Undo(struct Node** linkedList, struct Stack* stack) {
    if (stack->top != NULL) {
        Operation lastOp = pop(stack);
        if (lastOp.type == Add) {
            Delete(linkedList, lastOp.node->name);
        }
        else if (lastOp.type == Del) {
            struct Node* del = lastOp.node;
            struct Node* last = lastOp.last;

            if (last == NULL) {
                del->next = *linkedList;
                *linkedList = del;
            }
            else {
                del->next = last->next;
                last->next = del;
            }
        }
    }
    else {
        printf("Failed to undo...\n");
    }
}

Operation Delete(struct Node** head, char* name) {
    struct Node* current = *head;
    struct Node* last = NULL;

    while (current != NULL) {
        if (strncmp(current->name, name, LONGEST_NAME) == 0) {
            if (last == NULL) {
                *head = current->next;
            }
            else {
                last->next = current->next;
            }

            Operation delete;
            delete.type = Del;
            delete.node = current;
            delete.last = last;

            return delete;
        }

        last = current;
        current = current->next;
    }

    Operation delete;
    delete.type = Del;
    delete.node = NULL;
    delete.last = NULL;

    return delete;
}

struct Node* Create(char* name) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    strncpy(new -> name, name, LONGEST_NAME);
    new -> next = NULL;
    return new;
}

Operation Insert(struct Node** head, char* name) {
    struct Node* new = Create(name);
    if (*head == NULL) {
        new -> next = *head;
        *head = new;
    } else {
        struct Node* current = *head;
        while (current -> next != NULL) {
            current = current -> next;
        }
        current -> next = new;
    }
    Operation insert;
    insert.type = Add;
    insert.node = new;
    return insert;
}

void ShowInfos(struct Node* head) {
    struct Node* current = head;
    printf("All students' info: ");
    while (current != NULL) {
        printf("%s ", current -> name);
        current = current -> next;
    }
    printf("\n");
}

void Menu() {
    printf("-----------------------------------------------------------------\n");
    printf("--                                                             --\n");
    printf("--                          Menu                               --\n");
    printf("--                                                             --\n");
    printf("--             1. Add                 2. Delete                --\n");
    printf("--             2. Revoke              4. Exit                  --\n");
    printf("--                                                             --\n");
    printf("--                                                             --\n");
    printf("-----------------------------------------------------------------\n");
}

void initialize(Stack* stack) {
    stack -> top = NULL;
}

void push(Stack* stack, Operation operate) {
    struct StackNode* new = (struct StackNode*) malloc(sizeof(struct StackNode));
    new -> operation = operate;
    new -> next = stack -> top;
    stack -> top = new;
}

Operation pop(struct Stack* stack) {
    struct StackNode* top = stack->top;
    Operation operate = top -> operation;
    stack->top = top -> next;
    free(top);
    return operate;
}