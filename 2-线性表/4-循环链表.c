#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct ListNode {
    ElemType element;
    struct ListNode *next;
}Node , *List;

List CreateList()
{
    List head = (List)malloc(sizeof(Node));
    head->next = head;
    return head;
}

bool insertNode(List head,ElemType e,int index)
{
    if(index < 1) return false;
    while (--index)
    {
        head = head->next;
        if(head == NULL) return false;
    }
    List node = CreateList();
    node->element = e;
    node->next = head->next;
    head->next = node;
    return true;
}

bool delNode(List head,int index)
{
    if(index < 1) return false;
    while(--index)
    {
        head = head->next;
        if(head == NULL) return false;
    }
    List p = head->next;
    head->next = head->next->next;
    free(p);
    return true;
}

void PrintList(List head)
{
    List p = head;
    while(head->next != p)
    {
        printf("%d ",head->next->element);
        head = head->next;
    }
    printf("\n");
    head = head->next;
    while(head->next != p)
    {
        printf("%d ",head->next->element);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    List head = CreateList();
    insertNode(head,1,1);
    insertNode(head,2,2);
    insertNode(head,3,3);
    delNode(head,3);
    PrintList(head);
    return 0;
}