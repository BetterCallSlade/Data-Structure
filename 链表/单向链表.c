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
	if (index == 0)                                     // 在头部插入元素
	{
		if (linked_list->size == 0)                     // 当前链表为空，添加的是第一个节点
		{
			linked_list->first = new_node;              // 使新节点成为链表的头节点
		}
		else                                            // 当前链表不为空
		{
			Node* first_node = linked_list->first;           // 1. 找到第一个节点
			new_node->next = first_node;                     // 2. 使新节点指向第一个节点
			linked_list->first = new_node;                   // 3. 使新节点成为链表的头节点
		}
	}
	else                                                // 在中间和尾部插入元素
	{
		Node* previous_node = GetNode(linked_list, index - 1); // 1. 找到插入位置的前一个节点
		new_node->next = previous_node->next;                  // 2. 将新节点指向前一个节点指向的节点
		previous_node->next = new_node;                        // 3. 将前一个节点指向新节点
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
		to_delete_node = linked_list->first;                     // 1. 将待删除节点指针指向链表头节点
		linked_list->first = to_delete_node->next;               // 2. 将链表头节点指针指向待删除节点的下一个节点
	}
	else
	{
		Node* previous_node = GetNode(linked_list, index - 1);   // 1. 找到删除位置的前一个节点
		to_delete_node = previous_node->next;                    // 2. 找到要删除的节点
		previous_node->next = to_delete_node->next;              // 3. 将删除位置的前一个节点指向待删除节点指向的节点
	}
	free(to_delete_node);                                        // 释放内存
	linked_list->size--;                                         // 链表长度 - 1
}

void Clear_(Node* node, int times)
{
	if (times == 0)
	{
		return;
	}
	Clear_(node->next, --times);
	printf("删除节点：%d\n", node->next->data);
	free(node->next);
}

void Clear(LinkedList* linked_list)
{
	Clear_(linked_list->first, --linked_list->size);
	printf("删除节点：%d\n", linked_list->first->data);
	free(linked_list->first);
}

int main()
{
	LinkedList* linked_list = CreateLinkedList();

	pdelimiter("测试1：");
	Add(linked_list, CreateNode(10));
	Add(linked_list, CreateNode(20));
	Print(linked_list); // 10 20

	pdelimiter("测试2：");
	SetNodeData(linked_list, 1, 30);
	pf(d, GetNodeData(linked_list, 1)); // 30
	pl();

	pdelimiter("测试3：");
	Print(linked_list); // 10 30
	pl();
	Insert(linked_list, 1, CreateNode(40));
	Insert(linked_list, 0, CreateNode(20));
	Insert(linked_list, 4, CreateNode(60));
	Print(linked_list); // 20 10 40 30 60

	pdelimiter("测试4：");
	pf(d, IndexOf(linked_list, 40));
	pl();
	pf(d, Contains(linked_list, 35));
	pl();
	pf(d, Contains(linked_list, 60));
	pl();

	pdelimiter("测试5：");
	Remove(linked_list, 0); // 20
	Remove(linked_list, 1); // 40
	Remove(linked_list, linked_list->size - 1); // 60
	Print(linked_list); // 10 30

	pdelimiter("测试6：");
	Clear(linked_list); // 30 10
	pl();

	pf(d, 1);
}