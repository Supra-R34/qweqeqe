#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Clientes/Cad_cliente.h"
#include "Produtos/Cad_produto.h"
#include "Fornecedores/Cad_fornecedor.h"
#include "Caixa/Caixa.c"
#include "Relatorio/relatorio.h"
#include "Utilitarios/mascara.c"

//Cria a função Login
void login() {
    char us[100], pass[100];
    const char user[] = "admin";
    const char password[] = "admin";

    while (1) {
        printf("Digite o Login de Administrador: \n");
        printf("Usuario: ");
        scanf("%s", us);
       
        printf("Senha: ");
        mascara_senha(pass, 100);

        if (strcmp(us, user) == 0 && strcmp(pass, password) == 0) {
            break;
        } else {
            printf("Senha ou usuario incorreto. Tente Novamente!\n");
        }
    }
}

//Cria a função para operar com os clientes
void menuClientes() {
    cliente_t clientes[100];
    int numClientes = carregarClientesDeArquivo(clientes);
    int subOpcao;

    do {
        printf("\n");
        printf("+---------------- :: MENU CLIENTES :: ----------------+ \n");
        printf("|                                                     | \n");
        printf("|         1 - Adicionar Cliente                       | \n");
        printf("|         2 - Visualizar Clientes                     | \n");
        printf("|         3 - Pesquisar Cliente                       | \n");
        printf("|         4 - Remover Cliente                         | \n");
        printf("|         5 - Voltar ao Menu Principal                | \n");
        printf("|                                                     | \n");
        printf("+-----------------------------------------------------+ \n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &subOpcao);
        getchar();
        system("cls");

        switch (subOpcao) {
            case 1:
                adicionarCliente(clientes, &numClientes);
                break;
            case 2:
                visualizarClientes(clientes, numClientes);
                break;
            case 3:
                pesquisarCliente(clientes, numClientes);
                break;
            case 4:
                removerCliente(clientes, &numClientes);
                break;
            case 5:
                printf("Voltando ao menu principal...\n");
                system("cls");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (subOpcao != 5);

    sobrescreverClientesEmArquivo(clientes, numClientes);
}

//Cria a função para operar com os produtos
void menuProdutos() {
    produto_t produto[100];
    int numProdutos = carregarProdutosDeArquivo(produto);
    int subOpcao;



    do {
        printf("\n");
        printf("+---------------- :: MENU PRODUTOS :: -------+ \n");
        printf("|                                            | \n");
        printf("|          1 - Adicionar Produto             | \n");
        printf("|          2 - Estoque de Produtos           | \n");
        printf("|          3 - Pesquisar Produto             | \n");
        printf("|          4 - Remover Produto               | \n");
        printf("|          5 - Voltar ao Menu Principal      | \n");
        printf("|                                            | \n");
        printf("+--------------------------------------------+ \n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &subOpcao);
        getchar();

        system("cls");

        switch (subOpcao) {
            case 1:
                adicionarProduto(produto, &numProdutos);
                break;
            case 2:
                visualizarProdutos(produto, numProdutos);
                break;
            case 3:
                pesquisarProduto(produto, numProdutos);
                break;
            case 4:
                removerProduto(produto, &numProdutos);
                break;
            case 5:
                printf("Voltando ao menu principal...\n");
                system("cls");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (subOpcao != 5);

    sobrescreverProdutosEmArquivo(produto, numProdutos);
}



// Função para operar com os fornecedores
void menuFornecedores() {
    fornecedor_t fornecedores[100];
    int numFornecedores = carregarFornecedoresDeArquivo(fornecedores);
    int subOpcao;

    do {
        printf("\n");
        printf("+---------------- :: MENU FORNECEDORES :: ----------------+ \n");
        printf("|                                                         | \n");
        printf("|         1 - Adicionar Fornecedor                        | \n");
        printf("|         2 - Visualizar Fornecedores                     | \n");
        printf("|         3 - Pesquisar Fornecedor                        | \n");
        printf("|         4 - Remover Fornecedor                          | \n");
        printf("|         5 - Voltar ao Menu Principal                    | \n");
        printf("|                                                         | \n");
        printf("+---------------------------------------------------------+ \n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &subOpcao);
        getchar();
        system("cls");

        switch (subOpcao) {
            case 1:
                adicionarFornecedor(fornecedores, &numFornecedores);
                break;
            case 2:
                visualizarFornecedores(fornecedores, numFornecedores);
                break;
            case 3:
                pesquisarFornecedor(fornecedores, numFornecedores);
                break;
            case 4:
                removerFornecedor(fornecedores, &numFornecedores);
                break;
            case 5:
                printf("Voltando ao menu principal...\n");
                system("cls");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (subOpcao != 5);

    sobrescreverFornecedoresEmArquivo(fornecedores, numFornecedores);
}


int main() {
    int opcao;
    venda_t vendas[100];
    produto_t produto[100];
    int numVendas = carregarVendasDeArquivo(vendas);
    int numProdutos = carregarProdutosDeArquivo(produto);

    do {
        printf("\n");
        printf("+---------------- :: MENU PRINCIPAL :: ----------------+ \n");
        printf("|                                                      | \n");
        printf("|         1 - Gerenciar Clientes                       | \n");
        printf("|         2 - Gerenciar Produtos                       | \n");
        printf("|         3 - Gerenciar Fornecedores                   | \n");
        printf("|         4 - Caixa                                    | \n");
        printf("|         5 - Relatorio                                | \n");
        printf("|         6 - Sair                                     | \n");
        printf("|                                                      | \n");
        printf("+------------------------------------------------------+ \n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                login();
                system("cls");
                menuClientes();
                break;

            case 2:
                login();
                system("cls");
                menuProdutos();
                break;
                
            case 3:
                login();
                system("cls");
                menuFornecedores();
                break;

            case 4:
            system("cls");
                printf("\n--- SISTEMA DE CAIXA ---\n");
                caixa(produto, numProdutos);
                break;

            case 5:
                system("cls");
                printf("Gerando relatorio de vendas...\n");
                printf("+--------------------------------------------------------------------------------+\n");
                gerarRelatorioDeVendas(vendas, numVendas);
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 6);

    return 0;
}
