#include <iostream>
using namespace std;

#define MaxVertex 5

typedef char E;

typedef struct MatrixGraph {
    int vertexCount , edgeCount ;
    int matrix[MaxVertex][MaxVertex]; // 邻接矩阵
    E data[MaxVertex]; // 各个顶点对应的数据
} * Graph;

Graph CreateGraph() 
{
    Graph graph = (Graph)malloc(sizeof(struct MatrixGraph));
    graph->vertexCount = graph->edgeCount = 0;
    for(int i=0 ; i < MaxVertex ; ++i)
        for(int j=0 ; j<MaxVertex ; ++j)
            graph->matrix[i][j] = 0;
    return graph;
}

void addVertex(Graph graph,E element) 
{
    if(graph->vertexCount >= MaxVertex) return ;
    graph->data[graph->vertexCount++] = element;
}

void addEdge(Graph graph , int a , int b)
{
    if(graph->matrix[a][b] == 0) {
        graph->matrix[a][b] = 1; // 无向图的话，也要执行graph->matrix[b][a] = 1;
        graph->edgeCount++;
    }
}

void printGraph(Graph graph) {
    for(int i=-1;i<graph->vertexCount;++i) {
        for(int j = -1 ; j<graph->vertexCount;++j) {
            if(j==-1)
                printf("%c",'A'+i);
            else if(i==-1)
                printf("%3c",'A'+j);
            else
                printf("%3d",graph->matrix[i][j]);
        }
        putchar('\n');
    }
}

int main()
{
    Graph graph = CreateGraph();
    for(int c='A';c<='D';++c) 
        addVertex(graph,(char)c);
    addEdge(graph,0,1); // A->B
    addEdge(graph,1,2); // B->C
    addEdge(graph,2,3); // C->D
    addEdge(graph,3,0); // D->A
    addEdge(graph,2,0); // C->A
    printGraph(graph);
    return 0;
}