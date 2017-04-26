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
	if (list->head == NULL) { printf("Нельзя удалить элементы из пустого списка!\n");return; }

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
	printf("Элемент со значением %i был удален!\n", tmp);
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
		printf("Нельзя удалить элементы из пустого списка!\n"); return;
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
	printf("Элемент со значением %i был удален!\n", tmp);
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
		printf("Вы ввели число больше, чем элементов в списке, поэтому я вставил элемент %i в конец!\n", value);
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
	printf("Элемент %i был вставлен на позицию %i\n", value, index);
}

void deleteNth(DblLinkedList *list, size_t index) {
	Node *elm = NULL;
	void *tmp = NULL;
	elm = getNth(list, index-1);
	if (elm == NULL) {
		printf("В списке нет элемента с таким номером!\n");
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
	printf("Элемент под номером %i был удален!\n", index);
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
	printf("Команды для работы:\n");
	printf("1 - Добавить элемент впереди списка\n");
	printf("2 - Удалить элемент впереди списка\n");
	printf("3 - Добавить элемент сзади списка\n");
	printf("4 - Удалить элемент сзади списка\n");
	printf("5 - Добавить элемент на n-ую позицию\n");
	printf("6 - Удалить элемент на n-ой позиции\n");
	printf("7 - Напечатать список\n");
	printf("8 - Напечатать n-ый элемент списка\n");
	printf("9 - Элементы, которые больше своего номера, записываются в новый список\n");
	printf("10 - Удалить список и завершить программу\n");
	printf("//////////////////////////////////////\n");
	printf("Выберите одну из команд: ");
}

int main()
{
	setlocale(LC_ALL, "rus");
	DblLinkedList *list=NULL;
	unsigned int n;
	int k=-1;
	int *m;
	int *znach;
	printf("Для начала работы нужно создать список, введите 0 что бы создать его\n");
	while (k != 0)
	{
		scanf("%i", &k);
		switch (k)
		{
		case 0:
			list = createList();
			printf("Список создан\n");
			while (k != 10)
			{
				menu();
				scanf("%i", &k);
				switch (k)
				{
				case 1: //add elements (front)
					printf("Введите количество эл-тов, которые хотите добавить в список впереди: ");
					scanf("%i", &n); // Количество эл-тов в списке
					for (unsigned int i = 0; i < n; i++)
					{
						printf("Введите значение %i элемента ", i);
						scanf_s("%i", &znach);
						pushFront(list, znach);
					}
					
					break;
				case 2: //del element (front)
					popFront(list);
					
					break;
				case 3: //add elements (back)
					printf("Введите количество эл-тов, которые хотите добавить в список сзади: ");
					scanf("%i", &n); // Количество эл-тов в списке
					for (unsigned int i = 0; i < n; i++)
					{
						printf("Введите значение %i элемента", i);
						scanf_s("%i", &znach);
						pushBack(list, znach);
					}
					
					break;
				case 4: //del element (back)
					popBack(list);
					
					break;
				case 5: //add element (nth position)
					printf("Введите номер позиции, куда хотите вставить элемент: ");
					scanf("%i", &n);
					printf("Введите значение элемента: ");
					scanf("%i", &m);
					insert(list, n, m);
					
					break;
				case 6: //del element (nth position)
					printf("Введите номер элемента, который хотите удалить: ");
					scanf("%i", &n);
					deleteNth(list, n);
					
					break;
				case 7:
					printf("Список: ");
					printDblLinkedList(list);
					
					break;
				case 8:
					printf("Введите номер элемента, который хотите увидеть: ");
					scanf("%i", &n);
					if (getNth(list, n - 1))
						printf("%i\n", getNth(list, n-1)->value);
					else printf("В списке нет элемента с таким номером!\n");
					
					break;
				case 9:
					DblLinkedList *list1;
					list1 = createList();
					MyFunc(list, list1, list->size);
					printf("Новый список: ");
					printDblLinkedList(list1);
					deleteDblLinkedList(&list1);
					
					break;
				case 10: //del list
					deleteDblLinkedList(&list);
					printf("Список удален!");
					Sleep(1000);
					exit(0);
				default:
					printf("Не существует такой команды, попробуйте еще раз!");
					break;
				}
			}
			break;
		case 424:
			exit(0);
		default:
			printf("Введите 0, что бы создать список или 424 что бы завершить работу!\n");
			break;
		}
	}
	system("pause");
	return 0;
}