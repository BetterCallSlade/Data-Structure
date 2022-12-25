#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node* next;
} node;

typedef struct {
	#define VERTICES 5
	int edges;
	node* adjacency_list[VERTICES];
} Graph;

node* create_node(int val)
{
	node* new_node = malloc(sizeof(node));
	new_node->val = val;
	new_node->next = NULL;
	return new_node;
}

Graph* create_undirected_unweighted_graph()
{
	Graph* graph = malloc(sizeof(Graph));
	scanf("%d", &graph->edges);
	for (int i = 0; i < VERTICES; i++)
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
			graph->adjacency_list[va] = create_node(vb);
		}
		else
		{
			node* node = graph->adjacency_list[va];
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = create_node(vb);
		}
		if (graph->adjacency_list[vb] == NULL)
		{
			graph->adjacency_list[vb] = create_node(va);
		}
		else
		{
			node* node = graph->adjacency_list[vb];
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = create_node(va);
		}
	}
	return graph;
}

void print_graph(Graph* graph)
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
	Graph* graph = create_undirected_unweighted_graph();
	print_graph(graph);
}