#include <iostream>
using namespace std;

typedef char E;

typedef struct TreeNode
{
    E element;
    struct TreeNode *left, *right;
    int flag;
} *Node;

typedef Node ElemType;

// 栈的实现

typedef struct ListNode {
    ElemType element;
    struct ListNode *next;
}LNode , *List;

typedef struct QNode
{
    ElemType element;
    struct QNode *next;
} QNode, *Queue;

typedef struct LinkedQ
{
    Queue front, rear;
} *LinkedQueue;

Queue CreateQueue()
{
    Queue head = (Queue)malloc(sizeof(QNode));
    head->next = NULL;
    return head;
}

LinkedQueue initLinkedQueue()
{
    LinkedQueue lq = (LinkedQueue)malloc(sizeof(struct LinkedQ));
    lq->front = lq->rear = NULL;
    return lq;
}

bool is_Empty(LinkedQueue lq)
{
    return lq->front == NULL && lq->rear == NULL;
}

bool EnQueue(LinkedQueue lq, ElemType e)
{
    Queue node = CreateQueue();
    if (node == NULL)
        return false;
    node->element = e;
    if (is_Empty(lq))
        lq->front = lq->rear = node;
    else
    {
        node->next = lq->rear->next;
        lq->rear->next = node;
        lq->rear = lq->rear->next;
    }
    return true;
}

ElemType DeQueue(LinkedQueue lq)
{
    if (is_Empty(lq))
        return NULL;
    ElemType elem = lq->front->element;
    if (lq->front == lq->rear)
        lq->front = lq->rear = NULL;
    else
        lq->front = lq->front->next;
    return elem;
}

void PrintQueue(LinkedQueue lq)
{
    Queue q = lq->front;
    while (q)
    {
        printf("%d ", q->element);
        q = q->next;
    }
    printf("\n");
}

List CreateStack()
{
    List head = (List)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

bool Push(List head,ElemType e)
{
    List node = CreateStack();
    if(node == NULL) return false;
    node->element = e;
    node->next = head->next;
    head->next = node;
    return true;
}

ElemType getTop(List head)
{
    return head->next->element;
}

ElemType Pop(List head)
{
    if(head->next==NULL) return NULL;
    ElemType elem = head->next->element;
    List p = head->next;
    head->next = p->next;
    free(p);
    return elem;
}

bool is_Empty(List head)
{
    return head->next == NULL;
}

void PrintStack(List head)
{
    head = head->next;
    while(head)
    {
        printf("%c ",head->element->element);
        head = head->next;
    }
    printf("\n");
}

// END

void preOrder(TreeNode *tree)
{
    if (tree == NULL)
        return;
    cout << tree->element << " ";
    preOrder(tree->left);
    preOrder(tree->right);
}

void preOrder0(TreeNode *tree)
{
    List stack = CreateStack();
    while(tree || !is_Empty(stack))
    {
        while(tree)
        {
            cout<<tree->element<<" ";
            Push(stack,tree);
            tree = tree->left;
            PrintStack(stack);
        }
        do {tree = Pop(stack);} while(!tree->right);
        tree = tree->right;
    }
}

void inOrder(TreeNode *root)
{
    if(root==NULL) return;
    inOrder(root->left);
    cout<<root->element<<" ";
    inOrder(root->right);
}

void inOrder0(TreeNode *root)
{
    List stack = CreateStack();
    while(root || !is_Empty(stack))
    {
        while(root)
        {
            Push(stack,root);
            root->flag = 0; // 0 表示左子树遍历完成
            root = root->left;
        }
        root = Pop(stack);
        cout<<root->element<<" ";
        root = root->right; // 如果没有右节点，正好就是返回上一个
    }
}

void postOrder(TreeNode *root)
{
    if(root==NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->element<<" ";
}

void postOrder0(TreeNode *root)
{
    List stack = CreateStack();
    while(root || !is_Empty(stack))
    {
        while(root)
        {
            Push(stack,root);
            root->flag = 0;
            root = root->left;
        }
        root = getTop(stack);
        if(root->flag==0) {
            root->flag = 1;
            root = root->right;
        } else {
            cout<<root->element<<" ";
            Pop(stack);
            root = NULL; // 跳过while，继续取栈里面的结点
        }
    }
}

void levelOrder(TreeNode *tree)
{
    LinkedQueue q = initLinkedQueue();
    while(tree || !is_Empty(q))
    {
        cout<<tree->element<<" ";
        if(tree->left) EnQueue(q,tree->left); // if不能少
        if(tree->right) EnQueue(q,tree->right);
        tree = DeQueue(q);
    }
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

    // preOrder0(a);
    inOrder0(a);
    // postOrder0(a);
    // levelOrder(a);

    return 0;
}