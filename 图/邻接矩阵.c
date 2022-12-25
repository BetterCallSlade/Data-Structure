#include <stdio.h>
#include <stdlib.h>

typedef struct {
	#define VERTICES 5
	int edges;
	int adjacency_matrix[VERTICES][VERTICES];
} Graph;

// 创建无向无权图
Graph* create_undirected_unweighted_graph()
{
	Graph* graph = malloc(sizeof(Graph));
	for (int i = 0; i < VERTICES; i++) {
		for (int j = 0; j < VERTICES; j++) {
			graph->adjacency_matrix[i][j] = 0;
		}
	}
	scanf("%d", &graph->edges);
	int va, vb;
	for (int i = 0; i < graph->edges; ++i)
	{
		scanf("%d", &va);
		scanf("%d", &vb);
		graph->adjacency_matrix[va][vb] = 1;
		graph->adjacency_matrix[vb][va] = 1;
	}
	return graph;
}

#define MaxInt 32767

// 创建无向有权图
Graph* create_undirected_weighted_graph()
{
	Graph* graph = malloc(sizeof(Graph));
	for (int i = 0; i < VERTICES; i++) {
		for (int j = 0; j < VERTICES; j++) {
			graph->adjacency_matrix[i][j] = MaxInt;
		}
	}
	scanf("%d", &graph->edges);
	int va, vb, vw;
	for (int i = 0; i < graph->edges; ++i)
	{
		scanf("%d", &va);
		scanf("%d", &vb);
		scanf("%d", &vw);
		graph->adjacency_matrix[va][vb] = vw;
		graph->adjacency_matrix[vb][va] = vw;
	}
	return graph;
}

void PrintGraph(Graph* graph)
{
	for (int i = 0; i < VERTICES; i++)
	{
		for (int j = 0; j < VERTICES; j++)
		{
			printf("%d ", graph->adjacency_matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	// Graph* graph = create_undirected_unweighted_graph();
	Graph* graph = create_undirected_weighted_graph();
	PrintGraph(graph);
}