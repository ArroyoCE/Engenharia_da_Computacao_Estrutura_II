#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#define MAX 256


typedef struct no
{
    unsigned char letra;
    unsigned int frequencia;
    struct no *esquerda;
    struct no *direita;
    struct no *proximo;
}No;

typedef struct lista
{
    No *inicio;
    int tamanho;
}Lista;


void inicializa_tabela(unsigned int*);
void preenche_tabela(unsigned int*, unsigned char*);
void criar_lista (Lista*);
void ordenar_lista(Lista*, No*);
void preencher_lista(unsigned int*, Lista*);
No*  cria_arvore(Lista*);
No*  remove_lista(Lista*);
int altura_arvore (No*);
char** aloca_dicionario(int);
void gerar_dicionario(char**, No*, char*, int); 
char* codificar(char**, unsigned char*);
int tamanho_string(char**, unsigned char*);
char* decodificar(char*, No*);



void imprimir_dicionario (char**);
void imprimir_lista (Lista*);
void imprime_frequencia(unsigned int*);
void imprime_arvore(No*, int);



int main()
{
    setlocale(LC_ALL, "");
    
    
    unsigned char *texto = (unsigned char*)malloc(sizeof(unsigned char)*MAX);
    char *temp = (char*)malloc(sizeof(char)*MAX);
	unsigned int tabela_frequencia[MAX];
    Lista *lista;
    lista = (Lista*)malloc(sizeof(Lista));
    No *arvore;
    int altura;
    char **dicionario;
    char *codigo;
    char *decodificado;
  	char *g = (char*)malloc(sizeof(char));
  	float a, b;
    
    printf("Informe o texto que deseja codificar: ");
    fflush(stdin);
    //fgets(temp, 255, stdin);
    scanf("%[^'\n']", temp);
    texto = (unsigned char*)temp;
    system("cls");
    
    inicializa_tabela(tabela_frequencia);
    preenche_tabela(tabela_frequencia, texto);
    imprime_frequencia(tabela_frequencia);
    
    
    criar_lista(lista);
    preencher_lista(tabela_frequencia, lista);
    imprimir_lista(lista);
    

    arvore = cria_arvore(lista);
    printf("------------ÁRVORE------------\n\n");
    imprime_arvore(arvore, 0);
    
    
	altura = altura_arvore(arvore) + 1;
	dicionario = aloca_dicionario(altura);
    gerar_dicionario(dicionario, arvore, g, altura);
    imprimir_dicionario(dicionario);
    
    codigo = codificar(dicionario, texto);
    printf("\n\nTexto Codificado: \n %s \n\n", codigo);
    
    decodificado = decodificar(codigo, arvore);
    printf("\nTexto Decodificado:\n%s\n\n", decodificado);
    a = (float)strlen(decodificado);
    b = (float)strlen(codigo);
    printf("\nTAXA DE COMPRESSÃO: %.2f por cento\n\n", (1-b/(a*8))*100);

    system("pause");

    return 0;
}


void inicializa_tabela(unsigned int t[])
{
    int i;
    for (i = 0; i<MAX; i++)
            t[i] = 0;
}

void preenche_tabela(unsigned int t[], unsigned char text[])
{
    int i = 0;
    while (text[i] != '\0')
    {
        t[text[i]]++;
        i++;
    }
}

void criar_lista (Lista *l)
{
	
    l->inicio = NULL;
    l->tamanho = 0;
}

void ordenar_lista (Lista *l, No *n)
{
    

    if(l->inicio == NULL)
        l->inicio = n;
        
     
    else if (l->inicio->frequencia > n->frequencia)
    {
            n->proximo = l->inicio;
            l->inicio = n;
            
    }
    else
    {
    	No *aux;
        aux = l->inicio;
        while(aux->proximo != NULL && aux->proximo->frequencia < n->frequencia)
            aux = aux->proximo;
        n->proximo = aux->proximo;
        aux->proximo = n;
       
    }
    l->tamanho++;
}

void preencher_lista (unsigned int t[], Lista *l)
{
    int i;
    No *novo;
    for (i=0;i<MAX;i++)
        if(t[i] > 0)
        {
            novo = (No*)malloc(sizeof(No));
            novo->letra = i;
            novo->frequencia = t[i];
            novo->direita = NULL;
            novo->esquerda = NULL;
            novo->proximo = NULL;

            ordenar_lista(l, novo);
        }

}

No* cria_arvore (Lista *l)
{
    No *primeiro, *segundo, *novo;
    
    while(l->tamanho > 1)
    {
        primeiro = remove_lista(l);
        segundo = remove_lista(l);
        novo = (No*)malloc(sizeof(No));
        novo->letra = '+';
        novo->frequencia = primeiro->frequencia + segundo->frequencia;
        novo->esquerda = primeiro;
        novo->direita = segundo;
        novo->proximo = NULL;
        ordenar_lista(l, novo);
    }
    return l->inicio;
}

No* remove_lista(Lista *l)
{
    No *aux = NULL;
    
    aux = l->inicio;
    l->inicio = aux->proximo;
    aux->proximo = NULL;
    l->tamanho--;

    return aux;
}



int altura_arvore (No *n)
{
	int esq, dir;
	if (n==NULL)
		return -1;
	else
	{
		esq = altura_arvore(n->esquerda) + 1;
		dir = altura_arvore(n->direita) + 1;
	}
	
	if (esq>dir)
		return esq;
	else
		return dir;
}



char** aloca_dicionario (int altura)
{
	char **dicionario;
	int i;
	dicionario = (char**)malloc(sizeof(char*)*MAX);
	for(i=0; i<MAX;i++)
		dicionario[i] = (char*)calloc(altura, sizeof(char));
		
	return dicionario;	
	
}

void gerar_dicionario(char **dicionario, No *n, char *caminho, int altura)
{
	char *esquerda = (char*)malloc(sizeof(char)*altura); 
	char *direita = (char*)malloc(sizeof(char)*altura);
	

	if(n->esquerda == NULL && n->direita == NULL)
		strcpy(dicionario[n->letra], caminho);
		
	else
	{
		memcpy(esquerda, caminho, strlen(caminho) + 1);
		strcpy(direita, caminho);
		strcat(esquerda, "0");
		strcat(direita, "1");
		gerar_dicionario(dicionario, n->esquerda, esquerda, altura);
		gerar_dicionario(dicionario, n->direita, direita, altura);
			
	}	
}


char* codificar(char **dicionario, unsigned char *texto)
{
	int i = 0;
	char *codigo = (char*)calloc(tamanho_string(dicionario, texto), sizeof(char*));
	while(texto[i]!= '\0')
	{
		strcat(codigo, dicionario[texto[i]]);
		i++;
	}
	return codigo;
}

int tamanho_string (char **dicionario, unsigned char *texto)
{
	int i = 0, tam = 0;
	while(texto[i] != '\0')
	{
		tam = tam + strlen(dicionario[texto[i]]);
		i++;
	}
	return tam + 1;
}


char* decodificar (char *texto, No *n)
{
	int i = 0;
	No *aux = n;
	char *decodificado = (char*)calloc(strlen(texto), sizeof(char));
	char temp[2];
	
	
	while(texto[i] != '\0')
	{
		if(texto[i] == '0')
			aux = aux->esquerda;
		else
			aux = aux->direita;
			
		if(aux->esquerda == NULL && aux->direita==NULL)
		{
			temp[0] = aux->letra;
			temp[1] = '\0';
			strcat(decodificado, temp);
			aux = n;
		}
		i++;		
	}
	return decodificado;
}

void imprimir_dicionario(char **dicionario)
{
	int i;
	printf("------------DICIONÁRIO------------\n\n");
	for (i=0; i<MAX; i++)
		if(strlen(dicionario[i])>0)
			printf("\t%c: %s \n", i, dicionario[i]);
	
	printf("\n\n");
}

void imprime_arvore(No *n, int t)
{
	
    if(n->esquerda == NULL && n->direita == NULL)
        printf("Folha: %c / Altura: %i / Frequência: %i\n\n", n->letra, t, n->frequencia);
    else
    {
        imprime_arvore(n->esquerda,t+1);
        imprime_arvore(n->direita, t+1);
    }
     
}



void imprimir_lista(Lista *l)
{
    No *aux = l->inicio;
    printf("------------LISTA INICIAL------------\n\n");
    while(aux)
    {
     printf("Caracter: %c\nFrequencia: %d\n\n", aux->letra, aux->frequencia);
     aux = aux->proximo;
    }
}


void imprime_frequencia(unsigned int t[])
{
    int i;
    printf("------------TABELA DE FREQUÊNCIA------------\n\n");
    for(i=0; i<MAX; i++)
        if (t[i] > 0)
            printf("\tCódigo ASCII: %d / Frequência: %u / Caractere: %c\n\n", i, t[i], i);
}


