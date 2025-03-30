#include <iostream>
#include <string.h>
using namespace std;

#define T Tree

#define E char

// 哈夫曼树
typedef struct TreeNode {
    E element;
    TreeNode *left;
    TreeNode *right;
    int value; // 权值
    string code;
} *Tree;

// 优先级队列
typedef struct LNode {
    T element;
    LNode *next;
} *List;

struct Queue
{
    List front,rear;
};

typedef struct Queue *LinkedQueue;

bool initQueue(LinkedQueue queue)
{
    List node = new LNode;
    if(node == NULL) return 0;
    queue->front = queue->rear = node;
    node->next = NULL; // 因为会用到判断下一个是否为空
    return true;
}

// 优先级插入方式
bool offerQueue(LinkedQueue queue,T element)
{
    List node = new LNode;
    if(node == NULL) return false;
    node->element = element;
    node->next = NULL;
    List pre = queue->front;
    while(pre->next && pre->next->element->value <= element->value)
        // 从小到大的优先级队列，这里寻找pre->element比element大的pre
        pre = pre->next;
    if(pre == queue->rear) {
        // 插入队尾
        queue->rear->next = node;
        queue->rear = node;
    } else {
        // VIP模式，插在pre后面
        node->next = pre->next;
        pre->next = node;
    }
    return true;
}

T pollQueue(LinkedQueue queue)
{
    T elem = queue->front->next->element; // 跳过首节点，取第一个
    List node = queue->front->next; 
    queue->front->next = queue->front->next->next; 
    if(queue->rear == node) queue->rear = queue->front;
    delete node;
    return elem;
}

// 会从小到大输出
void printQueue(LinkedQueue queue)
{
    cout<<"<<< ";
    List node = queue->front->next; // 跳过首节点，取第一个
    while(node)
    {
        cout<<node->element->element<<" ";
        node = node->next;
    }
    cout<<"<<<"<<endl;
}

// 创建二叉树结点
Tree createNode(E element, int value)
{
    Tree node = new TreeNode;
    node->element = element;
    node->left = node->right = NULL;
    node->value = value;
    return node;
}

void inOrder(Tree root)
{
    if(root==NULL) return;
    inOrder(root->left);
    // cout<<root->element<<" ";
    if(root->element!='r') cout<<root->code<<endl;
    inOrder(root->right);
}

// 写的没看懂
// char* encode(Tree root,E elem)
// {
//     if(root == NULL) return NULL;
//     if(root->element == elem) return "";
//     char *str = encode(root->left,elem);
//     char *s = (char*)malloc(sizeof(char)*10);
//     if(str != NULL)
//     {
//         s[0] = '0';
//         str = strcat(s,str);
//     } else {
//         str = encode(root->right,elem);
//         if(str != NULL)
//         {
//             s[0] = '1';
//             str = strcat(s,str);
//         }
//     }
//     return str;
// }

// 下面两个是自己写的

// 最佳编码方案
void Encode(Tree root,string str)
{
    if(root == NULL) return ;
    root->code = str;
    Encode(root->left,str+"0");
    Encode(root->right,str+"1");
}

// 输出单个
string encode(Tree root, string str, E elem) {
    if (root == nullptr) return "";
    if (root->element == elem) return str;
    // 先探索左子树，若找到则直接返回编码
    string left = encode(root->left, str + "0", elem);
    if (!left.empty()) return left;
    // 左子树未找到，再探索右子树并返回结果
    string right = encode(root->right, str + "1", elem);
    return right;
}

int main()
{
    LinkedQueue queue = new Queue;
    initQueue(queue);
    
    offerQueue(queue,createNode('A',5));
    offerQueue(queue,createNode('B',16));
    offerQueue(queue,createNode('C',8));
    offerQueue(queue,createNode('D',13));
    // printQueue(queue); // A C D B

    
    while(queue->front->next != queue->rear)
    {
        Tree left = pollQueue(queue);
        Tree right = pollQueue(queue);
        Tree node = createNode('r',left->value + right->value);
        node->left = left;
        node->right = right;
        offerQueue(queue,node);  
    }

    Tree root = pollQueue(queue);
    Encode(root,"");
    inOrder(root);
    cout<<encode(root,"",'B')<<endl;
    cout<<encode(root,"",'D')<<endl;
    cout<<encode(root,"",'A')<<endl;
    cout<<encode(root,"",'C')<<endl;

    return 0;
}