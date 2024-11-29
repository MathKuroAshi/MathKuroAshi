/*---------------------------------------------------------------  *
* Disciplina: Programação Estruturada e Modular                    *
*                   Prof. Carlos Verissimo                         *               
*----------------------------------------------------------------  *
* Objetivo: Melhorar o código 23                     *   
* Data – 29/11/2024                                      	       *
* Autor: Matheus Arthur Moreira da Silva                           *
*----------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define MAX_NOME 50

// Funções de validação de entrada
int lerInteiroPositivo() {
    int num;
    while (scanf("%d", &num) != 1 || num < 0) {
        while (getchar() != '\n'); // Limpa o buffer
        printf("Entrada inválida! Digite um valor válido: ");
    }
    return num;
}

double lerDoublePositivo() {
    double num;
    while (scanf("%lf", &num) != 1 || num <= 0) {
        while (getchar() != '\n'); // Limpa o buffer
        printf("Entrada inválida! Digite um número positivo válido: ");
    }
    return num;
}

void lerString(char *str, int tamanho) {
    getchar();
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove o '\n' da string
}

int isStringValida(char *str) {
    // Verifica se a string contém apenas letras e espaços
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            return 0; // Se encontrar um caractere não válido
        }
    }
    return 1; // Se a string for válida
}
// Estrutura para armazenar informações de um produto
typedef struct {
    int id;
    char nome[MAX_NOME];
    int quantidadeEmEstoque;
    double valorDoProduto;
} Produto;

// Declaração das funções CRUD
void incluirProduto(Produto *produtos, int *quantidade);
Produto* consultarProduto(Produto *produtos, int quantidade, int id);
void alterarProduto(Produto *produtos, int quantidade);
void excluirProduto(Produto *produtos, int *quantidade);
void imprimirProduto(Produto *produto);
void venderProduto(Produto *produtos, int quantidade);
void aplicarDesconto(Produto *produtos, int quantidade);

// Função principal
int main() {
    Produto produtos[MAX_PRODUTOS];
    int quantidade = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Incluir produto\n");
        printf("2 - Consultar produto\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Vender produto\n");
        printf("6 - Aplicar desconto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        opcao = lerInteiroPositivo();
        switch (opcao) {
            case 1:
                incluirProduto(produtos, &quantidade);
                break;
            case 2: {
                int id;
                printf("Digite o ID do produto a ser consultado: ");
                id = lerInteiroPositivo();
                Produto *produto = consultarProduto(produtos, quantidade, id);
                if (produto) {
                    imprimirProduto(produto);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 3:
                alterarProduto(produtos, quantidade);
                break;
            case 4:
                excluirProduto(produtos, &quantidade);
                break;
            case 5:
                venderProduto(produtos, quantidade);
                break;
            case 6:
                aplicarDesconto(produtos, quantidade);
                break;            
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// Função para incluir um novo produto
void incluirProduto(Produto *produtos, int *quantidade) {
    if (*quantidade < MAX_PRODUTOS) {
        int novoId;
        do {
            printf("Digite o ID do produto: ");
            novoId = lerInteiroPositivo();

            // Verificar se o ID já existe
            if (consultarProduto(produtos, *quantidade, novoId) != NULL) {
                printf("ID já existente. Escolha um ID diferente.\n");
            } else {
                break;
            }
        } while (1);

        Produto *produto = &produtos[*quantidade];
        produto->id = novoId;
        
        do {
            printf("Digite o nome do produto: ");
            lerString(produto->nome, MAX_NOME);
            
            if (!isStringValida(produto->nome)) {
                printf("Nome inválido! Use apenas letras e espaços.\n");
            }
        } while (!isStringValida(produto->nome));
        
        printf("Digite a quantidade em estoque: ");
        produto->quantidadeEmEstoque = lerInteiroPositivo();
        
        printf("Digite o valor do produto (Use ponto no lugar de vírgula): ");
        produto->valorDoProduto = lerDoublePositivo();

        (*quantidade)++;
        printf("Produto incluído com sucesso!\n");
    } else {
        printf("Capacidade máxima de produtos atingida.\n");
    }
}

// Função para consultar um produto pelo ID
Produto* consultarProduto(Produto *produtos, int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}

// Função para alterar um produto pelo ID
void alterarProduto(Produto *produtos, int quantidade) {
    int id;
    printf("Digite o ID do produto a ser alterado: ");
    id = lerInteiroPositivo();

    Produto *produto = consultarProduto(produtos, quantidade, id);
    if (produto) {
        do {
            printf("Digite o novo nome do produto: ");
            lerString(produto->nome, MAX_NOME);
            
            if (!isStringValida(produto->nome)) {
                printf("Nome inválido! Use apenas letras e espaços.\n");
            }
        } while (!isStringValida(produto->nome));

        printf("Digite a nova quantidade em estoque: ");
        produto->quantidadeEmEstoque = lerInteiroPositivo();

        printf("Digite o novo valor do produto (Use \'. no lugar de vírgula): ");
        produto->valorDoProduto = lerDoublePositivo();

        printf("Produto alterado com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

// Função para excluir um produto pelo ID
void excluirProduto(Produto *produtos, int *quantidade) {
    int id;
    printf("Digite o ID do produto a ser excluído: ");
    id = lerInteiroPositivo();

    for (int i = 0; i < *quantidade; i++) {
        if (produtos[i].id == id) {
            for (int j = i; j < *quantidade - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            (*quantidade)--;
            printf("Produto excluído com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

// Função para imprimir os dados de um produto
void imprimirProduto(Produto *produto) {
    printf("ID: %d\n", produto->id);
    printf("Nome: %s\n", produto->nome);
    printf("Quantidade em Estoque: %d\n", produto->quantidadeEmEstoque);
    printf("Valor do Produto: %.2f\n", produto->valorDoProduto);
}

// Função para vender um produto, reduzindo a quantidade em estoque
void venderProduto(Produto *produtos, int quantidade) {
    int id, quantidadeVendida;
    printf("Digite o ID do produto a ser vendido: ");
    id = lerInteiroPositivo();

    Produto *produto = consultarProduto(produtos, quantidade, id);
    if (produto) {
        printf("Digite a quantidade a ser vendida: ");
        quantidadeVendida = lerInteiroPositivo();

        if (quantidadeVendida <= produto->quantidadeEmEstoque) {
            produto->quantidadeEmEstoque -= quantidadeVendida;
            printf("Venda realizada com sucesso!\n");
            imprimirProduto(produto);
        } else {
            printf("Quantidade em estoque insuficiente.\n");
        }
    } else {
        printf("Produto não encontrado.\n");
    }
}

// Função para aplicar desconto em um produto pelo ID
void aplicarDesconto(Produto *produtos, int quantidade){
    int id;
    double desconto;
    
    printf("Informe o ID do produto para aplicar desconto: ");
    id = lerInteiroPositivo();
    
    // Busca o produto pelo ID
    for (int i=0; i < quantidade; i++) {
        if (produtos[i].id == id) {
            printf("Informe o percentual de desconto (0-100): ");
            desconto = lerDoublePositivo();
            
            if (desconto < 0 || desconto > 100) {
                printf("Desconto inválido! Deve estar entre 0 e 100.\n");
                return;
            }
            
            produtos[i].valorDoProduto *= (1 - desconto / 100); // Aplica o desconto
            printf("Desconto aplicado com sucesso! Novo preço: %.2lf\n", produtos[i].valorDoProduto);
            return;
        }
    }
        printf("Produto inexistente.\n");
}