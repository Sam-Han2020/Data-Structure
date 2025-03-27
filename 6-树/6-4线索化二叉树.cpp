#include <iostream>
using namespace std;

typedef char E;

typedef struct TreeNode {
    E element;
    struct TreeNode *left;
    struct TreeNode *right;
    int leftTag, rightTag; // 标志位，如果为1表示这一步指针指向的是线索，不为1的就是正常的孩子节点
    struct TreeNode *parent; // 为后序提供
} *Node;

Node createNode(E element) 
{
    Node node = (Node)malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->leftTag = node->rightTag = 0;
    node->element = element;
    return node;
}

Node prev1 = NULL; // 记录当前遍历结点的前驱结点
void preOrderThreaded(Node root) 
{ // 为二叉树建立前序遍历的线索
    if(root==NULL) return ;
    if(root->left == NULL) {
        root->left = prev1;
        root->leftTag = 1;
    }
    if(prev1 && prev1->right == NULL) {
        prev1->right = root;
        prev1->rightTag = 1;
    }
    prev1 = root;
    if(root->leftTag==0) preOrderThreaded(root->left);
    if(root->rightTag==0) preOrderThreaded(root->right);
}

Node prev2 = NULL;
void inOrderThreaded(Node root)
{ // 为二叉树建立中序遍历的线索
    if(root==NULL) return ;
    if(root->leftTag==0) inOrderThreaded(root->left);
    if(root->left == NULL) {
        root->left = prev2; // 注意到，对于最左边的结点，此时prev2是空的
        root->leftTag = 1;
    }
    if(prev2 && prev2->right == NULL) {
        prev2->right = root;
        prev2->rightTag = 1;
    }
    prev2 = root;
    if(root->rightTag==0) inOrderThreaded(root->right);
}

Node prev3 = NULL;
void postOrderThreaded(Node root)
{
    if(root == NULL) return ;
    if(root->leftTag==0) 
    {
        postOrderThreaded(root->left);
        if(root->left) root->left->parent = root;
    }
    if(root->rightTag==0)
    {
        postOrderThreaded(root->right);
        if(root->right) root->right->parent = root;
    }
    if(root->left==NULL) root->left = prev3 , root->leftTag = 1;
    if(prev3 && prev3->right == NULL) prev3->right = root , prev3->rightTag = 1;
    prev3 = root;
}

void preOrder(Node root) 
{
    while(root)
    {
        cout<<root->element<<" ";
        if(root->leftTag==0) root = root->left;
        else root = root->right;
    }
}

void inOrder(Node root)
{
    while(root) 
    {
        while(root && root->leftTag == 0)
        {
            root = root->left;
        }
        cout<<root->element<<" ";
        while(root && root->rightTag == 1)
        {
            root = root->right;
            cout<<root->element<<" ";
        }
        root = root->right;
    }
}

void postOrder(Node root)
{
    Node prev = NULL , node = root; // 记录前驱结点，以及根节点
    while(node) 
    {
        while(node->left!=prev && node->leftTag == 0)
            node = node->left; // 先找最左 , 前一个判断条件，是防止死循环
        // 下面两个while循环，遍历左子树
        while(node && node->rightTag == 1)
        {
            cout<<node->element<<" ";
            prev = node;
            node = node->right;
        } // D F G
        if(node == root && node->right == prev)
        { // 右子树上来到根节点，结束
            cout<<root->element<<" ";
            return;
        }
        while(node && node->right == prev)
        {
            cout<<node->element<<" ";
            prev = node;
            node = node->parent;
        } // D F G E B
        if(node && node->rightTag == 0) {
            // 这里只可能是左子树上来回到根节点的情况
            node = node->right;
        }
    }
}

int main()
{
    Node a = createNode('A');
    Node b = createNode('B');
    Node c = createNode('C');
    Node d = createNode('D');
    Node e = createNode('E');
    Node f = createNode('F');
    Node g = createNode('G');
    Node h = createNode('H');

    a->left = b;
    b->left = d;
    a->right = c;
    b->right = e;
    e->left = f;
    e->right = g;
    c->right = h;

    // preOrderThreaded(a);
    // preOrder(a);

    // inOrderThreaded(a);
    // inOrder(a);

    postOrderThreaded(a);
    postOrder(a);

    return 0;
}