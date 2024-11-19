#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Produtos/Cad_produto.h" 
#include "../Relatorio/venda.h"


//Cria a função caixa e abre o arquivo TXT para salvar os dados da compras e criar relatórios
void caixa(produto_t produto[], int numProdutos) {
    int id, quantidade;
    char opcao;
    char data[11]; 
    char hora[6];   
    float total = 0.0;

    FILE *vendasFile = fopen("Relatorio/vendas.txt", "a");
    if (vendasFile == NULL) {
        printf("Erro ao abrir o arquivo vendas.txt.\n");
        return;
    }

    do {
        printf("Digite o ID do produto que deseja adicionar ao caixa (ou -1 para finalizar): ");
        if (scanf("%d", &id) != 1) {  
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();  

        if (id == -1) {
            break;
        }

        int encontrado = 0;
        for (int i = 0; i < numProdutos; i++) {
            if (produto[i].idProd == id) {
                printf("Digite a quantidade desejada de %s: ", produto[i].nome);
                if (scanf("%d", &quantidade) != 1) {  
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n'); 
                    continue;
                }
                getchar();

                if (produto[i].quant >= quantidade) {
                    produto[i].quant -= quantidade;
                    total += produto[i].prec * quantidade;

                    // Obtém a data e hora atuais
                    time_t agora = time(NULL);
                    struct tm *t = localtime(&agora);

                    // Formata a data e a hora
                    sprintf(data, "%02d-%02d-%04d",  t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
                    sprintf(hora, "%02d:%02d",t->tm_hour,  t->tm_min );

                    // Registra a venda no arquivo
                    fprintf(vendasFile, "Produto: %s, Quantidade: %d, Preco Unitario: %.2f, Total: %.2f, Data: %s, Hora: %s\n",
                                    produto[i].nome, quantidade, produto[i].prec, produto[i].prec * quantidade, data, hora);
                    
                    printf("Adicionado: %d x %s (R$%.2f cada) Total = %.2f\n", quantidade, produto[i].nome, produto[i].prec, produto[i].prec * quantidade);
                    printf("Quantidade restante de %s: %d\n", produto[i].nome, produto[i].quant);
                } else {
                    printf("Quantidade insuficiente de %s. Estoque disponível: %d\n", produto[i].nome, produto[i].quant);
                }
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Produto com ID %d não encontrado.\n", id);
        }

        printf("\nTotal da compra: R$%.2f\n", total);
        printf("\nDeseja adicionar outro produto? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    system("cls");

    fclose(vendasFile); 
    printf("\nCOMPRA REALIZADA COM SUCESSO!\n");
    printf("\nOBRIGADO E VOLTE SEMPRE!!!\n");
    printf("\n");
    system("pause");
    system("cls");
}
