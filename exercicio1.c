#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um cliente 
typedef struct {
    int numero;
    char nome[50];
    int tempoAtendimento // em minutos
} Cliente;

// Estrutura do Nó da Fila
typedef struct No {
    Cliente cliente;
    struct No* proximo;
} No;

// Estrutura da Fila
typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Fila;

// Funções da Fila
Fila* criar_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

// Implemente função para adicionar cliente
void adicionar_cliente(Fila* f, int numero, const char* nome, int tempoAtendimento) {
    No* novo_no = (No*) malloc(sizeof(No));
    
    novo_no->cliente.numero = numero;
    strcpy(novo_no->cliente.nome, nome);
    novo_no->cliente.tempoAtendimento = tempoAtendimento;
    novo_no->proximo = NULL;

    if (f->fim != NULL) {
        f->fim->proximo = novo_no;
    }
    f->fim = novo_no;

    if (f->inicio == NULL) {
        f->inicio = novo_no;
    }
    f->tamanho++;
    printf("Cliente '%s' (ID: %d) entrou na fila.\n", nome, numero);
}

// Implemente função para atender próximo cliente
Cliente atender_proximo_cliente(Fila* f) {
    if (f->inicio == NULL) {
        Cliente vazio = {-1, "Nenhum", 0};
        printf("Fila vazia. Nenhum cliente para atender.\n");
        return vazio;
    }

    No* temp = f->inicio;
    Cliente cliente_atendido = temp->cliente;
    
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(temp);
    f->tamanho--;
    
    printf("Atendendo cliente '%s' (ID: %d), tempo de atendimento: %d min.\n", 
           cliente_atendido.nome, cliente_atendido.numero, cliente_atendido.tempoAtendimento);
           
    return cliente_atendido;
}

int main() {
    Fila* fila_banco = criar_fila();

    //Calcule tempo médio de espera
    double soma_tempos_espera = 0;
    double tempo_acumulado_atendimento = 0;
    int clientes_atendidos = 0;

    printf("--- Iniciando Simulação de Atendimento Bancário ---\n");
    adicionar_cliente(fila_banco, 101, "Ana Silva", 5);
    adicionar_cliente(fila_banco, 102, "Bruno Costa", 8);
    adicionar_cliente(fila_banco, 103, "Carlos Dias", 4);
    adicionar_cliente(fila_banco, 104, "Daniela Souza", 10);
    
    printf("\n--- Processando Fila de Atendimento ---\n");
    while (fila_banco->inicio != NULL) {
        // O tempo de espera para o cliente atual é o tempo total gasto atendendo os anteriores
        double tempo_espera_atual = tempo_acumulado_atendimento;
        soma_tempos_espera += tempo_espera_atual;
        printf("  -> Tempo de espera para o próximo cliente: %.0f min.\n", tempo_espera_atual);

        Cliente c = atender_proximo_cliente(fila_banco);
        
        // Acumula o tempo de atendimento do cliente que acabou de ser servido
        tempo_acumulado_atendimento += c.tempoAtendimento;
        clientes_atendidos++;
    }

    printf("\n--- Fim da Simulação ---\n");
    if (clientes_atendidos > 0) {
        double tempo_medio = soma_tempos_espera / clientes_atendidos;
        printf("Total de clientes atendidos: %d\n", clientes_atendidos);
        printf("Tempo médio de espera: %.2f minutos.\n", tempo_medio);
    } else {
        printf("Nenhum cliente foi atendido.\n");
    }

    free(fila_banco);
    return 0;
}