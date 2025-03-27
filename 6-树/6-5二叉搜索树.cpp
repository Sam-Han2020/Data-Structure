#include <iostream>
using namespace std;

#define E int

struct TreeNode {
    E element;
    TreeNode *left;
    TreeNode *right;
};

typedef TreeNode *Node;

Node CreateNode(E element)
{
    Node node = (Node)malloc(sizeof(TreeNode));
    node->left = node->right = NULL;
    node->element = element;
    return node;
}

Node insert(Node root, E element)
{
    if(root) {
        if(root->element > element)
            root->left = insert(root->left,element);
        else if(root->element < element)
            root->right = insert(root->right,element);
    } else {
        root = CreateNode(element);
    }
    return root;
}

void inOrder(Node root)
{
    if(root == NULL) return;
    inOrder(root->left);
    cout<<root->element<<" ";
    inOrder(root->right);
}

Node find(Node root , E target)
{
    while(root)
    {
        if(root->element > target) 
            root = root->left;
        else if(root->element < target) 
            root = root->right;
        else break;
    }
    return root;
}

Node findMAX(Node root)
{
    while(root && root->right)
    {
        root = root->right;
    }
    return root;
}

Node deleteNode(Node root,E target)
{
    if(root == NULL) return NULL;
    if(root->element > target)
        root->left = deleteNode(root->left,target);
    else if(root->element < target)
        root->right = deleteNode(root->right,target);
    else { // 找到了该删除的节点
        if(root->left && root->right) { // 结点有左右孩子，取左子树最大结点上位
            Node max = findMAX(root->left); // 左子树的最大节点
            root->element = max->element; // 上位
            root->left = deleteNode(root->left,root->element); // 去删除下方冗余的节点
        } else { // 另外的两种情况
            Node tmp = root;
            if(root->right != NULL) root = root->right;
            else root = root->left;
            free(tmp); // 这里新的root会被返回上来
        }
    }
    return root;
}

int main()
{
    Node root = insert(NULL,18);
    root = insert(root,10);
    root = insert(root,20);
    root = insert(root,7);
    root = insert(root,15);
    root = insert(root,22);
    root = insert(root,9);
    root = deleteNode(root,18); // 测试删除
    inOrder(root); // 从小到大依次输出
    cout<<endl;
    cout<<find(root,17)<<endl; // 找不到
    cout<<find(root,9)<<endl; // 找到了
    return 0;
}