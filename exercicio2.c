#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Estruturas de Nó, Fila e Pilha
typedef struct No {
    char dado;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

typedef struct {
    No* topo;
} Pilha;

//Funções Auxiliares (Fila e Pilha)
void inicializar_fila(Fila* f) { f->inicio = f->fim = NULL; }
void enfileirar(Fila* f, char dado) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    novo->proximo = NULL;
    if (f->fim) f->fim->proximo = novo;
    f->fim = novo;
    if (!f->inicio) f->inicio = novo;
}
char desenfileirar(Fila* f) {
    No* temp = f->inicio;
    char dado = temp->dado;
    f->inicio = f->inicio->proximo;
    if (!f->inicio) f->fim = NULL;
    free(temp);
    return dado;
}

void inicializar_pilha(Pilha* p) { p->topo = NULL; }
void empilhar(Pilha* p, char dado) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    novo->proximo = p->topo;
    p->topo = novo;
}
char desempilhar(Pilha* p) {
    No* temp = p->topo;
    char dado = temp->dado;
    p->topo = p->topo->proximo;
    free(temp);
    return dado;
}

//Função Principal do Exercício
bool eh_palindromo(const char* palavra) {
    Fila fila;
    Pilha pilha;
    inicializar_fila(&fila);
    inicializar_pilha(&pilha);

    //Preencher a fila e a pilha com os caracteres da palavra
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = tolower(palavra[i]); //Ignorar maiúsculas/minúsculas
        if (isalnum(c)) { //Considerar apenas letras e números
            enfileirar(&fila, c);
            empilhar(&pilha, c);
        }
    }

    //Comparar caracteres do início (fila) e do fim (pilha)
    bool palindromo = true;
    while (fila.inicio != NULL) {
        if (desenfileirar(&fila) != desempilhar(&pilha)) {
            palindromo = false;
            break;
        }
    }
    
    //Limpar o que sobrou (caso a palavra tenha tido caracteres ignorados)
    while(fila.inicio) desenfileirar(&fila);
    while(pilha.topo) desempilhar(&pilha);

    return palindromo;
}

int main() {
    const char* palavras[] = {"arara", "ovo", "Radar", "Ame a ema", "socorram me subi no onibus em marrocos", "teste", "palindromo"};
    int num_palavras = sizeof(palavras) / sizeof(char*);

    for (int i = 0; i < num_palavras; i++) {
        if (eh_palindromo(palavras[i])) {
            printf("A frase/palavra '%s' é um palíndromo.\n", palavras[i]);
        } else {
            printf("A frase/palavra '%s' NÃO é um palíndromo.\n", palavras[i]);
        }
    }

    return 0;
}