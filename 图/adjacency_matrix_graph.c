#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int vertices;
	int edges;
	int** adjacency_matrix;
} Graph;

Graph* CreateGraph()
{
	Graph* graph = malloc(sizeof(Graph));
	scanf("%d", &graph->vertices);
	graph->adjacency_matrix = malloc(sizeof(int*) * graph->vertices);
	for (int i = 0; i < graph->vertices; ++i)
	{
		graph->adjacency_matrix[i] = malloc(sizeof(int) * graph->vertices);
		for (int j = 0; j < graph->vertices; ++j)
		{
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

void PrintGraph(Graph* graph)
{
	printf("vertices = %d，edges = %d\n", graph->vertices, graph->edges);
	for (int i = 0; i < graph->vertices; ++i)
	{
		for (int j = 0; j < graph->vertices; ++j)
		{
			printf("%d ", graph->adjacency_matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	Graph* graph = CreateGraph();
	PrintGraph(graph);
}