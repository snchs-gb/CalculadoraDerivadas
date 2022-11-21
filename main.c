#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvore{
    struct arvore *esquerda;
    struct arvore *direita;
    char valor;
}Arvore;

typedef struct elemento{
    Arvore *dado;
    struct elemento *proximo;
}Elemento;

typedef struct pilha{
    Elemento *topo;
    int tamanho;
}Pilha;

Arvore *inicializaArvore(){
    return NULL;
}

Pilha *inicializaPilha(){
    Pilha *p;
    p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

Arvore *insereArvore(char ch, Arvore *a){

    if(a == NULL){
        Arvore *novo;
        novo = (Arvore*)malloc(sizeof(Arvore));
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->valor = ch;
        a = novo;
    }
    else if(a->direita == NULL){
        a->direita = insereArvore(ch, a->direita);
    }
    else{
        a->esquerda = insereArvore(ch, a->esquerda);
    }

    return a;
}

void inserePilha(Arvore *a, Pilha *p) {

    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->dado = a;
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void retiraPilha(Pilha *p) {
    
    if(p->topo != NULL){
        Elemento *aux = p->topo;
        p->topo = p->topo->proximo;
        free(aux);
        aux = NULL;
        p->tamanho--;
    }
}

void imprimeFuncaoArvore(Arvore *a){

    if(a != NULL){
        if(a->valor == '+'){
            printf("(");
            imprimeFuncaoArvore(a->esquerda);
            printf(")+(");
            imprimeFuncaoArvore(a->direita);
            printf(")");
        }
        else if( a->valor == '-'){
            printf("(");
            imprimeFuncaoArvore(a->esquerda);
            printf(")-(");
            imprimeFuncaoArvore(a->direita);
            printf(")");
        }
        else if( a->valor == '*'){
            printf("(");
            imprimeFuncaoArvore(a->esquerda);
            printf(")*(");
            imprimeFuncaoArvore(a->direita);
            printf(")");
        }
        else if( a->valor == '/'){
            printf("(");
            imprimeFuncaoArvore(a->esquerda);
            printf(")/(");
            imprimeFuncaoArvore(a->direita);
            printf(")");
        }
        else if( a->valor == '^'){
            printf("(");
            imprimeFuncaoArvore(a->esquerda);
            printf(")^(");
            imprimeFuncaoArvore(a->direita);
            printf(")");
        }
        else{
            printf("%c", a->valor);
        }
    }
}

void imprimeFuncaoPilha(Pilha *p) {

    Elemento *aux = p->topo;
    if(p->tamanho > 1){
        printf("Função inválida");
        exit(-1);
    }
    while(aux != NULL){
        imprimeFuncaoArvore(p->topo->dado);
        aux = aux->proximo;
    }


}

Pilha *arvoreFuncao(char *str){

    int i = 0;
    Pilha *p = inicializaPilha();

    while(i < strlen(str)){
        
        if(str[i] == 'x' || (str[i] >= '0' && str[i] <= '9') ){
            Arvore *a = inicializaArvore();
            a = insereArvore(str[i], a);
            inserePilha(a, p);
        }
        else if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^'){
            
            if(p->tamanho < 2){
                printf("Função inválida");
                exit(-1);
            }
            Arvore *a = inicializaArvore();
            a = insereArvore(str[i], a);
            a->direita = p->topo->dado;
            retiraPilha(p);
            a->esquerda = p->topo->dado;
            retiraPilha(p);
            inserePilha(a, p);
        }
        i++;
    }
    return p;
}

int main (void){

    char str[50];
    gets(str);
    Pilha *p = inicializaPilha();
    p = arvoreFuncao(str);
    imprimeFuncaoPilha(p);
    
    return 0;
}
