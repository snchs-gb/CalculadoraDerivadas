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
            imprimeFuncaoArvore(a->esquerda);
            printf("%c", a->valor);
            imprimeFuncaoArvore(a->direita);

        }
    }
}

void imprimeFUncaoPilha(Pilha *p) {

    Elemento *aux = p->topo;

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
            
            if(p->tamanho != 2){
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


/*Arvore *arvoreFuncao(char *str){
    
    int i;
    Pilha *p = inicializaPilha();
    Arvore *a = inicializaArvore();

    for(i=0; i<strlen(str); i++){
        
        if((str[i] >= '0' && str[i] <= '9') || str[i] == 'x'){
            
            a = insereArvoreNULL(str[i], a);
            inserePilha(a, p);
        }
        else if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^'){

            // o tamanho pode ser maior que dois, só não pode ser menor
            if(p->tamanho != 2){
                printf("Função inválida");
                exit(-1);
            }
            a = insereArvoreNULL(str[i], a);
            a->direita = p->topo->dado;
            retiraPilha(p);
            a->esquerda = p->topo->dado;
            retiraPilha(p);
            inserePilha(a, p);
        }
    }
    a = p->topo->dado;
    retiraPilha(p);
    if(p->topo != NULL){
        printf("Função inválida\n");
        exit(-1);
    }
    free(p);
    
    return a;
}*/



int main (void){

    char str[50];
    gets(str);
    Pilha *p = inicializaPilha();
    p = arvoreFuncao(str);
    imprimeFUncaoPilha(p);
    
    return 0;
}