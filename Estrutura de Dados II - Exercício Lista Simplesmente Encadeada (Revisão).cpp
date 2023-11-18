#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct aux
{
	int key;
	struct aux* next;	
}LISTA;



void PrintList (LISTA*);
void InsertOrder (LISTA*, int);
void InsertFirst (LISTA*, int);
void InsertLast (LISTA*, int);
void RemoveFirst (LISTA*);
void RemoveLast (LISTA*);


main ()
{
	setlocale(LC_ALL, "");
	
	LISTA lista;
	lista.next = NULL;
	int newrec, inserir;
	
	printf("Inserção de elementos em ordem à lista(16, 2, 31, 18): \n\n");
	
	newrec = 16;
	InsertOrder(&lista, newrec);
	newrec = 2;
	InsertOrder(&lista, newrec);
	newrec = 31;
	InsertOrder(&lista, newrec);
	newrec = 18;
	InsertOrder(&lista, newrec);
	
	
	PrintList(&lista);
	
	printf("\n\n");
	
	printf("Informe um número para inserir no começo da lista: ");
	scanf("%i", &inserir);
	
	printf("\n\n");
	
	InsertFirst(&lista, inserir);
	
	
	
	printf("\n\n");
	
	PrintList(&lista);
	
	printf("\n\nInforme um número para inserir no final da lista: ");

	scanf("%i", &inserir);
	printf("\n\n");
	InsertLast (&lista, inserir);
	
	PrintList(&lista);
	printf("\n\n");
	
	printf("\n\nRemovendo o primeiro número da lista: ");
	printf("\n\n");
	RemoveFirst(&lista);
	PrintList(&lista);
	printf("\n\n");
	printf("\n\nRemovendo o último número da lista: ");
	printf("\n\n");
	RemoveLast(&lista);
	PrintList(&lista);
	printf("\n\n");
	
	system("pause");
	
	
	
}

void InsertOrder (LISTA *controle, int newrec)
{
	LISTA *entrada;
	LISTA *node;
	node = controle;
	entrada = (LISTA*)malloc(sizeof(LISTA));
	entrada->key = newrec;
	
	while (node->next != NULL && entrada->key > node->next->key)
		node = node->next;
		
	if (node->next == NULL)
		{
		node->next = entrada;
		entrada->next = NULL;
		}
	else
		{
		entrada->next = node->next;
		node->next = entrada;	
		}
	
}

void PrintList (LISTA *list)
{
	LISTA *node;
	node = list;
	
	while(node->next != NULL)
	{
		 printf(" %i", node->next->key);
		 node = node->next;
	}
}

void InsertFirst (LISTA *controle, int newrec)
{
	LISTA *entrada;
	LISTA *node;
	node = controle;
	entrada = (LISTA*)malloc(sizeof(LISTA));
	entrada->key = newrec;
	
	node = controle->next;
	controle->next = entrada;
	entrada->next = node;
		
}
	
void InsertLast (LISTA *controle, int newrec)
{
	LISTA *entrada;
	LISTA *node;
	node = controle;
	entrada = (LISTA*)malloc(sizeof(LISTA));
	entrada->key = newrec;
	
	while (node->next != NULL)
		node = node->next;
		

	node->next = entrada;
	entrada->next = NULL;
	
}	

void RemoveFirst (LISTA *controle)
{

	LISTA *node;
	node = controle;
	node=node->next;
	controle->next=node->next;
	free(node);	

		
}	


void RemoveLast (LISTA *controle)
{

	LISTA *node;
	LISTA *node2;
	node = controle;
	node2 = controle;
	while(node->next!=NULL)
		node=node->next;
	while(node2->next!=node)
		node2=node2->next;
	node2->next = NULL;	
	free(node);	

}	


	


