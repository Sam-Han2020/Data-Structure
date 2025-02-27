#include <iostream>
using namespace std;

typedef char E;

typedef struct TreeNode
{
    E element;
    struct TreeNode *left, *right;
} *Node;

void preOrder(TreeNode *tree)
{
    if (tree == NULL)
        return;
    cout << tree->element << " ";
    preOrder(tree->left);
    preOrder(tree->right);
}

int main()
{
    Node a = (Node)malloc(sizeof(struct TreeNode));
    Node b = (Node)malloc(sizeof(struct TreeNode));
    Node c = (Node)malloc(sizeof(struct TreeNode));
    Node d = (Node)malloc(sizeof(struct TreeNode));
    Node e = (Node)malloc(sizeof(struct TreeNode));
    Node f = (Node)malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';
    f->element = 'F';

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->left = NULL;
    c->right = f;
    d->left = d->right = NULL;
    e->left = e->right = NULL;
    f->left = f->right = NULL;

    preOrder(a);

    return 0;
}