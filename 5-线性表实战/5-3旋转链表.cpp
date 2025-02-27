/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    int getLength(ListNode *head)
    {
        int count = 0;
        while (head)
        {
            ++count;
            head = head->next;
        }
        return count;
    }
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == NULL || k == 0)
            return head;
        int l = getLength(head);
        k = k % l;
        ListNode *p = head;
        for (int i = 0; i < l - k - 1; ++i)
        {
            p = p->next;
        }
        ListNode *q = p->next, *h = q;
        p->next = NULL;
        if (q == NULL)
            return head;
        while (q->next)
            q = q->next;
        q->next = head;
        return h;
    }
};