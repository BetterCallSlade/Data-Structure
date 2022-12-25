#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node* next;
} node;

#define VERTICES 5

typedef struct {
	int edges;
	node* adjacency_list[VERTICES];
} Graph;

node* CreateNode(int val)
{
	node* new_node = malloc(sizeof(node));
	new_node->val = val;
	new_node->next = NULL;
	return new_node;
}

Graph* CreateGraph()
{
	Graph* graph = malloc(sizeof(Graph));
	scanf("%d", &graph->edges);
	for (int i = 0; i < VERTICES; ++i)
	{
		graph->adjacency_list[i] = NULL;
	}
	int va, vb;
	for (int i = 0; i < graph->edges; ++i)
	{
		scanf("%d", &va);
		scanf("%d", &vb);
		if (graph->adjacency_list[va] == NULL)
		{
			graph->adjacency_list[va] = CreateNode(vb);
		}
		else
		{
			node* node = graph->adjacency_list[va];
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = CreateNode(vb);
		}
		if (graph->adjacency_list[vb] == NULL)
		{
			graph->adjacency_list[vb] = CreateNode(va);
		}
		else
		{
			node* node = graph->adjacency_list[vb];
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = CreateNode(va);
		}
	}
	return graph;
}

void PrintGraph(Graph* graph)
{
	for (int i = 0; i < VERTICES; ++i)
	{
		node* node = graph->adjacency_list[i];
		while (node != NULL)
		{
			printf("%d ", node->val);
			node = node->next;
		}
		printf("\n");
	}
}

int main()
{
	Graph* graph = CreateGraph();
	PrintGraph(graph);
}