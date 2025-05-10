#include <stdio.h>

#define SIZE 128

typedef int K;
typedef int V;

typedef struct LNode
{
    K key;
    V value;
    struct LNode *next;
} *Node;

typedef struct HashTable
{
    struct LNode *table;
} *HashTable;

void init(HashTable hashTable)
{
    hashTable->table = (Node)malloc(sizeof(struct LNode)*SIZE);
    for(int i=0;i<SIZE;++i)
    {
        hashTable->table[i].key = -1;
        hashTable->table[i].value = -1;
        hashTable->table[i].next = NULL;
    }
}

int hashF(unsigned int key)
{
    return key % SIZE;
}

Node create(K key, V value)
{
    Node node = (Node)malloc(sizeof(struct LNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

void insert(HashTable hashTable,K key,V value)
{
    int hashCode = hashF(key);
    Node head = hashTable->table + hashCode;
    while(head->next) head = head->next;
    head->next = create(key,value);
}

Node find(HashTable hashTable,K key)
{
    int hashCode = hashF(key);
    Node head = hashTable->table + hashCode;
    while(head->next && head->next->key != key)
        head = head->next;
    return head->next;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* result(int i,int j,int *returnSize)
{
    *returnSize = 2;
    int *result = (int*)malloc(sizeof(int)*2);
    result[0] = i;
    result[1] = j;
    return result;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashTable table = (HashTable)malloc(sizeof(struct HashTable));
    init(table);
    for(int i=0;i<numsSize;++i)
    {
        Node node = find(table,target-nums[i]);
        if(node) return result(i,node->value,returnSize);
        insert(table,nums[i],i);
    }
    return NULL;
}




