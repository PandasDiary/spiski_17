#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#define NULL 0

typedef struct _Node
{
	int *value;
	struct _Node *next;
	struct _Node *prev;
} Node;

typedef struct _DblLinkedList
{
	size_t size;
	Node *head;
	Node *tail;
} DblLinkedList;

void pushFront(DblLinkedList *list, int *data) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(1);
	}
	tmp->value = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) {
		list->tail = tmp;
	}
	list->size++;
}

void popFront(DblLinkedList *list) {
	Node *prev;
	void *tmp;
	if (list->head == NULL) { printf("������ ������� �������� �� ������� ������!\n");return; }

	prev = list->head;
	list->head = list->head->next;
	if (list->head) { list->head->prev = NULL; }
	if (prev == list->tail)
	{
		list->tail = NULL;
	}
	tmp = prev->value;
	free(prev);

	list->size--;
	printf("������� �� ��������� %i ��� ������!\n", tmp);
	return;
}

void pushBack(DblLinkedList *list, int *value) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}

void popBack(DblLinkedList *list) {
	Node *next;
	void *tmp;
	if (list->tail == NULL) {
		printf("������ ������� �������� �� ������� ������!\n"); return;
	}

	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail) {
		list->tail->next = NULL;
	}
	if (next == list->head) {
		list->head = NULL;
	}
	tmp = next->value;
	free(next);

	list->size--;
	printf("������� �� ��������� %i ��� ������!\n", tmp);
	return;
}

Node* getNth(DblLinkedList *list, size_t index) {
	Node *tmp = list->head;
	size_t i = 0;

	while (tmp && (i < index)) {
		tmp = tmp->next;
		i++;
	}

	return tmp;
}

void printDblLinkedList(DblLinkedList *list) {
	Node *tmp = list->head;
	while (tmp) {
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}
void insert(DblLinkedList *list, size_t index, int *value) {
	Node *elm = NULL;
	Node *ins = NULL;
	elm = getNth(list, index-2);
	if (elm == NULL) {
		pushBack(list, value);
		printf("�� ����� ����� ������, ��� ��������� � ������, ������� � ������� ������� %i � �����!\n", value);
		return;
	}
	ins = (Node*)malloc(sizeof(Node));
	ins->value = value;
	ins->prev = elm;
	ins->next = elm->next;
	if (elm->next) {
		elm->next->prev = ins;
	}
	elm->next = ins;

	if (!elm->prev) {
		list->head = elm;
	}
	if (!elm->next) {
		list->tail = elm;
	}

	list->size++;
	printf("������� %i ��� �������� �� ������� %i\n", value, index);
}

void deleteNth(DblLinkedList *list, size_t index) {
	Node *elm = NULL;
	void *tmp = NULL;
	elm = getNth(list, index-1);
	if (elm == NULL) {
		printf("� ������ ��� �������� � ����� �������!\n");
		return;
	}
	if (elm->prev) {
		elm->prev->next = elm->next;
	}
	if (elm->next) {
		elm->next->prev = elm->prev;
	}
	tmp = elm->value;

	if (!elm->prev) {
		list->head = elm->next;
	}
	if (!elm->next) {
		list->tail = elm->prev;
	}

	free(elm);

	list->size--;
	printf("������� ��� ������� %i ��� ������!\n", index);
	return;
}

_DblLinkedList* createList() {
	_DblLinkedList*list = (_DblLinkedList*)malloc(sizeof(_DblLinkedList));

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}


void deleteDblLinkedList(DblLinkedList **list) {
	Node *tmp = (*list)->head;
	Node *next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

void MyFunc(DblLinkedList *list, DblLinkedList *list1, int sizelist)
{
	for (int i = 0; i < sizelist; i++)
	{

		if (i < int((getNth(list, i)->value)))
		{
			pushBack(list1, getNth(list, i)->value);
		}
	}
}

void menu()
{	
	printf("//////////////////////////////////////\n");
	printf("������� ��� ������:\n");
	printf("1 - �������� ������� ������� ������\n");
	printf("2 - ������� ������� ������� ������\n");
	printf("3 - �������� ������� ����� ������\n");
	printf("4 - ������� ������� ����� ������\n");
	printf("5 - �������� ������� �� n-�� �������\n");
	printf("6 - ������� ������� �� n-�� �������\n");
	printf("7 - ���������� ������\n");
	printf("8 - ���������� n-�� ������� ������\n");
	printf("9 - ��������, ������� ������ ������ ������, ������������ � ����� ������\n");
	printf("10 - ������� ������ � ��������� ���������\n");
	printf("//////////////////////////////////////\n");
	printf("�������� ���� �� ������: ");
}

int main()
{
	setlocale(LC_ALL, "rus");
	DblLinkedList *list=NULL;
	unsigned int n;
	int k=-1;
	int *m;
	int *znach;
	printf("��� ������ ������ ����� ������� ������, ������� 0 ��� �� ������� ���\n");
	while (k != 0)
	{
		scanf("%i", &k);
		switch (k)
		{
		case 0:
			list = createList();
			printf("������ ������\n");
			while (k != 10)
			{
				menu();
				scanf("%i", &k);
				switch (k)
				{
				case 1: //add elements (front)
					printf("������� ���������� ��-���, ������� ������ �������� � ������ �������: ");
					scanf("%i", &n); // ���������� ��-��� � ������
					for (unsigned int i = 0; i < n; i++)
					{
						printf("������� �������� %i �������� ", i);
						scanf_s("%i", &znach);
						pushFront(list, znach);
					}
					
					break;
				case 2: //del element (front)
					popFront(list);
					
					break;
				case 3: //add elements (back)
					printf("������� ���������� ��-���, ������� ������ �������� � ������ �����: ");
					scanf("%i", &n); // ���������� ��-��� � ������
					for (unsigned int i = 0; i < n; i++)
					{
						printf("������� �������� %i ��������", i);
						scanf_s("%i", &znach);
						pushBack(list, znach);
					}
					
					break;
				case 4: //del element (back)
					popBack(list);
					
					break;
				case 5: //add element (nth position)
					printf("������� ����� �������, ���� ������ �������� �������: ");
					scanf("%i", &n);
					printf("������� �������� ��������: ");
					scanf("%i", &m);
					insert(list, n, m);
					
					break;
				case 6: //del element (nth position)
					printf("������� ����� ��������, ������� ������ �������: ");
					scanf("%i", &n);
					deleteNth(list, n);
					
					break;
				case 7:
					printf("������: ");
					printDblLinkedList(list);
					
					break;
				case 8:
					printf("������� ����� ��������, ������� ������ �������: ");
					scanf("%i", &n);
					if (getNth(list, n - 1))
						printf("%i\n", getNth(list, n-1)->value);
					else printf("� ������ ��� �������� � ����� �������!\n");
					
					break;
				case 9:
					DblLinkedList *list1;
					list1 = createList();
					MyFunc(list, list1, list->size);
					printf("����� ������: ");
					printDblLinkedList(list1);
					deleteDblLinkedList(&list1);
					
					break;
				case 10: //del list
					deleteDblLinkedList(&list);
					printf("������ ������!");
					Sleep(1000);
					exit(0);
				default:
					printf("�� ���������� ����� �������, ���������� ��� ���!");
					break;
				}
			}
			break;
		case 424:
			exit(0);
		default:
			printf("������� 0, ��� �� ������� ������ ��� 424 ��� �� ��������� ������!\n");
			break;
		}
	}
	system("pause");
	return 0;
}