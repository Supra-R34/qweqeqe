#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cad_produto.h"
#include "../Utilitarios/mascara.h"

//Função para adicionar os produtos no arquivo TXT
void adicionarProdutoEmArquivo(produto_t produto) {
    FILE *arquivo = fopen("Produtos/produtos.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para salvar os dados");
        return;
    }
    fprintf(arquivo, "%s\n%.2f\n%d\n%d\n%s\n%s\n", produto.nome, produto.prec, produto.quant, produto.idProd, produto.dat, produto.cat);
    fclose(arquivo);
}

//Função para sobrescrever os produtos no arquivo TXT
void sobrescreverProdutosEmArquivo(produto_t produto[], int numProdutos) {
    FILE *arquivo = fopen("Produtos/produtos.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para sobrescrever os dados");
        return;
    }
    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivo, "%s\n%.2f\n%d\n%d\n%s\n%s\n", produto[i].nome, produto[i].prec, produto[i].quant, produto[i].idProd, produto[i].dat, produto[i].cat);
    }
    fclose(arquivo);
}

//Função para carregar os produtos no arquivo TXT
int carregarProdutosDeArquivo(produto_t produtos[]) {
    FILE *arquivo = fopen("Produtos/produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de produtos encontrado. Iniciando sem produtos.\n");
        return 0;
    }

    int numProdutos = 0;
    char buffer[200];

    while (fscanf(arquivo, "%[^\n]\n%f\n%d\n%d\n%[^\n]\n%[^\n]\n",
                  produtos[numProdutos].nome,
                  &produtos[numProdutos].prec,
                  &produtos[numProdutos].quant,
                  &produtos[numProdutos].idProd,
                  produtos[numProdutos].dat,
                  produtos[numProdutos].cat) == 6) {
        numProdutos++;
        if (numProdutos >= 100) {
            printf("Limite maximo de produtos atingido.\n");
            break;
        } 
    } 
    fclose(arquivo);
    return numProdutos;
}

//Função para adicionar produtos
void adicionarProduto(produto_t produto[], int *numProdutos) {
    if (*numProdutos >= 100) {
        printf("Limite maximo de produtos atingido!\n");
        return;
    }

    int idExistente;
    printf("\nDigite o ID do produto: ");
    scanf("%d", &idExistente);
    getchar();

    // Verifica se o ID já existe
    for (int i = 0; i < *numProdutos; i++) {
        if (produto[i].idProd == idExistente) {
            printf("Erro: O ID %d ja esta cadastrado para o produto '%s'.\n", idExistente, produto[i].nome);
            return;
        }
    }

    // Se o ID não existe, atribui ao novo produto
    produto[*numProdutos].idProd = idExistente;

    printf("\nDigite o nome do Produto: ");
    fgets(produto[*numProdutos].nome, sizeof(produto[*numProdutos].nome), stdin);
    strtok(produto[*numProdutos].nome, "\n");

    printf("\nDigite o preco do produto: ");
    scanf("%f", &produto[*numProdutos].prec);
    getchar();

    printf("\nDigite a quantidade do produto: ");
    scanf("%d", &produto[*numProdutos].quant);
    getchar();

    printf("\nDigite a data (dd/mm/aaaa): ");
    mascara_dat(produto[*numProdutos].dat);

    printf("\nDigite a categoria: ");
    fgets(produto[*numProdutos].cat, sizeof(produto[*numProdutos].cat), stdin);
    strtok(produto[*numProdutos].cat, "\n");

    printf("\nProduto cadastrado com sucesso!\n");
    adicionarProdutoEmArquivo(produto[*numProdutos]);
    (*numProdutos)++;
}

//Função de comparação para definir a ordem em que os produtos serão classificados (por ID, neste caso).
int compararPorID(const void *a, const void *b) {
    produto_t *produtoA = (produto_t *)a;
    produto_t *produtoB = (produto_t *)b;
    return produtoA->idProd - produtoB->idProd;
}

//Função para visualizar o estoque de produtos salvos no arquivo TXT
void visualizarProdutos(produto_t produto[], int numProdutos) {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    qsort(produto, numProdutos, sizeof(produto_t), compararPorID);

    printf("+-------------- ESTOQUE DE PRODUTOS ------------------+\n");
    printf("|-----------------------------------------------------|\n");
    printf("| ID | Produto          | Quantidade | Preco Unitario |\n");
    printf("+-----------------------------------------------------+\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("| %-2d | %-16s | %10d | %14.2f |", produto[i].idProd, produto[i].nome, produto[i].quant, produto[i].prec );


    printf("\n");
    } 
    printf("+-----------------------------------------------------+\n");
    system("pause");
    system("cls");
}

//Função para pesquisar os produtos no arquivo TXT com base no seu ID
void pesquisarProduto(produto_t produto[], int numProdutos) {
    int ID;
    printf("Digite o ID para pesquisar: ");
    scanf("%d", &ID);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (produto[i].idProd == ID) {

          printf("\n+------ DADOS DO PRODUTO --------------+\n");
            printf("|--------------------------------------|\n");
            printf("| Nome:        | %-21s |\n", produto[i].nome);
            printf("| Preco:       | %-20.2f  |\n", produto[i].prec);
            printf("| Quantidade:  | %-18d    |\n", produto[i].quant);
            printf("| ID:          | %-18d    |\n", produto[i].idProd);
            printf("| Data:        | %-18s    |\n", produto[i].dat);
            printf("| Categoria:   | %-18s    |\n", produto[i].cat);
            printf("+--------------------------------------+\n");
            encontrado = 1;

            char opcao;
            printf("\nDeseja editar os dados do produto? (s/n): ");
            scanf(" %c", &opcao); 
            getchar();

            if (opcao == 's' || opcao == 'S') {
                int editOp;
                do {
                    printf("\nQual dado deseja editar?\n");
                    printf("1 - Nome\n");
                    printf("2 - Preco\n");
                    printf("3 - Quantidade\n");
                    printf("4 - Data\n");
                    printf("5 - Categoria\n");
                    printf("6 - Sair\n");
                    printf("Opcao: ");
                    scanf("%d", &editOp);
                    getchar();

                    switch (editOp) {
                    case 1:
                        printf("Digite o novo nome: ");
                        fgets(produto[i].nome, sizeof(produto[i].nome), stdin);
                        strtok(produto[i].nome, "\n");
                        printf("Nome alterado com sucesso!\n");
                        break;
                    case 2:
                        printf("Digite o novo preco: ");
                        scanf("%f", &produto[i].prec);
                        printf("Preco alterado com sucesso!\n");
                        getchar();
                        break;
                    case 3:
                        printf("Digite a nova quantidade: ");
                        scanf("%d", &produto[i].quant);
                        printf("Quantidade alterada com sucesso!\n");
                        getchar();
                        break;
                    case 4:
                        printf("Digite a nova data: ");
                        fgets(produto[i].dat, sizeof(produto[i].dat), stdin);
                        strtok(produto[i].dat, "\n");
                        printf("Data alterada com sucesso!\n");
                        break;
                    case 5:
                        printf("Digite a nova categoria: ");
                        fgets(produto[i].cat, sizeof(produto[i].cat), stdin);
                        strtok(produto[i].cat, "\n");
                        printf("Categoria alterado com sucesso!\n");
                        break;
                    case 6:
                        printf("Saindo da edicao...\n");
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }

                    sobrescreverProdutosEmArquivo(produto, numProdutos);

                    printf("\n");
                    system("pause");
                    system("cls");

                } while (editOp != 6);
            }
            break;
        }
    }

    system("cls");

    if (!encontrado) {
        printf("Produto com ID %d nao encontrado.\n", ID);
    }
}

//Função para remover os produtos no arquivo TXT
void removerProduto(produto_t produto[], int *numProdutos) {
    int ID;
    printf("Digite o ID para remover: ");
    scanf("%d", &ID);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < *numProdutos; i++) {
        if (produto[i].idProd == ID) {
            for (int j = i; j < *numProdutos - 1; j++) {
                produto[j] = produto[j + 1];
            }
            (*numProdutos)--;
            printf("Produto removido com sucesso!\n");
            sobrescreverProdutosEmArquivo(produto, *numProdutos);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto com ID %d nao encontrado.\n", ID);
    }
}
