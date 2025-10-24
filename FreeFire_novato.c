#include <stdio.h>
#include <string.h>

#define MAX 10

struct Item {
    char nome[50], tipo[30];
    int quant;
};

struct Item mochila[MAX];
int total = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionar() {
    if (total >= MAX) {
        printf("❌ Mochila cheia!\n");
        return;
    }
    
    printf("\n➕ ADICIONAR ITEM\nNome: ");
    fgets(mochila[total].nome, 50, stdin);
    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';
    
    printf("Tipo: ");
    fgets(mochila[total].tipo, 30, stdin);
    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    if (scanf("%d", &mochila[total].quant) != 1) {
        limparBuffer();
        printf("❌ Entrada inválida!\n");
        return;
    }
    limparBuffer();
    
    if (mochila[total].quant > 0) {
        printf("✅ Item '%s' adicionado!\n", mochila[total].nome);
        total++;
    } else {
        printf("❌ Quantidade inválida!\n");
    }
}

void remover() {
    if (total == 0) {
        printf("❌ Mochila vazia!\n");
        return;
    }

    printf("\n🗑️ REMOVER ITEM\nNome: ");
    char nome[50];
    fgets(nome, 50, stdin);
    nome[(strcspn(nome, "\n"))] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            total--;
            printf("✅ Item '%s' removido!\n", nome);
            return;
        }
    }
    printf("❌ Item '%s' não encontrado!\n", nome);
}

void listar() {
    if (total == 0) {
        printf("\n📭 Mochila vazia!\n");
        return;
    }

    printf("\n📋 ITENS NA MOCHILA (%d/%d)\n", total, MAX);
    printf("┌────────────────────────────────────┬──────────────────────────┬────────────┐\n");
    printf("│ %-35s│ %-24s│ %-10s │\n", "NOME", "TIPO", "QUANTIDADE");
    printf("├────────────────────────────────────┼──────────────────────────┼────────────┤\n");

    for (int i = 0; i < total; i++) {
        printf("│ %-35s│ %-24s│ %-10d │\n", mochila[i].nome, mochila[i].tipo, mochila[i].quant); 
    }
    printf("└────────────────────────────────────┴──────────────────────────┴────────────┘\n");
}

int main() {
    int op;

    printf("=== INVENTÁRIO FREE FIRE ===\n");

    do {
        printf("\n--- MENU ---\n1. Adicionar\n2. Remover\n3. Listar\n4. Sair\nOpção: ");
        if (scanf("%d", &op) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer();

        switch(op) {
            case 1: adicionar(); break;
            case 2: remover(); break;
            case 3: listar(); break;
            case 4: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(op != 4);

    return 0;
}