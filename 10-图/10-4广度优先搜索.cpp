#include <iostream>
#include <queue>
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

bool bfs(Graph graph,int startVertex,int targetVertex,int *visited,queue<int> &q)
{
    q.push(startVertex);
    visited[startVertex] = 1;
    while(!q.empty()) {
        int next = q.front();
        q.pop();
        cout<<graph->vertex[next].element<<" -> ";
        List node = graph->vertex[next].next;
        while(node) {
            if(node->nextVertex == targetVertex) return 1;
            if(!visited[node->nextVertex]) {
                q.push(node->nextVertex);
                visited[node->nextVertex] = 1;
            }
            node = node->next;
        }
    }
    return 0;
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
    queue<int> q;
    bfs(graph,0,5,arr,q);
    return 0;
}
