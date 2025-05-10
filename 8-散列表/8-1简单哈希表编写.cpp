#include <iostream>
using namespace std;

#define SIZE 9

typedef struct Element
{
    int key;
} *Elem;


typedef struct HashTable
{
    Elem *table;
} *HashT;

void init(HashT &hashTable)
{
    hashTable->table = (Elem*)malloc(sizeof(Elem)*SIZE);
    for(int i=0;i<SIZE;++i)
    {
        hashTable->table[i] = NULL;
    }
}

int hashF(int key)
{
    return key%SIZE;
}

void insert(HashT hashTable , Elem e)
{
    int hashCode = hashF(e->key);
    hashTable->table[hashCode] = e;
}

bool find(HashT hashTable,int key)
{
    int hashCode = hashF(key);
    if(hashTable->table[hashCode] == NULL) return false;
    return hashTable->table[hashCode]->key == key;
}

Elem create(int key)
{
    Elem e = new Element;
    e->key = key;
    return e;
}

int main()
{
    HashT table = new HashTable;
    init(table);

    insert(table,create(10));
    insert(table,create(7));
    insert(table,create(13));
    insert(table,create(29));

    for(int i=0;i<SIZE;++i)
    {
        if(table->table[i]){
            cout<<table->table[i]->key<<" ";
        } else {
            cout<<"NULL ";
        }
    }

    cout<<endl;

    cout<<find(table,1)<<endl;
    cout<<find(table,13)<<endl;
}