#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct root
{
	int num;
	struct root* direita;
	struct root* esquerda;
} RAIZ; 

RAIZ* inserir (RAIZ*, int);
RAIZ* criar (int);
void preordem (RAIZ*);
void emordem (RAIZ*);
void posordem (RAIZ*);

main ()
{
	RAIZ *main = NULL;
	int num, op;
	setlocale(LC_ALL,"");
	
	do
	{
		system("cls");
		printf("------------------- M E N U -------------------\n\n");
		printf("1 - Inserir Elemento na �rvore\n");
		printf("2 - Exibir elementos em pr�-ordem\n");
		printf("3 - Exibir elementos em ordem\n");
		printf("4 - Exibir elementos em p�s-ordem\n");
		printf("0 - Sair\n\n");
		scanf("%i", &op);
		
		switch(op)
		{
			
			case 1: printf("Informe o n�mero que deseja inserir na �rvore: ");
					scanf("%i", &num);
					main = inserir(main, num);
					break;
		
			case 2: printf("Exibindo elementos da �rvore em Pr�-Ordem:\n\n");
					preordem (main);
					printf("\n\n");
					system("pause");
					break;
		
			case 3: printf("Exibindo elementos da �rvore em Ordem:\n\n");
					emordem (main);
					printf("\n\n");
					system("pause");
					break;
					
			case 4: printf("Exibindo elementos da �rvore em P�s-Ordem:\n\n");
					posordem (main);
					printf("\n\n");
					system("pause");
					break;
		}
	}while (op != 0);
	
	
	return 0;
}

RAIZ* inserir(RAIZ *r, int num)
{
	system("cls");
	if(r == NULL)
	{
		r = criar(num);
		return r;
	}
	else if (r->esquerda == NULL || r->esquerda->num <= num)
		r->esquerda = inserir(r->esquerda, num);
	else
		r->direita = inserir(r->direita, num);
	return r;		
}


RAIZ* criar(int num)
{
	RAIZ *r = (RAIZ*)malloc(sizeof(RAIZ));
	r->num = num;
	r->esquerda = NULL;
	r->direita = NULL;
	return r;
}

void preordem (RAIZ *r)
{
	if(r!=NULL)
	{
		printf("%i ", r->num);
		preordem(r->esquerda);
		preordem(r->direita);
	}
}

void emordem (RAIZ *r)
{
	if(r!=NULL)
	{
		emordem(r->esquerda);
		printf("%i ", r->num);
		emordem(r->direita);
	}
}

void posordem (RAIZ *r)
{
	if(r!=NULL)
	{
		posordem(r->esquerda);
		posordem(r->direita);
		printf("%i ", r->num);
	}
}
