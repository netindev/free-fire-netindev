#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define TAM_STR 50

// Estrutura de um item da mochila
typedef struct {
    char nome[TAM_STR];
    char tipo[TAM_STR];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Enum para os critérios de ordenação
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Variáveis globais
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// Funções utilitárias
void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n");
}

void exibirMenu() {
    printf("\n=== 🏝️ CÓDIGO DA ILHA – MOCHILA DE SOBREVIVÊNCIA ===\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome (busca binária)\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

void listarItens() {
    if (numItens == 0) {
        printf("\n⚠️ Mochila vazia!\n");
        return;
    }

    printf("\n📦 Itens na mochila:\n");
    printf("-------------------------------------------------------------\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-------------------------------------------------------------\n");
}

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;

    printf("\n✅ Item adicionado com sucesso!\n");
}

void removerItem() {
    if (numItens == 0) {
        printf("\n⚠️ Mochila vazia!\n");
        return;
    }

    char nomeRemover[TAM_STR];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nomeRemover);

    int indice = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\n❌ Item não encontrado.\n");
        return;
    }

    for (int i = indice; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numItens--;
    printf("\n🗑️ Item removido com sucesso!\n");
}

// Função de ordenação (Insertion Sort)
void insertionSort(CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item atual = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            bool condicao = false;

            switch (criterio) {
                case ORDENAR_NOME:
                    condicao = strcmp(mochila[j].nome, atual.nome) > 0;
                    break;
                case ORDENAR_TIPO:
                    condicao = strcmp(mochila[j].tipo, atual.tipo) > 0;
                    break;
                case ORDENAR_PRIORIDADE:
                    condicao = mochila[j].prioridade < atual.prioridade;
                    break;
            }

            if (!condicao) break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = atual;
    }

    if (criterio == ORDENAR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;
}

// Menu de ordenação
void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("\n⚠️ Mochila vazia!\n");
        return;
    }

    int opcao;
    int comparacoes;

    printf("\n📊 Escolha o critério de ordenação:\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Tipo (A-Z)\n");
    printf("3. Prioridade (5-1)\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 3) {
        printf("\n❌ Opção inválida!\n");
        return;
    }

    insertionSort(opcao, &comparacoes);
    printf("\n✅ Mochila ordenada com sucesso!\n");
    printf("🔢 Comparações realizadas: %d\n", comparacoes);
    listarItens();
}

// Busca binária por nome
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("\n⚠️ É necessário ordenar por nome antes de buscar!\n");
        return;
    }

    char nomeBusca[TAM_STR];
    printf("\nDigite o nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int inicio = 0, fim = numItens - 1;
    bool encontrado = false;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            encontrado = true;
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            break;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (!encontrado)
        printf("\n❌ Item não encontrado.\n");
}

// Função principal
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\n🏁 Saindo da ilha... até a próxima batalha!\n");
                break;
            default:
                printf("\n❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
