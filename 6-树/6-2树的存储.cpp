#include <iostream>
using namespace std;

typedef char E;

typedef struct TreeNode
{
    E element;
    struct TreeNode *left, *right;
} *Node;

int main()
{
    Node a = (Node)malloc(sizeof(struct TreeNode));
    Node b = (Node)malloc(sizeof(struct TreeNode));
    Node c = (Node)malloc(sizeof(struct TreeNode));
    Node d = (Node)malloc(sizeof(struct TreeNode));
    Node e = (Node)malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->left = c->right = NULL;
    d->left = d->right = NULL;
    e->left = e->right = NULL;

    cout << a->left->right->element << endl;

    return 0;
}