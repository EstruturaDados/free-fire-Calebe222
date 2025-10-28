#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade;
} Item;

Item mochila[MAX];
int total = 0;
int comparacoes = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarItem() {
    if (total >= MAX) {
        printf("Mochila Cheia!!\n");
        return;
    }

    printf("Nome: ");
    if (!fgets(mochila[total].nome, sizeof(mochila[total].nome), stdin)) return;
    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0'; // Remove newline

    printf("Tipo: ");
    if (!fgets(mochila[total].tipo, sizeof(mochila[total].tipo), stdin)) return;
    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    if (scanf("%d", &mochila[total].quantidade) != 1) {
        limparBuffer();
        printf("Entrada inválida!\n");
        return;
    }

    printf("Prioridade (1-5): ");
    if (scanf("%d", &mochila[total].prioridade) != 1) {
        limparBuffer();
        printf("Entrada inválida!\n");
        return;
    }
    limparBuffer();

    if (mochila[total].prioridade < 1 || mochila[total].prioridade > 5) {
        printf("Prioridade deve ser entre 1 e 5!\n");
        return;
    }
    
    total++;
    printf("Item adicionado!\n");
}

void ordenarPorNome() {
    comparacoes = 0;
    for (int i = 1; i < total; i++) {
        Item temp = mochila[i];
        int j = i - 1;
        
        while (j >= 0 && strcmp(mochila[j].nome, temp.nome) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = temp;
    }
    printf("Ordenado por nome! Comparações: %d\n", comparacoes);
}

void ordenarPorTipo() {
    comparacoes = 0;
    for (int i = 1; i < total; i++) {
        Item temp = mochila[i];
        int j = i - 1;
        
        while (j >= 0 && strcmp(mochila[j].tipo, temp.tipo) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = temp;
    }
    printf("Ordenado por tipo! Comparações: %d\n", comparacoes);
}

void ordenarPorPrioridade() {
    comparacoes = 0;
    for (int i = 1; i < total; i++) {
        Item temp = mochila[i];
        int j = i - 1;
        
        while (j >= 0 && mochila[j].prioridade > temp.prioridade) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = temp;
    }
    printf("Ordenado por prioridade! Comparações: %d\n", comparacoes);
}

bool estaOrdenadoPorNome() {
    for (int i = 0; i < total - 1; i++) {
        if (strcmp(mochila[i].nome, mochila[i + 1].nome) > 0) {
            return false;
        }
    }
    return true;
}

void buscaBinaria() {
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    if (!estaOrdenadoPorNome()) {
        printf("Lista não está ordenada por nome! Ordene primeiro.\n");
        return;
    }

    char nome[50];
    printf("Nome do item a buscar: ");
    if (!fgets(nome, sizeof(nome), stdin)) return;
    nome[strcspn(nome, "\n")] = '\0';
    
    int inicio = 0, fim = total - 1;
    comparacoes = 0;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        
        int cmp = strcmp(mochila[meio].nome, nome);
        
        if (cmp == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            printf("Comparações na busca: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("❌ Item '%s' não encontrado! Comparações: %d\n", nome, comparacoes);
}

void listarItens() {
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("\nItens na mochila (%d/%d):\n", total, MAX);
    for (int i = 0; i < total; i++) {
        printf("%s | %s | %d | Pri: %d\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

int main() {
    int opcao;
    
    printf("=== INVENTÁRIO FREE FIRE COM ORDENAÇÃO ===\n");
    
    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar item\n");
        printf("2. Ordenar por nome\n");
        printf("3. Ordenar por tipo\n");
        printf("4. Ordenar por prioridade\n");
        printf("5. Busca binária\n");
        printf("6. Listar itens\n");
        printf("7. Sair\n");
        printf("Opção: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer();
        
        switch(opcao) {
            case 1: adicionarItem(); break;
            case 2: ordenarPorNome(); break;
            case 3: ordenarPorTipo(); break;
            case 4: ordenarPorPrioridade(); break;
            case 5: buscaBinaria(); break;
            case 6: listarItens(); break;
            case 7: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 7);
    
    return 0;
}



