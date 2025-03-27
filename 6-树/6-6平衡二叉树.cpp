#include <iostream>
using namespace std;

#define E int

struct TreeNode {
    E element;
    TreeNode *left;
    TreeNode *right;
    int height; // 新增高度便于计算平衡因子 
};

typedef TreeNode *Node;

Node CreateNode(E element)
{
    Node node = (Node)malloc(sizeof(TreeNode));
    node->left = node->right = NULL;
    node->element = element;
    return node;
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

int max(int a,int b)
{
    return  a > b ? a : b;
}

int getHeight(Node root)
{
    if(root == NULL) return 0;
    else return root->height;
}

int calcAVL(Node root)
{
    // cout<<root->left->element<<" "<<root->right->element<<endl;
    // cout<<getHeight(root->left)<<" "<<getHeight(root->right)<<endl;
    return getHeight(root->left) - getHeight(root->right);
}

// 左旋
Node leftRotation(Node root)
{// 传入原本的根节点，返回新的根节点
    Node newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node rightRotation(Node root)
{
    Node newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node leftRightRotation(Node root)
{
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

Node rightLeftRotation(Node root)
{
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

Node insert(Node root, E element)
{
    if(root) {
        if(root->element > element)
        {
            root->left = insert(root->left,element);
            if(calcAVL(root) > 1)
            {
                if(root->left->element > element)
                    root = rightRotation(root);
                else
                    root = leftRightRotation(root);
            }
        }
        else if(root->element < element)
        {
            root->right = insert(root->right,element);
            if(calcAVL(root) < -1)
            {
                if(root->right->element < element)
                    root = leftRotation(root);
                else
                    root = rightLeftRotation(root);
            }
        }
    } else {
        root = CreateNode(element);
    }
    root->height = max(getHeight(root->left),getHeight(root->right)) + 1; 
    return root;
}

Node findMinNode(Node node) {
    Node current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

Node deleteNode(Node root, E target) {
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
    // 第二次判断，排除根节点被删除的情况
    if(root == NULL) return NULL;

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get balance factor
    int balance = calcAVL(root);

    // Left Left Case
    if (balance > 1 && calcAVL(root->left) >= 0)
        return rightRotation(root);

    // Left Right Case
    if (balance > 1 && calcAVL(root->left) < 0) {
        return leftRightRotation(root);
    }

    // Right Right Case
    if (balance < -1 && calcAVL(root->right) <= 0)
        return leftRotation(root);

    // Right Left Case
    if (balance < -1 && calcAVL(root->right) > 0) {
        return rightLeftRotation(root);
    }

    return root;
}



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
    Node root = insert(NULL,7);
    // cout<<root->element<<endl;
    root = insert(root,10);
    // cout<<root->element<<endl;
    root = insert(root,20);
    root = insert(root,18);
    root = insert(root,15);
    root = insert(root,22);
    root = insert(root,9);
    root = deleteNode(root,15);
    root = deleteNode(root,22);
    root = deleteNode(root,9);
    root = deleteNode(root,18);
    inOrder(root); // 从小到大依次输出
    cout<<endl;
    // preOrder(root);
    // cout<<endl;
    cout<<root->element<<endl;
    return 0;
}