#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 10

typedef struct
{
	int valor;
	int vetor[MAX];
} LISTA;

void iniciar_lista (LISTA*);
int lista_cheia (LISTA*);
void inserir (LISTA*);
void remover (LISTA*);
int lista_vazia (LISTA*);
void imprimir_lista (LISTA*);

int main ()
{
	setlocale(LC_ALL,"");
	LISTA *l = (LISTA*)malloc(sizeof(LISTA));
	iniciar_lista(l);
	int op;
	
	do
	{
		system("cls");
		printf("------------------- M E N U -------------------\n\n");
		printf("1 - Inserir\n");
		printf("2 - Remover\n");
		printf("3 - Imprimir lista\n");
		printf("0 - Sair\n\n");
		scanf("%i", &op);
		
		switch(op)
		{
			
			case 1: inserir(l);
					break;
		
			case 2: remover(l);
					break;
		
			case 3: imprimir_lista(l);
					system("pause");
					break;
		}
	}while (op != 0);
	
	
}

void iniciar_lista (LISTA *l)
{
	l->valor = -1;
}

int lista_cheia (LISTA *l)
{
	if (l->valor == MAX-2)
		return 1;
	else
		return 0;	
}

void inserir (LISTA *l)
{
	system("cls");
	int a, c, b, i;

	if (lista_cheia(l) == 1)
	{
		printf("\n\nNão é possível inserir - lista cheia!\n\n");
		system("pause");
	}
	else if (lista_vazia(l) == 1)
	{
		printf("Lista vazia, informe o primeiro valor a ser inserido: ");
		scanf("%i", &a);
		l->valor++;
		l->vetor[l->valor] = a;
		printf("\n\nNúmero %i inserido na lista.\n\n", a);
		system("pause");
	}
	
	else
	{
		
		printf("\n\nInformar o valor a ser colocado na lista: ");
		scanf("%i", &a);
		l->valor = l->valor+1;
		b=l->valor;
		l->vetor[l->valor] = 0;
		
		for(i = 0; i<=l->valor; i++)
		{
			if(a<l->vetor[i])
				b = i;
		}
		
				
		for (c=l->valor; c>b; c--)
				l->vetor[c]=l->vetor[c-1];
				
		l->vetor[b] = a;
				
			
			
		printf("\n\nNúmero %i inserido na lista.\n\n", a);
		system("pause");
	}
}

int lista_vazia (LISTA *l)
{
	if (l->valor < 0)
		return 1;
	else
		return 0;	
}

void remover (LISTA *l)
{
	int i, a;
	if (lista_vazia(l) == 1)
	{
		printf("\n\nNão é possível remover, lista vazia!");
		printf("\n\n");
		system("pause");
	}
	else
	{
		printf("\nInforme a posição do valor a ser removido:\n\nPosição\n");
		for(i=0;i<=l->valor;i++)
			printf("0%i  ", i+1);
		printf("\n");	
		for (i = 0; i <= l->valor; i++)
			printf("%i  ", l->vetor[i]);
		printf("\nValor\n\n");
		printf("\n\n");	
		scanf("%i", &a);
		for(i=a-1; i<l->valor;i++)
			l->vetor[i] = l->vetor[i+1];
		l->valor--;
		printf("\n\nValor removido com sucesso!\n\n");
		system("pause");
	}
}

void imprimir_lista (LISTA *l)
{
	system("cls");
	int i;
	for (i = 0; i <= l->valor; i++)
		printf("%i  ", l->vetor[i]);
	printf("\nValor\n\n");
	printf("\n\n");	
}
