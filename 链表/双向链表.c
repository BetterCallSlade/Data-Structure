#include "lyz.h"

typedef int ElementType;

typedef struct Node
{
	ElementType data;
	struct Node* prev;
	struct Node* next;
} Node;

typedef struct LinkedList
{
	int size;
	Node* first;
	Node* last;
} LinkedList;

LinkedList* CreateLinkedList();
Node* CreateNode(ElementType data);
Node* GetNode(LinkedList* linked_list, int index);
void Add(LinkedList* linked_list, Node* new_node);
void Print(LinkedList* linked_list);
void SetNodeData(LinkedList* linked_list, int index, ElementType data);
ElementType GetNodeData(LinkedList* linked_list, int index);
void Insert(LinkedList* linked_list, int index, Node* new_node);
int IndexOf(LinkedList* linked_list, ElementType data);
bool Contains(LinkedList* linked_list, ElementType data);
void Remove(LinkedList* linked_list, int index);
void Clear_(Node* node, int times);
void Clear(LinkedList* linked_list);

LinkedList* CreateLinkedList()
{
	LinkedList* linked_list = malloc(sizeof(LinkedList));
	linked_list->size = 0;
	linked_list->first = NULL;
	linked_list->last = NULL;
	return linked_list;
}

Node* CreateNode(ElementType data)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

Node* GetNode(LinkedList* linked_list, int index)
{
	Node* node;
	if (index < (linked_list->size / 2)) // ��ǰ������
	{
		node = linked_list->first;
		for (int i = 0; i < index; ++i)
		{
			node = node->next;
		}
	}
	else                                 // �Ӻ���ǰ��
	{
		node = linked_list->last;
		for (int i = linked_list->size - 1; i > index; --i)
		{
			node = node->prev;
		}
	}
	return node;
}

void Add(LinkedList* linked_list, Node* new_node)
{
	Insert(linked_list, linked_list->size, new_node);
}

void Print(LinkedList* linked_list)
{
	Node* node = linked_list->first;
	for (int i = 0; i < linked_list->size; ++i, node = node->next)
	{
		pf(d, node->data);
		pl();
	}
}

void SetNodeData(LinkedList* linked_list, int index, ElementType data)
{
	Node* node = GetNode(linked_list, index);
	node->data = data;
}

ElementType GetNodeData(LinkedList* linked_list, int index)
{
	Node* node = GetNode(linked_list, index);
	return node->data;
}

void Insert(LinkedList* linked_list, int index, Node* new_node)
{
	if (index == 0)                     // �������ͷ������
	{
		if (linked_list->size == 0)         // ��ǰ����Ϊ�գ�������ǵ�һ���ڵ�
		{
			linked_list->first = new_node;
			linked_list->last = new_node;
		}
		else                                // ��ǰ����ǿ�
		{
			linked_list->first->prev = new_node;
			new_node->next = linked_list->first;
			linked_list->first = new_node;
		}
	}
	else
	{
		if (index == linked_list->size) // �������β������
		{
			new_node->prev = linked_list->last;
			linked_list->last->next = new_node;
			linked_list->last = new_node;
		}
		else                            // ��������м����
		{
			Node* next_node = GetNode(linked_list, index);
			Node* prev_node = next_node->prev;
			new_node->next = next_node;
			new_node->prev = prev_node;
			next_node->prev = new_node;
			prev_node->next = new_node;
		}
	}
	linked_list->size++;
}

int IndexOf(LinkedList* linked_list, ElementType data)
{
	Node* node = linked_list->first;
	for (int i = 0; i < linked_list->size; ++i, node = node->next)
	{
		if (node->data == data)
		{
			return i;
		}
	}
	return -1;
}

bool Contains(LinkedList* linked_list, ElementType data)
{
	return IndexOf(linked_list, data) == -1 ? false : true;
}

void Remove(LinkedList* linked_list, int index)
{
	Node* to_delete_node;
	if (index == 0)                         // ɾ����һ�����
	{
		to_delete_node = linked_list->first;
		Node* next_node = to_delete_node->next;
		next_node->prev = NULL;
		linked_list->first = next_node;
	}
	else
	{
		if (index == linked_list->size - 1) // ɾ�����һ���ڵ�
		{
			to_delete_node = linked_list->last;
			Node* prev_node = to_delete_node->prev;
			prev_node->next = NULL;
			linked_list->last = prev_node;
		}
		else                                // ɾ�������м�Ľڵ�
		{
			to_delete_node = GetNode(linked_list, index);
			Node* prev_node = to_delete_node->prev;
			Node* next_node = to_delete_node->next;
			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	free(to_delete_node);
	linked_list->size--;
}

void Clear_(Node* node, int times)
{
	if (times == 0)
	{
		return;
	}
	Clear_(node->next, --times);
	printf("ɾ���ڵ㣺%d\n", node->next->data);
	free(node->next);
}

void Clear(LinkedList* linked_list)
{
	Clear_(linked_list->first, --linked_list->size);
	printf("ɾ���ڵ㣺%d\n", linked_list->first->data);
	free(linked_list->first);
}

int main()
{
	LinkedList* linked_list = CreateLinkedList();

	pdelimiter("����1��");
	Add(linked_list, CreateNode(10));
	Add(linked_list, CreateNode(20));
	Print(linked_list); // 10 20

	pdelimiter("����2��");
	SetNodeData(linked_list, 1, 30);
	pf(d, GetNodeData(linked_list, 1)); // 30
	pl();

	pdelimiter("����3��");
	Print(linked_list); // 10 30
	pl();
	Insert(linked_list, 1, CreateNode(40));
	Insert(linked_list, 0, CreateNode(20));
	Insert(linked_list, 4, CreateNode(60));
	Print(linked_list); // 20 10 40 30 60

	pdelimiter("����4��");
	pf(d, IndexOf(linked_list, 40)); // 2
	pl();
	pf(d, Contains(linked_list, 35)); // 0
	pl();
	pf(d, Contains(linked_list, 60)); // 1
	pl();

	pdelimiter("����5��");
	Remove(linked_list, 0); // 20
	Remove(linked_list, 1); // 40
	Remove(linked_list, linked_list->size - 1); // 60
	Print(linked_list); // 10 30

	pdelimiter("����6��");
	Clear(linked_list); // 30 10
	pl();

	pf(d, 1);
}