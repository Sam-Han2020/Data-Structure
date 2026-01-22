#include <iostream>
using namespace std;

#define MaxVertex 7

typedef char E;

typedef struct Node
{ // 结点和头结点分开定义，普通结点记录邻接顶点信息
    int nextVertex;
    struct Node *next;
} * List;

struct HeadNode 
{ // 头结点记录元素，代表每一个顶点
    E element;
    struct Node* next;
};

typedef struct AdjacencyGraph {
    int vertexCount; // 顶点数
    int edgeCount;   // 边数
    struct HeadNode vertex[MaxVertex];
} * Graph;

Graph CreateGraph() 
{
    Graph graph = (Graph)malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    return graph;
}

void addVertex(Graph graph,E element) 
{
    if(graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

void addEdge(Graph graph , int a , int b) // a和b都是vertex数组的下标
{
    List node = graph->vertex[a].next;
    List newNode = (List)malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->nextVertex = b;
    if(!node) {  // 如果头结点下一个都没有，那么直接连上去
        graph->vertex[a].next = newNode;
    } else {  // 否则说明当前顶点已经连接了至少一个其他顶点了，有可能出现已经连接过的情况，需要特别处理一下
        do {
            if(node->nextVertex == b) {
                delete newNode;
                return;
            } // 如果已经连接了对应的顶点，直接返回
            if(node->next) node = node->next; // 否则继续向后遍历
            else break; // 遍历到最后一个结点，直接结束
        } while(1);
        node->next = newNode;
    }
    graph->edgeCount++;
}

void printGraph(Graph graph) {
    for(int i=0;i<graph->vertexCount;++i) {
        printf("%d | %c",i,graph->vertex[i].element);
        List node = graph->vertex[i].next;
        while(node) {
            printf(" -> %d",node->nextVertex);
            node = node->next;
        }
        putchar('\n');
    }
}


#define ElemType int

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
        return -1;
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

/**
 * @param startVertex 起点顶点下标
 * @param targetVertex 目标顶点下标
 */
bool dfs(Graph graph , int startVertex , int targetVertex , int * visited) 
{
    printf("%c -> ",graph->vertex[startVertex].element);
    visited[startVertex] = 1;
    if(startVertex == targetVertex) return true;
    List node = graph->vertex[startVertex].next; // node == NULL 就直接返回了，隐含的结束条件
    while(node) {
        if(!visited[node->nextVertex]) 
            if(dfs(graph,node->nextVertex,targetVertex,visited)) return true;
        node = node->next;
    }
    return false;
}

bool bfs(Graph graph,int startVertex,int targetVertex,int *visited,LinkedQueue queue)
{
    EnQueue(queue,startVertex); // 首先把起始位置顶点丢进去
    visited[startVertex] = 1; // 起始位置设置为已走过
    while(!is_Empty(queue)) {
        int next = DeQueue(queue);
        printf("%c -> ",graph->vertex[next].element);
        List node = graph->vertex[next].next;
        while(node) {
            if(node->nextVertex == targetVertex) return true;
            if(!visited[node->nextVertex]) { // 如果没有走过，那么就直接入队
                EnQueue(queue,node->nextVertex);
                visited[node->nextVertex] = 1;
            }
            node = node->next;
        }
    }
    return false;
}

int main()
{
    Graph graph = CreateGraph();
    for(int c='A';c<='G';++c) 
        addVertex(graph,(char)c);
    addEdge(graph,0,1); 
    addEdge(graph,1,2); 
    addEdge(graph,1,3); 
    addEdge(graph,1,4); 
    addEdge(graph,4,5); 
    addEdge(graph,3,6); 
    // printGraph(graph);
    int arr[graph->vertexCount] = {0};
    // printf("\n%d",dfs(graph,0,5,arr));
    LinkedQueue queue = initLinkedQueue();
    printf("\n%d",bfs(graph,0,5,arr,queue));
    return 0;
}
