#include "lyz.h"

typedef int ElementType;

typedef struct Node
{
	ElementType data;
	struct Node* next;
} Node;

typedef struct LinkedList
{
	int size;
	Node* first;
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
	return linked_list;
}

Node* CreateNode(ElementType data)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

Node* GetNode(LinkedList* linked_list, int index)
{
	Node* node = linked_list->first;
	for (int i = 0; i < index; ++i)
	{
		node = node->next;
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
	if (index == 0)                                     // ��ͷ������Ԫ��
	{
		if (linked_list->size == 0)                     // ��ǰ����Ϊ�գ���ӵ��ǵ�һ���ڵ�
		{
			linked_list->first = new_node;              // ʹ�½ڵ��Ϊ�����ͷ�ڵ�
		}
		else                                            // ��ǰ����Ϊ��
		{
			Node* first_node = linked_list->first;           // 1. �ҵ���һ���ڵ�
			new_node->next = first_node;                     // 2. ʹ�½ڵ�ָ���һ���ڵ�
			linked_list->first = new_node;                   // 3. ʹ�½ڵ��Ϊ�����ͷ�ڵ�
		}
	}
	else                                                // ���м��β������Ԫ��
	{
		Node* previous_node = GetNode(linked_list, index - 1); // 1. �ҵ�����λ�õ�ǰһ���ڵ�
		new_node->next = previous_node->next;                  // 2. ���½ڵ�ָ��ǰһ���ڵ�ָ��Ľڵ�
		previous_node->next = new_node;                        // 3. ��ǰһ���ڵ�ָ���½ڵ�
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
	if (index == 0)
	{
		to_delete_node = linked_list->first;                     // 1. ����ɾ���ڵ�ָ��ָ������ͷ�ڵ�
		linked_list->first = to_delete_node->next;               // 2. ������ͷ�ڵ�ָ��ָ���ɾ���ڵ����һ���ڵ�
	}
	else
	{
		Node* previous_node = GetNode(linked_list, index - 1);   // 1. �ҵ�ɾ��λ�õ�ǰһ���ڵ�
		to_delete_node = previous_node->next;                    // 2. �ҵ�Ҫɾ���Ľڵ�
		previous_node->next = to_delete_node->next;              // 3. ��ɾ��λ�õ�ǰһ���ڵ�ָ���ɾ���ڵ�ָ��Ľڵ�
	}
	free(to_delete_node);                                        // �ͷ��ڴ�
	linked_list->size--;                                         // ������ - 1
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
	pf(d, IndexOf(linked_list, 40));
	pl();
	pf(d, Contains(linked_list, 35));
	pl();
	pf(d, Contains(linked_list, 60));
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