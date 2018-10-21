#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#define MAX_NAME 100

int main()
{
	char command[MAX_NAME], name[MAX_NAME];
	int val;

	head = NULL;

	while (1)
	{
		scanf("%s", command);
		if (strcmp(command, "wypisz") == 0)
		{
			scanf(" %d", &val);
			print(val);
		}
		else if (strcmp(command, "zjedz") == 0)
		{
			scanf(" %s %d", name, &val);
			eat(name, val);
		}
		else if (strcmp(command, "utworz") == 0)
		{
			scanf(" %s", name);
			create(name);
		}
		else if (strcmp(command, "zapisz") == 0)
		{
			scanf(" %s", name);
			save(name);
		}
		else if (strcmp(command, "wczytaj") == 0)
		{
			scanf(" %s", name);
			read(name);
		}
		else if (strcmp(command, "wyjdz") == 0)
		{
			clear();
			return 0;
		}
		else if (strcmp(command, "help") == 0)
		{
			printf("Dostepne komendy:\n");
			printf("> wypisz 0 - wypisuje zawartosc tacki bez ciasteczek\n");
			printf("> wypisz 1 - wypisuje zawartosc tacki z ciasteczkami\n");
			printf("> utworz nazwa - tworzy nowy stosik ciastek o nazwie: nazwa\n");
			printf("> zjedz nazwa x - probuje zjesc x ciastek ze stosiku o nazwie: nazwa\n");
			printf("> zapisz nazwa - zapisuje zawartosc tacki do pliku o nazwie: nazwa\n");
			printf("> wczytaj nazwa - wczytuje zawartosc tacki z pliku o nazwie: nazwa\n");
			printf("> wyjdz - wychodzi z programu\n");
		}
		else
		{
			printf("Nie ma takiej komendy. Wpisz help aby dostac pomoc\n");
		}
	}

	return 0;
}
