#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct ListNode {
    ElemType element;
    struct ListNode *next;
    struct ListNode *prev;
}Node , *List;

List CreateList()
{
    List head = (List)malloc(sizeof(Node));
    head->next = head->prev = NULL;
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
    if(head->next!=NULL) head->next->prev = node;
    head->next = node;
    node->prev = head;
    return true;
}

bool delNode(List head,int index)
{
    if(index < 1) return false;
    while(index--) // 注意查找的是待删除结点
    {
        head = head->next;
        if(head == NULL) return false;
    }
    head->prev->next = head->next;
    if(head->next) head->next->prev = head->prev;
    free(head);
    return true;
}

void PrintList(List head)
{
    List p = head;
    while(head->next)
    {
        printf("%d ",head->next->element);
        head = head->next;
    }
    printf("\n");
    while(head!=p)
    {
        printf("%d ",head->element);
        head = head->prev;
    }
    printf("\n");
}

int main()
{
    List head = CreateList();
    insertNode(head,1,1);
    insertNode(head,2,2);
    insertNode(head,3,3);
    delNode(head,2);
    PrintList(head);
    return 0;
}