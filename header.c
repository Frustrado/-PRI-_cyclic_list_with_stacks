#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#define MAX_NAME 100

#define MIN_CAKES 5
#define MAX_CAKES 100

void addToStack(CakesStack* stack)
{
	CakesStackElement* newElement;
	newElement = (CakesStackElement*)malloc(sizeof(CakesStackElement));
	newElement->created = time(NULL);
	newElement->next = stack->topOfStack;
	stack->topOfStack = newElement;
	stack->count++;
}

void removeFromStack(CakesStack* stack)
{
	CakesStackElement* deleteElement;
	deleteElement = stack->topOfStack;
	stack->topOfStack = deleteElement->next;
	free(deleteElement);
	stack->count--;
}

void refill(CakesStack* iter)
{
	int add, i;

	if (iter->count < MIN_CAKES)
	{
		printf("Liczba ciastek na stosie o nazwie %s wynosi %d\n", iter->name, iter->count);
		add = rand() % (MAX_CAKES - iter->count + 1);

		for (i = 0; i < add; i++)
		{
			addToStack(iter);
		}

		printf("Dodano %d sztuk\n", add);
	}
}

void create(char* name)
{
	CakesStack *iter, *next;

	if (head == NULL)
	{
		head = (CakesStack*)malloc(sizeof(CakesStack));
		strcpy(head->name, name);
		head->count = 0;
		head->next = head;
		head->topOfStack = NULL;
		refill(head);
		return;
	}

	iter = head;
	while (iter->next != head && (strcmp(iter->next->name, name) <= 0 || strcmp(iter->name, name) > 0))
	{
		iter = iter->next;
	}

	if (strcmp(iter->name, name) == 0)
	{
		printf("Stos ciastek o nazwie: %s istnieje\n", name);
		return;
	}

	next = iter->next;
	iter->next = (CakesStack*)malloc(sizeof(CakesStack));
	strcpy(iter->next->name, name);
	iter->next->topOfStack = NULL;
	iter->next->count = 0;
	iter->next->next = next;

	refill(iter->next);

	if (strcmp(head->name, name) > 0)
	{
		head = iter->next;
	}

}

void eat(char* name, int count)
{
	CakesStack *iter;
	int i;

	if (head == NULL)
	{
		printf("Stolik jest pusty\n");
		return;
	}

	iter = head;

	while (iter->next != head && strcmp(iter->name, name) < 0)
	{
		iter = iter->next;
	}

	if (strcmp(iter->name, name) != 0)
	{
		printf("Stos ciastek o nazwie %s nie istnieje\n", name);
		return;
	}

	if (iter->count < count)
	{
		printf("Brakuje ciastek na stosie o nazwie: %s\n", iter->name);
		return;
	}

	for (i = 0; i < count; i++)
	{
		removeFromStack(iter);
	}

	refill(iter);
}



void print(int val)
{
	CakesStack *iter;
	CakesStackElement *element;
	char buff[100];

	if (head == NULL)
	{
		printf("Stolik jest pusty\n");
		return;
	}

	iter = head;

	printf("Stolik zawiera:\n");

	do
	{
		printf("%s %d\n", iter->name, iter->count);
		if (val == 1)
		{
			for (element = iter->topOfStack; element != NULL; element = element->next)
			{
				strftime(buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime(&element->created));
				printf("-> %s\n", buff);
			}



		}
		iter = iter->next;
	}

	while (iter != head);

}

void clear()
{
	CakesStack *iter, *next;
	CakesStackElement *element;
	if (head == NULL)
	{
		return;
	}

	iter = head;

	do
	{
		next = iter->next;

		while (iter->topOfStack != NULL)
		{
			element = iter->topOfStack->next;
			free(iter->topOfStack);
			iter->topOfStack = element;
		}

		free((void*)iter);
		iter = next;
	} while (iter != head);

	head = NULL;
}

void save(char* name)
{
	CakesStack *iter;
	CakesStackElement *iterElement;
	FILE *handle;
	handle = fopen(name, "wb");
	if (head != NULL)
	{
		iter = head;
		do
		{
			fwrite(iter, sizeof(CakesStack), 1, handle);

			for (iterElement = iter->topOfStack; iterElement != NULL; iterElement = iterElement->next)
			{
				fwrite(iterElement, sizeof(CakesStackElement), 1, handle);
			}

			iter = iter->next;
		} while (iter != head);
	}

	fclose(handle);
}

void read(char* name)
{
	CakesStack *iter, *next;
	CakesStackElement* element;
	FILE *handle;
	int i;
	handle = fopen(name, "rb");
	clear();
	iter = NULL;
	next = (CakesStack*)malloc(sizeof(CakesStack));
	while (fread(next, sizeof(CakesStack), 1, handle) > 0)
	{
		next->topOfStack = NULL;
		if (next->count > 0)
		{
			fseek(handle, (next->count - 1) * sizeof(CakesStackElement), SEEK_CUR);
			for (i = 0; i < next->count; i++)
			{
				element = (CakesStackElement*)malloc(sizeof(CakesStackElement));
				fread(element, sizeof(CakesStackElement), 1, handle);
				element->next = next->topOfStack;
				next->topOfStack = element;
				fseek(handle, (i < next->count - 1 ? -2 : -1) * sizeof(CakesStackElement), SEEK_CUR);
			}

			fseek(handle, next->count * sizeof(CakesStackElement), SEEK_CUR);
		}

		if (iter == NULL)
		{
			iter = next;
			head = next;
		}
		else
		{
			iter->next = next;
			iter = next;
		}

		next = (CakesStack*)malloc(sizeof(CakesStack));
	}

	free(next);

	if (head != NULL)
	{
		iter->next = head;
	}

	fclose(handle);
}
