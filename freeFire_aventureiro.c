#include <stdio.h>
#include <string.h>

#define MAX 10

struct Item {
    char nome[50];
    char tipo[30];
    int quantidade;
};

struct Item mochila[MAX];
int total = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarItem() {
    if (total >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome: ");
    if (!fgets(mochila[total].nome, sizeof(mochila[total].nome), stdin)) return;
    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

    printf("Tipo: ");
    if (!fgets(mochila[total].tipo, sizeof(mochila[total].tipo), stdin)) return;
    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    if (scanf("%d", &mochila[total].quantidade) != 1) {
        limparBuffer();
        printf("Entrada inválida!\n");
        return;
    }
    limparBuffer();

    if (mochila[total].quantidade <= 0) {
        printf("Quantidade inválida!\n");
        return;
    }

    total++;
    printf("Item adicionado!\n");
}

void buscarItem() {
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[50];
    printf("Nome do item a buscar: ");
    if (!fgets(nome, sizeof(nome), stdin)) return;
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado!\n");
    }
}

void listarItens() {
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("Itens na mochila:\n");
    for (int i = 0; i < total; i++) {
        printf("%s | %s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int main() {
    int opcao;

    printf("=== INVENTÁRIO FREE FIRE ===\n");

    do {
        printf("\n--- Menu da Mochila ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Buscar Item\n");
        printf("3. Listar Itens\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opcao invalida!\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                buscarItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}


