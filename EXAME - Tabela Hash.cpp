#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#define TAM 100


typedef struct produto
{
	char nome[50];
	int codigo;
	float preco;
	int chave; 
	struct produto *next;
} PRODUTO;

typedef struct lista
{
	produto *inicio;
	int tam;
} LISTA;

void inicializarTabela(LISTA[]);
int funcaoHash(int);
void inserir(LISTA[], char*, float, int);
int busca(LISTA[], int);
void imprimir (LISTA[]);
void inicializarLista(LISTA*);
void inserirLista (LISTA*, char*, float, int);	
int buscarLista (LISTA*, int);
void imprimirLista(LISTA*);
void preencher(LISTA*);


int main()
{
	setlocale(LC_ALL, "");
	int opcao, codigo, retorno;
	char nome[50]; 
	float preco;
	LISTA tabela[TAM];
	inicializarTabela(tabela);
	
	do
	{
	    system("cls");
		printf("\n\t1 - Inserir Produto\n\t2 - Buscar\n\t3 - Imprimir\n\t0 - Sair\n\n\n\n");
		scanf("%i", &opcao);
		switch(opcao)
		{
			case 1:
				printf("\t\nQual o nome do produto que deseja inserir: ");
				scanf("%s", nome);
				printf("\t\nInforme o preço do Produto que deseja inserir: ");
				scanf("%f", &preco);
				printf("\t\nInforme o código do produto: ");
				scanf("%i", &codigo);
				inserir(tabela, nome, preco, codigo);
				printf("Elemento inserido com sucesso!!");
				printf("\n\n\n");
				system("pause");
				break;
			case 2:
				printf("\tQual valor deseja buscar? ");
				scanf("%i", &codigo);
				retorno = busca(tabela, codigo);
				//if(retorno!=0)
				//	printf("\tValor encontrado: %i\n", retorno);
				if(retorno==0)
					printf("\tValor não encontrado\n");
					
				printf("\n\n\n");
				system("pause");
				
				break;
			case 3:
				imprimir(tabela);
				printf("\n\n\n");
				system("pause");
				break;
			case 4:
				preencher(tabela);
				printf("\n\n\n");
				system("pause");
				break;	
			default:
				
				
				printf("Opção inválida");
				printf("\n\n\n");
				system("pause");			
		}
		
	
	
	
	}while(opcao != 0);
	
	
	return 0;
}


void inicializarTabela(LISTA t[])
{
	int i;
	for(i=0;i<TAM;i++)
		inicializarLista(&t[i]);
}

int funcaoHash(int codigo)
{
	return codigo%TAM;
}

void inserir(LISTA t[], char nome[], float preco, int codigo)
{
	int id = funcaoHash(codigo);
	inserirLista(&t[id], nome, preco, codigo);
}

int busca(LISTA t[], int codigo)
{
	int id = funcaoHash(codigo);
	printf("\n\nÍndice gerado: %i\n", id);
		
	return buscarLista(&t[id], codigo);		 
}

void imprimir (LISTA t[])
{
	int i;
	for(i=0;i<TAM;i++)
	{
		printf("%2d = ", i);
		imprimirLista(&t[i]);
		printf("\n");
	}
}

void inicializarLista(LISTA *l)
{
	l->inicio = NULL;
	l->tam = 0;
}

void inserirLista (LISTA *l, char nome[], float preco, int codigo)
{
	PRODUTO *novo = (PRODUTO*)malloc(sizeof(PRODUTO));
	if(novo)
	{
		novo->codigo = codigo;
		novo->next = l->inicio;
		strcpy(novo->nome,nome);
		novo->preco = preco;
		l->inicio = novo;
		l->tam++;
	}
	else
		printf("\n\n\tErro ao alocar memória!!");
}

int buscarLista (LISTA *l, int codigo)
{
	PRODUTO *aux = l->inicio;
	while(aux && aux->codigo != codigo)
		aux = aux->next;
	if(aux != NULL)
	{
		printf("Produto encontrado!\n\nNome: %s\nPreço: %.2f\nCódigo: %i", aux->nome, aux->preco, aux->codigo);
	    return aux->codigo;
	}
	return 0;		
}

void imprimirLista(LISTA *l)
{
	PRODUTO *aux = l->inicio;
	printf("Tam: %i: ", l->tam);
	while(aux)
	{
		printf("%i  ", aux->codigo);
		aux=aux->next;
	}
}

void preencher (LISTA *l)
{
	inserir(l, "biscoito", 2.50, 5843);
	inserir(l, "bolacha", 3.50, 3321);
	inserir(l, "arroz", 5.50, 1257);
	inserir(l, "feijão", 6.00, 8523);
	inserir(l, "cereal", 0.50, 9632);
	inserir(l, "iogurte", 3.70, 9835);
	inserir(l, "manteiga", 11.50, 9647);
	inserir(l, "requeijão", 9.50, 6254);
	inserir(l, "cigarro", 13.50, 8126);
	inserir(l, "maçã", 1.75, 2785);
	inserir(l, "banana", 2.36, 3651);
	inserir(l, "trigo", 1.90, 3651);
	
}
