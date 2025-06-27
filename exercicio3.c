#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char descricao[100];
} TipoItem;

typedef struct {
    TipoItem dado;
    int prioridade; // 1=alta, 2=média, 3=baixa 
} ItemPrioridade;

typedef struct No {
    ItemPrioridade item;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

Fila* criar_fila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

//Implemente enqueue que insere na posição correta 
bool fila_enqueue_prioridade(Fila* fila, ItemPrioridade item) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) return false;
    novo_no->item = item;
    novo_no->proximo = NULL;

    //Caso 1: Fila está vazia
    if (fila->inicio == NULL) {
        fila->inicio = novo_no;
        fila->fim = novo_no;
        return true;
    }
    
    //Caso 2: Novo item tem prioridade maior que o primeiro (valor menor)
    if (item.prioridade < fila->inicio->item.prioridade) {
        novo_no->proximo = fila->inicio;
        fila->inicio = novo_no;
        return true;
    }

    //Caso 3: Percorrer para encontrar a posição de inserção
    No* atual = fila->inicio;
    while (atual->proximo != NULL && atual->proximo->item.prioridade <= item.prioridade) {
        atual = atual->proximo;
    }

    novo_no->proximo = atual->proximo;
    atual->proximo = novo_no;

    //Se o novo nó foi inserido no final, atualize o ponteiro 'fim'
    if (novo_no->proximo == NULL) {
        fila->fim = novo_no;
    }

    return true;
}

ItemPrioridade fila_dequeue(Fila* fila) {
    if (fila->inicio == NULL) {
        ItemPrioridade item_vazio = {{"Vazio"}, -1};
        return item_vazio;
    }
    No* temp = fila->inicio;
    ItemPrioridade item_removido = temp->item;
    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(temp);
    return item_removido;
}

void imprimir_fila(Fila* fila) {
    if (!fila->inicio) {
        printf("Fila de prioridade vazia.\n");
        return;
    }
    printf("Estado atual da fila de prioridade:\n");
    No* atual = fila->inicio;
    while(atual != NULL) {
        printf("  -> Tarefa: '%s' (Prioridade: %d)\n", atual->item.dado.descricao, atual->item.prioridade);
        atual = atual->proximo;
    }
}

int main() {
    Fila* fila_tarefas = criar_fila();
    
    printf("--- Adicionando Tarefas com Prioridades ---\n");
    
    ItemPrioridade tarefa1 = {{"Resolver bug crítico"}, 1}; // Alta
    ItemPrioridade tarefa2 = {{"Enviar relatório semanal"}, 2}; // Média
    ItemPrioridade tarefa3 = {{"Fazer backup do sistema"}, 3}; // Baixa
    ItemPrioridade tarefa4 = {{"Responder e-mail urgente"}, 1}; // Alta
    ItemPrioridade tarefa5 = {{"Organizar arquivos"}, 3}; // Baixa
    
    fila_enqueue_prioridade(fila_tarefas, tarefa1);
    fila_enqueue_prioridade(fila_tarefas, tarefa2);
    fila_enqueue_prioridade(fila_tarefas, tarefa3);
    fila_enqueue_prioridade(fila_tarefas, tarefa4);
    fila_enqueue_prioridade(fila_tarefas, tarefa5);

    imprimir_fila(fila_tarefas);

    printf("\n--- Processando Tarefas por Ordem de Prioridade ---\n");
    while (fila_tarefas->inicio != NULL) {
        ItemPrioridade tarefa_processada = fila_dequeue(fila_tarefas);
        printf("Processando: '%s' (Prioridade: %d)\n", tarefa_processada.dado.descricao, tarefa_processada.prioridade);
    }

    free(fila_tarefas);
    return 0;
}