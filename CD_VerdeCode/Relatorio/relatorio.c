#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Produtos/Cad_produto.h" 
#include "venda.c"
#include "relatorio.h"



// Função para gerar o relatório de vendas
void gerarRelatorioDeVendas() {
    venda_t vendas[100]; 
    int numVendas = carregarVendasDeArquivo(vendas); 

    if (numVendas == 0) {
        printf("Nenhuma venda encontrada.\n");
        return;
    }

    float totalVendas = 0;
    printf("+------------------ :: RELATORIO DE VENDAS :: -----------------------------------+\n");
    printf("| Produto          | Quantidade | Preco Unitario | Total   | Data       | Hora   |\n");
    printf("+--------------------------------------------------------------------------------+\n");

    for (int i = 0; i < numVendas; i++) {
        printf("| %-16s | %10d | %14.2f | %7.2f | %-10s | %-6s |\n", 
               vendas[i].produto, 
               vendas[i].quantidade, 
               vendas[i].precoUnitario, 
               vendas[i].totalVenda, 
               vendas[i].data, 
               vendas[i].hora);
        totalVendas += vendas[i].totalVenda;
    }

    printf("+--------------------------------------------------------------------------------+\n");
    printf("| TOTAL VENDAS: %64.2f |\n", totalVendas);
    printf("+--------------------------------------------------------------------------------+\n");

    system("pause");
    system("cls");
}

