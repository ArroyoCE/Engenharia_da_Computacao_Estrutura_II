#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
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

void imprimir_lista (Lista*);
void imprime_frequencia(unsigned int*);
void imprime_arvore(No*, int);

int main()
{
    setlocale(LC_ALL, "");
    unsigned char texto[] = "vocês";
    unsigned int tabela_frequencia[MAX];
    Lista *lista;
    No *arvore;
    
    inicializa_tabela(tabela_frequencia);
    preenche_tabela(tabela_frequencia, texto);
    imprime_frequencia(tabela_frequencia);
    criar_lista(lista);
    preencher_lista(tabela_frequencia, lista);
    imprimir_lista(lista);

    arvore = cria_arvore(lista);
    
   
    imprime_arvore(arvore, 0);

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
    No *aux;

    if(l->inicio == NULL)
        l->inicio = n;
        
     
    else if (l->inicio->frequencia > n->frequencia)
    {
            n->proximo = l->inicio;
            l->inicio = n;
            
    }
    else
    {
        aux = l->inicio;
        while(aux->proximo != NULL &&  aux->proximo->frequencia < n->frequencia)
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

void imprime_arvore(No *n, int t)
{
    if(n->esquerda == NULL && n->direita == NULL)
        printf("Folha: %c\nAltura: %i\nFrequência: %i\n\n", n->letra, t, n->frequencia);
    else
    {
        imprime_arvore(n->esquerda,t+1);
        imprime_arvore(n->direita, t+1);
    }
     
}



void imprimir_lista(Lista *l)
{
    No *aux = l->inicio;
    while(aux)
    {
     printf("Caracter: %c\nFrequencia: %d\n\n", aux->letra, aux->frequencia);
     aux = aux->proximo;
    }
}






void imprime_frequencia(unsigned int t[])
{
    int i;
    for(i=0; i<MAX; i++)
        if (t[i] > 0)
            printf("\t%d = %u = %c\n", i, t[i], i);
}

