#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct ListNode {
    ElemType element;
    struct ListNode *next;
}Node , *List;

List CreateStack()
{
    List head = (List)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

bool Push(List head,ElemType e)
{
    List node = CreateStack();
    if(node == NULL) return false;
    node->element = e;
    node->next = head->next;
    head->next = node;
    return true;
}

ElemType Pop(List head)
{
    if(head->next==NULL) return -1;
    ElemType elem = head->next->element;
    List p = head->next;
    head->next = p->next;
    free(p);
    return elem;
}

bool is_empty(List head)
{
    return head->next == NULL;
}

void PrintStack(List head)
{
    head = head->next;
    while(head)
    {
        printf("%d ",head->element);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    List head = CreateStack();
    printf("%d\n",is_empty(head));
    Push(head,1);
    Push(head,2);
    Push(head,3);
    printf("%d\n",Pop(head));
    PrintStack(head);
    return 0;
}