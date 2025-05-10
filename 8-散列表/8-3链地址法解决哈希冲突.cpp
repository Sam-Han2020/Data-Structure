#include <iostream>
using namespace std;

#define SIZE 9

typedef struct ListNode {
    int key;
    struct ListNode *next;
} *Node;

typedef struct HashTable {
    struct ListNode *table; // 存放头节点
} *HashT;

void init(HashT hashTable)
{
    hashTable->table = (struct ListNode *)malloc(sizeof(struct ListNode)*SIZE);
    for(int i=0;i<SIZE;++i)
    {
        hashTable->table[i].key = -1; // 头结点的key置为-1
        hashTable->table[i].next = NULL; // next指向NULL
    }
}

int hashF(int key)
{
    return key % SIZE;
}

Node createNode(int key)
{
    Node node = (Node)malloc(sizeof(struct ListNode));
    node->key = key;
    node->next = NULL;
    return node;
}

void insert(HashT hashTable,int key)
{
    int hashCode = hashF(key);
    Node head = hashTable->table + hashCode; // 同&hashTable->table[hashCode]
    while(head->next!=NULL) head = head->next;
    head->next = createNode(key);
}

bool find(HashT hashTable,int key)
{
    int hashCode = hashF(key);
    Node head = hashTable->table + hashCode;
    while(head->next && head->key != key)
        head = head->next;
    return head->key == key;
}

int main()
{
    HashT table = new struct HashTable;
    init(table);

    insert(table,10);
    insert(table,19);
    insert(table,20);

    cout<<find(table,20)<<endl;
    cout<<find(table,17)<<endl;
    cout<<find(table,19)<<endl;
}

