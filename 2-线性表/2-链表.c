#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int E;

struct ListNode {
    E element;
    struct ListNode *next;
};

typedef struct ListNode Node,*List;

List CreateList()
{
    List node = (List)malloc(sizeof(Node));
    node->next = NULL;
    return node;
}

bool insertNode(List head, E element, int index)
{// 链表带头结点，插入对应的位置
    if(index < 1) return false;
    while(--index)
    {
        head = head->next;
        if(head == NULL) return false;
    } // 循环完成后，head代表待插入位置结点的前驱结点
    List node = CreateList();
    if(node == NULL) return 0;
    node->next = head->next;
    node->element = element;
    head->next = node;
    return true;
}

bool delNode(List head, int index)
{
    if(index < 1) return 0;
    while(--index)
    {
        head = head->next;
        if(head == NULL) return 0;
    }
    List p = head->next;
    head->next = p->next;
    free(p);
    return 1;
}

List getNode(List head,int index)
{
    if(index < 1) return NULL;
    do{
        head = head->next;
    }while(--index);
    return head;
}

int findNode(List head,E element)
{ // 找不到返回-1
    int index = 0;
    while(1){
        head = head->next;
        if(head == NULL) return -1;
        ++index;
        if(head->element == element) break;
    }
    return index;
}

int getLength(List head)
{
    int index = 0;
    while(head)
    {
        ++index;
        head = head->next;
    }
    return index - 1;
}

void PrintList(List head)
{
    while (head->next)
    {
        head = head->next;
        printf("%d ",head->element);
    }
    printf("\n");    
}

int main()
{
    List head = CreateList();
    insertNode(head,100,1);
    insertNode(head,200,2);
    insertNode(head,300,3);
    delNode(head,1);
    PrintList(head);
    printf("%d\n",getNode(head,2)->element);
    printf("%d\n",findNode(head,400));
    printf("%d\n",getLength(head));
    return 0;
}